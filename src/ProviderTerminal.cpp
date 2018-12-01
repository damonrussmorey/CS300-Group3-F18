/*
Damon Morey, Philip Prater, Samuel Shippey, Son Vu, Yves Wienecke 2018©
ProviderTerminal.cpp
*/

#include "ProviderTerminal.h"
    
ProviderTerminal::ProviderTerminal(DataCenter * dc) {
    this->dc = dc;
}

void ProviderTerminal::run(void) {
	string providerID;
	string memberID;
	string serviceCode;
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
			memberID = getString("Enter 9 digit member ID");
			if(!dc->hasMember(memberID)) {
				cout << "Invalid member ID.\n";
				break;
			}

			if(!dc->memberStatus(memberID)) {
				cout << "Member is suspended. Cannot provide member with any services.\n";
				break;
			}
				
      dc->printServiceList();
			do
			{
				serviceCode = getString("Enter service Code: ");
				if(!dc->hasService(serviceCode)) cout << "Invalid service Code.\n";
			} while (!dc->hasService(serviceCode));

			if(dc->confirmConsultation(memberID, providerID, serviceCode)) {
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


