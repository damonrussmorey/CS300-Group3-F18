/*
Damon Morey, Philip Prater, Samuel Shippey, Son Vu, Yves Wienecke 2018©
defs.h

Definitions for common structures and libraries for the entire project
*/

//Standard Library Includes
#include <string>
#include <vector>
#include <map>
#include <cassert>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <regex>

#define MEMBERSHIP_FEE 45.99
#define BASE_CONSULTATION_FEE 120.00
#define PROVIDER_DIRECTORY "../stash/provider_directory.txt"
#define PROVIDERS "../stash/providers.txt"
#define MEMBERS "../stash/members.txt"
#define REPORTS "../stash/reports.txt"

using namespace std;

//helper readers
int getOption(string prompt, int lower, int upper);
string getString(string prompt);
void clear();

struct address {
  address();
	string streetAddress;
	string city;
	string state;
	string zip;
};

class Service;
class Member;
class Provider;
class DataCenter;
class ManagerTerminal;
class ProviderTerminal;
