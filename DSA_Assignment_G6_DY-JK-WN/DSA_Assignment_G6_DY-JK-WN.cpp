// DSA_Assignment_G6_DY-JK-WN.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
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
vector<string>* LineList;

vector<string>* Split(string str, char delimiter);
bool ReadFile(string filename, vector<string>* outList);
int GetDistance(string stationID);
int CountFileLines(string filename);
int CalculateRoute(string source, string destination, Dictionary<Station> stationDict, ListDictionary<string> lineDict);
int CalculateRouteDistance(vector<string> line, string source, string destination, Dictionary<Station> stationDict);
int CalculateFares(int routeLength);
bool WriteIntoInterchanges(string stationID, string stationName, Dictionary<Station>* dic);
bool WriteIntoRoutes(string stationID, string dist);
bool WriteIntoStations(string stationID, string stationName, Dictionary<Station>* dic);
bool AddNewStation(string stationID, string stationName, string distToNext);
bool WriteFile(string filePath, string str);
bool WriteFile(string filePath, string str, int line);
void InitDictionary(vector<string>* StationsList, Dictionary<Station>* outDictionary, ListDictionary<string>* outListDictionary);
void printLinesOptions();
void printStationsInLine(int lineNumber);
void init();

int main()
{
	Dictionary<Station>* dic = new Dictionary<Station>();
	ListDictionary<string>* linesDict = new ListDictionary<string>();

	init();

	cout << "\n";
	InitDictionary(StationsList, dic, linesDict);
	cout << "len = " << dic->getLength() << endl;
	//vector<Station> stations = dic->getAll();
	//for (int i = 0; i < stations.size(); i++)
	//{
	//	cout << stations.at(i).getStationName() << endl;
	//}

	string stationName;

	// Initialising variables
	int lineNumber;

	//for (int i = 0; i < linesDict->get("NS")->getSize(); i++)
	//{
	//	cout << *(linesDict->get("NS")->get(i)) << endl;
	//}

	// while loop
	int option = 0;
	while (true)
	{
		string source;
		string destination;
		int distance = 0;

		//Display Menu
		cout << "MAIN MENU\n";
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
			// Exit
			case 0:
				return 0;
				break;

			// Display all stations in a given line
			case 1:
				cout << "Available MRT Lines: \n";
				cout << "===============================\n";
				printLinesOptions();
				cout << "===============================\n";
				cout << "Choose a line: ";
				cin.ignore();
				cin >> lineNumber;

				cout << "\nDisplaying stations in ";
				// Printing stations in a line
				printStationsInLine(lineNumber);
				continue;

			// Display station information for a given station name
			case 2:
				cout << "Enter a station name: ";
				cin.ignore();			   // Kind of pauses for the input. Without this, programme continues without waiting for input
				getline(cin, stationName); // Reads entire line instead of just the first word
				dic->printStationInformation(stationName);
				continue;

			// Add and save a new station on a given line
			case 3:
				cout << "Enter new station name: ";
				cin >> stationName;
				cout << "\nEnter new station name: ";
				continue;

			// Find and display a route and its price, given the source and destination stations
			case 4:
				cout << "Enter the source station: ";
				cin.ignore();
				getline(cin, source);
				cout << "Enter the destination station: ";
				getline(cin, destination);
				cout << endl;

				distance = CalculateRoute(source, destination, *dic, *linesDict);
				if (distance > 0)
				{
					cout << "Distance: " << distance << endl;
					cout << "Fare: " << CalculateFares(distance) << endl;
				}
				else
				{
					cout << "Invalid Query" << endl;
				}

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
		vector<string> itemList = *Split(fares[i], ',');
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
	trimAll(&source);
	trimAll(&destination);

	Station sourceStation;
	Station destinationStation;

	bool isSourceExists = stationDict.contains(source);
	bool isDestinationExists = stationDict.contains(destination);

	if (isSourceExists && isDestinationExists)
	{
		sourceStation = *stationDict.get(source);
		destinationStation = *stationDict.get(destination);
	}
	else
	{
		if (!isSourceExists)
			cout << "Source Station does not exist." << endl;
		if (!isDestinationExists)
			cout << "Destination Station does not exist." << endl;
		return 0;
	}

	//if (!stationDict.get(source, &sourceStation) || !stationDict.get(source, &destinationstation))
	//{
	//	cout << "Station does not exist." << endl;
	//	return 0;
	//}

	string sourceLine = sourceStation.getStationID().substr(0, 2);
	string destinationLine = destinationStation.getStationID().substr(0, 2);

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
		vector<string> interchange = *Split(InterchangesList->at(i), ',');
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

vector<string>* Split(string str, char delimiter)
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
			vector<string>* faresList = Split(RoutesList->at(rowIndex), ',');
			while (faresList->size() > 0)
			{
				string currentID;
				currentID = faresList->front();
				faresList->erase(faresList->begin());
				if (currentID == stationID)
					break;
				if (faresList->size() <= 0)
					return -1;
				columnIndex++;
			}
			faresList = Split(RoutesList->at(rowIndex + 1), ',');
			string fare;
			fare = faresList->front(); // if columnIndex == 0, fare will still have a value
			for (int j = 0; i < columnIndex; i++)
			{
				fare = faresList->front();
				faresList->erase(faresList->begin());
			}
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

bool WriteIntoInterchanges(string stationID, string stationName, Dictionary<Station>* dic) // step 3
{
	vector<Station>* stations = dic->getStations(stationName);
	if (stations->size() >= 0)
	{
		//write to interchagne.csv
	}
	cout << stationName << " will not be an interchange" << endl;
	return false;
}

bool WriteIntoRoutes(string stationID, string dist) // step 2
{
	// check if station exists.
	// if it dosnt, add at that id
	// else (it exists), return error msg
	return false;
}

bool WriteIntoStations(string stationID, string stationName, Dictionary<Station>* dic) // step 1, once this is passed, the other two can run.
{
	// check if station exists.
	// if it dosnt, add at that id
	// else (it exists), return error msg

	vector<Station>* stations = dic->getStations(stationName);
	if (stations->size() > 0) //station exists, so check if the line already exists (cannot add station of same name on same line)
	{
		for (int i = 0; i < stations->size(); i++)
		{
			if (stations->at(i).getLine() == stationID.substr(0, 2)) // station already exists on line
				return false;
		}
	}
	// station does not exist on line yet
	// is the stationID available?
	for (int i = 0; i < StationsList->size(); i++)
	{
		string str = StationsList->at(i);
		vector<string>* split = Split(str, ','); // pass by value. i dont want to alter StationsList
		if (split->front() == stationID) //if the stationID user entered already exists, fail
			return false; 
	}
	// Name and ID are available on that line.
	// Proceed to add into csv
	// station dont need to be in order so can just add to the end. 
	// routes need to be in order so must adjust
	// interchanges also need
	string strToWrite = stationID + "," + stationName;
	WriteFile(StationsPath, strToWrite);

	return true;
}

bool WriteFile(string filePath, string str) // adds to end of file
{
	ofstream myfile(filePath);
	if (myfile.is_open())
	{
		myfile << str << "\n";
		myfile.close();
		return true;
	}
	cout << "Unable to open file";
	return false;

}

bool WriteFile(string filePath, string str, int line)
{
	vector<string>* fileData = new vector<string>();
	ReadFile(filePath, fileData);

	fileData->at(line) = str; // replacing old line with new

	ofstream myfile(filePath);
	if (myfile.is_open())
	{
		for (int i = 0; i < fileData->size(); i++)
		{
			myfile << fileData->front() << "\n";
			fileData->erase(fileData->begin());
		}

		myfile.close();
		return true;
	}
	cout << "Unable to open file";
	return false;
}



bool AddNewStation(string stationID, string stationName, string distToNext)
{
	//if stationID substr 0,2 is in lines list
	//if stationID is correct format
	return false;
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
		vector<string>* currentStationInfo = Split(currentStation, ',');

		string currentStationID, currentStationName;
		currentStationName = currentStationInfo->back();
		currentStationInfo->pop_back();
		currentStationID = currentStationInfo->back();
		currentStationInfo->pop_back();

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
	LineList = new vector<string>();

	LineList->push_back("EW,East-West Line");
	LineList->push_back("NS,North-South Line");
	LineList->push_back("CC,Circle Line");
	LineList->push_back("DT,Downtown Line");
	LineList->push_back("NE,North-East Line");
	LineList->push_back("CG,East-West Branch Line");
	LineList->push_back("CE,Circle Branch Line");

	if (!ReadFile(FaresPath, FaresList))
		cout << "Error init Fares..." << endl;
	if (!ReadFile(InterchangesPath, InterchangesList))
		cout << "Error init Interchanges..." << endl;
	if (!ReadFile(RoutesPath, RoutesList))
		cout << "Error init Routes..." << endl;
	if (!ReadFile(StationsPath, StationsList))
		cout << "Error init Stations..." << endl;
}

// [1] Print menu of all lines
void printLinesOptions()
{
	for (int i = 0; i < LineList->size(); i++) {
		vector<string>* splitList;
		splitList = Split(LineList->at(i), ',');
		cout << i + 1 << ". " << splitList->at(1) << " (" << splitList->at(0) << ")" << endl;
	}
}

// [1] Display all stations in selected line
void printStationsInLine(int lineNumber)
{
	int lineIndex = lineNumber - 1;
	vector<string>* splitList;
	splitList = Split(LineList->at(lineIndex), ',');

	cout << splitList->at(1) << " (" << splitList->at(0) << ")..." << endl;

	for (int i = 0; i < StationsList->size(); i++) {
		if ((StationsList->at(i)).find(splitList->at(0)) != -1)
			cout << StationsList->at(i) << endl;
	}

	cout << endl;
}