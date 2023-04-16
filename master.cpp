
//=================================================================================
// Name         : DS Assignment#4 
// Author       : 
// Version      : 1.0
// Date Created : Apr-17-2022
// Date Modified: 
// Description  : Starter Code for Flight-Ticket Management System using HASH TABLE in C++
//=================================================================================
#include<iostream>
#include<cstdlib>
#include<sstream>
#include <fstream>

using namespace std;


string int_to_str1(int num){
    ostringstream str1;
    str1<<num;
    return str1.str();
}

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

class Flight_Ticket
{
	private:
		string companyName;
		int flightNumber;
		string country_of_origin;
		string country_of_destination;
		string stopOver;
		string price;
		string time_of_departure;
		string time_of_arrival;
		string date;

	public:
		Flight_Ticket();
		Flight_Ticket(Flight_Ticket* data);
		Flight_Ticket(string companyName, int flightNumber, string country_of_origin, string country_of_destination, string stopOver, string price, string time_of_departure, string time_of_arrival, string date);
		// add additional methods as needed
		string get_companyName ();
		int get_flightNumber ();
		string get_country_of_origin ();
		string get_country_of_destination ();
		string get_stopOver ();
		string get_price ();
		string get_time_of_departure ();
		string get_time_of_arrival ();
		string get_date ();
		string get_line();

};

class HashNode
{
	private:
		string key; // key = companyName+flightNumber
		Flight_Ticket value;
	public:
        HashNode();
		HashNode(string key, Flight_Ticket value){
			this->key = key;
			this->value = value;
		};
		friend class FlightHASHTABLE;
        Flight_Ticket get_val(){return value;}
};

//=============================================================================
class FlightHASHTABLE
{
	private:
		MyList<HashNode> *buckets;				//List of Buckets, Please create your own List Class called MyList
		int size;					    //Current Size of HashTable
		int capacity;				    // Total Capacity of HashTable
		int collisions;
		// add more attributes as needed
	public:
		FlightHASHTABLE(int capacity);						//constructor
		~FlightHASHTABLE();						//destructor
		long hashCode(const string key); 						//implement and test different hash functions 
		int importCSV(string path); 			//Load all the flight-tickets from the CSV file to the HashTable
		int exportCSV(string path); 			//Export all the flight-tickets from the HashTable to a CSV file in an ascending order		
		int count_collisions();					//return the number of collisions on the HashTable
		int add(Flight_Ticket* data);			//add new flight to the HashTable
		int removeRecord (string companyName, int flightNumber);	//Delete a record with key from the hashtable
		void find(string companyName, int flightNumber);		//Find and Display records with same key entered 
		void allinday(string date);  					//Find and Display records with same day entered
		void printASC(string companyName, int flightNumber);  		//display the collisions for the entered key in an ascending order 

		// add more methods as needed	
};


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

Flight_Ticket::Flight_Ticket(){}

Flight_Ticket::Flight_Ticket(Flight_Ticket* data){
    this->companyName = data->companyName;
    this->flightNumber = data->flightNumber;
    this->country_of_origin = data->country_of_origin;
    this->country_of_destination = data->country_of_destination;
    this->stopOver = data->stopOver;
    this->price = data->price;
    this->time_of_departure = data->time_of_departure;
    this->time_of_arrival = data->time_of_arrival;
    this->date = data->date;
}

Flight_Ticket::Flight_Ticket(string companyName, int flightNumber, string country_of_origin, string country_of_destination, string stopOver, string price, string time_of_departure, string time_of_arrival, string date){
    this->companyName = companyName;
    this->flightNumber = flightNumber;
    this->country_of_origin = country_of_origin;
    this->country_of_destination = country_of_destination;
    this->stopOver = stopOver;
    this->price = price;
    this->time_of_departure = time_of_departure;
    this->time_of_arrival = time_of_arrival;
    this->date = date;
}

string Flight_Ticket::get_companyName (){
    return companyName;
}

int Flight_Ticket::get_flightNumber (){
    return flightNumber;
}

string Flight_Ticket::get_country_of_origin (){
    return country_of_origin;
}

string Flight_Ticket::get_country_of_destination (){
    return country_of_destination;
}

string Flight_Ticket::get_stopOver (){
    return stopOver;
}

string Flight_Ticket::get_price (){
    return price;
}

string Flight_Ticket::get_time_of_departure (){
    return time_of_departure;
}

string Flight_Ticket::get_time_of_arrival (){
    return time_of_arrival;
}

string Flight_Ticket::get_date (){
    return date;
}

string Flight_Ticket::get_line(){
    return this->get_companyName()+","+int_to_str1(this->get_flightNumber())+","+this->get_country_of_origin()+","+this->get_country_of_destination()+","+this->get_stopOver()+","+this->get_price()+","+this->get_time_of_departure()+","+this->get_time_of_arrival()+","+this->get_date()+"\n";
}

HashNode::HashNode(){}

FlightHASHTABLE::FlightHASHTABLE(int capacity){
    buckets = new MyList<HashNode>[capacity];			//Create an array of size capacity. Each locaiton of Array is a list/chain
	this->capacity = capacity;
	this->size = 0;
	this->collisions = 0;
}

FlightHASHTABLE::~FlightHASHTABLE(){
	delete[] buckets;
}

long FlightHASHTABLE::hashCode(const string key){	
	unsigned long hash = 0;
	for (int i = 0; i < key.length(); i++) {
		hash = hash + (int(key[i]));
	}
	hash = hash % capacity;
    
	return hash;
}

int str_to_int(string s){
   stringstream ss; 
   // a variable named num, that is of int data type
   int num;
   //extract the string from the str variable (input the string in the stream)
   ss << s;
   // place the converted value to the int variable
   ss >> num;
   
   return num;
}

int FlightHASHTABLE::importCSV(string path){
    ifstream file(path);

    if (!file.is_open()){
        cout<<"Error opening file\n";
        return -1;
    }

    string record ="";
    string entry = "";
    string entries[9];
    bool comma_infield = false;
    int i = 0;

    getline(file,record);	
    int count = 0;

    while(getline(file,record,'\n')){
    	count++;
		comma_infield = false;
        for (char c : record){
            if (c=='"'){
                comma_infield = !comma_infield;
            }
            if (c!=','){
                entry+=c;
            }
            else if(c==',' && comma_infield){
                entry+=c;
            }
            else if(c==',' && !comma_infield){
                entries[i] = entry;
                entry = "";
                i++;
            }
        }
		entries[i] = entry;
		entry = "";
		i = 0;

        string key = entries[0]+entries[1];

        long location = this->hashCode(key);


        Flight_Ticket ft(entries[0],str_to_int(entries[1]),entries[2],entries[3],entries[4],entries[5],entries[6],entries[7],entries[8]);
        
        this->add(&ft);


        record = "";
    }

    file.close();
    return count;
}

int FlightHASHTABLE::exportCSV(string path){
    string all_data = "";
    for (int i=0;i<capacity;i++){
        if (buckets!=NULL){
            all_data += buckets[i].getLines();
        }
    }

    ofstream myfile;
    
    myfile.open(path);
	if (!myfile.is_open()){
        cout<<"Could not open file for writing\n";
        return -1;
    }
    myfile<<all_data;
    myfile.close();
    return 1;
}

int FlightHASHTABLE::count_collisions(){
    return collisions;
}

int FlightHASHTABLE::add(Flight_Ticket* data){
    try{
        string key = data->get_companyName()+int_to_str1(data->get_flightNumber());
		long location = this->hashCode(key);
        Flight_Ticket ft(data);
        HashNode n(key, ft);

		string s = buckets[location].getEl(data->get_companyName(),data->get_flightNumber());
		if (s!=""){
			collisions++;
		}
		// cout<<"here: " << buckets[location].front().key<<endl;
        buckets[location].addBack(n);

        return 1;
    }
    catch(...){
        return -1;
    }
    
}

int FlightHASHTABLE::removeRecord(string company_name, int flight_num){
    string key = company_name+int_to_str1(flight_num);
    long location = this->hashCode(key);

    if (buckets[location].empty()){
        return -1;
    }
    
	
	return buckets[location].removeEl(company_name,flight_num);
}

void FlightHASHTABLE::find(string company_name, int flight_num){
    string key = company_name+int_to_str1(flight_num);
    long location = this->hashCode(key);

    if (buckets[location].empty()){
        cout<<"record doesn't exist";
        return;
    }

    string out = buckets[location].getEl(company_name,flight_num) == "" ? "record not found" : buckets[location].getEl(company_name,flight_num);
    cout<< out;
}

void FlightHASHTABLE::allinday(string date){
    string dt_els = "";
    for (int i=0;i<capacity;i++){
		// cout<<"i: "<<i<<endl;
        if (!buckets[i].empty()){
           dt_els+=buckets[i].getElOnDate(date);
        }
    }
    string out = dt_els == "" ? "record not found" : dt_els;

    cout<<out;

}

void FlightHASHTABLE::printASC(string companyName, int flightNumber){
    string key = companyName+int_to_str1(flightNumber);
    long location = this->hashCode(key);

    if (buckets[location].empty()){
        cout<<"record doesn't exist";
        return;
    }
	cout<<"enter\n";
    cout<<buckets[location].getLinesSorted(key);
	cout<<"exit\n";

}
//==========================================================
void listCommands()
{
	cout<<"\n----------------------------------"<<endl;
	cout<<"import <path>      	:Import flight-tickets from a CSV file"<<endl
		<<"export <path>      	:Export flight-tickets to a CSV file"<<endl
		<<"count_collisions   	:Print number of collisions"<<endl
		<<"add                	:Add a new flight-ticket"<<endl
		<<"delete <key>       	:Delete a flight-ticket"<<endl
		<<"find <key>         	:Find a flight-ticket's details"<<endl
		<<"allinday <date>    	:Display all flight-tickets in a day"<<endl
		<<"printASC <key>     	:Print flight-tickets in ascending order"<<endl
		<<"exit               	:Exit the program"<<endl;
}
//==========================================================

// to be completed with all the necessary method definitions

//==========================================================
int main(void)
{
	FlightHASHTABLE myFlightHASHTABLE(1000);

	string companyName;
	int flightNumber;
	string country_of_origin;
	string country_of_destination;
	string stopover;
	string price;
	string time_of_departure;
	string time_of_arrival;
	string date;
	string collision_count;

	string user_input = "";
	string command;
	string key;

	while(true){
		listCommands();
		cout<<">";
		//to be completed 
		getline(cin, user_input);

		stringstream sstr(user_input);
		getline(sstr, command, ' ');
		getline(sstr, key);

		if (command == "import")
		{
			cout<<myFlightHASHTABLE.importCSV(key)<<endl;
			continue;
		}
		else if(command =="")
		{
			continue;
		}
		else if (command == "export")
		{
			cout<<myFlightHASHTABLE.exportCSV(key)<<endl;
			continue;
		}
		else if (command == "count_collisions")
		{
			cout << "Total number of collisions is " << myFlightHASHTABLE.count_collisions() << endl;
		}
		else if (command == "add")
		{
			cout << "Please enter the details of the flight-ticket:" << endl;
			cout << "Company Name: ";
			cin >> companyName;
			cout << "Flight Number: ";
			cin >> flightNumber;
			cout << "Country of Origin: ";
			cin >> country_of_origin;
			cout << "Country of Destination: ";
			cin >> country_of_destination;
			cout << "Stopover: ";
			cin >> stopover;
			cout << "Price: ";
			cin >> price;
			cout << "Time of Departure: ";
			cin >> time_of_departure;
			cout << "Time of Arrival: ";
			cin >> time_of_arrival;
			cout << "Date: ";
			cin >> date;

			Flight_Ticket * data = new Flight_Ticket(companyName,flightNumber,country_of_origin,country_of_destination, stopover, price, time_of_departure, time_of_arrival, date);

			myFlightHASHTABLE.add(data);
			cout << "Flight-ticket has successfully been added!\n";
			continue;
		}
		else if (command == "delete")
		{
			
			cout << "Company Name: ";
			string x;
			int l = 0;
			getline(cin,companyName,'\n');
			
			cout << "Flight Number: ";
			cin >> flightNumber;
			myFlightHASHTABLE.removeRecord(companyName, flightNumber);
		}
		else if (command == "find")
		{
			cout << "Company Name: ";
			string x;
			int l = 0;
			getline(cin,companyName,'\n');
			
			cout << "Flight Number: ";
			cin >> flightNumber;
			myFlightHASHTABLE.find(companyName, flightNumber);
		}
		else if (command == "allinday")
		{
			cout << "Date: ";
			cin >> date;
			myFlightHASHTABLE.allinday(date);
		}
		else if (command == "printASC")
		{	cout << "Company Name: ";
			string x;
			int l = 0;
			getline(cin,companyName,'\n');
			
			cout << "Flight Number: ";
			cin >> flightNumber;
			myFlightHASHTABLE.printASC(companyName, flightNumber);
		}
		else if (command == "exit")
		{
			return 0;
		}
		else
		{
			cout << "Invalid command !!!" << endl;
		}

	}
}
