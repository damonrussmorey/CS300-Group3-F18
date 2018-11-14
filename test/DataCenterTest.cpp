/*
Damon Morey, Philip Prater, Samuel Shippey, Son Vu, Yves Wienecke 2018©
DataCenterTest.cpp
*/

#include "DataCenter.h"
#include <iostream>

/* Design considerations for tests:
 * 	Currently on a failure it returns false. Is this good?
 * 	If not what should we use to signal a failed test?
 */
bool addServiceTest() {
	try {
		Service dummyService;
		Member dummyMember;
		dummyMember.addService(dummyService);
		// probably do real testing here this is just a skeleton
		// is this an integration test or a unit test? Several classes involved.
	}
	catch (...) {
		// pass/fail conditions here
		cout << "addService test failed, reason unknown." << endl;
		return false;
	}
	return true;
}

bool providerAddServiceTest() {
	try {
		Service dummyService;
		Provider dummyProvider;
		dummyProvider.addService(dummyService);
	}
	catch (...) {
		cout << "addService test failed, reason unknown." << endl;
		return false;
	}
	return true;
}
