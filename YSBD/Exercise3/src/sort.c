#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bf.h"
#include "hp_file.h"
#include "record.h"
#include "sort.h"
#include "merge.h"
#include "chunk.h"

bool shouldSwap(Record* rec1,Record* rec2) {
    // Compare the combination of name and surname
    int result = strcmp(rec1->name, rec2->name);
    
    // If names are equal, compare surnames
    if (result == 0) {
        result = strcmp(rec1->surname, rec2->surname);
    }

    // If result > 0, rec1 should come after rec2 (swap is needed)
    // If result < 0, rec1 should come before rec2 (no swap needed)
    // If result == 0, names and surnames are equal, no swap needed

    return result > 0;
}

void sort_FileInChunks(int file_desc, int numBlocksInChunk) {
    CHUNK_Iterator iterator = CHUNK_CreateIterator(file_desc, numBlocksInChunk);
    iterator.file_desc = file_desc;
    iterator.current = 1;  // Assuming chunks start from block 1
    iterator.lastBlocksID = numBlocksInChunk;  // Use HP_GetIdOfLastBlock
    iterator.blocksInChunk = numBlocksInChunk;

    CHUNK chunk;
    chunk.blocksInChunk = iterator.blocksInChunk;
    chunk.file_desc = iterator.file_desc;
    chunk.from_BlockId = 1;
    chunk.to_BlockId = chunk.blocksInChunk;
    chunk.recordsInChunk = HP_GetMaxRecordsInBlock(iterator.file_desc) * chunk.blocksInChunk;
    sort_Chunk(&chunk);
    //Iterate through chunks and sort each chunk
    while (!CHUNK_GetNext(&iterator, &chunk)) {
        // Function to sort records within a CHUNK in ascending order based on name and surname
        sort_Chunk(&chunk);
    }
}

void swapRecords(Record *rec1, Record *rec2) {
    Record temp;
    memcpy(&temp, rec1, sizeof(Record));
    memcpy(rec1, rec2, sizeof(Record));
    memcpy(rec2, &temp, sizeof(Record));
}

void sort_Chunk(CHUNK* chunk) {
    int numRecords = chunk->recordsInChunk;
    // Allocate memory for the chunk of records
    Record *records = malloc(numRecords * sizeof(Record));
    if (records == NULL) {
        // Handle memory allocation error
        return;
    }

    CHUNK_RecordIterator iterator = CHUNK_CreateRecordIterator(chunk);
    HP_GetRecord(chunk->file_desc, chunk->from_BlockId, /* cursor */ 0, &records[0]);
    HP_Unpin(chunk->file_desc, chunk->from_BlockId);
    // Read records from the chunk into the array
    for (int i = 1; i < numRecords; i++) {
        CHUNK_GetNextRecord(&iterator, &records[i]);
    }
    // Perform sorting (bubble sort in this example)
    for (int i = 0; i < numRecords - 1; i++) {
        for (int j = 0; j < numRecords - i - 1; j++) {
            if (shouldSwap(&records[j], &records[j + 1])) {
                swapRecords(&records[j], &records[j + 1]);
            }
        }
    }

    // Write the sorted records back to the chunk
    for (int i = 0; i < numRecords; i++) {
        CHUNK_UpdateIthRecord(chunk, i, records[i]);
    }

    // Free allocated memory
    free(records);
}