/* File: QueueTypes.h */

typedef BTNode ItemType;

typedef struct QueueNodeTag {
	ItemType Item;
	struct QueueNodeTag *Link;
} QueueNode;

typedef struct {
    QueueNode *Front;
    QueueNode *Rear;
} Queue;
