/* File: functions.h */

BTTree BTCreate(void);
int BTHeight(BTTree);
int BTSize(BTTree);
BTNode BTGetRoot(BTTree);
BTNode BTGetParent(BTTree, BTNode);
BTNode BTGetChildLeft(BTTree, BTNode);
BTNode BTGetChildRight(BTTree, BTNode);
int BTIsNil(BTNode);
int BTGetItem(BTTree, BTNode);
int BTInsertRoot(BTTree, BTItem);
int BTInsertLeft(BTTree, BTNode, BTItem);
int BTInsertRight(BTTree, BTNode, BTItem);
int BTRemove(BTTree, BTNode);
void BTChange(BTTree, BTNode, BTItem);
void BTPreOrder(BTTree, BTNode, VisitType);
void BTInOrder(BTTree, BTNode, VisitType);
void BTPostOrder(BTTree, BTNode, VisitType);
void BTLevelOrder(BTTree, VisitType);
void Visit(BTTree, BTNode);

