/*
Damon Morey, Philip Prater, Samuel Shippey, Son Vu, Yves Wienecke 2018©
ProviderTerminal.cpp
*/

#include "ProviderTerminal.h"

//date format: MM-DD-YYYY
static bool properDate(string date) {
  int x;
  return 3 == sscanf(date.c_str(), "%d-%d-%d", &x, &x, &x);
}
    
ProviderTerminal::ProviderTerminal(DataCenter * dc) {
    this->dc = dc;
}

void ProviderTerminal::run(void) {
	string providerID;
	string memberName;
	string serviceCode;
  string dateProvided;

    int attempts = 3;
    bool validatedProvider = false;   
    
    //For testing purposes
    dc->printProviders(); 

    //Using the provider ID is a requirement for this program
    do
    {    
        --attempts;
        providerID = getString("\nEnter provider ID");
        providerID.resize(9);
        providerID.shrink_to_fit();

        validatedProvider = dc->hasProvider(providerID);
        if(!validatedProvider) {
            cout << "Invalid Provider ID. " << attempts << " attempts left.\n";
            if (attempts <= 0) return;
        }
    } while(!validatedProvider);
    

	int choice = 0;
	while(choice != 4) {
		choice = getOption("1. Report a consultation for a member\n"
				 "2. Output a weekly report\n"
				 "3. View master service list\n"
				 "4. Log off", 1, 4);
		switch(choice){
		case 1:
      dc->printMembers();
			memberName = getString("Enter member name");
			if(!dc->hasMember(memberName)) {
				cout << "Invalid member name.\n";
				break;
			}

			if(!dc->memberStatus(memberName)) {
				cout << "Member is suspended. Cannot provide member with any services.\n";
				break;
			}
				
      dc->printServiceList();
			do
			{
				serviceCode = getString("Enter service Code: ");
				if(!dc->hasService(serviceCode)) cout << "Invalid service Code.\n";
			} while (!dc->hasService(serviceCode));

      do {
        dateProvided = getString("Enter consultation date (MM-DD-YYYY)");
        //confirm proper date formatting
        if(properDate(dateProvided))
          break;
        cout << "Invalid date format." << endl;
      } while(true);

			if(dc->confirmConsultation(memberName, providerID, serviceCode, dateProvided)) {
        cout << "Consultation successfully recorded with Data Center." << endl;
      } else {
        cout << "Error recording consultation with Data Center, try again later." << endl;
      }

			break;
		case 2:
			cout << "Generating provider report at normal directory..." << endl;
			dc->providerReport(providerID);
			cout << "Done. Output and emailed provider reports." << endl;
			break;
		case 3:
            dc->printServiceList();
			break;
		case 4:
			//already done and while loop will terminate
			break; 
		}
	}
}


