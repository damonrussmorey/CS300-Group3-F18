/*
Damon Morey, Philip Prater, Samuel Shippey, Son Vu, Yves Wienecke 2018©
ProviderTerminal.cpp
*/

#include "ProviderTerminal.h"
    
ProviderTerminal::ProviderTerminal(DataCenter * dc) {
    this->dc = dc;
}

void ProviderTerminal::run(void) {
	string providerName;
	string memberName;
	string serviceCode;
	//no longer using provider ID
	//providerName = getString("Enter provider ID");
	do
	{
	providerName = getString("Enter provider name: ");
	if(!dc->hasProvider(providerName)) cout << "Invalid Provider name.\n";
	} while(!dc->hasProvider(providerName));

	int choice = 0;
	while(choice != 4) {
		choice = getOption("1. Report a consultation for a member\n"
				 "2. Output a weekly report\n"
				 "3. View master service list\n"
				 "4. Log off", 1, 4);
		switch(choice){
		case 1:
			memberName = getString("Enter member name: ");
			if(!dc->hasMember(memberName)) {
				cout << "Invalid member name.\n";
				break;
			}

			if(!dc->memberStatus(memberName)) {
				cout << "Member is suspended. Cannot provide member with any services.\n";
				break;
			}
				
			do
			{
				serviceCode = getString("Enter service Code: ");
				if(!dc->hasService(serviceCode)) cout << "Invalid service Code.\n";
			} while (!dc->hasService(serviceCode));

			dc->confirmConsultation(memberName, providerName, serviceCode);
			break;
		case 2:
			cout << "Generating provider report at normal directory..." << endl;
			dc->providerReport(providerName);
			cout << "Done." << endl;
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


