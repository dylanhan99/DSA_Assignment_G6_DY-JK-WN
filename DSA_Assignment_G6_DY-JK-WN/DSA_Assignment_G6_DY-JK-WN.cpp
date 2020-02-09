// DSA_Assignment_G6_DY-JK-WN.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>;
#include <fstream>
#include <sstream>  
#include <vector>
using namespace std;

#include "Globals.h"
#include "Queue.h"
#include "Stack.h"
#include "List.h"
#include "ArrayList.h"
#include "Dictionary.h"
#include "ListDictionary.h"

string fullPath = "full\\";

string FaresPath = fullPath + "Fares.csv";
string InterchangesPath = fullPath + "Interchanges.csv";
string RoutesPath = fullPath + "Routes.csv";
string StationsPath = fullPath + "Stations.csv";

vector<string>* FaresList;
vector<string>* InterchangesList;
vector<string>* RoutesList;
vector<string>* StationsList;

Queue* SplitQ(string str, char delimiter);
List<string>* SplitL(string str, char delimiter);
vector<string>* SplitV(string str, char delimiter);
bool ReadFile(string filename, vector<string>* outList);
int GetDistance(string stationID);
int CountFileLines(string filename);
int CalculateRoute(string source, string destination, Dictionary<Station> stationDict, ListDictionary<string> lineDict);
int CalculateRouteDistance(vector<string> line, string source, string destination, Dictionary<Station> stationDict);
int CalculateFares(int routeLength);
void InitDictionary(vector<string>* StationsList, Dictionary<Station>* outDictionary, ListDictionary<string>* outListDictionary);
void init();

int main()
{
	Dictionary<Station>* dic = new Dictionary<Station>();
	ListDictionary<string>* linesDict = new ListDictionary<string>();

	init();

	cout << "\n";
	InitDictionary(StationsList, dic, linesDict);
	cout << "len = " << dic->getLength() << endl;
	string stationName;

	//for (int i = 0; i < linesDict->get("NS")->getSize(); i++)
	//{
	//	cout << *(linesDict->get("NS")->get(i)) << endl;
	//}

	int option = 0;
	while (true)
	{
		string source;
		string destination;
		int distance = 0;

		//Display Menu
		cout << "===============================\n";
		cout << "1. Display all stations\n"; // Choose a line after selecting this option
		cout << "2. Display station information\n"; // Ask for station name after selecting this option
		cout << "3. Add new station\n"; // Add new station at specified line in file
		cout << "4. Display route\n"; // Ask for source and destination stations. Display a route and price.
		cout << "0. Quit\n"; // Exit
		cout << "===============================\n";
		cout << "Select an option: ";

		cin >> option;
		cout << "Option selected: " << option << "\n\n";

		switch (option)
		{
			case 0: // Exit
				return 0;
				break;
			case 1:
				continue;
			case 2:
				cout << "Enter a station name: ";
				cin.ignore();			   // Kind of pauses for the input. Without this, programme continues without waiting for input
				getline(cin, stationName); // Reads entire line instead of just the first word
				dic->printStationInformation(stationName);
				continue;
			case 3:
				cout << "Enter new station name: ";
				cin >> stationName;
				cout << "\nEnter new station name: ";
				continue;
			case 4:
				cout << "Enter the source station: ";
				cin.ignore();
				getline(cin, source);
				cout << "Enter the destination station: ";
				getline(cin, destination);
				cout << endl;

				distance = CalculateRoute(source, destination, *dic, *linesDict);
				cout << "Distance: " << distance << endl;
				cout << "Fare: " << CalculateFares(distance) << endl;
				continue;
			default:
				break;
		}

	}
}

int CalculateFares(int routeLength)
{
	vector<string> fares = *FaresList;
	int fare = 0;
	double routeDistance = (double)routeLength / 1000;

	for (int i = 0; i < fares.size(); i++)
	{
		vector<string> itemList = *SplitV(fares[i], ',');
		double distance = stod(itemList[0]);
		int price = stoi(itemList[1]);

		if (routeDistance >= distance)
		{
			fare = price;
		}

	}

	return fare;

}

int CalculateRoute(string source, string destination, Dictionary<Station> stationDict, ListDictionary<string> lineDict)
{
	int totalDistance = 0;
	Station sourceStation = *stationDict.get(source);
	Station destinationstation = *stationDict.get(destination);

	string sourceLine = sourceStation.getStationID().substr(0, 2);
	string destinationLine = destinationstation.getStationID().substr(0, 2);

	vector<string> line;

	//Compare Lines
	if (sourceLine == destinationLine)
	{
		line = *lineDict.get(sourceLine);
	}

	else
	{


	}
	
	totalDistance = CalculateRouteDistance(line, source, destination, stationDict);

	return totalDistance;

}

string FindInterchange(vector<string> line, string sourceLine, string source, string destinationLine, Dictionary<Station> stationDict)
{
	vector<vector<string>> availableInterchanges;
	vector<string> lineInterchanges;
	for (int i = 0; i < InterchangesList->size(); i++)
	{
		vector<string> interchange = *SplitV(InterchangesList->at(i), ',');
		for (int l = 0; l < interchange.size(); l++)
		{
			if (interchange[i] == sourceLine)
			{
				availableInterchanges.push_back(interchange);
				lineInterchanges.push_back(interchange[i]);

			}

		}

	}

	string nearestInterchange;
	int shortestDistance = 0;
	for (int i = 0; i < availableInterchanges.size(); i++)
	{

		int interchangeDistance = CalculateRouteDistance(line, source, lineInterchanges[i], stationDict);
		if (shortestDistance == 0)
			shortestDistance = interchangeDistance;

		if (interchangeDistance < shortestDistance)
		{
			shortestDistance = interchangeDistance;
			nearestInterchange = lineInterchanges[i];

		}

	}

	return nearestInterchange;

}

int CalculateRouteDistance(vector<string> line, string source, string destination, Dictionary<Station> stationDict)
{
	int distance = 0;
	int lineLength = line.size();
	if (lineLength > 0)
	{
		int start;
		int end;

		for (int i = 0; i < lineLength; i++)
		{
			if (line[i] == source)
				start = i;
			if (line[i] == destination)
				end = i;

		}

		if (start - end > 0)
		{
			int temp = end;
			end = start;
			start = temp;

		}

		for (int i = start; i < end; i++)
		{
			distance += stationDict.get(line[i])->getDistance();
		}

		return distance;

	}
}

Queue* SplitQ(string str, char delimiter)
{
	Queue* internal = new Queue();
	stringstream ss(str); // Turn the string into a stream.
	string tok;

	while (getline(ss, tok, delimiter))
		internal->enqueue(tok);


	return internal;
}

List<string>* SplitL(string str, char delimiter)
{
	// count number of delimiter in string to determine List size
	int size = 0;
	for (int i = 0; i < str.size(); i++)
		if (str[i] == delimiter) 
			size++;

	List<string>* internal = new List<string>();
	stringstream ss(str); // Turn the string into a stream.
	string tok;

	while (getline(ss, tok, delimiter))
		internal->add(tok);


	return internal;
}

vector<string>* SplitV(string str, char delimiter)
{
	// count number of delimiter in string to determine List size
	int size = 0;
	for (int i = 0; i < str.size(); i++)
		if (str[i] == delimiter)
			size++;

	vector<string>* internal = new vector<string>();
	stringstream ss(str); // Turn the string into a stream.
	string tok;

	while (getline(ss, tok, delimiter))
		internal->push_back(tok);


	return internal;
}

bool ReadFile(string filename, vector<string>* outList)
{
	ifstream myfile(filename);
	//cout << "Filename = " << filename << endl;
	if (myfile.is_open())
	{
		string line;
		while (getline(myfile, line))
		{
			cout << line << endl;
			outList->push_back(line);
		}
		myfile.close();
		return true;
	}
	cout << "Unable to open file";
	return false;
}

int GetDistance(string stationID)
{
	string line;
	int rowIndex, columnIndex = 0;
	for (int i = 0; i < RoutesList->size(); i++)
	{
		rowIndex = i;
		if (i % 2 != 0)
		{
			//i++;
			continue; 
		}
		line = RoutesList->at(rowIndex).substr(0, 2); // Get first 2 letters in string to check line. EW/NS/DT/etc.
		if (stationID.substr(0, 2) == line)
		{
			Queue* faresQueue = SplitQ(RoutesList->at(rowIndex), ',');
			while (!faresQueue->isEmpty())
			{
				string currentID;
				faresQueue->dequeue(currentID);
				if (currentID == stationID)
					break;
				if (faresQueue->isEmpty())
					return -1;
				columnIndex++;
			}
			faresQueue = SplitQ(RoutesList->at(rowIndex + 1), ',');
			string fare;
			faresQueue->getFront(fare); // if columnIndex == 0, fare will still have a value
			for (int j = 0; i < columnIndex; i++)
				faresQueue->dequeue(fare);

			return stoi(fare); //converts the string fare into int
		}
		else
			continue;
			//i++;
	}
	return -1;
}

int CountFileLines(string filename)
{
	int number_of_lines = 0;
	string line;
	ifstream myfile(filename);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
			++number_of_lines;
		myfile.close();
		cout << "num of lines = " << number_of_lines << endl;
		return number_of_lines;
	}
	else
	{
		cout << "Unable to open file";
		return -1;
	}
}

void InitDictionary(vector<string>* StationsList, Dictionary<Station>* outDictionary, ListDictionary<string>* outListDictionary)
//void InitDictionary(List* StationsList, Dictionary<Station>* outDictionary)
{
	//cout << "length" << StationsList->getSize() << endl;
	string line = "";
	vector<string> LineStationsList;
	for (int i = 0; i < StationsList->size(); i++)
	{
		string currentStation = StationsList->at(i);
		Queue* currentStationInfo = SplitQ(currentStation, ',');

		string currentStationID, currentStationName;
		currentStationInfo->dequeue(currentStationID);
		currentStationInfo->dequeue(currentStationName);

		string currentLine = currentStationID.substr(0, 2);
		if (currentLine != line)
		{
			if (line != "")
				outListDictionary->add(line, LineStationsList);

			line = currentLine;
			LineStationsList = vector<string>();
		}
		
		LineStationsList.push_back(currentStationName);

		//cout << "stationID = " << currentStationID << endl;
		//cout << "stationName = " << currentStationName << endl;

		outDictionary->add(currentStationName, currentStationID, GetDistance(currentStationID));
		//cout << "added to dic" << endl;
	}
}

void init()
{
	FaresList = new vector<string>();
	InterchangesList = new vector<string>();
	RoutesList = new vector<string>();
	StationsList = new vector<string>();

	if (!ReadFile(FaresPath, FaresList))
		cout << "Error init Fares..." << endl;
	if (!ReadFile(InterchangesPath, InterchangesList))
		cout << "Error init Interchanges..." << endl;
	if (!ReadFile(RoutesPath, RoutesList))
		cout << "Error init Routes..." << endl;
	if (!ReadFile(StationsPath, StationsList))
		cout << "Error init Stations..." << endl;
}