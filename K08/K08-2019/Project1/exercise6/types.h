/* File: types.h */

typedef char WordType[11];
typedef struct NodeTag {
		WordType word;
		struct NodeTag *Link;
		} NodeType;
typedef struct NodeTag *NodePointer;
typedef struct QueueNodeTag {
		NodePointer list;
		struct QueueNodeTag *Link;
		} QueueNode;
typedef struct {
		QueueNode *Front;
		QueueNode *Rear;
		} Queue;
typedef struct ArrayTag {
		int size;
		char **Array;
		} ArrayType;
