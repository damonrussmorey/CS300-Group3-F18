/*
Damon Morey, Philip Prater, Samuel Shippey, Son Vu, Yves Wienecke 2018©
defs.h

Definitions for common structures and libraries for the entire project
*/

//Standard Library Includes

#include <string>
#include <vector>

using namespace std;

struct address{
	string streetAddress;
	string city;
	string state;
	string zip;
};

class Service;
class Member;
class Provider;
class DataCenter;
