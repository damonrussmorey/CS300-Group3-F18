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

void Member::consultation(Service & service) {
	weeklyConsultations.push_back(service);
}

bool Member::operator<(const Member & member) const {
	return (member.name > name ? true : false);
}

bool Member::operator==(const Member & member) const {
	return member.name == name;
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

Provider::~Provider(){}

void Provider::consultation(Service & service) {
	// Went with the running total thing, seemed simpler. 
	// Didn't call parent function cause no reason to go adding more overhead.
	weeklyConsultations.push_back(service);
	weeklyConsultationFees += service.fee;
}

bool Provider::operator<(const Provider & provider) const {
	return (provider.name > name ? true : false);
}

bool Provider::operator==(const Provider & provider) const {
	return provider.name == name;
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

Service::~Service() {}

bool Service::operator<(const Service & service) const {
	return (service.serviceCode > serviceCode ? true : false);
}

bool Service::operator==(const Service & service) const {
	return service.serviceCode == serviceCode;
}

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
  //get the member, provider, and service
  set<Member>::iterator mi = memberSet.find(Member(memberName, NULL, nullAdr));
  if(mi == memberSet.end())
    return false;
  set<Provider>::iterator pi = providerSet.find(Provider(providerName, NULL, nullAdr, 0));
  if(pi == providerSet.end())
    return false;
  set<Service>::iterator si = serviceSet.find(Service(serviceCode, 0));
  if(si == serviceSet.end())
    return false;

  //workaround to constness - remove from set
  Member m = *mi;
  memberSet.erase(mi);
  Provider p = *pi;
  providerSet.erase(pi);
  Service s = *si;
  serviceSet.erase(si);

  //create consultaton for reporting
  Service c = Service(s, &m, &p);

  //give to member and provider
  m.consultation(c);
  p.consultation(c);

  //record fee for manager
  ++weeklyConsultationCount;
  weeklyConsultationFees += c.fee;

  return true;
}

//clears all consultations for the week
void DataCenter::newWeek() {
  weeklyConsultationCount = 0;
  weeklyConsultationFees = 0.0;
  /*TODO
  for(set<Member>::iterator x = memberSet.begin(); x != memberSet.end(); ++x)
    x->clear();
  for(set<Provider>::iterator x = providerSet.begin(); x != providerSet.end(); ++x)
    x->clear();
    */
}

void DataCenter::addService(Service & service) {
	serviceSet.insert(service);
}

void DataCenter::addProvider(Provider & provider) {
	providerSet.insert(provider);
}

void DataCenter::addMember(Member & member) {
	memberSet.insert(member);
  ++activeMemberCount;
}

void DataCenter::removeService(string serviceCode) {
	serviceSet.erase(serviceSet.find(
        Service(serviceCode, 0)));
}

void DataCenter::removeProvider(string providerName) {
	providerSet.erase(providerSet.find(
        Provider(providerName, NULL, nullAdr, 0)));
}

void DataCenter::removeMember(string memberName) {
  unsigned int c = memberSet.size();
	memberSet.erase(memberSet.find(
        Member(memberName, NULL, nullAdr)));
  if(c != memberSet.size())
    --activeMemberCount;
}

bool DataCenter::hasService(string serviceCode) {
	return serviceSet.find(
      Service(serviceCode, 0)) != serviceSet.end();
}

bool DataCenter::hasMember(string memberName) {
	return memberSet.find(
      Member(memberName, NULL, nullAdr)) != memberSet.end();
}

bool DataCenter::hasProvider(string providerName) {
  return providerSet.find(
      Provider(providerName, NULL, nullAdr, 0)) != providerSet.end();
}

// Dummy main
// Should ideally be moved elsewhere I think
// - Sam
/*int main(){
	return 1;
}*/
