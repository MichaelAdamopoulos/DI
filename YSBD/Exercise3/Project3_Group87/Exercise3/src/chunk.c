#include <merge.h>
#include <stdio.h>
#include "chunk.h"


CHUNK_Iterator CHUNK_CreateIterator(int fileDesc, int blocksInChunk){
    CHUNK_Iterator iterator;
    iterator.file_desc = fileDesc;
    iterator.current = 1; // Start from block 1
    iterator.lastBlocksID = 0; // Initially, no lastBlocksID
    iterator.blocksInChunk = blocksInChunk;

    return iterator;
}


int CHUNK_GetNext(CHUNK_Iterator *iterator, CHUNK* chunk) {

    // Update CHUNK struct with the current iterator settings
    chunk->file_desc = iterator->file_desc;

    // If there is no next block
    if ((iterator->lastBlocksID + 1) > HP_GetIdOfLastBlock(iterator->file_desc))
        return -1;
    else
        chunk->from_BlockId = iterator->lastBlocksID + 1;

    // When the last chunk has not enough blocks
    if ((chunk->from_BlockId + iterator->blocksInChunk - 1) > HP_GetIdOfLastBlock(iterator->file_desc))
        chunk->to_BlockId = HP_GetIdOfLastBlock(iterator->file_desc);
    else
        chunk->to_BlockId = chunk->from_BlockId + iterator->blocksInChunk - 1;
    
    // Calculate the number of records
    int totalRecordsInChunk = 0;
    for (int blockId = chunk->from_BlockId; blockId <= chunk->to_BlockId; blockId++)
        totalRecordsInChunk += HP_GetRecordCounter(iterator->file_desc, blockId);

    // Update CHUNK with the correct number of records
    chunk->recordsInChunk = totalRecordsInChunk;
    chunk->blocksInChunk = iterator->blocksInChunk;

    // Update iterator properties for the next iteration
    iterator->current = chunk->from_BlockId;
    iterator->lastBlocksID = chunk->to_BlockId;

    return 0; // Success, a new chunk is retrieved
}

int CHUNK_GetIthRecordInChunk(CHUNK* chunk,  int i, Record* record) {
    // Check if i is a valid index within the chunk
    if (i < 0 || i >= chunk->recordsInChunk) {
        // Invalid index
        return -1;
    }

    int remainingRecordsToSearch = i + 1;  // Records are 0-indexed

    // Traverse each block in the chunk
    for (int blockId = chunk->from_BlockId; blockId <= chunk->to_BlockId; blockId++) {
        // Retrieve the number of records in the current block
        int recordsInBlock = HP_GetRecordCounter(chunk->file_desc, blockId);

        // If the remaining records to search are in the current block
        if (remainingRecordsToSearch <= recordsInBlock) {
            // Retrieve the record from the heap file
            int cursor = remainingRecordsToSearch - 1;  // 0-indexed
            if (HP_GetRecord(chunk->file_desc, blockId, cursor, record) == 0) {
                HP_Unpin(chunk->file_desc, blockId);
                // Successfully retrieved the record
                return 0;
            } else {
                // Failed to retrieve the record
                return -1;
            }
        }

        // Update the remaining records to search
        remainingRecordsToSearch -= recordsInBlock;
    }

    // If we reach here, the function did not successfully retrieve the ith record
    return -1;
}

int CHUNK_UpdateIthRecord(CHUNK* chunk,  int i, Record record) {
    int remainingRecordsToSearch = i + 1;  // Records are 0-indexed

    // Traverse each block in the chunk
    for (int blockId = chunk->from_BlockId; blockId <= chunk->to_BlockId; blockId++) {
        // Retrieve the number of records in the current block
        int recordsInBlock = HP_GetRecordCounter(chunk->file_desc, blockId);

        // If the remaining records to search are in the current block
        if (remainingRecordsToSearch <= recordsInBlock) {
            // Update the record in the heap file
            int cursor = remainingRecordsToSearch - 1;  // 0-indexed
            if (HP_UpdateRecord(chunk->file_desc, blockId, cursor, record)) {
                HP_Unpin(chunk->file_desc, blockId);
                return 0;
            }
            else {
                HP_Unpin(chunk->file_desc, blockId);
                return -1;
            }
        }

        // Update the remaining records to search
        remainingRecordsToSearch -= recordsInBlock;
    }

    // If we reach here, the function did not successfully update the ith record
    return -1;
}

void CHUNK_Print(CHUNK chunk) {
    printf("Printing records within the chunk:\n");

    // Traverse each block in the chunk
    for (int blockId = chunk.from_BlockId; blockId <= chunk.to_BlockId; blockId++) {
        printf("Block %d:\n", blockId);

        // Print all entries (records) within the current block
        HP_PrintBlockEntries(chunk.file_desc, blockId);
    }

}

CHUNK_RecordIterator CHUNK_CreateRecordIterator(CHUNK *chunk) {
    CHUNK_RecordIterator iterator;
    iterator.chunk = *chunk;
    iterator.currentBlockId = chunk->from_BlockId;
    iterator.cursor = 0;
    return iterator;
}

int CHUNK_GetNextRecord(CHUNK_RecordIterator *iterator, Record* record) {
    // Try to retrieve the record from the current block and cursor
    iterator->cursor++;

    // Check if we have reached the end of the current block
    if (iterator->cursor == HP_GetRecordCounter(iterator->chunk.file_desc, iterator->currentBlockId)) {
        // Move to the next block in the chunk
        iterator->currentBlockId++;
        iterator->cursor = 0;
    }

    // Check if there are no more blocks
    if (iterator->currentBlockId > iterator->chunk.to_BlockId)
        return -1;

    // Return the next record
    HP_GetRecord(iterator->chunk.file_desc, iterator->currentBlockId, iterator->cursor, record);
    HP_Unpin(iterator->chunk.file_desc, iterator->currentBlockId);

    return 0;
}
