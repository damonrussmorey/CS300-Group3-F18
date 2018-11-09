/*
Damon Morey, Philip Prater, Samuel Shippey, Son Vu, Yves Wienecke 2018©
DataCenterTest.cpp
*/

#include "DataCenter.h"
#include <iostream>

bool addServiceTest() {
	try {
		Service dummyService;
		Member dummyMember;
		dummyMember.addService(&dummyService);
		// probably do real testing here this is just a skeleton
		// is this an integration test or a unit test? Several classes involved.
	}
	catch (...) {
		// pass/fail conditions here
		cout << "addService test failed, reason unknown." << endl;
	}
}
