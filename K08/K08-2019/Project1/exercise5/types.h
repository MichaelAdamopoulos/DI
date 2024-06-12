/* File: types.h */

typedef char WordType[11];		// maximum lenght of a word in the dictionary is '10' ( w/o '\0' )
typedef struct NodeTag {
                WordType word;
                struct NodeTag *Link;
                } NodeType;
typedef struct NodeTag *NodePointer;
typedef struct ArrayTag {		// struct that includes
		int size;		// the size of the array
		char **Array;		// and array
		} ArrayType;
