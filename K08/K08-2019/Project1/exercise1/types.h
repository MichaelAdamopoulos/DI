/* File: types.h */

typedef char AirportCode[4];
typedef struct NodeTag {
        AirportCode Airport;
        struct NodeTag *Link;
        } NodeType;
typedef NodeType *NodePointer;

