#include <sstream>
#include "flightticket.h"

string int_to_str1(int num){
    ostringstream str1;
    str1<<num;
    return str1.str();
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