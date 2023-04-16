
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

#include "flightticket.h"
#include "flighthashtable.h"
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