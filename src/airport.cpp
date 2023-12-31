
 #include "header/airport.h"

using namespace std;


Airport::Airport(string code, string name, string city, string country, double lati, double longi){
    this->code = code;
    this->name = name;
    this->city = city;
    this->country = country;
    this->coordinate = Coordinate(lati, longi);
}

Airport::Airport() {
    this->code = "";
    this->name = "";
    this->city = "";
    this->country = "";
    this->coordinate = Coordinate(0, 0);
}

string Airport::getCode(){
    return this->code;
}

string Airport::getName(){
    return this->name;
}

string Airport::getCity(){
    return this->city;
}

string Airport::getCountry(){
    return this->country;
}

Coordinate Airport::getCoordinate(){
    return this->coordinate;
}

bool Airport::operator > (const Airport e) const {
    return this->code > e.code;
}

bool Airport::operator < (const Airport e) const {
    return this->code < e.code;
}

bool Airport::operator == (const Airport e) const {
    return this->code == e.code;
}
