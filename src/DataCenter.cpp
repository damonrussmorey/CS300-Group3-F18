/*
Damon Morey, Philip Prater, Samuel Shippey, Son Vu, Yves Wienecke 2018©
DataCenter.cpp
*/

#include "DataCenter.h"

void Member::addService(Service * service) {
	servicesList.push_back(service);
}

void Provider::addService(Service * service) {
	// Went with the running total thing, seemed simpler. 
	// Didn't call parent function cause no reason to go adding more overhead.
	servicesList.push_back(service);
	++totalConsultations;
	totalFee += service->getFee();
}

double Service::getFee() {
	return fee;
}

// Dummy main
// Should ideally be moved elsewhere I think
// - Sam
int main(){
	return 1;
}
