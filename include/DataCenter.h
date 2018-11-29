/*
Damon Morey, Philip Prater, Samuel Shippey, Son Vu, Yves Wienecke 2018©
DataCenter.h
Includes:
	Member class definition
	Provider class definition
	DataCenter class definition
*/

#include "defs.h"

//TODO: Write copy constructors if needed

class Member {
	public:
		Member();
		Member(string, string, address &);
		~Member();
		virtual void addService(Service & service);
		bool operator<(const Member & member) const;
		bool operator==(const Member & member) const;
		virtual void clearServices();
	protected:
		string name;
		string phoneNumber;
		address fullAddress;
		vector<Service> servicesList;
};

class Provider : public Member{
	public:
		Provider();
    Provider(string, string, address &);
		~Provider();
		void addService(Service & service);
		bool operator<(const Provider & Provider) const;
		bool operator==(const Provider & Provider) const;
		void clearServices();
	protected:
		unsigned int totalConsultations;
		double totalFee;
};

class Service {
	public:
		Service();
		Service(Provider*, Member*, string, double);
		~Service();
		double getFee();
		bool operator<(const Service & service) const;
		bool operator==(const Service & service) const;
	protected:
		// Although there are indeed a pair of pointers in here,
		// we need them to be shallow copied if they're copied
		// (as they point to pre-existing members and providers)
		// and thus no copy constructor is provided
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
		void addService(const Service & service);
		void addProvider(const Provider & provider);
		void addMember(const Member & member);
		// TODO: untested
		bool hasService(string);
		// TODO: unimplemented
		bool hasMember(string);
		bool hasProvider(string);
		void removeService(string);
		bool modifyService(string);
		void removeMember(string);
		void removeProvider(string);
	protected:
		set<Service> serviceSet;
		set<Member> memberSet;
		set<Provider> providerSet;

    address nullAdr;
};
