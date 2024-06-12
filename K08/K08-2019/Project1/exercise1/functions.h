/* File: functions.h */

NodePointer Create();
void Print(NodePointer);
NodePointer Search(NodePointer, AirportCode);
void InsertLast(NodePointer, AirportCode);
void InsertAfter(NodePointer, AirportCode, NodePointer);
void DeleteLast(NodePointer);
void Delete(NodePointer, NodePointer);
