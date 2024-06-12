/* File: types.h */

typedef char AirportCode[4];
typedef AirportCode ItemType;				// typedef AirportCode as ItemType
typedef struct NodeTag {
                        ItemType item;
                        struct NodeTag *next;
			struct NodeTag *prev;
                } NodeType;
typedef NodeType *NodePointer;
typedef char *ItemTypeFormat;
typedef int (*CompareType)(ItemType a, ItemType b); 	// typedef CompareType as a function pointer

