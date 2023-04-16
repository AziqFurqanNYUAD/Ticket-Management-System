// #ifndef MYLIST_H
// #define MYLIST_H
#include<iostream>
#include<iomanip>
#include<algorithm>
#pragma once

using namespace std;


template <typename T>
class Node
{
	private:
		T elem; //data element 
		Node* next; //Link (pointer) to the next Node
		Node* prev; //Link (pointer) to the previous Node
		template <typename T2> friend class MyList;
		
	public:
		Node(): next(NULL), prev(NULL)
		{}
		Node(T elem) : elem(elem),next(NULL), prev(NULL)
		{}
};
//==============================================================
template <typename T> 
class MyList
{
	private:
		Node<T>* head; 	// pointer to the head of List
		Node<T>* tail; 	// pointer to the tail of List
	public:
		MyList (); // empty list constructor
		~MyList (); // destructor to clean up all nodes
		bool empty() const; // is list empty?
		const T& front() const; // get the value (element) from front Node<T> of list
		const T& back() const;  // get the value (element) from last Node<T> of the List 
		void addBefore(Node<T> *ptr, const T& elem);	 //add a new node before ptr
		void addFront(const T& elem); // add a new node to the front of list
		void addBack(const T & elem); //add a new node to the back of the list
		void removeFront(); // remove front node from list
		void removeBack();  // remove last node from list
		void reverseList();	// reverse the list
		bool isPalindrome(); //check if the List is Palindrome or not
		string getLines() const;	// display all element of the list
		string getLinesSorted(string) const;	// display all element of the list
		int getSize();
		int removeEl(string, int);
		string getEl(string,int);
		string getElOnDate(string);
		//Iterator
		class iterator;   //Forwarding declarion of iterator class
		iterator begin()  
		{
			//todo
			return head->next;
		}
		iterator end()
		{
			//todo
			return tail;
		}

		class iterator
		{
			//complete the itereator class (which include iterator traits)
			private:
			Node<T> *nodePtr;
		public:
			using value_type = T;
			using pointer = Node<T>*;
			using reference = Node<T>;
			using iterator_category = bidirectional_iterator_tag;
			using difference_type = ptrdiff_t;
		public:
			iterator(Node<T>* node)
			{
				this->nodePtr = node;
			}
			T &operator*()
			{
				return nodePtr->elem;
			}
			iterator& operator++()
			{
				this->nodePtr = nodePtr->next;
				return *this;
			}
			iterator& operator--()
			{
				this->nodePtr = nodePtr->prev;
				return *this;
			}
			bool operator==(const iterator& other) const
			{
				return this-> nodePtr ==  other.nodePtr;
			}
			bool operator!=(const iterator& other) const
			{
				return this->nodePtr !=  other.nodePtr;
			}
            Node<T>* getNodePtr(){
                return this->nodePtr;
            }
		};
};
