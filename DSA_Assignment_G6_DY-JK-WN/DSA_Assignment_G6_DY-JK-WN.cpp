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

List<string>* FaresList;
List<string>* InterchangesList;
List<string>* RoutesList;
List<string>* StationsList;

Queue* SplitQ(string str, char delimiter);
List<string>* SplitL(string str, char delimiter);
bool ReadFile(string filename, List<string>* outList);
int GetDistance(string stationID);
int CountFileLines(string filename);
int CalculateRoute(string source, string destination, Dictionary<Station> stationDict, ListDictionary<string> lineDict);
int CalculateRouteDistance(vector<string> line, string source, string destination, Dictionary<Station> stationDict);
int CalculateFares(int routeLength);
void InitDictionary(List<string>* StationsList, Dictionary<Station>* outDictionary, ListDictionary<string>* outListDictionary);
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
	List<string> fares = *FaresList;
	int fare = 0;
	double routeDistance = (double)routeLength / 1000;

	for (int i = 0; i < fares.getSize(); i++)
	{
		List<string> itemList = *SplitL(*fares.get(i), ',');
		double distance = stod(*itemList.get(0));
		int price = stoi(*itemList.get(1));

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

	//else
	//{
	//	List<string> availableInterchanges = List<string>();
	//	for (int i = 0; i < InterchangesList->getSize(); i++)
	//	{
	//		List<string> interchange = *SplitL(*InterchangesList->get(0), ',');
	//		for (int l = 0; l < interchange.getSize(); l++)
	//		{
	//			if (*interchange.get(l) == sourceLine)
	//			{
	//				availableInterchanges.add()
	//			}

	//		}

	//	}

	//}
	//
	totalDistance = CalculateRouteDistance(line, source, destination, stationDict);

	return totalDistance;

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

bool ReadFile(string filename, List<string>* outList)
{
	ifstream myfile(filename);
	//cout << "Filename = " << filename << endl;
	if (myfile.is_open())
	{
		string line;
		while (getline(myfile, line))
		{
			cout << line << endl;
			outList->add(line);
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
	for (int i = 0; i < RoutesList->getSize(); i++)
	{
		rowIndex = i;
		if (i % 2 != 0)
		{
			//i++;
			continue; 
		}
		line = RoutesList->get(rowIndex)->substr(0, 2); // Get first 2 letters in string to check line. EW/NS/DT/etc.
		if (stationID.substr(0, 2) == line)
		{
			Queue* faresQueue = SplitQ(*RoutesList->get(rowIndex), ',');
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
			faresQueue = SplitQ(*RoutesList->get(rowIndex + 1), ',');
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

void InitDictionary(List<string>* StationsList, Dictionary<Station>* outDictionary, ListDictionary<string>* outListDictionary)
//void InitDictionary(List* StationsList, Dictionary<Station>* outDictionary)
{
	//cout << "length" << StationsList->getSize() << endl;
	string line = "";
	vector<string> LineStationsList;
	for (int i = 0; i < StationsList->getSize(); i++)
	{
		string currentStation = *StationsList->get(i);
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
	FaresList = new List<string>();
	InterchangesList = new List<string>();
	RoutesList = new List<string>();
	StationsList = new List<string>();

	if (!ReadFile(FaresPath, FaresList))
		cout << "Error init Fares..." << endl;
	if (!ReadFile(InterchangesPath, InterchangesList))
		cout << "Error init Interchanges..." << endl;
	if (!ReadFile(RoutesPath, RoutesList))
		cout << "Error init Routes..." << endl;
	if (!ReadFile(StationsPath, StationsList))
		cout << "Error init Stations..." << endl;
}