/*
Damon Morey, Philip Prater, Samuel Shippey, Son Vu, Yves Wienecke 2018©
ProviderTerminal.cpp
*/

#include "ProviderTerminal.h"
    
ProviderTerminal::ProviderTerminal(DataCenter * dc) {
    dc = dc;
}

void ProviderTerminal::run(void) {
	string providerName;
	string memberName;
	string serviceName;
	providerName = getString("Enter provider ID");
	int choice = 0;
	while(choice != 4) {
		choice = getOption("1. Report a consultation for a member\n"
				 "2. Output a weekly report\n"
				 "3. View master service list\n"
				 "4. Log off", 1, 4);
		switch(choice){
		case 1:
			memberName = getString("Enter member name");
			serviceName = getString("Enter service name");
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

