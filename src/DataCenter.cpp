/*
Damon Morey, Philip Prater, Samuel Shippey, Son Vu, Yves Wienecke 2018©
DataCenter.cpp
*/

#include "DataCenter.h"

// Member
void Member::addService(Service service) {
	servicesList.push_back(service);
}

bool Member::operator<(const Member & member) const {
	return (member.name > name ? true : false);
}

void Member::clearServices() {
	servicesList.clear();
}

// Provider
void Provider::addService(Service service) {
	// Went with the running total thing, seemed simpler. 
	// Didn't call parent function cause no reason to go adding more overhead.
	servicesList.push_back(service);
	++totalConsultations;
	totalFee += service.getFee();
}

bool Provider::operator<(const Provider & provider) const {
	return (provider.name > name ? true : false);
}

void Provider::clearServices() {
	servicesList.clear();
	totalConsultations = 0;
	totalFee = 0;
}

// Service

Service::~Service() {}

double Service::getFee() {
	return fee;
}

bool Service::operator<(const Service & service) const {
	return (service.serviceCode > serviceCode ? true : false);
}

// Data Center
void DataCenter::addService(const Service & service) {
	servicesSet.insert(service);
}

void DataCenter::addProvider(const Provider & provider) {
	providerSet.insert(provider);
}

// Dummy main
// Should ideally be moved elsewhere I think
// - Sam
int main(){
	return 1;
}
