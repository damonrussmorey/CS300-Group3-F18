/*
Damon Morey, Philip Prater, Samuel Shippey, Son Vu, Yves Wienecke 2018©
ManagerTerminal.cpp
*/

#include "ManagerTerminal.h"
using namespace std;

int getOption(string prompt, int lower, int upper) {
  int opt;
  assert(lower <= upper);

  while(true) {
    cout << prompt << "\n: ";
    cout.flush();
    cin >> opt;
    if (cin.fail()) {
        cin.clear();
        opt = lower -1;
    }

    cin.ignore(100, '\n');
    if(opt >= lower && opt <= upper)
      break;
    else
      cout << "Invalid option, try again.\n\n";
  }
  return opt;
}

string getString(string prompt) {
	cout << prompt << ": ";
  cout.flush();
	string response;
	getline(cin, response);
	return response;
}

void clear() {
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

//ManagerTerminal

ManagerTerminal::ManagerTerminal(DataCenter * dc) {
  this->dc = dc;
}

void ManagerTerminal::run() {
  int opt;
  bool running;

  cout << "Starting Manager Terminal..." << endl;

  //main loop for manager terminal operations
  running = true;
  while(running) {
    opt = getOption(
           "Select an option from the list:\n" 
           "1) Manage Service Directory\n"
           "2) Manage Memberships\n"
           "3) Manage Provider Network\n"
           "4) Request Report\n"
           "5) Quit Manager Terminal", 1, 5);
    switch(opt) {
      case 1:
        switch(getOption("1) Add Service\n"
                         "2) Remove Service\n"
                         "3) Modify Service", 1, 3)) {
          case 1:
            addService();
            break;
          case 2:
            removeService();
            break;
          case 3:
            modifyService();
            break;
          default:
            assert(true);
            break;
        }
        break;
      case 2:
        switch(getOption("1) Add Member\n"
                         "2) Remove Member\n"
                         "3) Modify Member", 1, 3)) {
          case 1:
            addMember();
            break;
          case 2:
            removeMember();
            break;
          case 3:
            modifyMember();
            break;
          default:
            assert(true);
            break;
        }
        break;
      case 3:
        switch(getOption("1) Add Provider\n"
                         "2) Remove Provider\n"
                         "3) Modify Provider", 1, 3)) {
          case 1:
            addProvider();
            break;
          case 2:
            removeProvider();
            break;
          case 3:
            modifyProvider();
            break;
          default:
            assert(true);
            break;
        }
        break;
      case 4:
        requestReport();
        break;
      case 5:
        running = false;
        break;
      default:
        break;
    }
  }
}



//TODO read in the rest of the data
//for all of these functions



void ManagerTerminal::addMember(void) {
  string name;
  string number;
  address adr;
  name = getString("Enter full name of member to be added");
  number = getString("Enter phone number");
	adr.streetAddress = getString("Enter street address");
	adr.city = getString("Enter city");
	adr.state = getString("Enter state");
	adr.zip = getString("Enter zip");
  Member m(name, number, adr);
  dc->addMember(m);
}

void ManagerTerminal::removeMember(void) {
  string name;
  name = getString("Enter full name of member to be removed");
  if(dc->hasMember(name)) {
    dc->removeMember(name);
    cout << "Member successfully removed from the system." << endl;
  } else {
    cout << "Member was not found in the system." << endl;
  }
}

void ManagerTerminal::modifyMember(void) {
  string name;
  name = getString("Enter full name of member to be modified");
  if(dc->hasMember(name)) {
    //TODO figure out how to modify
    //I think we should probably be referencing Member objects directly
    //-Damon
    cout << "todo";
  } else {
    cout << "Member was not found in the system." << endl;
  }
}

void ManagerTerminal::addProvider(void) {
  string name;
  string number;
  address adr;
  name = getString("Enter full name of member to be added");
  number = getString("Enter phone number");
	adr.streetAddress = getString("Enter street address");
	adr.city = getString("Enter city");
	adr.state = getString("Enter state");
	adr.zip = getString("Enter zip");
  Provider p(name, number, adr, 0);
  dc->addProvider(p);
}

void ManagerTerminal::removeProvider(void) {
  string name;
  name = getString("Enter name of provider to be removed");
  if(dc->hasProvider(name)) {
    dc->removeProvider(name);
    cout << "Provider successfully removed from the system." << endl;
  } else {
    cout << "Provider was not found in the system." << endl;
  }
}

void ManagerTerminal::modifyProvider(void) {
  string name;
  name = getString("Enter name of provider to be modified");
  if(dc->hasProvider(name)) {
    //TODO figure out how to modify
    //I think we should probably be referencing Provider objects directly
    //-Damon
  } else {
    cout << "Provider was not found in the system." << endl;
  }
}

void ManagerTerminal::addService(void) {
  string code;
  long double cost;
  code = getString("Enter code of service to be added");
  
  cin >> get_money(cost);
  Service s(code, cost);
  dc->addService(s);
}

void ManagerTerminal::removeService(void) {
  string code;
  code = getString("Enter code of service to be removed");
  if(dc->hasService(code)) {
    dc->removeService(code);
    cout << "Service successfully removed from the system." << endl;
  } else {
    cout << "Service was not found in the system." << endl;
  }
}

void ManagerTerminal::modifyService(void) {
  string name;
  name = getString("Enter name of service to be modified");
  if(dc->hasService(name)) {
    //TODO figure out how to modify
    //I think we should probably be referencing Service objects directly
    //-Damon
  } else {
    cout << "Service was not found in the system." << endl;
  }
}

void ManagerTerminal::requestReport(void) {
  //TODO
}

