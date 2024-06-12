/* File: functions.h */

NodePointer Create();
void Print(NodePointer, ItemTypeFormat);
void InsertLast(NodePointer, ItemType);
void InsertAfter(NodePointer, ItemType, NodePointer);
void InsertBefore(NodePointer, ItemType, NodePointer);
void DeleteLast(NodePointer);
void Delete(NodePointer, NodePointer);
int Compare(ItemType, ItemType);
NodePointer Search(NodePointer, ItemType, CompareType);
