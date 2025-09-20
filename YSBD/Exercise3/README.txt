Μετατροπές Συναρτήσεων από ChatGPT:

- CHUNK_CreateIterator: 

	- Καμία αλλαγή

- CHUNK_GetNext:

	- Προσθήκη ελέγχου στην αρχή για την περίπτωση που δεν υπάρχει επόμενο chunk.

		if ((iterator->lastBlocksID + 1) > HP_GetIdOfLastBlock(iterator->file_desc))
        		return -1;
    		else
        		chunk->from_BlockId = iterator->lastBlocksID + 1;

	- Προσθήκη ελέγχου για την περίπτωση που το τελευταίο chunk δεν έχει τον μέγιστο αριθμό block.

		if ((iterator->lastBlocksID + 1) > HP_GetIdOfLastBlock(iterator->file_desc))
        		return -1;
   		else
        		chunk->from_BlockId = iterator->lastBlocksID + 1;

- CHUNK_GetIthRecordInChunk:

	- Προσθήκη HP_Unpin
		
- CHUNK_UpdateIthRecord:
	
	- Προσθήκη ελέγχου επιτυχίας HP_UpdateRecord

		if (HP_UpdateRecord(chunk->file_desc, blockId, cursor, record)) {
                	HP_Unpin(chunk->file_desc, blockId);
                	return 0;
            	}
            	else {
                	HP_Unpin(chunk->file_desc, blockId);
                	return -1;
            	}

	- Προσθήκη HP_Unpin

- CHUNK_Print: 

	- Καμία αλλαγή

- CHUNK_CreateRecordIterator:

	- Καμία αλλαγή

- CHUNK_GetNextRecord: 

	- Προσθήκη HP_Unpin

	- Προσθήκη ελέγχου στην περίπτωση που το chunk δεν έχει άλλα blocks
		
    		if (iterator->currentBlockId > iterator->chunk.to_BlockId)
        		return -1;

- shouldSwap:

	- Καμία αλλαγή

- sort_FileInChunks:

	- Αλλαγή iterator.lastBlocksID

		iterator.lastBlocksID = numBlocksInChunk;

	- Αρχικοποίηση και κλήση της sort_Chunk για το πρώτο chunk πριν την κλήση της CHUNK_GetNext στην επανάληψη while

		CHUNK chunk;
    		chunk.blocksInChunk = iterator.blocksInChunk;
    		chunk.file_desc = iterator.file_desc;
    		chunk.from_BlockId = 1;
    		chunk.to_BlockId = chunk.blocksInChunk;
    		chunk.recordsInChunk = HP_GetMaxRecordsInBlock(file_desc) * chunk.blocksInChunk;
    		sort_Chunk(&chunk);





