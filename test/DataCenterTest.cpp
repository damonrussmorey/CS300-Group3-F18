/*
Damon Morey, Philip Prater, Samuel Shippey, Son Vu, Yves Wienecke 2018©
DataCenterTest.cpp
*/

#include "../include/DataCenter.h"
#include <iostream>
#include <gtest/gtest.h>
/*"lib/googletest-master/googletest/include/gtest/"*/

/* Design considerations for tests:
 * 	Currently on a failure it returns false. Is this good?
 * 	If not what should we use to signal a failed test?
 */

//struct DataCenter 

//**Not sure what in this is 'Re-sharper' and what is google test**
//**need to fix**

/*
struct AddressTest : testing::Test
{
	address dum_add;

	AddressTest()
	{
		dum_add = new address;
	}

	~AddressTest()
	{
		delete dum_add;
	}
};
*/

TEST(AddressTest, SetValuesTest)
{
	//struct address dum_add = new address;
	string d_streetAddress = "12345 MapleSprucePine St.";
	//string d_city = "NilbogIsGoblin";
	//string d_state = "OR";
	//string d_zip = "67890";

	string streetAddress = d_streetAddress;
	//dum_add->city = d_city;
	//dum_add->state = d_state;
	//dum_add->zip = d_zip;

	EXPECT_TRUE(streetAddress == d_streetAddress);
	//EXPECT_TRUE(dum_add->city == d_city);
	//EXPECT_TRUE(dum_add->state == d_state);
	//EXPECT_TRUE(dum_add->zip == d_zip);
}

/*
struct EmptyMemberTest : testing::Test
{
	Member* e_mem;t

	EmptyMemberTest()
	{
		e_mem = new Member(NULL, NULL, NULL);
	}

	EmptyMemberTest()
	{
		delete e_mem;
	}
};

TEST_F(MemberTest, EmptyMember)
{
	EXPECT_EQ(e_mem->name, nullptr);
	EXPECT_EQ(e_mem->phoneNumber, nullptr);
	EXPECT_EQ(e_mem->fullAddress, nullptr);
	EXPECT_EQ(e_mem->servicesList, nullptr);
}
*/

/*
struct MemberTest :testing::Test
{
	Member* mem;
	string dum_name;
	string dum_phone;
	address dum_address;

	MemberTest()
	{
		mem = new Member(dum_name, dum_phone, dum_address);
	}

	~MemberTest()
	{
		delete mem;
	}
};



TEST_F(MemberTest, Happy)
{
	EXPECT_EQ(mem->name
}

TEST_F(MemberTest, NameBig)
{
}

TEST_F(MemberTest, PhoneBig)
{
}
*/

/*
struct DataCenterTest : testing::Test
{
	DataCenter* fake;
	//Member* fake_mem;
	//Priovider* dr.nick;
	//Service* fake_serv;
	//EFT* fake_mon;

	DataCenterTest()
	{
		fake = new DataCenter;
		//fake_mem = new Member;
		//dr.nick = new Provider;
		//fake_serv = new Service;
		//fake_mon = new EFT;
	}

	virtual ~DataCenterTest()
	{
		delete fake;
		//delete fake_mem;
		//delete dr.nick;
		//delete fake_serv;
		//delete fake_mon;
	}
		
};

TEST_F(DataCenterTest, EmptyCenter)
{
	EXPECT_EQ(0, fake->members);
	EXPECT_EQ(0, fake->providers);
	EXPECT_EQ(0, fake->providerDirectory);
	EXPECT_EQ(0, fake->recordsEFT);
}

TEST_F(DataCenterTest, CanAddMem)
{
	//fake->addMem(fake_mem);
	//EXPECT_EQ(fake_mem, fake->members);
}

TEST_F(DataCenterTest, CanAddProv)
{
	//fake->addProv(dr.nick);
	//EXPECT_EQ(dr.nick, fake->dr.nick);
}

TEST_F(DataCenterTest, CanAddServ)
{
	//fake->addServ(fake_serv);
	//EXPECT_EQ(fake_serv, fake->providerDirectory);
}

TEST_F(DataCenterTest, CanAddEFT)
{
	//fake->addEFT(fake_mon);
	//EXPECT_EQ(fake_mon, fake->EFTdata);
}
*/

/*
struct dc_state
{
	Member fake_mem;
	Provider fake_prov;
	Service fake_serv;
	EFT fake_cash;
	bool success;
};

struct addDataTest : DataCenterTest, testing::withParameterInterface<dc_state>
{
	addDataTest()
	{
		fake->members = GetParam().fake_mem;
	}
};


//set of different test cases we can use with parameterized tests (big feed list)
INSTANTIATE_TEST_CASE_P(Default, addDataTest,
		testing::Values(
			dc_state{x,y,z,a,true}, //set we expect to work
			dc_state{a,b,c,d,false} //set we expect to fail (good for testing classes like Member/Provider)
		));
*/

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

/*
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
*/
