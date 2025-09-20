![run-tests](../../workflows/run-tests/badge.svg)

## Δομές Δεδομένων και Τεχνικές Προγραμματισμού

### Κώδικας Εργαστηρίου 4

Εκφώνηση: https://k08.chatzi.org/labs/lab4/

ADTPriorityQueue UsingHeap:

- naive_heapify: O(nlogn)

- efficient_heapify: O(n)

ADTPriorityQueue UsingADTList:

- pqueue_create without data: O(1)

- pqueue_create with data: O(nlogn) -> first insert is faster and each one after is usually progressivly slower 

- pqueue_size: O(1)

- pqueue_max: O(1)

- pqueue_insert: O(n)

- pqueue_remove_max: O(1) -> always remove first element