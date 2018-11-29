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
}

Member::Member(){}
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
Provider::Provider(string n, string number, address & ad, int total, double f) {
	name = n;
	phoneNumber = number;
	fullAddress.streetAddress = ad.streetAddress;
	fullAddress.city = ad.city;
	fullAddress.state = ad.state;
	fullAddress.zip = ad.zip;
	totalConsultations = total;
	totalFee = f;
}

Provider::~Provider(){}

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
	serviceSet.insert(service);
}

void DataCenter::addProvider(const Provider & provider) {
	providerSet.insert(provider);
}

void DataCenter::addMember(const Member & member) {
	memberSet.insert(member);
}

void DataCenter::removeService(string serviceCode) {
	serviceSet.erase(serviceSet.find(
        Service(NULL, NULL, serviceCode, 0)));
}

void DataCenter::removeProvider(string providerName) {
	providerSet.erase(providerSet.find(
        Provider(providerName, NULL, nullAdr, 0, 0)));
}

void DataCenter::removeMember(string memberName) {
	memberSet.erase(memberSet.find(
        Member(memberName, NULL, nullAdr)));
}

bool DataCenter::hasService(string serviceCode) {
	return serviceSet.find(
      Service(NULL, NULL, serviceCode, 0)) != serviceSet.end();
}

bool DataCenter::hasMember(string memberName) {
	return memberSet.find(
      Member(memberName, NULL, nullAdr)) != memberSet.end();
}

bool DataCenter::hasProvider(string providerName) {
  return providerSet.find(
      Provider(providerName, NULL, nullAdr, 0, 0)) != providerSet.end();
}

// Dummy main
// Should ideally be moved elsewhere I think
// - Sam
int main(){
	return 1;
}
