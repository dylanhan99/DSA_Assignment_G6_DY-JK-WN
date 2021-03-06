#pragma once
#include<string>
#include"Globals.h"

using namespace std;
class Station
{
private:
	string stationName;
	string stationID;
	int distanceToNext; //in ascending order of ID. So EW23 to EW24 is 3500m

public:
	Station();
	~Station();

	Station(string stationName, string stationID);

	void SetDistance(int distance);

	string getStationName();

	string getStationID();

	string getLine();

	int getDistance();
};

