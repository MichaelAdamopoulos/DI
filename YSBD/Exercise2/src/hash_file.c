#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "bf.h"
#include "hash_file.h"
#define HASH_SIZE 32

#define CALL_BF(call)       \
{                           \
  BF_ErrorCode code = call; \
  if (code != BF_OK) {         \
    BF_PrintError(code);    \
    return HP_ERROR;        \
  }                         \
}

void printRecord(Record);
void hash_function(int, char *);
void hash_to_int(char *, int *, int );

// Array to hold all open files
HT_Info *open_files[MAX_OPEN_FILES];

HT_ErrorCode HT_Init() {

  // Create an array for 20 open_files
  for (int i = 0; i < MAX_OPEN_FILES; i++)
    open_files[i] = NULL;

  return HT_OK;
}

HT_ErrorCode HT_CreateIndex(const char *filename, int depth) {
  
  // Number of initial buckets
  int size = pow(2,depth);

  BF_CreateFile(filename);

  // Create meta-data for hash_table
  HT_Info *info = malloc(sizeof(HT_Info));
  info->filename = malloc(sizeof(filename));
  memcpy(info->filename, filename, sizeof(filename));
  info->global_depth = depth;
  
  // Initialize hash_table for initial buckets
  int *hash_table = malloc(size * sizeof(int));
  for (int i = 0; i < size; i++)
    hash_table[i] = -1;

  info->hash_table = hash_table;

  // Store meta-data to file's array
  for (int i = 0; i < MAX_OPEN_FILES; i++) {
    if (open_files[i] == NULL) {
      open_files[i] = info;
      return HT_OK;
    }
  }
  
  // If file array is full
  printf("Not enough space to open file!\n");
  return HT_ERROR;

}

HT_ErrorCode HT_OpenIndex(const char *fileName, int *indexDesc) {

  int fd;
  
  BF_OpenFile(fileName, &fd); 

  // Allocate first block
  BF_Block *block;
  BF_Block_Init(&block);
  BF_AllocateBlock(fd, block);
  void *data = BF_Block_GetData(block);
  HT_Info *info;
  info = data;
  int i;
  // Finding file and adding meta-data
  for (i = 0; i < MAX_OPEN_FILES; i++) {
    if (open_files[i] != NULL && !strcmp(open_files[i]->filename, fileName)) {
        info->global_depth = open_files[i]->global_depth;
        *indexDesc = i;
         info->filename = open_files[i]->filename;
         info->fd = fd;
         info->hash_table = open_files[i]->hash_table;
        break;
      }
  }
  
  if (i == MAX_OPEN_FILES)  // File not found
    return HT_ERROR;    

  // Create 2^depth empty buckets for hash table
  for (int i = 0; i < pow(2, info->global_depth); i++) {
    BF_Block *block;
    BF_Block_Init(&block);
    BF_AllocateBlock(fd, block);
    void *data = BF_Block_GetData(block);
    Bucket_Info *bucket = data;
    bucket->capacity = (BF_BLOCK_SIZE - sizeof(Bucket_Info)) / sizeof(Record);
    bucket->records = 0;
    bucket->local_depth = info->global_depth;
    int block_id;
    BF_GetBlockCounter(fd, &block_id);
    info->hash_table[i] = block_id-1;
    BF_Block_SetDirty(block);
    BF_UnpinBlock(block);
    BF_Block_Destroy(&block);
  }
  // Do not unpin block 0, because it is needed until file closes
  BF_Block_SetDirty(block);

  return HT_OK;
}

HT_ErrorCode HT_CloseFile(int indexDesc) {

  HT_Info *info = open_files[indexDesc];
  int fd = info->fd;

  BF_Block *block;
  BF_Block_Init(&block);
  BF_GetBlock(fd, 0, block);
  void *data = BF_Block_GetData(block);

  // Update meta-data of block 0
  HT_Info *update_info = data;
  update_info->global_depth = info->global_depth;
  memcpy(update_info->filename, info->filename, sizeof(info->filename));
  update_info->fd = info->fd;
  update_info->hash_table = info->hash_table;

  // How many hash table elements can each block store
  int capacity =  BF_BLOCK_SIZE / sizeof(int);
  int total_blocks = pow(2, info->global_depth);    // Hash table's items left to store
  // How many blocks are needed to store the hash
  int i = 0;
  for (i = 0; i <= sizeof(int) * pow(2, info->global_depth) / BF_BLOCK_SIZE; i++) {
    BF_Block *block;
    BF_Block_Init(&block);
    BF_AllocateBlock(fd, block);
    void *data = BF_Block_GetData(block);
    // Save specific parts of the hash table to each block
    if (total_blocks < capacity)
      memcpy(data, info->hash_table + (i * capacity), sizeof(int) * total_blocks);
    else
      memcpy(data, info->hash_table + (i * capacity), sizeof(int) * capacity);
    total_blocks -= capacity;
    BF_Block_SetDirty(block);
    BF_UnpinBlock(block);
    BF_Block_Destroy(&block);
  }

  free(info->filename);
  free(info->hash_table);
  free(info);

  // Remove file from open file's array
  open_files[indexDesc] = NULL;

  // Unpin first block and save it
  BF_Block_SetDirty(block);
  BF_UnpinBlock(block);
  BF_Block_Destroy(&block);

  BF_CloseFile(fd);
  
  return HT_OK;
}

HT_ErrorCode HT_InsertEntry(int indexDesc, Record record) {
 
  // Get record hash value
  int global_depth = open_files[indexDesc]->global_depth;
  char hash[HASH_SIZE];
  hash_function(record.id, hash);
  int index;
  hash_to_int(hash, &index, global_depth);

  // Insert record
  HT_Info *info = open_files[indexDesc];
  BF_Block *block;
  BF_Block_Init(&block);
  int block_id = info->hash_table[index];
  BF_GetBlock(info->fd, block_id, block);
  void *data = BF_Block_GetData(block);
  Bucket_Info *bucket = data;

  // 1st case: avalaible space
  if (bucket->records < bucket->capacity) {
    memcpy(data + sizeof(Bucket_Info) + bucket->records * sizeof(Record), &record, sizeof(Record));
    (bucket->records)++;
  }
  // 2nd case: no available space
  else if (bucket->local_depth == info->global_depth) {
    // Double the size of the hash table
    int new_size = pow(2, info->global_depth + 1);
    int *new_hash_table = malloc(new_size * sizeof(int));
    for (int i = 0; i < new_size; i++)
      new_hash_table[i] = info->hash_table[i/2];
    free(info->hash_table);
    info->hash_table = new_hash_table;
    (info->global_depth)++;

    // Create new bucket and insert record
    BF_Block *new_block;
    BF_Block_Init(&new_block);
    BF_AllocateBlock(info->fd, new_block);
    void *new_data = BF_Block_GetData(new_block);
    Bucket_Info *new_bucket = new_data;
    int new_block_id;
    BF_GetBlockCounter(info->fd, &new_block_id);
    new_bucket->local_depth = ++(bucket->local_depth);
    new_bucket->capacity = bucket->capacity;
    new_bucket->records = 0;
    bucket->records = 0;
    
    new_hash_table[2 * index + 1] = new_block_id - 1;

    for (int i = 0; i < bucket->capacity; i++) {
      Record new_record;
      memcpy(&new_record, data + sizeof(Bucket_Info) + sizeof(Record) * i, sizeof(Record));
      char new_hash[HASH_SIZE];
      hash_function(new_record.id, new_hash);
      int new_index;
      hash_to_int(new_hash, &new_index, bucket->local_depth);
      // Find which bucket to store each record, depending on its previous hashing
      if (new_index == index)
        new_index = index * 2;
      else
        new_index = index * 2 + 1;

      // Re-hash and re-insert
      if (new_hash_table[new_index] == new_block_id - 1) {
        memcpy(new_data + sizeof(Bucket_Info) + new_bucket->records * sizeof(Record), &new_record, sizeof(Record));
        (new_bucket->records)++;
      } else {
        memcpy(data + sizeof(Bucket_Info) + bucket->records * sizeof(Record), &new_record, sizeof(Record));
        (bucket->records)++;
      }
    }

    // Hash and insert the new Record
    // Find which bucket to store the Record
    int new_index;
    hash_to_int(hash, &new_index, bucket->local_depth);
    if (new_index == index)
      new_index = index * 2;
    else
      new_index = index * 2 + 1;

    if (new_hash_table[new_index] == new_block_id - 1) {
      memcpy(new_data + sizeof(Bucket_Info) + new_bucket->records * sizeof(Record), &record, sizeof(Record));
      (new_bucket->records)++;
    } else {
      memcpy(data + sizeof(Bucket_Info) + bucket->records * sizeof(Record), &record, sizeof(Record));
      (bucket->records)++;
    }

    BF_Block_SetDirty(new_block);
    BF_UnpinBlock(new_block);
    BF_Block_Destroy(&new_block);
  } 
  else {
    // Create new bucket and insert record
    BF_Block *new_block;
    BF_Block_Init(&new_block);
    BF_AllocateBlock(info->fd, new_block);
    void *new_data = BF_Block_GetData(new_block);
    Bucket_Info *new_bucket = new_data;
    int new_block_id;
    BF_GetBlockCounter(info->fd, &new_block_id);
    new_bucket->local_depth = ++(bucket->local_depth);
    new_bucket->capacity = bucket->capacity;
    new_bucket->records = 0;
    bucket->records = 0;

    info->hash_table[index + 1] = new_block_id - 1;
    for (int i = 0; i < bucket->capacity; i++) {
      Record new_record;
      memcpy(&new_record, data + sizeof(Bucket_Info) + sizeof(Record) * i, sizeof(Record));
      char new_hash[HASH_SIZE];
      hash_function(new_record.id, new_hash);
      int new_index;
      hash_to_int(new_hash, &new_index, bucket->local_depth);
      int pos = index % 2; // 0 or 1
      int dig = (new_index >= pow(2, (bucket->local_depth - 1))) ? 1 : 0;  // 0 or 1
      if (pos == dig)
        new_index = index;
      else if (dig > pos)
        new_index = index + 1;
      else
        new_index = index - 1;

      // Re-hash and re-insert
      if (info->hash_table[new_index] == new_block_id - 1) {
        memcpy(new_data + sizeof(Bucket_Info) + new_bucket->records * sizeof(Record), &new_record, sizeof(Record));
        (new_bucket->records)++;
      } else {
        memcpy(data + sizeof(Bucket_Info) + bucket->records * sizeof(Record), &new_record, sizeof(Record));
        (bucket->records)++;
      }
    }

    // Hash and insert the new Record
    int new_index;
    hash_to_int(hash, &new_index, bucket->local_depth);
    int pos = index % 2; // 0 or 1
    int dig = (new_index >= pow(2, (bucket->local_depth - 1))) ? 1 : 0;  // 0 or 1
    if (pos == dig)
      new_index = index;
    else if (dig > pos)
      new_index = index - 1;
    else
      new_index = index + 1;

    if (info->hash_table[new_index] == new_block_id - 1) {
      memcpy(new_data + sizeof(Bucket_Info) + new_bucket->records * sizeof(Record), &record, sizeof(Record));
      (new_bucket->records)++;
    } else {
      memcpy(data + sizeof(Bucket_Info) + bucket->records * sizeof(Record), &record, sizeof(Record));
      (bucket->records)++;
    }
    BF_Block_SetDirty(new_block);
    BF_UnpinBlock(new_block);
    BF_Block_Destroy(&new_block);
  }
  
  BF_Block_SetDirty(block);
  BF_UnpinBlock(block);
  BF_Block_Destroy(&block);
  
  return HT_OK;
}

HT_ErrorCode HT_PrintAllEntries(int indexDesc, int *id) {
  
  // Find the file
  HT_Info *info = open_files[indexDesc];
  int previous_index = -1;
  int i, j, count = 0;

  for (i = 0; i < pow(2, info->global_depth) ; i++) {
    BF_Block *block;
    BF_Block_Init(&block);

    // To avoid searching the same buckets
    if (info->hash_table[i] == previous_index) {
      BF_Block_SetDirty(block);
      BF_UnpinBlock(block);
      BF_Block_Destroy(&block);
      continue;
    }
      
    previous_index = info->hash_table[i];

    BF_GetBlock(info->fd, info->hash_table[i], block);
    void * data = BF_Block_GetData(block);
    Bucket_Info *bucket = data;
    for (j = 0 ; j < bucket->records; j++) {
      Record record;
      memcpy(&record, data + sizeof(Bucket_Info) + sizeof(Record) * j, sizeof(Record));
      if (record.id == *id)
        printRecord(record);
      count++;
    }
    BF_Block_SetDirty(block);
    BF_UnpinBlock(block);
    BF_Block_Destroy(&block);
  }
  return HT_OK;
}

HT_ErrorCode HashStatistics(char* filename) {

  // Check if the file is open
  int i, fileIndex = -1;
  for (i = 0; i < MAX_OPEN_FILES; i++) {
    if (open_files[i] != NULL && !strcmp(open_files[i]->filename, filename)) {
      fileIndex = i;
      break;
    }
  }

  // If filename doesn't exist
  HT_Info *info;
  BF_Block *block;
  void *data;
  if (i == MAX_OPEN_FILES) {
    printf("File was closed, let's open it!\n");
    int fd;
  
    BF_OpenFile(filename, &fd); 

    BF_Block_Init(&block);
    BF_GetBlock(fd, 0, block);
    data = BF_Block_GetData(block);
    info = data;
  } else
    info = open_files[fileIndex];

  // Search minimum, maximum and average number of records per bucket
  int min = (BF_BLOCK_SIZE - sizeof(Bucket_Info)) / sizeof(Record) + 1;
  int max = 0;
  int sum = 0;
  int previous_index = -1;
  int bucket_counter = 0;
  for (int j = 0; j < pow(2, info->global_depth); j++) {
    BF_Block *block;
    BF_Block_Init(&block);
    BF_GetBlock(info->fd, info->hash_table[j], block);
    void * data = BF_Block_GetData(block);
    Bucket_Info *bucket = data;

    // To avoid searching the same bucket
    if (info->hash_table[j] == previous_index) {
      BF_Block_SetDirty(block);
      BF_UnpinBlock(block);
      BF_Block_Destroy(&block);
      continue;
    }
    previous_index = info->hash_table[j];

    // For minimum
    if (bucket->records < min)
      min = bucket->records;

    // For maximum
    if (bucket->records > max)
      max = bucket->records;

    sum += bucket->records;
    bucket_counter++;
    BF_Block_SetDirty(block);
    BF_UnpinBlock(block);
    BF_Block_Destroy(&block);
  }
  
  // Print statistics
  printf("\nThe filename '%s' statistics are:\n", filename);

  // Print block bumber
  int blockCounter = 0;
  BF_GetBlockCounter(info->fd, &blockCounter);
  printf("Blocks: %d\n", blockCounter);

  // Print min, max and average
  printf("Minimum number of records: %d\n", min); 
  printf("Maximum number of records: %d\n", max);
  float average;
  if (bucket_counter != 0) {
    //printf("Records are: %d\n", sum);
    average = (float) sum / bucket_counter; // not counting the HT_Info block and the blocks where
                                            // the hash table is stored(in case file was closed)
    printf("Average number of records: %0.2f\n", average);
  }
  else
    printf("Average number of records: 0\n");

  // If file was closed and we open it, save again first block
  if (i == MAX_OPEN_FILES) {
    BF_Block_SetDirty(block);
    BF_UnpinBlock(block);
    BF_Block_Destroy(&block);
  }

  return HT_OK;
}

void hash_function(int num, char *key) {
  key[HASH_SIZE - 1] = '\0';
  for (int i = HASH_SIZE - 2; i >= 0 - 1; i--, num /= 2)
    key[HASH_SIZE - 2 - i] = num % 2 + '0';
}

void hash_to_int(char key[HASH_SIZE], int *index, int depth) {
  *index = 0;
  for (int i = 0; i < depth; i++)
    *index = *index + (key[i] - '0') * (int)pow(2, i);
}

void printRecord(Record record) {
    printf("(%d,%s,%s,%s)\n",record.id,record.name,record.surname,record.city);
}