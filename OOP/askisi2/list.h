/* File: list.h */

class post;

class list {

	private:
		struct node {
			post *postptr;
			node *next;
		};
		node* head;		// pointer to first node

	public:
		list();
		~list();
		void insert(post *);
		void merge(list *);
		void print();
};

