/* File: tree.h */

class list;
class post;

class tree {

	private:
		struct node {
			std::string creator;		// each node of the tree contains a creator paired
			list *listptr;			// with a list of posts
			node* right;
			node* left;
		};
		node *root;				// pointer of first node/root of tree

		void insert(std::string, list*, node*);
		void delete_tree(node *nodeptr);
		void print_inorder(node *);
		node *create_node(std::string, list *);
		void enhance(node *);

	public:
		tree();
		~tree();
		void insert(std::string, list *);
		void enhance(tree *);
		void print_inorder();
		void insert(post *);
};

