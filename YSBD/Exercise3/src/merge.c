#include <merge.h>
#include <stdio.h>
#include <stdbool.h>

void merge(int input_FileDesc, int chunkSize, int bWay, int output_FileDesc ) {
    
    // Determine the total number of blocks in the input file, exluding block 0
    int totalBlocks = HP_GetIdOfLastBlock(input_FileDesc);

    // Calculate the total number of chunks
    int totalChunks = totalBlocks / chunkSize;

    // Initialize CHUNK_Iterator for input file
    CHUNK_Iterator input_Iterator;
    input_Iterator.file_desc = input_FileDesc;
    input_Iterator.current = 1 - chunkSize;  // Assuming chunks start from block 1
    input_Iterator.lastBlocksID = 0;  // Last block in the input file
    input_Iterator.blocksInChunk = chunkSize;

    // Initialize CHUNK_RecordIterator
    CHUNK_RecordIterator record_Iterators[bWay];

    // Iterate through chunks and merge every b chunks
    while (!CHUNK_GetNext(&input_Iterator, &record_Iterators[0].chunk)) {
        // Open new CHUNK_RecordIterators for the next b-1 chunks
        for (int i = 1; i < bWay; i++) {
            // Check if there are more chunks to merge
            if (CHUNK_GetNext(&input_Iterator, &record_Iterators[i].chunk)) {
                // No other Chunk to merge
                bWay = i;
                break;
            }
        }

        // Initialize the iterators to the first record of each block
        for (int i = 0; i < bWay; i++) {
            record_Iterators[i] = CHUNK_CreateRecordIterator(&record_Iterators[i].chunk);
            record_Iterators[i].cursor = -1;
        }
        Record records[bWay];
        for (int i = 0; i < bWay; i++)
            CHUNK_GetNextRecord(&record_Iterators[i], &records[i]);

        // Continue comparing and inserting records until all iterators have no more records
        int remainingIterators = bWay;

        while (remainingIterators > 0) {
            
            int smallestRecordIndex = -1;
            Record smallestRecord;
            
            // Find the smallest record of bWay chunks
            for (int i = 0; i < bWay; i++) {
                // Skip this Chunk if there are no more records in it
                if (record_Iterators[i].cursor == -1) {
                     continue;
                }
                if (smallestRecordIndex == -1 || shouldSwap(&smallestRecord, &records[i])) {
                    smallestRecordIndex = i;
                    smallestRecord = records[i];
                }
            }
                    
            HP_InsertEntry(output_FileDesc, smallestRecord);
            if (CHUNK_GetNextRecord(&record_Iterators[smallestRecordIndex], &records[smallestRecordIndex])) {
                // In this case it means that this Chunk has no more records 
                // so we do not have to iterate through his records anymore
                remainingIterators--;
                record_Iterators[smallestRecordIndex].cursor = -1;
            }
        }
    }

}

