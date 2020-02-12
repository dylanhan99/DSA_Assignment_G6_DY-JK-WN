#pragma once
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <string>
using namespace std;

// Han Wei Dylan
// 10178483G
// Group 6
// trim whitespace from start of string
static inline string &ltrim(string &s) {
	s.erase(s.begin(), find_if(s.begin(), s.end(),
		not1(ptr_fun<int, int>(isspace))));
	return s;
}

// Han Wei Dylan
// 10178483G
// Group 6
// trim whitespace from end of string
static inline string &rtrim(string &s) {
	s.erase(find_if(s.rbegin(), s.rend(),
		not1(ptr_fun<int, int>(isspace))).base(), s.end());
	return s;
}

// Han Wei Dylan
// 10178483G
// Group 6
// Trim function. Used to trim off white space at 
// the beginning and end of string.
static string trim(string str)
{
	return ltrim(rtrim(str));
}

// Han Wei Dylan
// 10178483G
// Group 6
// Remove all white space in string
static void trimAll(string* str)
{
	str->erase(remove_if(str->begin(), str->end(), isspace), str->end());
}

//Remove white space and convert to lower case.
static void trimAllLower(string* str)
{
	trimAll(str);
	for (int i = 0; i < str->length(); i++)
		str[i] = tolower(str->at(i));
}

// Han Wei Dylan
// 10178483G
// Group 6
// Get the Line prefix from string.
// Does this by getting all the alphabets from the string until
// reaching a non-alphabet.
// eg. GetLine("EW24") = "EW"
// eg. GetLine("MyLinePrefix8899") = "MyLinePrefix"
static string GetLine(string str)
{
	string returnString = "";
	for (int i = 0; i < str.length(); i++)
	{
		if (isalpha(str[i]))
			returnString += str[i];
		// If not char, break
		else
			break;
	}
	return returnString;
}

// Han Wei Dylan
// 10178483G
// Group 6
// Get the station ID from the entered string
// eg. GetNum("EW24") = 24
// eg. GetNum("qwErT9009") = 9009
static string GetNum(string str)
{
	string line = GetLine(str);
	return str.substr(line.length(), str.length() - 1);
}