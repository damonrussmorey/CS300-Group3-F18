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
Service::Service(const Service &s, const Member *m, const Provider *p) {
  stringstream ss;
  tm *timeinfo;

	fee = s.fee;
	serviceCode = s.serviceCode;
    serviceName = s.serviceName;
	provider = p;
	member = m;
    dateEntered = s.dateEntered;
    dateProvided = s.dateProvided;
	time_t t;
	time(&t);
	timeinfo = localtime(&t);
  ss << timeinfo->tm_mon << '-' << timeinfo->tm_mday << '-' << timeinfo->tm_year+1900;//11-30-2018;11-30-2018 15:35:23
  dateProvided = ss.str();
  ss.clear();ss.str("");

  t += 300;   //5min to record, artificial delay
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


bool DataCenter::confirmConsultation(string memberName, string providerID, string serviceCode) {
  try{
    //get the member, provider, and service
    Member &m = memberMap.at(memberName);
    Provider &p = providerMap.at(providerID);
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
        cout << x->second.memberNumber << " - " <<x->second.name << endl;
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

    string providerID, memberName, serviceCode;
    string dateProvided, dateEntered;

    inFile.open(fileName);
    if (!inFile.is_open()) {
        return false;
    }
    
    // Read in reports from file
    while (!getline(inFile, providerID, ';').eof()) {
        getline(inFile, memberName, ';');
        getline(inFile, serviceCode, ';');
        getline(inFile, dateProvided, ';');
        getline(inFile, dateEntered);

        // Point to references of read in provider, member, service
        provider = &providerMap.at(providerID);
        member = &memberMap.at(memberName);

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
    
    // provider id;member name;service code;dateProvided;dateEntered
    int size = 0;
    Provider currProv;
    Service currServ;
    for(auto x = providerMap.begin(); x != providerMap.end(); ++x) { 
        currProv = x->second;
        size = currProv.weeklyConsultations.size();
        // Write to disk all rendered services by this provider
        for (int i = 0; i < size; ++i) {
            currServ= currProv.weeklyConsultations[i];
            outFile << currProv.memberNumber << ";" << currServ.member->name << ";" 
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
	memberMap[member.name] = member;
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
void DataCenter::removeMember(string memberName) {
  try {
    if(memberMap.at(memberName).status)
      --activeMemberCount;
  } catch(const out_of_range &e) {
    return;
  }
  memberMap.erase(memberName);
}

    
bool DataCenter::modifyService(string serviceCode) { 
    // Try to retrieve service from database
    Service * service = &serviceMap.at(serviceCode);
    int choice = 0;

    // If couldn't retrieve service, return failure
    if (!service)
        return false;
    
    do {
        cout << "Service name: " << service->serviceName << endl;
        cout << "Enter a new name for this service? 0-no;1-yes";
        cin >> choice;
        if (cin.fail()) {cin.clear(); choice = 2;} 
    } while (choice != 0 && choice != 1);
    
    // Modify name of service
    if (choice) {
        do {
            cout << "Enter new name, up to 20 chars:\n";
            getline(cin, service->serviceName); 
        } while(service->serviceName.size() > 20);
    }

    do {
        cout << "Service fee: " << service->fee << endl;
        cout << "Enter a new fee for this service? 0-no;1-yes";
        cin >> choice;
        if (cin.fail()) {cin.clear(); choice = 2;} 
    } while (choice != 0 && choice != 1);
    
    // Modify cost of service
    if (choice) {
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
    //int choice = 0;

    // If couldn't retrieve provider, return failure
    if (!provider)
        return false;
    
    return true;
}
 

bool DataCenter::modifyMember(string memberID) { 
    // Try to retrieve member from database
    Member * member = &memberMap.at(memberID);
    //int choice = 0;

    // If couldn't retrieve member, return failure
    if (!member)
        return false;

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
bool DataCenter::hasMember(string memberName) {
  try {
    memberMap.at(memberName);
    return true;
  } catch(const out_of_range &e) {
    return false;
  }
}


//check member status
bool DataCenter::memberStatus(string memberName) {
	if(hasMember(memberName)) {
		return memberMap.at(memberName).status ? true : false;
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
