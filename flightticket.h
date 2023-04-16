#ifndef FLIGHT_TICKET_H
#define FLIGHT_TICKET_H

#include<iostream>
using namespace std;

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

#endif
