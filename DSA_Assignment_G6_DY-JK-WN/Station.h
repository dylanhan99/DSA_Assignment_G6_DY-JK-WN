#pragma once
#include "List.h"

class Station
{
private:
	bool isInterchange;
	List stationIDs;

public:
	Station();
	~Station();

	Station(bool isInterchange, string stationID);

	void setIsInterchange(bool interchange);

	bool addStationID(string stationID);

	int getNumStationIDs();
};

