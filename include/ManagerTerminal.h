/*
Damon Morey, Philip Prater, Samuel Shippey, Son Vu, Yves Wienecke 2018©
ManagerTerminal.h
*/

#include "DataCenter.h"

void clear();

class ManagerTerminal {
  public:
    //create manager terminal/with reference to data center
    ManagerTerminal(DataCenter *);

    //main interface of manager terminal
    void run(void);

  private:
    //reference to main data center object
    //not allocate with manager terminal, only referenced
    DataCenter *dc;

    //interfacing with data center
    void addMember(void);
    void removeMember(void);
    void modifyMember(void);
    void addProvider(void);
    void removeProvider(void);
    void modifyProvider(void);
    void addService(void);
    void removeService(void);
    void modifyService(void);
    void requestReport(void);
};
