#pragma once
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <string>
using namespace std;

// trim from start
static inline string &ltrim(string &s) {
	s.erase(s.begin(), find_if(s.begin(), s.end(),
		not1(ptr_fun<int, int>(isspace))));
	return s;
}

// trim from end
static inline string &rtrim(string &s) {
	s.erase(find_if(s.rbegin(), s.rend(),
		not1(ptr_fun<int, int>(isspace))).base(), s.end());
	return s;
}

// Trim function. Used to trim off white space at 
// the beginning and end of string.
static string trim(string str)
{
	return ltrim(rtrim(str));
}

// Remove all white space in string
static void trimAll(string* str)
{
	str->erase(remove_if(str->begin(), str->end(), isspace), str->end());
}