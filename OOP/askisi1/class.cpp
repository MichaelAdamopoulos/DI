/* File: class.cpp */

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

#include "class.h"

using namespace std;

int post_id = 1;									// first post's id is 1

std::string creators[10] = {"Michael", "John", "Nick", "Zack", "Tom",
			    "Kate", "Anne", "Ellen", "Laura", "Zoe"};

std::string texts[10] = {"text01", "text02", "text03", "text04", "text05",
			 "text06", "text07", "text08", "text09", "text10"};

std::string titles[10] = {"title01", "title02", "title03", "title04", "title05",
			  "title06", "title07", "title08", "title09", "title10"};

std::string subjects[10] = {"subject01", "subject02", "subject03", "subject04", "subject05",
			    "subject06", "subject07", "subject08", "subject09", "subject10"};

post::post(int id, string title, string creator, date dates) {

	this->id = id;
	this->title = title;
	this->creator = creator;
	this->dates = dates;
	this->text = texts[rand()%10];							// get random text from the array of texts
	cout
		<< "Post " << id << " with title '" << title << "' has just been created from '"
		<<	creator << "' on the date " << dates.day << "." << dates.month << "." << dates.year
		<< " and contains the following text: '" << this->text << "'" << endl;
}

post::~post() {

	cout << "Post number " << this->id << " is about to be destroyed!" << endl;
}

void post::print() const {

	cout
		<< "Post " << id << " - " << title << " - " << creator << " - "
		<< dates.day << "." << dates.month << "." << dates.year
		<< " - " << text << endl;
}

int post::get_post() const {

	return this->id;
}

thread::thread(string subject, string creator, date dates) {

	for ( int i = 0 ; i < post_cap ; i++ ) {
											// fill array of 'post' pointers with new randomised posts
		this->posts[i] = new post(post_id, titles[rand()%10], creators[rand()%10], dates);
		post_id++;								// each post has unique id, so after a post is created
	}										// post_id grows by 1 for the next post

	this->subject = subject;
	this->creator = creator;
	this->dates = dates;

	cout << "Thread with subject '" << subject << "' has just been created!" << endl;
}

thread::~thread() {

	for ( int i = 0 ; i < post_cap ; i++ ) {
		delete posts[i];							// delete dynamic allocated memory for all posts
	}
	cout << "Thread with subject '" << subject << "'  is about to be destroyed!" << endl;
}

void thread::print() const {

	cout
		<< "Thread with subject: '" << subject << "' was created from '" << creator
		<< "' on the date " << dates.day << "." << dates.month << "." << dates.year
		<< " and contains the following posts:" << endl;
	for ( int i = 0 ; i < post_cap ; i++ ) {
		cout << "Post " << this->posts[i]->get_post() << endl;			// get id of current post
	}
}

string thread::get_thread() const{

	return this->subject;
}

post **thread::get_posts() {

			return this->posts;						// returning array of pointers, hence the double *
}

forum::forum(string title, date dates) {

											// first thread is always 'Rules and useful info'
	this->threads[0] = new thread("Rules and useful info", creators[rand()%10], dates);

	for ( int i = 1 ; i < thread_cap ; i++ ) {					// fill array of threads with randomised threads
		this->threads[i] = new thread(subjects[rand()%10], creators[rand()%10], dates);
	}

	this->title = title;

	cout << "Forum with title '" << title << "' has just been created!\n";
}

forum::~forum() {

	for ( int i = 0 ; i < thread_cap ; i++ ) {
		delete threads[i];							// delete dynamic allocated memory for all threads
	}

	cout << "Forum with title '" << title << "' is about to be destroyed!\n";
}

void forum::print() {


	cout << "Forum '" << title << "' contains the following threads: " << endl;

	for ( int i = 0 ; i < thread_cap ; i++ ) {
		 cout << this->threads[i]->get_thread() << endl;			// get subject of each thread
	}
}

void forum::print_thread(const string subject) {

	cout << "Lets print Thread '" << subject << "':" << endl;

	for ( int i = 0 ; i < thread_cap ; i++ ) {
		if ( this->threads[i]->get_thread() == subject ) {			// if thread with given subject exists
			this->threads[i]->print();					// print it
			return;
		}
	}

	cout << "No such thread exists!" << endl;
}

void forum::print_post(const int id) {

	for ( int i = 0 ; i < thread_cap ; i++ ) {					// search every post in every thread for the
		for ( int j = 0 ; j < post_cap ; j ++ ) {				// given post's id. If found, print the post
			if ( this->threads[i]->get_posts()[j]->get_post() == id ) {
				this->threads[i]->get_posts()[j]->print();
				return;
			}
		}
	}

	cout << "No such post exists!" << endl;
}
