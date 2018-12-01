/*
   Damon Morey, Philip Prater, Samuel Shippey, Son Vu, Yves Wienecke 2018©
   DataCenter.h

Includes:
Member class definition
Provider class definition
DataCenter class definition
 */

#include "defs.h"

//TODO: Write copy constructors if needed

class Member {
    public:
        Member();
        Member(string, string, string, address &);
        ~Member();
        void consultation(Service & service);
        bool operator<(const Member & member) const;
        bool operator==(const Member & member) const;
        void clear();
        string name;
        string memberNumber;
        string phoneNumber;
        address fullAddress;
        bool status;
        vector<Service> weeklyConsultations;
};

class Provider : public Member{
    public:
        Provider();
        Provider(string n, string number, string phone, address & ad, double f);
        ~Provider();
        void consultation(Service & service);
        bool operator<(const Provider & Provider) const;
        bool operator==(const Provider & Provider) const;
        void clear();
        //unsigned int totalConsultations;
        //don't need, use weeklyConsultation.size()
        //might consider fixed sized values for money
        //-Damon
        double weeklyConsultationFees;
};

class Service {
    public:
        Service();
        Service(string,string,double);
        Service(const Service &, const Member*, const Provider*, string);
        ~Service();
        bool operator<(const Service & service) const;
        bool operator==(const Service & service) const;
        // Although there are indeed a pair of pointers in here,
        // we need them to be shallow copied if they're copied
        // (as they point to pre-existing members and providers)
        // and thus no copy constructor is provided
        const Provider *provider;
        const Member *member;
        string serviceCode;
        string serviceName;
        string dateEntered;
        string dateProvided;
        double fee;
};

class DataCenter {
    public:
        DataCenter();
        ~DataCenter();

        //ProviderTerminal calls this to submit a consultation
        //Could add more functions to confirm IDs, etc, along the way, but not really necessary
        bool confirmConsultation(string, string, string, string);

        void newWeek();
        void printServiceList();
        void printProviders();
        void printMembers();
        
        //Loading data from disk
        bool loadServices(string);
        bool loadMembers(string);
        bool loadProviders(string);
        bool loadReports(string);

        //Saving data to disk
        bool saveServices(string);
        bool saveMembers(string);
        bool saveProviders(string);
        bool saveReports(string); 
        
        //Data management
        void addService(Service & service);
        void addProvider(Provider & provider);
        void addMember(Member & member);
        // TODO: untested
        bool hasService(string);
        bool hasMember(string);
        bool memberStatus(string);
        bool hasProvider(string);
        bool modifyService(string);
        bool modifyMember(string);
        bool modifyProvider(string);
        void removeService(string);
        void removeMember(string);
        void removeProvider(string);

        //Reports - Reporter.cpp
        void allReports();
        bool memberReport(string);
        bool providerReport(string);
        void managerReport();
        void eftReport();

    protected:
        void memberReport(const Member&);
        void providerReport(const Provider&);

        map<string,Service> serviceMap;
        map<string,Member> memberMap;
        map<string,Provider> providerMap;

        double weeklyConsultationFees;
        int weeklyConsultationCount;
        int activeMemberCount;
        //suspendedMemberCount = memberSet.size() - activeMemberCount

        address nullAdr;
};
