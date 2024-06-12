/* File: types.h */

typedef int BTItem;

typedef struct BTNodeTag {
	BTItem Item;
	struct BTNodeTag *RChild;
	struct BTNodeTag *LChild;
	struct BTNodeTag *Parent;
} *BTNode;

typedef struct BTTreeTag {
	int Height;				// height of tree
	int Size;				// number of elements
	BTNode Root;
} *BTTree;;

typedef void (*VisitType) (BTTree Tree, BTNode Node);

