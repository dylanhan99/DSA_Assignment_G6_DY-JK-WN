// DSA_Assignment_G6_DY-JK-WN.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>;
#include <fstream>
using namespace std;

#include "List.h"

bool ReadFile(string filename, List* outList)
{
	string line;
	ifstream myfile(filename);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
			outList->add(line);
		myfile.close();
		return true;
	}

	else
	{
		cout << "Unable to open file";
		return false;
	}
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
		return number_of_lines;
	}
	else
	{
		cout << "Unable to open file";
		return -1;
	}
}



int main()
{
	string DYmainpath = "C:\\Users\\HanWei\\Desktop\\NP stuff\\Year_3-2_FINAL\\DSA\\!Assignment\\";
	string JKmainpath = "";
	string WNmainpath = "";
	string full_simple = "full\\";

	string FaresPath		= DYmainpath + full_simple + "Fares.csv";
	string InterchangesPath = DYmainpath + full_simple + "Interchanges.csv";
	string RoutesPath		= DYmainpath + full_simple + "Routes.csv";
	string StationsPath		= DYmainpath + full_simple + "Stations.csv";

	List* FaresList			= new List(CountFileLines(FaresPath));
	List* InterchangesList	= new List(CountFileLines(InterchangesPath));
	List* RoutesList		= new List(CountFileLines(RoutesPath));
	List* StationsList		= new List(CountFileLines(StationsPath));

	if (ReadFile(FaresPath, FaresList))
		cout << "Fares success..." << endl;
	if (ReadFile(InterchangesPath, InterchangesList))
		cout << "Interchanges success..." << endl;
	if (ReadFile(RoutesPath, RoutesList))
		cout << "Routes success..." << endl;
	if (ReadFile(StationsPath, StationsList))
		cout << "Stations success..." << endl;


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

		switch (option)
		{
		case 0:
			break;
		case 1:
			break;
		case 2:
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

