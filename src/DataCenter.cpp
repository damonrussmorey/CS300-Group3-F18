/*
   Damon Morey, Philip Prater, Samuel Shippey, Son Vu, Yves Wienecke 2018©
   DataCenter.cpp
   */

#include "DataCenter.h"

//Address
address::address() {}

// Member constructor
Member::Member(string n, string number, string phone, address & ad) {
	name = n;
	phoneNumber = phone;
    memberNumber = number;
	fullAddress.streetAddress = ad.streetAddress;
	fullAddress.city = ad.city;
	fullAddress.state = ad.state;
	fullAddress.zip = ad.zip;
  status = true;
}

Member::Member(){}
Member::~Member(){}

//add new consultation to member
void Member::consultation(Service & service) {
	weeklyConsultations.push_back(service);
}

//clear member's list of consulations
void Member::clear() {
	weeklyConsultations.clear();
}

// Provider constructor
Provider::Provider(string n, string number, string phone, address & ad, double f) {
	name = n;
    memberNumber = number;
	phoneNumber = phone;
	fullAddress.streetAddress = ad.streetAddress;
	fullAddress.city = ad.city;
	fullAddress.state = ad.state;
	fullAddress.zip = ad.zip;
	weeklyConsultationFees = f;
}

Provider::Provider(){}
Provider::~Provider(){}

//add consultation to provider
void Provider::consultation(Service & service) {
	// Went with the running total thing, seemed simpler. 
	// Didn't call parent function cause no reason to go adding more overhead.
	weeklyConsultations.push_back(service);
	weeklyConsultationFees += service.fee;
}

//remove all consultations in provider
void Provider::clear() {
	weeklyConsultations.clear();
	weeklyConsultationFees = 0;
}

// Service constructor for datacenter
Service::Service(string code, string name, double f) {
	serviceCode = code;
    serviceName = name;
	fee = f;
	provider = NULL;
	member = NULL;
}

// Service constructor for members and providers
Service::Service(const Service &s, const Member *m, const Provider *p, string dateProvided) {
  stringstream ss;
  tm *timeinfo;
	time_t t;

	fee = s.fee;
	serviceCode = s.serviceCode;
  serviceName = s.serviceName;
	provider = p;
	member = m;
  this->dateProvided = s.dateProvided;

  //record now as the date entered
  //schould have used date format function strftime
	time(&t);
  timeinfo = localtime(&t);
  ss << timeinfo->tm_mon << '-' << timeinfo->tm_mday << '-' << timeinfo->tm_year+1900 << ' ' << timeinfo->tm_hour << ':' << timeinfo->tm_min << ':' << timeinfo->tm_sec;
  dateEntered = ss.str();
}

Service::Service(){}
Service::~Service(){}

// Data Center
DataCenter::DataCenter() {
	//load data from files
    if (loadServices(PROVIDER_DIRECTORY)) {
        cout << "Successfully loaded services from disk\n";
    } else {
        cout << "Failed to load services from disk\n";
    }

    if (loadMembers(MEMBERS)) {
        cout << "Successfully members from disk\n";
    } else {
        cout << "Failed to load members from disk\n";
    }

    if (loadProviders(PROVIDERS)) {
        cout << "Successfully loaded providers from disk\n";
    } else {
        cout << "Failed to load providers from disk\n";
    }

    if (loadReports(REPORTS)) {
        cout << "Successfully loaded reports from disk\n";
    } else {
        cout << "Failed to load reports from disk\n";
    }

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

    // Save data to disk
    if (saveServices(PROVIDER_DIRECTORY)) {
        cout << "Successfully saved services from disk\n";
    } else {
        cout << "Failed to save services from disk\n";
    }

    if (saveMembers(MEMBERS)) {
        cout << "Successfully members from disk\n";
    } else {
        cout << "Failed to save members from disk\n";
    }

    if (saveProviders(PROVIDERS)) {
        cout << "Successfully saved providers from disk\n";
    } else {
        cout << "Failed to save providers from disk\n";
    }
    
    if (saveReports(REPORTS)) {
        cout << "Successfully saved reports from disk\n";
    } else {
        cout << "Failed to save reports from disk\n";
    }
}


bool DataCenter::confirmConsultation(string memberID, string providerID, string serviceCode, string dateProvided) {
  try{
    //get the member, provider, and service
    Member &m = memberMap.at(memberID);
    Provider &p = providerMap.at(providerID);
    Service &s = serviceMap.at(serviceCode);

    //create consultaton for reporting
    Service c(s, &m, &p, dateProvided);

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

//prints a list of services
//XXX should probably be given an output stream
void DataCenter::printServiceList() {
  cout << "Master Service List: (" << serviceMap.size() << ")" << endl;
  if(serviceMap.size() == 0) {
    cout << "No services available" << endl;
    return;
  }
  for(auto x = serviceMap.begin(); x != serviceMap.end(); ++x) {
      cout.precision(6);
      cout.fill('0');
      cout << x->second.serviceCode << " - " << x->second.serviceName << " $" << x->second.fee << endl;
  }
}

void DataCenter::printProviders() {
cout << "All Providers: (" << providerMap.size() << ")" << endl;
  if(providerMap.size() == 0) {
    cout << "No providers available" << endl;
    return;
  }
    for(auto x = providerMap.begin(); x != providerMap.end(); ++x) {
        cout << x->second.memberNumber << " - " <<x->second.name << endl;
    }

}

void DataCenter::printMembers() {
  cout << "All Members: (" << memberMap.size() << ")" << endl;
  if(memberMap.size() == 0) {
    cout << "No members available" << endl;
    return;
  }
    for(auto x = memberMap.begin(); x != memberMap.end(); ++x) {
        cout << x->second.memberNumber << " - " <<x->second.name;
        if(!x->second.status)
          cout << " (suspended)";
        cout << endl;
    }
}

void DataCenter::addService(Service & service) {
	serviceMap[service.serviceCode] = service;
}

// Loading from disk
bool DataCenter::loadServices(string fileName) {
    ifstream inFile;
    
    // Temporary vars to hold data from file
    Service temp; 
    string name, code, fee;

    // Setting max size for strings

    inFile.open(fileName);
    if (!inFile.is_open())
        return false;
    
    // Ignore the first line in the file
    getline(inFile, name);
    while (!getline(inFile, name, ';').eof()) {
        // service name;cost;code 
        getline(inFile, fee, ';');
        getline(inFile, code); 
        
        temp = Service(code, name, stof(fee));
        addService(temp);    
    }
   
    inFile.close();
    return true;
}


bool DataCenter::loadMembers(string fileName) {
    ifstream inFile;
    
    // Temporary vars to hold data from file
    Member temp; 
    string name, number, phone;
    address ad;

    inFile.open(fileName);
    if (!inFile.is_open())
        return false;
    
    while (!getline(inFile, name, ';').eof()) {
        // member name;number;phone;
        getline(inFile, number, ';');
        getline(inFile, phone, ';');

        // streetAddress;city;state;zip 
        getline(inFile, ad.streetAddress, ';'); 
        getline(inFile, ad.city, ';'); 
        getline(inFile, ad.state, ';'); 
        getline(inFile, ad.zip); 
        
        temp = Member(name, number, phone, ad); 
        addMember(temp);    
    }
   
    inFile.close();
    
    return true;
}

bool DataCenter::loadProviders(string fileName) {
    ifstream inFile;
    
    // Temporary vars to hold data from file
    Provider temp; 
    string name, number, phone, fees;
    address ad;

    inFile.open(fileName);
    if (!inFile.is_open())
        return false;
    
    while (!getline(inFile, name, ';').eof()) {
        // provider name;number;phone;
        getline(inFile, number, ';');
        getline(inFile, phone, ';');

        // streetAddress;city;state;zip;fees 
        getline(inFile, ad.streetAddress, ';'); 
        getline(inFile, ad.city, ';'); 
        getline(inFile, ad.state, ';'); 
        getline(inFile, ad.zip, ';'); 
        getline(inFile, fees);

        temp = Provider(name, number, phone, ad, stod(fees)); 
        cout << temp.name << ";" <<temp.memberNumber <<";"<< temp.phoneNumber << ";" <<
        temp.fullAddress.streetAddress << ";" << temp.fullAddress.city << ";" <<
        temp.fullAddress.state << ";" << temp.fullAddress.zip << ";" << temp.weeklyConsultationFees <<endl;

        addProvider(temp);    
    }
         
    inFile.close(); 
    return true;
}

bool DataCenter::loadReports(string fileName) {
    ifstream inFile;  
    
    // Temporary variables to read from file
    Provider * provider;
    Member * member;
    Service service;

    string providerID, memberID, serviceCode;
    string dateProvided, dateEntered;

    inFile.open(fileName);
    if (!inFile.is_open()) {
        return false;
    }
    
    // Read in reports from file
    while (!getline(inFile, providerID, ';').eof()) {
        getline(inFile, memberID, ';');
        getline(inFile, serviceCode, ';');
        getline(inFile, dateProvided, ';');
        getline(inFile, dateEntered);

        // Point to references of read in provider, member, service
        provider = &providerMap.at(providerID);
        member = &memberMap.at(memberID);

        service = Service(serviceMap.at(serviceCode));
        service.member = member;
        service.provider = provider;
        service.dateProvided = dateProvided;
        service.dateEntered = dateEntered; 
        // Add service to provider and member
        provider->consultation(service);
        member->consultation(service); 
    }

    inFile.close();
    return true;
}

// Dave data to disk
bool DataCenter::saveServices(string fileName) {
    ofstream outFile(fileName);
    if (!outFile.is_open())
        return false; 

    // Reorders the services to be stored in alphabetical order
    map<string,Service> servicesAlphaOrder;

    for(auto x = serviceMap.begin(); x != serviceMap.end(); ++x) {
        servicesAlphaOrder[x->second.serviceName] = x->second;
    }

    outFile << "// service name;cost;code" << endl;
    for(auto x = servicesAlphaOrder.begin(); x != servicesAlphaOrder.end(); ++x) {
      outFile << x->second.serviceName << ";" << x->second.fee << ";" << x->second.serviceCode << endl;
  }

    return true;
}

bool DataCenter::saveMembers(string fileName) {
    ofstream outFile(fileName);
    if (!outFile.is_open())
        return false; 

    for(auto x = memberMap.begin(); x != memberMap.end(); ++x) {
        outFile.precision(6);
        outFile.fill('0');
        outFile << x->second.name << ";" << x->second.memberNumber << ";" << x->second.phoneNumber << ";"<<
        x->second.fullAddress.streetAddress << ";" << x->second.fullAddress.city << ";" << x->second.fullAddress.state << ";" <<
        x->second.fullAddress.zip << endl;
    }

    return true;
}

bool DataCenter::saveProviders(string fileName) {
    ofstream outFile(fileName);
    if (!outFile.is_open())
        return false; 
    
    for(auto x = providerMap.begin(); x != providerMap.end(); ++x) {
        outFile.precision(6);
        outFile.fill('0');
        outFile << x->second.name << ";" << x->second.memberNumber << ";" << x->second.phoneNumber << ";"<<
        x->second.fullAddress.streetAddress << ";" << x->second.fullAddress.city << ";" << x->second.fullAddress.state << ";" <<
        x->second.fullAddress.zip << ";" << x->second.weeklyConsultationFees << endl;
    }

    return true;
}

bool DataCenter::saveReports(string fileName) {
    ofstream outFile(fileName);

    if (!outFile.is_open())
        return false; 
    
    // provider id;member id;service code;dateProvided;dateEntered
    int size = 0;
    Provider currProv;
    Service currServ;
    for(auto x = providerMap.begin(); x != providerMap.end(); ++x) { 
        currProv = x->second;
        size = currProv.weeklyConsultations.size();
        // Write to disk all rendered services by this provider
        for (int i = 0; i < size; ++i) {
            currServ= currProv.weeklyConsultations[i];
            outFile << currProv.memberNumber << ";" << currServ.member->memberNumber << ";" 
            << currServ.serviceCode << ";" << currServ.dateProvided << ";" << currServ.dateEntered << endl;
        }
    }
    
    outFile.close();
    return true;
}

// add new provider to data center
void DataCenter::addProvider(Provider & provider) {
	providerMap[provider.memberNumber] = provider;
}

//add new member to provider
void DataCenter::addMember(Member & member) {
	memberMap[member.memberNumber] = member;
  if(member.status)
    ++activeMemberCount;
}

//remove service from Data center
void DataCenter::removeService(string serviceCode) {
  serviceMap.erase(serviceCode);
}

//remove provider from Data center
void DataCenter::removeProvider(string providerID) {
  providerMap.erase(providerID);
}

//remove member from Data Center
void DataCenter::removeMember(string memberID) {
  try {
    if(memberMap.at(memberID).status)
      --activeMemberCount;
  } catch(const out_of_range &e) {
    return;
  }
  memberMap.erase(memberID);
}

    
bool DataCenter::modifyService(string serviceCode) { 
    // Try to retrieve service from database
    Service * service = &serviceMap.at(serviceCode);

    // If couldn't retrieve service, return failure
    if (!service)
        return false;
   
    // Ask is user wants to modify name
    if(getYesOrNo(string("Service name: ") + service->serviceName + "\nEnter a new name for this service?")) {
        do {
            cout << "Enter new name, up to 20 chars:\n";
            getline(cin, service->serviceName); 
        } while(service->serviceName.size() > 20);
    }

    // Ask is user wants to modify service fee
    if(getYesOrNo(string("Service fee: ") + to_string(service->fee) + "\nEnter a new fee for this service?")) {
        string tempMoney;
        do { cout << "\nEnter new fee, up to 999.99: ";
            cin >> get_money(tempMoney);
        } while (stold(tempMoney) > 999.99);
        service->fee = stold(tempMoney);
    }

    return true;
}

bool DataCenter::modifyProvider(string providerID) { 
    // Try to retrieve provider from database
    Provider * provider= &providerMap.at(providerID);

    // If couldn't retrieve provider, return failure
    if (!provider)
        return false;

    // Ask is user wants to modify name
    if(getYesOrNo(string("Provider name: ") + provider->name + "\nEnter a new name for this provider?")) {
        do {
            cout << "Enter new name, up to 25 chars:\n";
            getline(cin, provider->name); 
        } while(provider->name.size() > 25);
    }

    // Ask if user wants to change phone
    if(getYesOrNo(string("Provider phone: ") + provider->phoneNumber + "\nEnter a new phone number for this provider?")) {
      regex phone_format("\\d{3}-\\d{3}-\\d{4}");
      do { provider->phoneNumber = getString("Enter new phone number in the form ###-###-####");
      } while (!regex_match(provider->phoneNumber, phone_format));
    }

    // Ask if user wants to change address
    if(getYesOrNo(string("Provider address: ") + provider->fullAddress.streetAddress
        + "\n" + provider->fullAddress.city + ", " + provider->fullAddress.state + ", " + provider->fullAddress.zip
        + "\nEnter a new address for this provider?")) {
    
        do { provider->fullAddress.streetAddress = getString("Enter new street address, up to 25 letters"); } while (provider->fullAddress.streetAddress.size() > 25);
        do { provider->fullAddress.city = getString("Enter new city, up to 14 letters"); } while (provider->fullAddress.city.size() > 14);
        do { provider->fullAddress.state = getString("Enter new state, ex. OR"); } while (provider->fullAddress.state.size() != 2); 
        do{ provider->fullAddress.zip = getString("Enter new zip code");
        } while (stoi(provider->fullAddress.zip) < 10000 || stoi(provider->fullAddress.zip) > 99999);
    }

    return true;
}
 

bool DataCenter::modifyMember(string memberID) { 
    // Try to retrieve member from database
    Member * member = &memberMap.at(memberID);

    // If couldn't retrieve member, return failure
    if (!member)
        return false;
    
    // Ask is user wants to modify name
    if(getYesOrNo(string("Member name: ") + member->name + "\nEnter a new name for this member?")) {
        do {
            cout << "Enter new name, up to 25 chars:\n";
            getline(cin, member->name); 
        } while(member->name.size() > 25);
    }

    // Ask if user wants to change phone
    if(getYesOrNo(string("Member phone: ") + member->phoneNumber + "\nEnter a new phone number for this member?")) {
        regex phone_format("\\d{3}-\\d{3}-\\d{4}");
        do { member->phoneNumber = getString("Enter new phone number in the form ###-###-####");
        } while (!regex_match(member->phoneNumber, phone_format));

    }

    // Ask if user wants to change address
    if(getYesOrNo(string("Member address: ") + member->fullAddress.streetAddress + "\n"
          + member->fullAddress.city + ", " + member->fullAddress.state + ", " + member->fullAddress.zip)) {

        do { member->fullAddress.streetAddress = getString("Enter new street address, up to 25 letters"); } while (member->fullAddress.streetAddress.size() > 25);
        do { member->fullAddress.city = getString("Enter new city, up to 14 letters"); } while (member->fullAddress.city.size() > 14);
        do { member->fullAddress.state = getString("Enter new state, ex. OR"); } while (member->fullAddress.state.size() != 2); 
        do{ member->fullAddress.zip = getString("Enter new zip code");
        } while (stoi(member->fullAddress.zip) < 10000 || stoi(member->fullAddress.zip) > 99999);
    }

    return true;
}

//check if data center has service 
bool DataCenter::hasService(string serviceCode) {
  try {
    serviceMap.at(serviceCode);
    return true;
  } catch(const out_of_range &e) {
    return false;
  }
}

//check if data center has member in data center
bool DataCenter::hasMember(string memberID) {
  try {
    memberMap.at(memberID);
    return true;
  } catch(const out_of_range &e) {
    return false;
  }
}

//check member status
bool DataCenter::memberStatus(string memberID) {
	if(hasMember(memberID)) {
		return memberMap.at(memberID).status;
	}
	return false;
}

bool DataCenter::suspendMember(string memberID) {
  if(hasMember(memberID)) {
    if(memberMap.at(memberID).status) {
        memberMap.at(memberID).status = false;
        --activeMemberCount;
    }
    return true;
  }
  return false;
}

bool DataCenter::activateMember(string memberID) {
  if(hasMember(memberID)) {
    if(!memberMap.at(memberID).status) {
        memberMap.at(memberID).status = true;
        ++activeMemberCount;
    }
    return true;
  }
  return false;
}

//check if data center has provider
bool DataCenter::hasProvider(string providerID) {
  try {
    providerMap.at(providerID);
    return true;
  } catch(const out_of_range &e) {
    return false;
  }
}
