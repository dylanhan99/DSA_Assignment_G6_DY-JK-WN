#include "pch.h"
#include "Station.h"

// Han Wei Dylan
// 10178483G
// Group 6
// Station constructor
Station::Station()
{
	
}

// Han Wei Dylan
// 10178483G
// Group 6
// Station destructor
Station::~Station()
{
}

// Han Wei Dylan
// 10178483G
// Group 6
// Station constructor
Station::Station(string stationName, string stationID)
{
	this->stationName = stationName;
	this->stationID = stationID;
	this->distanceToNext = 0;
}

// Han Wei Dylan
// 10178483G
// Group 6
// set the distance of this station
void Station::SetDistance(int distance)
{
	this->distanceToNext = distance;
}

// Han Wei Dylan
// 10178483G
// Group 6
// return the distance of this station
int Station::getDistance()
{
	return this->distanceToNext;
}

// Han Wei Dylan
// 10178483G
// Group 6
// return the station ID of this station
string Station::getStationID()
{
	return this->stationID;
}

// Han Wei Dylan
// 10178483G
// Group 6
// return the station name of this station
string Station::getStationName()
{
	return this->stationName;
}

// Han Wei Dylan
// 10178483G
// Group 6
// return the line prefix of this station
string Station::getLine()
{
	string line = stationID.substr(0, 1);
	return line;
}