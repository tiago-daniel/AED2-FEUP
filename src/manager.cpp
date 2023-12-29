#include "header/manager.h"
#include "header/airlines.h"
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

//Reads the csv files and fills the list airports with the elements of the class airport
//Time Complexity O(n), being n the number of lines of airports.csv
void Manager::buildAirports() {
    ifstream airportsData("../dataset/airports.csv");
    string line, code,name,city,country,latitude,longitude;
    getline(airportsData, line);
    while (getline(airportsData, line)) {
        istringstream info(line);
        getline(info, code, ',');
        getline(info, name, ',');
        getline(info, city, ',');
        getline(info, country, ',');
        getline(info, latitude, ',');
        getline(info, longitude, '\r');
        float fLatitude = stof(latitude);
        float fLongitude = stof(longitude);
        Airport airport = Airport(code, name, city, country, fLatitude, fLongitude);
        airports.push_back(airport);
        airportsGraph.addVertex(airport);
    }
    sort(airports.begin(), airports.end());
}

//Reads the csv files and fills the list airlines with the elements of the class airport
//Time Complexity O(n), being n the number of lines of airlines.csv
void Manager::buildAirlines() {
    ifstream airportsData("../dataset/airlines.csv");
    string line, code,name,callsign,country;
    getline(airportsData, line);
    while (getline(airportsData, line)) {
        istringstream info(line);
        getline(info, code, ',');
        getline(info, name, ',');
        getline(info, callsign, ',');
        getline(info, country, ',');
        Airlines airline = Airlines(name, code, callsign, country);
        airlines.push_back(airline);
    }
    sort(airlines.begin(), airlines.end());
}


//Reads the flights.csv files and fills the graph
//Time Complexity O(n * 2 log(h) * log(y)), being n the number of lines of flights.csv, h the size of the list of airports and y the size of the list of airlines
void Manager::buildFlights() {
    ifstream airportsData("../dataset/flights.csv");
    string line, source,target, airline;
    getline(airportsData, line);
    while (getline(airportsData, line)) {
        istringstream info(line);
        getline(info, source, ',');
        getline(info, target, ',');
        getline(info, airline, ',');
        Airport sourceAirport = findAirport(source);
        Airport targetAirport = findAirport(target);
        Airlines takenAirline = findAirlines(airline);
        airportsGraph.addEdge(sourceAirport, targetAirport, takenAirline);
    }
}


Airport Manager::findAirport(string code) {
    int left = 0;
    int right = airports.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (airports[mid].getCode() == code) {
            return airports[mid];
        }
        if (airports[mid].getCode() < code) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
}
Airlines Manager::findAirlines(string code) {
    int left = 0;
    int right = airlines.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (airlines[mid].getCode() == code) {
            return airlines[mid];
        }
        if (airlines[mid].getCode() < code) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
}



Graph<Airport> Manager::getAirports() {
    return airportsGraph;
}

list<string> Manager::airportFromCountry(string country){
    list<string> lista;
    for (auto b : airports) {
        if (b.getCountry() == country) {
            cout << b.getName() << "\n";
        }
    }
}

int Manager::numberAirports() {
    return airports.size();
}

int Manager::numberFlights() {
    int count = 0;
    for (auto a : airports){
        count += airportsGraph.findVertex(a)->getAdj().size();
    }
    return count;
}

//Search the graph fpr the right vertex and then returns the flights
// Time complexity O(n) being n the size of the graph vertex set
vector<Edge<Airport>> Manager::getFlightsOutAnAirportByName(string name) {
    for (auto i : airportsGraph.getVertexSet()) {
        if (i->getInfo().getName() == name) {
            return i->getAdj();
        }
    }
    return vector<Edge<Airport>>();
}

//Search the graph fpr the right vertex and then returns the flights
// Time complexity O(n) being n the size of the graph vertex set
vector<Edge<Airport>> Manager::getFlightsOutAnAirportByCode(string code) {
    for (auto i : airportsGraph.getVertexSet()) {
        if (i->getInfo().getCode() == code) {
            return i->getAdj();
        }
    }
    return vector<Edge<Airport>>();
}

//Returns the number of flights
// Time complexity O(n) being n the size of the graph vertex set
int Manager::getNumberOfFlightsOutAnAirportByName(string name) {
    return getFlightsOutAnAirportByName(name).size();
}


//Returns the number of flights
// Time complexity O(n) being n the size of the graph vertex set
int Manager::getNumberOfFlightsOutAnAirportByCode(string code) {
    return getFlightsOutAnAirportByCode(code).size();
}

//Returns the number of airlines
// Time complexity O(n) being n the size of the graph vertex set
int Manager::getNumberOfAirlinesOutAnAirportByName(string name) {
    set<Airlines> airlines;
    vector<Edge<Airport>> flights = getFlightsOutAnAirportByName(name);
    for (auto i: flights) {
        airlines.insert(i.getWeight());
    }
    return airlines.size();
}

//Returns the number of airlines
// Time complexity O(n) being n the size of the graph vertex set
int Manager::getNumberOfAirlinesOutAnAirportByCode(string code) {
    set<Airlines> airlines;
    vector<Edge<Airport>> flights = getFlightsOutAnAirportByCode(code);
    for (auto i: flights) {
        airlines.insert(i.getWeight());
    }
    return airlines.size();
}


int Manager::numberOfFlightsOutOfTheCity(string city) {
    int counter = 0;
    vector<Vertex<Airport>*> vertexes = airportsGraph.getVertexSet();
    for (auto i : vertexes) {
        if (i->getInfo().getCity() == city) {
            i++;
        }
    }
    return counter;
}

int Manager::numberOfFlightIntoTheCity(string city) {
    int counter = 0;
    vector<Vertex<Airport>*> vertexes = airportsGraph.getVertexSet();
    for (auto i : vertexes) {
        for (auto j : i->getAdj()) {
            if (j.getDest()->getInfo().getCity() == city) {
                i++;
            }
        }
    }
    return counter;
}
int numberOfFlightsPerAirlineName(string name);
int numberOfFlightsPerAirlineCode(string code);
