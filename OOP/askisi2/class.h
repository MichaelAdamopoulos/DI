/* File: class.h */

class tree;

const int post_cap = 5;						// number of posts per thread created
const int thread_cap = 3;					// number of threads per forum created

struct date {

	int day;
	int month;
	int year;
};

class post {

	private:
		int id;
		std::string title;
		std::string creator;
		date dates;
		std::string text;

	public:
 		post(int, std::string, std::string, date);
		~post();
		void print() const;
		int get_id() const;
		std::string get_creator() const;
		post *get_post();
};

class thread {

	private:
		std::string subject;
		std::string creator;
		date dates;
		post *posts[post_cap];				// array of pointers to class 'posts'

	public:
		thread(std::string, std::string, date);
		~thread();
		void print() const;
		std::string get_thread() const;
		post **get_posts();				// function returns an array of pointers, hence the double *
};

class forum {

	private:
		std::string title;
		thread *threads[thread_cap];			// array of pointers to class 'thread'

	public:
		forum(std::string, date);
		~forum();
		void print();
		void print_thread(const std::string title);
		thread **get_threads();				// function returns an array of pointers, hence the double *
		void print_post(const int id);
		tree *create_tree(thread *);			// create tree with given thread
		void print_sorted();
		std::string get_title() const;
};
