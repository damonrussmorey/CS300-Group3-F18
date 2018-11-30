/*
   Damon Morey, Philip Prater, Samuel Shippey, Son Vu, Yves Wienecke 2018©
   DataCenter.cpp
   */

#include "DataCenter.h"

//Address
address::address() {}

// Member
Member::Member(string n, string number, address & ad) {
	name = n;
	phoneNumber = number;
	fullAddress.streetAddress = ad.streetAddress;
	fullAddress.city = ad.city;
	fullAddress.state = ad.state;
	fullAddress.zip = ad.zip;
  status = true;
}

Member::Member(){}
Member::~Member(){}

void Member::consultation(Service & service) {
	weeklyConsultations.push_back(service);
}

void Member::clear() {
	weeklyConsultations.clear();
}

// Provider
Provider::Provider(string n, string number, address & ad, double f) {
	name = n;
	phoneNumber = number;
	fullAddress.streetAddress = ad.streetAddress;
	fullAddress.city = ad.city;
	fullAddress.state = ad.state;
	fullAddress.zip = ad.zip;
	weeklyConsultationFees = f;
}

Provider::Provider(){}
Provider::~Provider(){}

void Provider::consultation(Service & service) {
	// Went with the running total thing, seemed simpler. 
	// Didn't call parent function cause no reason to go adding more overhead.
	weeklyConsultations.push_back(service);
	weeklyConsultationFees += service.fee;
}

void Provider::clear() {
	weeklyConsultations.clear();
	weeklyConsultationFees = 0;
}

// Service
Service::Service(string code, double f) {
	serviceCode = code;
	fee = f;
	provider = NULL;
	member = NULL;
	date = NULL;
}

Service::Service(const Service &s, const Member *m, const Provider *p) {
	fee = s.fee;
	serviceCode = s.serviceCode;
	provider = p;
	member = m;
	time_t t;
	time(&t);
	date = localtime(&t);
}

Service::Service(){}
Service::~Service(){}

// Data Center
DataCenter::DataCenter() {
	//load data from files
	//TODO
	activeMemberCount = 0;
	weeklyConsultationCount = 0;
	weeklyConsultationFees = 0.0;
}

DataCenter::~DataCenter() {
	//clean up dynamic data
	//afaik, we don't have any, but then again we may be managing memory incorrectly
	//keep this in mind
	//c++ containers automatically manager their memory
	//adding to the container copies the object
	//because our objects are very small, this is absolutely fine
}


bool DataCenter::confirmConsultation(string memberName, string providerName, string serviceCode) {
  try{
    //get the member, provider, and service
    Member &m = memberMap.at(memberName);
    Provider &p = providerMap.at(providerName);
    Service &s = serviceMap.at(serviceCode);

    //create consultaton for reporting
    Service c(s, &m, &p);

    //give to member and provider
    m.consultation(c);
    p.consultation(c);

    //record fee for manager
    ++weeklyConsultationCount;
    weeklyConsultationFees += c.fee;

    return true;

  } catch(const out_of_range &) {
    return false;
  }
}

//clears all consultations for the week
void DataCenter::newWeek() {
  weeklyConsultationCount = 0;
  weeklyConsultationFees = 0.0;
  for(auto x = memberMap.begin(); x != memberMap.end(); ++x)
    x->second.clear();
  for(auto x = providerMap.begin(); x != providerMap.end(); ++x)
    x->second.clear();
}

void DataCenter::addService(Service & service) {
	serviceMap[service.serviceCode] = service;
}

void DataCenter::addProvider(Provider & provider) {
	providerMap[provider.name] = provider;
}

void DataCenter::addMember(Member & member) {
	memberMap[member.name] = member;
  if(member.status)
    ++activeMemberCount;
}

void DataCenter::removeService(string serviceCode) {
  serviceMap.erase(serviceCode);
}

void DataCenter::removeProvider(string providerName) {
  providerMap.erase(providerName);
}

void DataCenter::removeMember(string memberName) {
  try {
    if(memberMap.at(memberName).status)
      --activeMemberCount;
  } catch(const out_of_range &e) {
    return;
  }
  memberMap.erase(memberName);
}

bool DataCenter::hasService(string serviceCode) {
  try {
    serviceMap.at(serviceCode);
    return true;
  } catch(const out_of_range &e) {
    return false;
  }
}

bool DataCenter::hasMember(string memberName) {
  try {
    memberMap.at(memberName);
    return true;
  } catch(const out_of_range &e) {
    return false;
  }
}

bool DataCenter::hasProvider(string providerName) {
  try {
    providerMap.at(providerName);
    return true;
  } catch(const out_of_range &e) {
    return false;
  }
}
