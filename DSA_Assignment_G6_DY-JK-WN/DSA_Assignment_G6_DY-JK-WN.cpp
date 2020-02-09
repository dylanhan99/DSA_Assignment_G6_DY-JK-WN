// DSA_Assignment_G6_DY-JK-WN.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

#include "Globals.h"
#include "Dictionary.h"
#include "ListDictionary.h"

string fullPath = "full\\";
//string simplePath = "simple\\";

string FaresPath = fullPath + "Fares.csv";
string InterchangesPath = fullPath + "Interchanges.csv";
string RoutesPath = fullPath + "Routes.csv";
string StationsPath = fullPath + "Stations.csv";

vector<string>* FaresList;
vector<string>* InterchangesList;
vector<string>* RoutesList;
vector<string>* StationsList;
vector<string>* LineList;
Dictionary<Station>* dic;
ListDictionary<string>* linesDict;
vector<string>* splitLineList;

vector<string>* Split(string str, char delimiter);
bool ReadFile(string filename, vector<string>* outList);
int GetDistance(string stationID);
int CountFileLines(string filename);
int CalculateRoute(string source, string destination, Dictionary<Station> stationDict, ListDictionary<string> lineDict);
int CalculateRouteDistance(vector<string> line, string source, string destination, Dictionary<Station> stationDict);
int CalculateFares(int routeLength);
void WriteIntoInterchanges(string stationID, string stationName, Dictionary<Station>* dic);
bool WriteIntoRoutes(string stationID, string dist);
bool WriteIntoStations(string stationID, string stationName, Dictionary<Station>* dic);
bool AddNewStation(string stationID, string stationName, string distToNext, Dictionary<Station>* dic);
bool WriteFile(string filePath, string str);
bool WriteFile(string filePath, string str, int line);
void InitDictionary();
string FindInterchange(vector<string> sourceLineStations, string sourceLineName, string source, string destinationLineName, Dictionary<Station> stationDict);
void printLinesOptions();
void printStationsInLine(int lineNumber);
void CalculateThreeRoutes(string source, string destination);
vector<vector<Station>*>* CheckStation(int routeNum, string source, string destination,
	vector<vector<Station>*>* routesList);
vector<string>* getConnections(string stationName);
void init();

int main()
{
	init();

	cout << "\n";
	InitDictionary();
	cout << "len = " << dic->getLength() << endl;

	// Initialising variables
	int lineNumber;
	string stationID, stationName, dist;
	string linePrefix;
	bool lineExists = false;

	// while loop
	int option = 0;
	while (true)
	{
		string source;
		string destination;
		int distance = 0;
		int lineIndex;

		//Display Menu
		cout << "MAIN MENU\n";
		cout << "===============================\n";
		cout << "1. Display all stations\n"; // Choose a line after selecting this option
		cout << "2. Display station information\n"; // Ask for station name after selecting this option
		cout << "3. Add new station\n"; // Add new station at specified line in file
		cout << "4. Display route\n"; // Ask for source and destination stations. Display a route and price.
		cout << "5. Display three routes\n"; // Ask for source and destination stations. Display 3 routes and price.
		cout << "6. Add new line\n"; // Add a new line and then prompt to add new stations.
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
				printLinesOptions();
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
				// Prompt users to choose a line to add a new station to
				printLinesOptions();
				cin.ignore();
				cin >> lineNumber;
				// Print all stations in the current line
				cout << "\nCurrent stations in ";
				printStationsInLine(lineNumber);

				cout << "\nEnter new station name: ";
				cin.ignore();
				getline(cin, stationName);

				// Users can input `station ID: -` if it is the last station,
				// and `station ID: 2~` if it is in between and there are no stations at current ID.
				lineIndex = lineNumber - 1;
				cout << "Enter new station ID (Enter '-' if it is the last station): " << LineList->at(lineIndex);
				cin >> stationID;
				stationID = LineList->at(lineIndex) + stationID; // Prepending the station prefix in front of ID

				// If it is the last station
				if (stationID == "-")
					stationID = "";

				// We want to calculate the distance here.
				// The distance recorded is between the current station and the previous station.
				if (stationID != "0") {
					cout << "Distance to previous station: ";
					cin >> dist;
 				}

				// Add a new station
				if (AddNewStation(stationID, stationName, dist, dic))
				{
					cout << "New station added: ";
					cout << stationID << ", " << stationName << endl << endl;
				}
				else
					cout << "Unable to add new station." << endl << endl;
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

			// Find and display a route and its price, given the source and destination stations
			case 5:
				//cout << "Enter the source station: ";
				//cin.ignore();
				//getline(cin, source);
				//cout << "Enter the destination station: ";
				//getline(cin, destination);
				//cout << endl;
				source = "Jurong East";
				destination = "Clementi";
				CalculateThreeRoutes(source, destination);

				continue;
			// Adding a new line
			case 6:
				cout << "\nEnter new line prefix: ";
				cin >> linePrefix;
				transform(linePrefix.begin(), linePrefix.end(), linePrefix.begin(), ::toupper); // uppercase

				// Add a new line
				// Check if line prefix already exists
				for (int i = 0; i < StationsList->size(); i++) {
					if (StationsList->at(i).substr(2, 2) == linePrefix)
						lineExists = true;
				}


				// If line exists
				if (lineExists)
					cout << "Line already exists." << endl << endl;
				// If line does not exist
				else
				{
					LineList->push_back(linePrefix);
					cout << "New line added: " << linePrefix << endl;
					cout << "Please add some new stations..." << endl;

					// ADDING A NEW STATION
					cout << "\nEnter new station name: ";
					cin.ignore();
					getline(cin, stationName);

					// Users can input `station ID: -` if it is the last station,
					// and `station ID: 2~` if it is in between and there are no stations at current ID.
					cout << "Enter new station ID (Enter '-' if it is the last station): " << linePrefix;
					cin >> stationID;
					stationID = linePrefix + stationID; // Prepending the station prefix in front of ID

					// If it is the last station
					if (stationID == "-")
						stationID = "";

					// We want to calculate the distance here.
					// The distance recorded is between the current station and the previous station.
					if (stationID != "0") {
						cout << "Distance to previous station: ";
						cin >> dist;
					}

					// Add a new station
					if (AddNewStation(stationID, stationName, dist, dic))
					{
						cout << "New station added: ";
						cout << stationID << ", " << stationName << endl << endl;
					}
					else
						cout << "Unable to add new station." << endl << endl;
				}

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

	string sourceLineName = sourceStation.getStationID().substr(0, 2);
	string destinationLineName = destinationStation.getStationID().substr(0, 2);

	vector<string> sourceLineStations;
	vector<string> destinationLineStations;
	//vector<string> interchangeLineStations;

	//Compare Lines
	sourceLineStations = *lineDict.get(sourceLineName);
	destinationLineStations = *lineDict.get(destinationLineName);

	if (sourceLineName != destinationLineName)
	{
		string nearestInterchange = FindInterchange(sourceLineStations, sourceLineName, source, destinationLineName, stationDict);
		//interchangeLineStations = *lineDict.get(nearestInterchange.substr(0, 2));

		Station interchangeStation = stationDict.getByID(nearestInterchange);
		string interchange = interchangeStation.getStationName();
		trimAll(&interchange);

		totalDistance += CalculateRouteDistance(sourceLineStations, source, interchange, stationDict);

		source = interchange;
		sourceLineStations = destinationLineStations;

	}

	totalDistance += CalculateRouteDistance(sourceLineStations, source, destination, stationDict);
	return totalDistance;

}

string FindInterchange(vector<string> sourceLineStations, string sourceLineName, string source, string destinationLineName, Dictionary<Station> stationDict)
{
	vector<vector<string>> availableInterchanges;
	vector<string> lineInterchanges;
	for (int i = 0; i < InterchangesList->size(); i++)
	{
		vector<string> interchange = *Split(InterchangesList->at(i), ',');
		for (int n = 0; n < interchange.size(); n++)
		{
			if (interchange[n].substr(0, 2) == sourceLineName)
			{
				availableInterchanges.push_back(interchange);
				lineInterchanges.push_back(interchange[n]);

			}

		}

	}

	string nearestInterchange;
	int shortestDistance = -1;
	for (int i = 0; i < availableInterchanges.size(); i++)
	{
		Station destStation = stationDict.getByID(lineInterchanges[i]);
		string destination = destStation.getStationName();
		trimAll(&destination);

		int interchangeDistance = CalculateRouteDistance(sourceLineStations, source, destination, stationDict);
		if (shortestDistance < 0 || interchangeDistance < shortestDistance)
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
			string stationName = line[i];
			trimAll(&stationName);

			if (stationName  == source)
				start = i;
			if (stationName == destination)
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
			string stationName = line[i];
			trimAll(&stationName);

			distance += stationDict.get(stationName)->getDistance();
		}

		return distance;

	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// [1] Print menu of all lines
void printLinesOptions()
{
	cout << "Available MRT Lines: \n";
	cout << "===============================\n";

	for (int i = 0; i < LineList->size(); i++) {
		cout << i + 1 << ". " << LineList->at(i) << endl;
	}

	cout << "===============================\n";
	cout << "Choose a line: ";
}

// [1] Display all stations in selected line
void printStationsInLine(int lineNumber)
{
	int lineIndex = lineNumber - 1;
	cout << LineList->at(lineIndex) << "..." << endl;

	for (int i = 0; i < StationsList->size(); i++) {
		if ((StationsList->at(i)).find(LineList->at(lineIndex)) != -1)
			cout << StationsList->at(i) << endl;
	}

	cout << endl;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


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


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


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


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// [3]  Step 1: Check if station ID and station name are valid
bool WriteIntoStations(string stationID, string stationName, Dictionary<Station>* dic)
{
	// Check if station entered exists in the same line
	// If it doesnt, add the station at that ID
	// Else (it exists), return error message
	vector<Station>* stations = dic->getStations(stationName);
	if (stations->size() > 0) // station exists, so check if the line already exists (cannot add station of same name on same line)
	{
		for (int i = 0; i < stations->size(); i++)
		{
			if (stations->at(i).getLine() == stationID.substr(0, 2)) // station already exists on line
				return false;
		}
	}

	// Station does not exist on line yet
	// Check if stationID is not taken
	for (int i = 0; i < StationsList->size(); i++)
	{
		string str = StationsList->at(i); // this returns station code + name (e.g. DT2,Cashew)
		vector<string>* split = Split(str, ','); // Pass by value. No alteration to StationsList
		if (split->front() == stationID) // if the stationID user entered already exists, fail
			return false;
	}

	// Name and ID are available on that line, add into CSV files
	// Station dont need to be in order so can just add to the end
	// Routes need to be in order so must adjust
	// Interchanges also need
	string strToWrite = stationID + "," + stationName;
	WriteFile(StationsPath, strToWrite);

	return true;
}

// [3]
// Step 2, writing into routes
bool WriteIntoRoutes(string stationID, string dist)
{
	vector<string> stationIDVector, distanceVector;
	int rowNumber = 0;
	string stationIDString, distanceString;

	for (int i = 0; i < RoutesList->size(); i++) {
		string row = RoutesList->at(i);

		// Getting the stationID row
		if (i % 2 == 0) {
			stringstream ss(row);

			// Get the prefix of the SECOND element in the routes list, and then compares it to the prefix of the one we want to add
			if (row.substr(row.find(",") + 1, 2) == stationID.substr(0, 2)) {
				// Retrieve all stationIDs of the row here
				while (ss.good())
				{
					string substr;
					getline(ss, substr, ',');
					stationIDVector.push_back(substr); // stationIDVector contains every stationID in the row (e.g. EW1, EW2, EW3...)
					rowNumber = i;
				}
			}
		}
	}

	// Getting a vector of distance strings
	stringstream ss(RoutesList->at(rowNumber + 1));
	while (ss.good())
	{
		string substr;
		getline(ss, substr, ',');
		distanceVector.push_back(substr); // distanceVector contains the distances corresponding to stationIDVector
	}

	// Compare the numbers here
	for (int i = 0; i < stationIDVector.size(); i++) {
		int stationIDNumber;

		if (stationIDVector.at(i).length() > 2)
			stationIDNumber = stoi(stationIDVector.at(i).substr(2, 2));
		else
			stationIDNumber = 0;

		// If station ID number is greater than that of the one you're adding (e.g. EW14 > EW12)
		// insert our new stationID inside the stationIDVector at the current position
		// Available range here: First number until (last - 1)
		if (stationIDNumber > stoi(stationID.substr(2, 2))) {
			stationIDVector.insert(stationIDVector.begin() + i, stationID);

			// Calculate the distances here!!!
			// Check if it is not the first number
			// Deduct the distance from the previous position
			if (i != 0)
				distanceVector.at(i - 1) = to_string(stoi(distanceVector.at(i - 1)) - stoi(dist));

			// insert our distance in this current position
			distanceVector.insert(distanceVector.begin() + i, dist);

			break;
		}

		// Check if it is the last number
		if (i == stationIDVector.size() - 1 && stationIDNumber < stoi(stationID.substr(2, 2))) {
			stationIDVector.push_back(stationID);

			// Calculate the distance between our current station ID and the previous station ID
			distanceVector.at(i - 1) = to_string(stoi(distanceVector.at(i - 1)) - stoi(dist));
			distanceVector.insert(distanceVector.begin() + i, dist);
			break;
		}
	}

	for (int i = 0; i < stationIDVector.size(); i++) {
		//cout << stationIDVector.at(i) << endl;
		stationIDString.append(stationIDVector.at(i) + ",");
	}
	for (int i = 0; i < distanceVector.size(); i++) {
		//cout << distanceVector.at(i) << endl;
		distanceString.append(distanceVector.at(i) + ",");
	}
	stationIDString.pop_back();
	distanceString.pop_back();

	cout << stationIDString << endl;
	cout << distanceString << endl;

	// Convert our vector into a string & write into file
	WriteFile(RoutesPath, stationIDString, rowNumber);
	WriteFile(RoutesPath, distanceString, rowNumber + 1);

	return false;
}

// [3]
// Step 3, writing into interchanges
void WriteIntoInterchanges(string stationID, string stationName, Dictionary<Station>* dic) // step 3
{
	string interchangeString;
	int rowNumber;

	// Check (INTERCHANGE)
	// 1. If the station is located at an interchange, i.e. if there is a station with the same name located on different lines
	vector<Station>* stations = dic->getStations(stationName);
	if (stations->size() >= 0)
	{
		// Store all the stations into a string
		for (int i = 0; i < stations->size(); i++) {
			interchangeString.append(stations->at(i).getStationID() + ",");
		}

		// If it is a new interchange
		if (stations->size() < 2) {
			int i = 0;
			while (i != stations->size()) {
				// write to Interchange.csv
				interchangeString.append(stationID);

				WriteFile(InterchangesPath, interchangeString);
				break;
			}
			i++;
		}
		// If the interchange already exists in the file
		else {
			for (int i = 0; i < stations->size(); i++) {
				string row = InterchangesList->at(i);
				if ((stations->at(i).getStationID()).find(row.substr(0, 4))) {
					WriteFile(InterchangesPath, interchangeString, i);
				}
			}
		}
	}
	else
		cout << stationName << " will not be an interchange" << endl;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// [3] Adding a new station to dictionary
bool AddNewStation(string stationID, string stationName, string distToNext, Dictionary<Station>* dic)
{
	if (WriteIntoStations(stationID, stationName, dic))
	{
		WriteIntoRoutes(stationID, distToNext);
		WriteIntoInterchanges(stationID, stationName, dic);
	}
	else
		return false;
}

void InitDictionary()
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
				linesDict->add(line, LineStationsList);

			line = currentLine;
			LineStationsList = vector<string>();
		}

		LineStationsList.push_back(currentStationName);

		//cout << "stationID = " << currentStationID << endl;
		//cout << "stationName = " << currentStationName << endl;

		dic->add(currentStationName, currentStationID, GetDistance(currentStationID));
		//cout << "added to dic" << endl;
	}
}

void CalculateThreeRoutes(string source, string destination)
{
	//trimAll(&source);
	//trimAll(&destination);

	vector<vector<Station>*>* routesList = new vector<vector<Station>*>();
	vector<Station>* firstRoute = new vector<Station>();
	Station* front = dic->get(source);
	firstRoute->push_back(*front);
	routesList->push_back(firstRoute);

	CheckStation(0, source, destination, routesList);
	cout << endl;
	/*
	1. get source and destination
	2. Literally recurse through every station starting from source
	3. if station is interchange, branch off (another loop in that direction)
	4. with each station youre at, update a dictionary(?) of stations chained together
	*/
}

vector<vector<Station>*>* CheckStation(int routeNum, string source, string destination,
	vector<vector<Station>*>* routesList)
{
	int count = 0;
	for (int i = 0; i < routesList->size(); i++) // checking how many of the routes so far has reached its destination
	{
		if (routesList->at(i)->front().getStationName() == source &&
			routesList->at(i)->back().getStationName() == destination)
			count++;
	}
	if (count >= 3) // Success condition
		return routesList;
	else // still havent 3 routes
	{
		vector<string>* connections = getConnections(source);
		if (connections != NULL)
		{
			for (int i = 0; i < connections->size(); i++) // removes the last visited station from connections
			{
				if (connections->at(i) == routesList->at(routeNum)->back().getStationName())
				{
					connections->erase(connections->begin() + i);
					continue;
				}
			}
			for (int i = 0; i < connections->size(); i++)
			{
				vector<Station>* stations = dic->getStations(connections->at(i));
				for (int j = 0; j < stations->size(); j++) // if this connection im checking is on my current route's line
				{
					//Station* newStation = &stations->front();

					Station* newStation = NULL;
					for (int l = 0; l < stations->size(); l++)
					{
						vector<Station>* st = dic->getStations(source);
						for (int m = 0; m < st->size(); m++)
						{
							if (stations->at(l).getLine() == st->at(m).getLine().substr(0, 2))
								newStation = &stations->front();
						}
					}
					routesList->at(routeNum)->push_back(*newStation);
					if (stations->at(j).getLine() == dic->get(source)->getLine())
						CheckStation(routeNum, connections->at(i), destination, routesList);
					else // create new route. While doing so, copy current route path to new route.
					{
						vector<Station>* newRoute = new vector<Station>();
						for (int k = 0; k < routesList->at(routeNum)->size(); k++) //copyign current path to new path
							newRoute->push_back(routesList->at(routeNum)->at(k));

						CheckStation(routesList->size() - 1, connections->at(i), destination, routesList);
					}
				}
			}
		}
	}
	// check if routesList has 3 complete routes. (get front and back)
	// if yes,
		//return routesList

	//else
		//if source NOT interchange,
			//

		//else (is interchange)
			// create new vector<station> and copy current route's statoins into the new one.
			// parse new
}

vector<string>* getConnections(string stationName)
{
	vector<Station>* stations = dic->getStations(stationName);
	vector<string>* connections = new vector<string>();
	if (stations->size() > 0)
	{
		for (int i = 0; i < stations->size(); i++)
		{
			string line = stations->at(i).getLine();
			vector<string>* lineVec = linesDict->get(line);
			for (int j = 0; j < lineVec->size(); j++)
			{
				if (lineVec->at(j) == stationName)
				{
					if ((j - 1 >= 0) && (j + 1 < lineVec->size()))
					{
						connections->push_back(lineVec->at(j - 1));
						connections->push_back(lineVec->at(j + 1));
					}
					else
					{
						if (j - 1 <= 0) // if station is the first one, just add the second name
							connections->push_back(lineVec->at(j + 1));
						if (j + 1 >= lineVec->size()) //if station is the last one, just add the second last name
							connections->push_back(lineVec->at(j - 1));
					}
				}
			}
		}
		return connections;
	}
	return NULL;
}

void init()
{
	FaresList = new vector<string>();
	InterchangesList = new vector<string>();
	RoutesList = new vector<string>();
	StationsList = new vector<string>();
	LineList = new vector<string>();
	dic = new Dictionary<Station>();
	linesDict = new ListDictionary<string>();

	if (!ReadFile(FaresPath, FaresList))
		cout << "Error init Fares..." << endl;
	if (!ReadFile(InterchangesPath, InterchangesList))
		cout << "Error init Interchanges..." << endl;
	if (!ReadFile(RoutesPath, RoutesList))
		cout << "Error init Routes..." << endl;
	if (!ReadFile(StationsPath, StationsList))
		cout << "Error init Stations..." << endl;

	// Adding all prefixes to LineList ("EW","NS",...)
	for (int i = 0; i < RoutesList->size(); i++) {
		// Read every alternate row
		if (i % 2 == 0) {
			string row = RoutesList->at(i);
			LineList->push_back(row.substr(row.find(",") + 1, 2));
		}
	}
}


	for (int i = 0; i < StationsList->size(); i++) {
		if ((StationsList->at(i)).find(splitList->at(0)) != -1)
			cout << StationsList->at(i) << endl;
	}

	cout << endl;
}
