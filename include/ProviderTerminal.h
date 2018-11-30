/*
Damon Morey, Philip Prater, Samuel Shippey, Son Vu, Yves Wienecke 2018©
ProviderTerminal.h
*/

#include "ManagerTerminal.h"

class ProviderTerminal {
    public:
        //create providerterminal/with reference to data center
        ProviderTerminal(DataCenter *);

        //main interface of provider terminal
        void run(void);
		void addConsultation();
		void viewWeeklyReport();
		void viewServiceList();
		void exit();

    private:
        DataCenter * dc;
};
