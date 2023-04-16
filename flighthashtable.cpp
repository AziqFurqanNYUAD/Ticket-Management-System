
#include <fstream>
#include <sstream>
#include <string>

#include "flighthashtable.h"

string int_to_str2(int num){
    ostringstream str1;
    str1<<num;
    return str1.str();
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
	unsigned long hash = 9;
	for (int i = 0; i < key.length(); i++) {
		hash = (hash * 31) + (long)key[i];
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

    while(getline(file,record,'\n')){
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
    return 1;
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
        string key = data->get_companyName()+int_to_str2(data->get_flightNumber());
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
    string key = company_name+int_to_str2(flight_num);
    long location = this->hashCode(key);

    if (buckets[location].empty()){
        return -1;
    }
    
	
	return buckets[location].removeEl(company_name,flight_num);
}

void FlightHASHTABLE::find(string company_name, int flight_num){
    string key = company_name+int_to_str2(flight_num);
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
    string key = companyName+int_to_str2(flightNumber);
    long location = this->hashCode(key);

    if (buckets[location].empty()){
        cout<<"record doesn't exist";
        return;
    }
	cout<<"enter\n";
    cout<<buckets[location].getLinesSorted(key);
	cout<<"exit\n";

}