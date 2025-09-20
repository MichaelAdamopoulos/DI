/* File: class.h */

using namespace std;

const int post_cap = 2;					// number of posts per thread created
const int thread_cap = 3;				// number of threads per forum created

struct date {

	int day;
	int month;
	int year;
};

class post {

	private:
		int id;
		string title;
		string creator;
		date dates;
		string text;

	public:
 		post(int, string, string, date);
		~post();
		void print() const;
		int get_post() const;
};

class thread {

	private:
		string subject;
		string creator;
		date dates;
		post *posts[post_cap];			// array of pointers to class 'posts'

	public:
		thread(string, string, date);
		~thread();
		void print() const;
		string get_thread() const;
		post **get_posts();			// function returns an array of pointers, hence the double *
};

class forum {

	private:
		string title;
		thread *threads[thread_cap];		// array of pointers to class 'thread'

	public:
		forum(string, date);
		~forum();
		void print();
		void print_thread(const string title);
		void print_post(const int id);
};



