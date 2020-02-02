#include "pch.h"
#include "Station.h"


Station::Station()
{

}

Station::~Station()
{
}

Station::Station(string stationName, string stationID)
{
	this->stationName = stationName;
	this->stationID = stationID;
	this->distanceToNext = 0;
}

void Station::SetDistance(int distance)
{
	this->distanceToNext = distance;
}

int Station::getDistance()
{
	return this->distanceToNext;
}

string Station::getStationID()
{
	return this->stationName;
}

string Station::getStationName()
{
	return this->stationID;
}
