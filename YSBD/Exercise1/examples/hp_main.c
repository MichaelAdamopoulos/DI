#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "bf.h"
#include "hp_file.h"

#define RECORDS_NUM 1000 // you can change it if you want
#define FILE_NAME "data.db"

#define CALL_OR_DIE(call)     \
  {                           \
    BF_ErrorCode code = call; \
    if (code != BF_OK) {      \
      BF_PrintError(code);    \
      exit(code);             \
    }                         \
  }

int main() {
  BF_Init(LRU);

  if (HP_CreateFile(FILE_NAME)) {
    printf("Error while creating the file.Exit..\n");
    return -1;
  }
   
  HP_info* info = HP_OpenFile(FILE_NAME);

  Record record;
  srand(12569874);
  int r;
  printf("Insert Entries\n");
  for (int id = 0; id < RECORDS_NUM; ++id) {
    record = randomRecord();
    if (!HP_InsertEntry(info, record)) {
      printf("Error in HP_InsertEntry.Exit..\n");
      return -1;
    }
  }

  printf("RUN PrintAllEntries\n");
  int id = rand() % RECORDS_NUM;
  printf("\nSearching for: %d",id);
  if (HP_GetAllEntries(info, id) == -1) {
    printf("Error in HP_GetAllEntries.Exit..\n");
    return -1;
  }

  if (HP_CloseFile(info)) {
    printf("Error while closing the file.Exit..\n");
    return -1;
  }
  BF_Close();

  return 0;
}
