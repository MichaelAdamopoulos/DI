/* File: functions.h */

void InitializeQueue(Queue *);
void Insert(NodePointer, Queue *);
void Remove(Queue *, NodePointer *);
void conversion(WordType, WordType, ArrayType);
int binsearch(char *, int, char **);
NodePointer Similar(char *, ArrayType);
NodePointer Search(NodePointer, char *);
void Delete(NodePointer, NodePointer);
NodePointer Create(void);
void InsertLast(NodePointer, WordType);
void InsertAfter(NodePointer, WordType, NodePointer);
void bubblesort(int, char**);
void swapd(char **, char **);
void Print(NodePointer);
void ReversePrint(NodePointer);
ArrayType WordArray();

