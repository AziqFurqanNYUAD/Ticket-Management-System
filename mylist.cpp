#include <sstream>
#include "flighthashtable.h"
#include "myList.h"


template <typename T>
MyList<T>::MyList ()
{
	this->head = new Node<T>;
	this->tail = new Node<T>;
	this->head->next = tail;
	this->tail->prev = head;
}
//============================================================
template <typename T>
MyList<T>::~MyList () // destructor to clean up all nodes
{
	while(!empty())
		removeFront();
}
//============================================================
template <typename T>
bool MyList<T>::empty() const // is list empty?
{
	return this->head->next == tail;
}
//============================================================
template <typename T>
const T& MyList<T>::front() const // get front element
{
	if(!empty())
		return this->head->next->elem;
	else
		throw runtime_error("List is Empty");
}
//============================================================
template <typename T>
const T& MyList<T>::back() const // get front element
{
	if(!empty())
		return this->tail->prev->elem;
	else
		throw runtime_error("List is Empty");
}
//============================================================
template <typename T>
void MyList<T>::addBefore(Node<T> *ptr, const T& elem)
{
	Node<T> *tmp = new Node<T>(elem);
	tmp->next = ptr;
	tmp->prev = ptr->prev;
	ptr->prev->next = tmp;
	ptr->prev=tmp;
}
//============================================================
template <typename T>
void MyList<T>::addFront(const T& elem) // add to front of list
{
	addBefore(this->head->next, elem);
}
//============================================================
template <typename T>
void MyList<T>::addBack(const T& elem) // add to Back of the list
{
	addBefore(this->tail, elem);
}
//============================================================
template <typename T>
void MyList<T>::removeFront() // remove front item from list
{
	if(!empty())
	{
		Node<T> *tmp = this->head->next;
		this->head->next = tmp->next;
		tmp->next->prev = head;
		delete tmp;
	}
}
//============================================================
template <typename T>
void MyList<T>::removeBack() // remove last item from list
{
	if(!empty())
	{
		Node<T> *tmp = this->tail->prev;
		this->tail->prev = tmp->prev;
		tmp->prev->next = tail;
		delete tmp;
	}
}

template <typename T>
int MyList<T>::removeEl(string cn, int fn) // remove item from list
{
	if(!empty())
	{
		Node<T> *curr = this->head->next;

		while (curr != NULL){

			if (curr->elem.get_val().get_companyName()==cn && curr->elem.get_val().get_flightNumber()==fn){

				Node<T>* tmp = curr;
				tmp->prev->next = tmp->next;
				tmp->next->prev = tmp->prev;
				delete tmp;

				return 1;
			}
			curr = curr->next;
		}
	}
	return -1;
}

template <typename T>
string MyList<T>::getEl(string cn, int fn) // remove item from list
{
	if(!empty())
	{

		Node<T> *curr = this->head->next;

		while (curr != NULL){
			if (curr->elem.get_val().get_companyName()==cn && curr->elem.get_val().get_flightNumber()==fn){

				return curr->elem.get_val().get_line();
			}
			curr = curr->next;
		}

	}
	return "";
}
//============================================================
template <typename T>
string MyList<T>::getLines() const
{
	Node<T> *curr=head->next;
	string return_string = "";
	while(curr!=NULL)
	{	
		if (curr->elem.get_val().get_flightNumber()!=0){
			return_string += curr->elem.get_val().get_line();
		}

		curr = curr->next;
	}
	return return_string;
}

string get_dest(string el){
    bool comma_infield = false;
    string entry = "";
    int count = 0;
    for (char c : el){
        if (c=='"'){
            comma_infield = !comma_infield;
        }
        if (c!=',' && count==3){
            entry+=c;
        }
        else if(c==',' && comma_infield && count==3){
            entry+=c;
        }
        else if(c==',' && !comma_infield){
            count++;
            if (count>3){
                return entry;
            }
        }
    }
	return entry;
}

string stringSorter(string buff, string el){
	istringstream f(buff);
	string line;
	string result;
	bool found = false;
	while(getline(f,line)){
		int res = get_dest(el).compare(get_dest(line));
		if (found){
			result+=line+"\n";
			continue;
		}
		if (res<0){
			result+=el;
			result+=line+"\n";
			found = true;
		}
		if (res>0){
			result+=line+"\n";
			continue;
		}
		
	}
	if (!found){
	    result+=el;
	}
	return result;
}
template <typename T>
string MyList<T>::getLinesSorted(string key) const
{	
	Node<T> *curr=head->next;
	string return_string = "";
	while (curr!=NULL && return_string==""){
		if (key==(curr->elem.get_val().get_companyName()+int_to_str1(curr->elem.get_val().get_flightNumber()))){
			return_string = curr->elem.get_val().get_line();
		}	
		curr = curr->next;
	}
	while(curr!=NULL)
	{
		if (key==(curr->elem.get_val().get_companyName()+int_to_str1(curr->elem.get_val().get_flightNumber()))){
			
			return_string = stringSorter(return_string,curr->elem.get_val().get_line());\
		}
		curr = curr->next;
	}

	return return_string;
}

template <typename T>
int MyList<T>::getSize() {
	int count = 0;
	MyList<T>::iterator p = this->begin();
	while(p!=this->end()){
		count++;
		++p;
	}
	return count;
}

template <typename T>
string MyList<T>::getElOnDate(string dt) // remove item from list
{
	string ret = "";
	dt+="\r\n";
	
	if(!empty())
	{
		Node<T> *curr = this->head->next;

		while (curr != NULL){
			cin.clear();
			cout.clear();
			string x = curr->elem.get_val().get_date()+"\n";
			// x.erase(x.size()-1);
			// dt.erase(dt.size()-1);
			
			cin.clear();
			cout.clear();

			if (x==dt){
				ret+=curr->elem.get_val().get_line();
			}
			curr = curr->next;
		}
	}
	
	return ret;
}

template class MyList<HashNode>;