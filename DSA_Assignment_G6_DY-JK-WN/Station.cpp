#include "pch.h"
#include "Station.h"


Station::Station()
{

}

Station::~Station()
{
}

Station::Station(bool isInterchange, string stationID)
{
	this->isInterchange = isInterchange;
	this->stationIDs.add(stationID);
}

void Station::setIsInterchange(bool isInterchange)
{
	this->isInterchange = isInterchange;
}

bool Station::addStationID(string stationID)
{
	if (this->isInterchange)
	{
		this->stationIDs.resizeList(this->stationIDs.getLength() + 1);
		this->stationIDs.add(stationID);
		return true;
	}
	return false;
}