#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "bf.h"
#include "hash_file.h"

#define RECORDS_NUM 100000 // You can change it if you want
#define GLOBAL_DEPT 2     // You can change it if you want

char *FILE_NAME[MAX_OPEN_FILES] = {
  "dataA.db",
  "dataB.db",
  "dataC.db",
  "dataD.db",
  "dataE.db",
  "dataF.db",
  "dataG.db",
  "dataH.db",
  "dataI.db",
  "dataJ.db",
  "dataK.db",
  "dataL.db",
  "dataM.db",
  "dataN.db",
  "dataO.db",
  "dataP.db",
  "dataQ.db",
  "dataR.db",
  "dataS.db",
  "dataT.db"
};

const char* names[] = {
  "Yannis",
  "Christofos",
  "Sofia",
  "Marianna",
  "Vagelis",
  "Maria",
  "Iosif",
  "Dionisis",
  "Konstantina",
  "Theofilos",
  "Giorgos",
  "Dimitris"
};

const char* surnames[] = {
  "Ioannidis",
  "Svingos",
  "Karvounari",
  "Rezkalla",
  "Nikolopoulos",
  "Berreta",
  "Koronis",
  "Gaitanis",
  "Oikonomou",
  "Mailis",
  "Michas",
  "Halatsis"
};

const char* cities[] = {
  "Athens",
  "San Francisco",
  "Los Angeles",
  "Amsterdam",
  "London",
  "New York",
  "Tokyo",
  "Hong Kong",
  "Munich",
  "Miami"
};

#define CALL_OR_DIE(call)     \
  {                           \
    HT_ErrorCode code = call; \
    if (code != HT_OK) {      \
      printf("Error\n");      \
      exit(code);             \
    }                         \
  }

int main() {
  
  CALL_OR_DIE(HT_Init());

  for (int i = 0; i < MAX_OPEN_FILES; i++) {

    BF_Init(LRU);

    int indexDesc;

    printf("\n\nHT_OpenIndex\n");
    CALL_OR_DIE(HT_CreateIndex(FILE_NAME[i], GLOBAL_DEPT));
    CALL_OR_DIE(HT_OpenIndex(FILE_NAME[i], &indexDesc));

    Record record;
    srand(time(NULL));
    int r;
    printf("Insert Entries\n");
    for (int id = 0; id < RECORDS_NUM; ++id) {
      // create a record
      record.id = id;

      r = rand() % 12;
      memcpy(record.name, names[r], strlen(names[r]) + 1);
      r = rand() % 12;
      memcpy(record.surname, surnames[r], strlen(surnames[r]) + 1);
      r = rand() % 10;
      memcpy(record.city, cities[r], strlen(cities[r]) + 1);

      CALL_OR_DIE(HT_InsertEntry(indexDesc, record));
    }

    printf("RUN PrintAllEntries\n");
    int id = rand() % RECORDS_NUM;
    CALL_OR_DIE(HT_PrintAllEntries(indexDesc, &id));
    printf("RUN HashStatistics");
    CALL_OR_DIE(HashStatistics(FILE_NAME[i]));
    printf("HT_CloseFile\n");
    HT_CloseFile(indexDesc);
    BF_Close();
  }   
}
