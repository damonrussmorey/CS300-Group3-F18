/*
Damon Morey, Philip Prater, Samuel Shippey, Son Vu, Yves Wienecke 2018©
DataCenter.h
Includes:
	Member class definition
	Provider class definition
	DataCenter class definition
*/

#include "defs.h"

class Member {
	public:
		Member();
		~Member();
		virtual void addService(Service * service);
	protected:
		string name;
		string phoneNumber;
		address fullAddress;
		vector<Service*> servicesList;
		// This is a pointer because the services should come from a services list
		// If a service is updated, it'll be updated here, too
};

class Provider : public Member{
	public:
		Provider();
		~Provider();
		void addService(Service * service);
	protected:
		unsigned int totalConsultations;
		double totalFee;
};

class Service {
	public:
		Service();
		~Service();
		// Although there are indeed a pair of pointers in here,
		// we need them to be shallow copied if they're copied
		// (as they point to pre-existing members and providers)
		// and thus no copy constructor is provided
		double getFee();
	protected:
		Provider *provider;
		Member *member;
		string serviceCode;
		double fee;
		//find good ways to put in dates	
};

class DataCenter {
	public:
		DataCenter();
		~DataCenter();
	protected:
		// memberSet
		// providerSet
		// servicesSet
};

