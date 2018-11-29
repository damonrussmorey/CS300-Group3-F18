/*
Damon Morey, Philip Prater, Samuel Shippey, Son Vu, Yves Wienecke 2018©
defs.h

Definitions for common structures and libraries for the entire project
*/

//Standard Library Includes

#include <string>
#include <vector>
#include <set>
#include <cassert>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>

#define MEMBERSHIP_FEE 45.99
#define BASE_CONSULTATION_FEE 120.00

using namespace std;

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


const int MAIN_MENU_OPTIONS = 4;
