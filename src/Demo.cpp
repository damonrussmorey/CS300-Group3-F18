/*
Damon Morey, Philip Prater, Samuel Shippey, Son Vu, Yves Wienecke 2018©
Demo.cpp

A demonstration of the ChocAn simulator in action
toggles between manager terminal and provider terminal
*/

#include "ProviderTerminal.h"

#define MAIN_MENU_OPTIONS 5

int main(){
    DataCenter        dataCenter;
    ManagerTerminal   managerTerminal(&dataCenter);
    ProviderTerminal  providerTerminal(&dataCenter);

    int opt = 0;

    // Menu
    do {
        clear();
        opt = getOption(
            "Welcome to The ChocAn Simulator.  "
            "Please select an option from the menu:\n"
            "1) Enter Provider Terminal\n"
            "2) Enter Manager Terminal\n"
            "3) Run Weekly Reports\n"
            "4) Start New Week\n"
            "5) Exit Simulator", 1, MAIN_MENU_OPTIONS);
        clear();
        switch(opt) {
            case 1:
                providerTerminal.run();
                break;

            case 2:
                managerTerminal.run();
                break;

            case 3:
                dataCenter.allReports();
                break;

            case 4:
                dataCenter.newWeek();
        }

    } while (opt != MAIN_MENU_OPTIONS);
	return 1;
}
