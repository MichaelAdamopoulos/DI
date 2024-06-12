#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bf.h"
#include "hp_file.h"
#include "record.h"

#define CALL_BF(call)       \
{                           \
  BF_ErrorCode code = call; \
  if (code != BF_OK) {         \
    BF_PrintError(code);    \
    return BF_ERROR;        \
  }                         \
}

int HP_CreateFile(char *fileName) {
    return (!BF_CreateFile(fileName) ? 0 : -1);
}

HP_info* HP_OpenFile(char *fileName) {

  int fd;
  BF_Block *block;
  BF_Block_Init(&block);
  BF_OpenFile(fileName, &fd);
  BF_AllocateBlock(fd, block);
  void *data = BF_Block_GetData(block);
  HP_info *info = data;

  // (Block size - Header size) / Record size
  info->capacity = (BF_BLOCK_SIZE - sizeof(HP_info)) / sizeof(Record);
  info->fd = fd;
  BF_Block_Destroy(&block);

  return info;
}

// free all memory from each block of the file and close file
int HP_CloseFile(HP_info* hp_info) {

  int blockCounter;
  BF_GetBlockCounter(hp_info->fd, &blockCounter);

  //unpin the first block
  BF_Block *block;
  BF_Block_Init(&block);
  BF_GetBlock(hp_info->fd, 0, block);
  BF_UnpinBlock(block);

  return BF_CloseFile(hp_info->fd) ? -1 : 0;
}

// Create a new block and insert a record at the beginning of it
void CreateBlockAndInsertFirstRecord(HP_info* hp_info, Record record) {
  BF_Block *block;
  BF_Block_Init(&block);
  BF_AllocateBlock(hp_info->fd, block);
  void *data = BF_Block_GetData(block);
  HP_block_info *blockInfo;
  // important data for the block are at he beginning of it
  blockInfo = data;
  blockInfo->count = 1;
  // insert record after HP_block_info
  memcpy(data + sizeof(HP_block_info), &record, sizeof(Record));
  BF_Block_SetDirty(block);
  BF_Block_Destroy(&block);
}

int HP_InsertEntry(HP_info* hp_info, Record record) {

  int fd = hp_info->fd;
  int capacity = hp_info->capacity;

  int totalBlocks;
  BF_GetBlockCounter(hp_info->fd, &totalBlocks);
  totalBlocks--;        //exclude block 0

  if (!totalBlocks)     // if file contains 0 blocks so far
     CreateBlockAndInsertFirstRecord(hp_info, record);
  else {
    BF_Block *block;
    BF_Block_Init(&block);
    BF_GetBlock(fd, totalBlocks, block);
    void *data = BF_Block_GetData(block);
    HP_block_info *blockInfo = data;
    // if current block if full of records unpin it and create a new one
    if (blockInfo->count == capacity) {
      BF_Block_SetDirty(block);
      BF_UnpinBlock(block);
      BF_Block_Destroy(&block);
      CreateBlockAndInsertFirstRecord(hp_info, record);
    }
    else {
      // insert record after the last record of the block
      memcpy(data+sizeof(HP_block_info)+sizeof(Record)*blockInfo->count, &record, sizeof(Record));
      (blockInfo->count)++;
      BF_Block_SetDirty(block);
      BF_Block_Destroy(&block);
    }
  }

  BF_GetBlockCounter(hp_info->fd, &totalBlocks);
  return totalBlocks;
}

int HP_GetAllEntries(HP_info* hp_info, int value){

  int blockCounter;
  BF_GetBlockCounter(hp_info->fd, &blockCounter);

  int curBlock;
  // Iterate all blocks
  for (curBlock = 1; curBlock < blockCounter; curBlock++) {
    BF_Block *block;
    BF_Block_Init(&block);
    BF_GetBlock(hp_info->fd, curBlock, block);
    void *data = BF_Block_GetData(block);
    HP_block_info *info = data;
    for (int recCount = 0; recCount < info->count; recCount++){
      Record *record;
      record = data + sizeof(HP_block_info) + sizeof(Record)*recCount;
      if (value == record->id)
        printRecord(*record);
    }
    BF_UnpinBlock(block);
    BF_Block_Destroy(&block);
  }

  return --curBlock;  //the number of blocks that we visited
}

