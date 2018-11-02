/*
Damon Morey, Philip Prater, Samuel Shippey, Son Vu, Yves Wienecke 2018©
DataCenter.h
Includes:
	Member class definition
	Provider class definition
	DataCenter class definition
*/

#include "defs.h"
#include <string>
#include <vector>

struct address{
	string streetAddress;
	string city;
	string state;
	string zip;
};

class Member {
	public:
		Member();
		~Member();
	protected:
		string name;
		string phoneNumber;
		address fullAddress;
		vector<Service> servicesList;
};

class Provider {
	public:
		Provider();
		~Provider();
	protected:
		string name;
		string phoneNumber;
		address fullAddress;
		unsigned int totalConsultations;
		unsigned double totalFee;
		vector<Service> servicesList;
};

class Service {
	public:
		Service();
		~Service();
	protected:
		Provider *provider;
		Member *member;
		string serviceCode;
		unsigned double fee;
		//find good ways to put in dates	
};
