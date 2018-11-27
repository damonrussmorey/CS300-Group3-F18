/*
Damon Morey, Philip Prater, Samuel Shippey, Son Vu, Yves Wienecke 2018©
DataCenter.cpp
*/

#include "DataCenter.h"

// Member
Member::Member(string n, string number, address & ad) {
	name = n;
	phoneNumber = number;
	fullAddress.streetAddress = ad.streetAddress;
	fullAddress.city = ad.city;
	fullAddress.state = ad.state;
	fullAddress.zip = ad.zip;
}

Member::~Member(){}

void Member::addService(Service & service) {
	servicesList.push_back(service);
}

bool Member::operator<(const Member & member) const {
	return (member.name > name ? true : false);
}

bool Member::operator==(const Member & member) const {
	return member.name == name;
}

void Member::clearServices() {
	servicesList.clear();
}

// Provider
void Provider::addService(Service & service) {
	// Went with the running total thing, seemed simpler. 
	// Didn't call parent function cause no reason to go adding more overhead.
	servicesList.push_back(service);
	++totalConsultations;
	totalFee += service.getFee();
}

bool Provider::operator<(const Provider & provider) const {
	return (provider.name > name ? true : false);
}

bool Provider::operator==(const Provider & provider) const {
	return provider.name == name;
}

void Provider::clearServices() {
	servicesList.clear();
	totalConsultations = 0;
	totalFee = 0;
}

// Service
Service::Service(Provider *p, Member *m, string code, double f) {
	provider = p;
	member = m;
	serviceCode = code;
	fee = f;
}

Service::~Service() {}

double Service::getFee() {
	return fee;
}

bool Service::operator<(const Service & service) const {
	return (service.serviceCode > serviceCode ? true : false);
}

bool Service::operator==(const Service & service) const {
	return service.serviceCode == serviceCode;
}

// Data Center
void DataCenter::addService(const Service & service) {
	servicesSet.insert(service);
}

void DataCenter::addProvider(const Provider & provider) {
	providerSet.insert(provider);
}

void DataCenter::addMember(const Member & member) {
	membersSet.insert(member);
}

bool DataCenter::hasService(string serviceCode) {
	Service searchService(NULL, NULL, serviceCode, 0);
	return servicesSet.find(searchService) != servicesSet.end();
}

bool DataCenter::hasMember(string name) {
	address dummyAddress;
	Member searchMember(name, "dummy", dummyAddress);
	return membersSet.find(searchMember) != membersSet.end();
}

// Dummy main
// Should ideally be moved elsewhere I think
// - Sam
int main(){
	return 1;
}
