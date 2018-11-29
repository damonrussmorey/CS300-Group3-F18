/*
Damon Morey, Philip Prater, Samuel Shippey, Son Vu, Yves Wienecke 2018©
Reporter.cpp
*/

#include "DataCenter.h"
using namespace std;

static string dateString() {
  time_t t;
  time(&t);
  tm *x = localtime(&t);
  ostringstream out;
  out << x->tm_mday << "_" << x->tm_mon << "_" << x->tm_year;
  return out.str();
}

void DataCenter::allReports() {
  for(set<Member>::iterator x = memberSet.begin();
      x != memberSet.end(); ++x) {
    memberReport(*x);
  }
  for(set<Provider>::iterator x = providerSet.begin();
      x != providerSet.end(); ++x) {
    providerReport(*x);
  }
  managerReport();
  eftReport();
}

void DataCenter::memberReport(string memberName) {
  auto member = memberSet.find(Member(memberName, NULL, nullAdr));
	if(member != memberSet.end())
    memberReport(*member);
}

void DataCenter::memberReport(const Member &member) {
  ofstream f;
  
  //open file to write report to
  f.open(string("member_reports/") + dateString() + "_" + member.name);
  assert(f);

  //preamble, member info
  f << member.name << endl
    //<< member.id << endl
    << member.phoneNumber << endl
    << member.fullAddress.streetAddress << endl
    << member.fullAddress.city << ", " << member.fullAddress.state << endl
    << member.fullAddress.zip << endl << endl;

  //summary of week
  f << "Consultations: " << member.weeklyConsultations.size() << endl;
  /*if(member.status) f << "Active" << endl;
  else              f << "Suspended" << endl;
  */
  
  //list each consultation
  for(  auto x = member.weeklyConsultations.begin();
        x != member.weeklyConsultations.end(); ++x) {
    f << endl;
    f << x->serviceCode << endl;
    //f << x->serviceDate << endl;
    f << x->provider->name << endl;
  }

  //cleanup
  f.close();
}

void DataCenter::providerReport(string providerName) {
  auto provider = providerSet.find(Provider(providerName, NULL, nullAdr, 0));
	if(provider != providerSet.end())
    providerReport(*provider);

}

void DataCenter::providerReport(const Provider &provider) {
  ofstream f;
  
  //open file to write report to
  f.open(string("provider_reports/") + dateString() + "_" + provider.name);
  assert(f);

  //preamble, provider info
  f << provider.name << endl
  //<< provider.id << endl
    << provider.phoneNumber << endl
    << provider.fullAddress.streetAddress << endl
    << provider.fullAddress.city << ", "
    << provider.fullAddress.state << endl
    << provider.fullAddress.zip << endl << endl;

  //summary of week
  f << "Consultations: " << provider.weeklyConsultations.size() << endl
    << "Fees           $" << provider.weeklyConsultationFees << endl;
  
  //list each consultation
  for(  auto x = provider.weeklyConsultations.begin();
        x != provider.weeklyConsultations.end(); ++x) {
    f << endl;
    f << x->serviceCode << endl;
    //f << x->serviceDate << endl;
    f << x->member->name << endl;
    f << x->fee << endl;
  }

  //cleanup
  f.close();
}

void DataCenter::managerReport() {
  ofstream f;

  //financial math, ezpz
  double membershipIncome = activeMemberCount * MEMBERSHIP_FEE;
  double profit = membershipIncome - weeklyConsultationFees;
  
  //open file to write report to
  f.open(string("manager_reports/") + dateString());
  assert(f);
  f.precision(2);
  f.fill('0');

  //summarize consultations
  f << "Number of Providers:     " << providerSet.size() << endl;
  f << "Total Consultations:     " << weeklyConsultationCount << endl;
  f << "Total Consultation Fees: $" << weeklyConsultationFees << endl << endl;

  //summarize memberships
  f << "Number of Members:        " << memberSet.size() << endl;
  f << "Number of Active Members: " << activeMemberCount << endl;
  f << "Total Member Fees:        $" << membershipIncome;

  //net profit for the week
  f << "Weekly Net Profit: $" << profit << endl;

  //list each provider
  cout << endl << "Providers";
  for(auto x = providerSet.begin(); x != providerSet.end(); ++x) {
    f << endl
      << "Provider:      " << x->name << endl
      << "Phone:         " << x->phoneNumber << endl
      << "Consultations: " << x->weeklyConsultations.size() << endl
      << "Fees:          " << x->weeklyConsultationFees;
  }

  //list each active member
  f << endl << endl << "Active Members";
  for(auto x = memberSet.begin(); x != memberSet.end(); ++x) {
    /*if(!x->status)
      continue;*/
    f << endl
      << "Member:        " << x->name << endl
      << "Phone:         " << x->phoneNumber << endl
      << "Consultations: " << x->weeklyConsultations.size();
  }
/*
  //list each suspended member
  f << endl << endl << "Suspended MEmbers";
  for(auto x = memberSet.begin(); x != memberSet.end(); ++x) {
    if(x->status)
      continue;
    f << endl
      << "Member:        " << x->name << endl
      << "Phone:         " << x->phoneNumber;
  }*/

  //cleanup
  f.close();
}

//simply calculation of payments in and out
//summarized, totals of week?
//or a list of all transactions (each consultation, each membership payment?)
//don't need membership payment, ACME gives us membership payments
//(need to mock membership payments coming from ACME?)
//-Damon
void DataCenter::eftReport() {
  //TODO
}
