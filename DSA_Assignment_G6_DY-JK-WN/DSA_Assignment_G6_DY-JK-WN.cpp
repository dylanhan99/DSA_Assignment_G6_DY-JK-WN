// DSA_Assignment_G6_DY-JK-WN.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>;
#include <fstream>
#include <sstream>  
#include <vector>
using namespace std;

#include "Dictionary.h"
#include "List.h"
#include "Queue.h"

string DYmainpath = "C:\\Users\\HanWei\\Desktop\\NP stuff\\Year_3-2_FINAL\\DSA\\!Assignment\\";
string JKmainpath = "";
string WNmainpath = "";
string full_simple = "full\\";

string folderPath = DYmainpath + full_simple;

string FaresPath = folderPath + "Fares.csv";
string InterchangesPath = folderPath + "Interchanges.csv";
string RoutesPath = folderPath + "Routes.csv";
string StationsPath = folderPath + "Stations.csv";

List<string>* FaresList;
List<string>* InterchangesList;
List<string>* RoutesList;
List<string>* StationsList;

Queue* SplitQ(string str, char delimiter);
List<string>* SplitL(string str, char delimiter);
bool ReadFile(string filename, List<string>* outList);
int GetDistance(string stationID);
int CountFileLines(string filename);
void InitDictionary(List<string>* StationsList, Dictionary* outDictionary);
void init();

int main()
{
	Dictionary* dic = new Dictionary();

	init();

	if (ReadFile(FaresPath, FaresList))
		cout << "Init Fares..." << endl;
	if (ReadFile(InterchangesPath, InterchangesList))
		cout << "Init Interchanges..." << endl;
	if (ReadFile(RoutesPath, RoutesList))
		cout << "Init Routes..." << endl;
	if (ReadFile(StationsPath, StationsList))
		cout << "Init Stations..." << endl;

	cout << "\n";

	InitDictionary(StationsList, dic);
	//cout << "len" << dic->getLength();
	//dic->print();
	string stationName;

	int option = 0;
	while (true)
	{
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
		cout << "\nOption selected: " << option << endl;

		switch (option)
		{
			case 0: // Exit
				return 0;
				break;
			case 1:
				break;
			case 2:
				cout << "Enter a station name: ";
				cin >> stationName;

				//Station station = dic->getStation(stationName);
				//if (station != NULL)
				//{
				//
				//}
				//else
				//	cout << "Station " << stationName << " does does not exist!";
				break;
			case 3:
				break;
			case 4:
				break;
			default:
				break;
		}

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
			//cout << "test" << endl;
			//cout << "line = " << line << endl;
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
		line = RoutesList->get(rowIndex).substr(0, 2); // Get first 2 letters in string to check line. EW/NS/DT/etc.
		if (stationID.substr(0, 2) == line)
		{
			Queue* faresQueue = SplitQ(RoutesList->get(rowIndex/* + 1*/), ',');
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
			faresQueue = SplitQ(RoutesList->get(rowIndex + 1), ',');
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

void InitDictionary(List<string>* StationsList, Dictionary* outDictionary)
{
	//cout << "length" << StationsList->getSize() << endl;
	for (int i = 0; i < StationsList->getSize(); i++)
	{
		string currentStation = *StationsList->get(i);
		Queue* currentStationInfo = SplitQ(currentStation, ',');

		string currentStationID, currentStationName;
		currentStationInfo->dequeue(currentStationID);
		currentStationInfo->dequeue(currentStationName);

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
}

