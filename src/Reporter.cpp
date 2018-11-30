/*
Damon Morey, Philip Prater, Samuel Shippey, Son Vu, Yves Wienecke 2018©
Reporter.cpp
*/

#include "DataCenter.h"
using namespace std;

static string dateString(tm *date, char sep) {
  if(!date) {
    time_t t;
    time(&t);
    date = localtime(&t);
  }
  ostringstream out;
  out << date->tm_mday << sep << date->tm_mon << sep << date->tm_year;
  return out.str();
}

void DataCenter::allReports() {
  for(auto x = memberMap.begin();
      x != memberMap.end(); ++x) {
    memberReport(x->second);
  }
  for(auto x = providerMap.begin();
      x != providerMap.end(); ++x) {
    providerReport(x->second);
  }
  managerReport();
  eftReport();
}

bool DataCenter::memberReport(string memberName) {
  try {
    memberReport(memberMap.at(memberName));
    return true;
  } catch(const out_of_range &) {
    return false;
  }
}

void DataCenter::memberReport(const Member &member) {
  ofstream f;
  
  //open file to write report to
  f.open(string("member_reports/") + dateString(NULL, '_') + "_" + member.name);
  assert(f);

  //preamble, member info
  f << member.name << endl
    << member.phoneNumber << endl
    << member.fullAddress.streetAddress << endl
    << member.fullAddress.city << ", " << member.fullAddress.state << endl
    << member.fullAddress.zip << endl << endl;

  //summary of week
  f << "Consultations: " << member.weeklyConsultations.size() << endl;
  if(member.status) f << "Active" << endl;
  else              f << "Suspended" << endl;
  
  //list each consultation
  for(  auto x = member.weeklyConsultations.begin();
        x != member.weeklyConsultations.end(); ++x) {
    f << endl;
    f << x->serviceCode << endl;
    f << dateString(x->date, '/') << endl;
    f << x->provider->name << endl;
  }

  //cleanup
  f.close();
}

bool DataCenter::providerReport(string providerName) {
  try {
    providerReport(providerMap.at(providerName));
    return true;
  } catch(const out_of_range &) {
    return false;
  }
}

void DataCenter::providerReport(const Provider &provider) {
  ofstream f;
  
  //open file to write report to
  f.open(string("provider_reports/") + dateString(NULL, '_') + "_" + provider.name);
  assert(f);

  //preamble, provider info
  f << provider.name << endl
    << provider.phoneNumber << endl
    << provider.fullAddress.streetAddress << endl
    << provider.fullAddress.city << ", "
    << provider.fullAddress.state << endl
    << provider.fullAddress.zip << endl << endl;

  //summary of week
  f.precision(2);
  f.fill('0');
  f << "Consultations: " << provider.weeklyConsultations.size() << endl
    << "Fees           $" << provider.weeklyConsultationFees << endl;
  
  //list each consultation
  for(  auto x = provider.weeklyConsultations.begin();
        x != provider.weeklyConsultations.end(); ++x) {
    f << endl;
    f << x->serviceCode << endl;
    f << dateString(x->date, '/') << endl;
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
  f.open(string("manager_reports/") + dateString(NULL, '_'));
  assert(f);
  f.precision(2);
  f.fill('0');

  //summarize consultations
  f << "Number of Providers:     " << providerMap.size() << endl;
  f << "Total Consultations:     " << weeklyConsultationCount << endl;
  f << "Total Consultation Fees: $" << weeklyConsultationFees << endl << endl;

  //summarize memberships
  f << "Number of Members:        " << memberMap.size() << endl;
  f << "Number of Active Members: " << activeMemberCount << endl;
  f << "Total Member Fees:        $" << membershipIncome;

  //net profit for the week
  f << "Weekly Net Profit: $" << profit << endl;

  //list each provider
  cout << endl << "Providers";
  for(auto x = providerMap.begin(); x != providerMap.end(); ++x) {
    f << endl
      << "Provider:      " << x->second.name << endl
      << "Phone:         " << x->second.phoneNumber << endl
      << "Consultations: " << x->second.weeklyConsultations.size() << endl
      << "Fees:          " << x->second.weeklyConsultationFees;
  }

  //list each active member
  f << endl << endl << "Active Members";
  for(auto x = memberMap.begin(); x != memberMap.end(); ++x) {
    /*if(!x->status)
      continue;*/
    f << endl
      << "Member:        " << x->second.name << endl
      << "Phone:         " << x->second.phoneNumber << endl
      << "Consultations: " << x->second.weeklyConsultations.size();
  }

  //list each suspended member
  f << endl << endl << "Suspended Members";
  for(auto x = memberMap.begin(); x != memberMap.end(); ++x) {
    if(x->second.status)
      continue;
    f << endl
      << "Member:        " << x->second.name << endl
      << "Phone:         " << x->second.phoneNumber;
  }

  //cleanup
  f << endl << endl;
  f.close();
}

//simply calculation of payments in and out
//summarized, totals of week?
//or a list of all transactions (each consultation, each membership payment?)
//don't need membership payment, ACME gives us membership payments
//(need to mock membership payments coming from ACME?)
//-Damon

// Refer back to the design document, section 4.6, page 13 -Yves
void DataCenter::eftReport() {
  //TODO
}
