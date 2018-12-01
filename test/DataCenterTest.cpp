/*
Damon Morey, Philip Prater, Samuel Shippey, Son Vu, Yves Wienecke 2018©
DataCenterTest.cpp
*/


//#include "DataCenter.h"
#include "DataCenter.cpp"
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


//test that we can set an address
//necessary for next test
TEST(AddressTest, AddressSetting)
{
	string street_ad("12345 MapleSprucePine St.");
	string city("Portlandialand");
	string state("OR");
	string zip("98765");

	address ad;
	ad.streetAddress = street_ad;
	ad.city = city;
	ad.state = state;
	ad.zip = zip;
	
	EXPECT_TRUE(street_ad == ad.streetAddress);
	EXPECT_TRUE(city == ad.city);
	EXPECT_TRUE(state == ad.state);
	EXPECT_TRUE(zip == ad.zip);
}

//test that we can construct a member with simulated entry
TEST(MemberTest, MemberConstruction)
{
	string n("Bob");
	string num ("123456789");
	string phn ("503-867-5309");
	string street_ad("12345 SprucePineMaine St.");
	string city("Portlandialand");
	string state("OR");
	string zip("98765");

	address ad;
	ad.streetAddress = street_ad;
	ad.city = city;
	ad.state = state;
	ad.zip = zip;

	Member to_add(n, num, phn, ad);

	EXPECT_TRUE(n == to_add.name);
	EXPECT_TRUE(num == to_add.memberNumber);
	EXPECT_TRUE(phn == to_add.phoneNumber);
	EXPECT_TRUE(street_ad == to_add.fullAddress.streetAddress);
	EXPECT_TRUE(city == to_add.fullAddress.city);
	EXPECT_TRUE(state == to_add.fullAddress.state);
	EXPECT_TRUE(zip == to_add.fullAddress.zip);
}

TEST(ProviderTest, ProviderConstruction)
{
	string n("Bob");
	string num ("123456789");
	string phn ("503-867-5309");
	string street_ad("12345 SprucePineMaine St.");
	string city("Portlandialand");
	string state("OR");
	string zip("98765");

	address ad;
	ad.streetAddress = street_ad;
	ad.city = city;
	ad.state = state;
	ad.zip = zip;

	double fee = 123.45;

	Provider to_add(n, num, phn, ad, fee);

	EXPECT_TRUE(n == to_add.name);
	EXPECT_TRUE(num == to_add.memberNumber); //looks weird, but is due to provider being a subclass of member.
	EXPECT_TRUE(phn == to_add.phoneNumber);
	EXPECT_TRUE(street_ad == to_add.fullAddress.streetAddress);
	EXPECT_TRUE(city == to_add.fullAddress.city);
	EXPECT_TRUE(state == to_add.fullAddress.state);
	EXPECT_TRUE(zip == to_add.fullAddress.zip);

	EXPECT_DOUBLE_EQ(fee, to_add.weeklyConsultationFees);

}

TEST(ServiceTest, ServiceConstruction1)
{
	string code = "987654321";
	string name = "Some Vegtables";
	double fee = 19.99;

	Service to_add(code, name, fee);
	EXPECT_TRUE(code == to_add.serviceCode);
	EXPECT_TRUE(name == to_add.serviceName);
	EXPECT_DOUBLE_EQ(fee, to_add.fee);

}

//necessary to test how we update a provider and member service lists
TEST(ServiceTest, ServiceConstruction2)
{
	string n("Bob");
	string num ("123456789");
	string phn ("503-867-5309");
	string street_ad("12345 SprucePineMaine St.");
	string city("Portlandialand");
	string state("OR");
	string zip("98765");

	address ad;
	ad.streetAddress = street_ad;
	ad.city = city;
	ad.state = state;
	ad.zip = zip;

	double p_fee = 123.45;

	string code = "987654";
	string s_name = "Some Vegtables";
	double s_fee = 19.99;


	//generally frowned upon for doctors to
	//be there own doctors, but it makes this
	//test easier to read
	Member m(n, num, phn, ad);
	Member* mem = &m;
	Provider p(n, num, phn, ad, p_fee);
	Provider* prov = &p;
	Service s(code, s_name, s_fee);

	Service consult(s, mem, prov);

	EXPECT_TRUE(consult.serviceCode == s.serviceCode);
	EXPECT_TRUE(consult.serviceName == s.serviceName);
	EXPECT_DOUBLE_EQ(consult.fee, s.fee);
	EXPECT_TRUE(consult.provider == &p);
	EXPECT_TRUE(consult.member == &m);
}


//testing fixture (constructor for a test if you're gonna be testing a class or struct repeatedly, 
//can be more useful for setting a default state than this)
struct DataCenterTest : testing::Test
{
	DataCenter* dc;
	DataCenterTest()
	{
		dc = new DataCenter;
	}

	~DataCenterTest()
	{
		delete dc;
	}
};

//test hasMember(string name) finds correct/rejects wrong entries
TEST_F(DataCenterTest, MemProvServSearch)
{
	EXPECT_TRUE(dc->hasMember("Chris Gilmore")); //known default
	EXPECT_FALSE(dc->hasMember("Det. Pikachu")); //known to beinvalid
	EXPECT_TRUE(dc->hasProvider("111111111")); //known default
	EXPECT_FALSE(dc->hasProvider("321456000")); //known to be invalid

	EXPECT_TRUE(dc->hasService("549567")); //known default
	EXPECT_FALSE(dc->hasService("333333")); //known to be invalid
}

//test confirmConsult() rejects bad entries
TEST_F(DataCenterTest, confirmConsultBad)
{
	string mem = "Chris Gilmore";
	string prov = "Dr. Nick";  //searching by a name, not an ID
	string serv_code = "549567"; //known default

	EXPECT_FALSE(dc->confirmConsultation(mem, prov, serv_code));
}

//test confirmConsult() accepts good entries
TEST_F(DataCenterTest, confirmConsultGood)
{
	string mem = "Chris Gilmore"; //known default
	string prov = "111111111";    //known default
	string serv_code = "549567";

	EXPECT_TRUE(dc->confirmConsultation(mem, prov, serv_code));
}

//tests a member can be added and removed from a DataCenter
TEST_F(DataCenterTest, AddAndRemoveMember)
{
	string n("Bob");
	string num ("123456789");
	string phn ("503-867-5309");
	string street_ad("12345 SprucePineMaine St.");
	string city("Portlandialand");
	string state("OR");
	string zip("98765");

	address ad;
	ad.streetAddress = street_ad;
	ad.city = city;
	ad.state = state;
	ad.zip = zip;

	Member to_add(n, num, phn, ad);

	int mem_count = dc->giveMemCount();

	dc->addMember(to_add);
	++mem_count;
	EXPECT_TRUE(dc->hasMember("Bob"));
	EXPECT_EQ(mem_count, dc->giveMemCount());

	dc->removeMember("Bob");
	--mem_count;
	EXPECT_FALSE(dc->hasMember("Bob"));
	EXPECT_EQ(mem_count, dc->giveMemCount());
}


TEST_F(DataCenterTest, ProviderAddAndRemove)
{
	string n("Bob");
	string num ("123456789");
	string phn ("503-867-5309");
	string street_ad("12345 SprucePineMaine St.");
	string city("Portlandialand");
	string state("OR");
	string zip("98765");

	address ad;
	ad.streetAddress = street_ad;
	ad.city = city;
	ad.state = state;
	ad.zip = zip;

	double fee = 123.45;

	Provider to_add(n, num, phn, ad, fee);

	dc->addProvider(to_add);
	EXPECT_TRUE(dc->hasProvider("123456789"));

	dc->removeProvider("123456789");
	EXPECT_FALSE(dc->hasProvider("123456789"));
}

TEST_F(DataCenterTest, ServiceAddAndRemove)
{
	string code = "987654";
	string s_name = "Some Vegtables";
	double s_fee = 19.99;
	
	Service s(code, s_name, s_fee);

	dc->addService(s);
	EXPECT_TRUE(dc->hasService("987654"));

	dc->removeService("987654");
	EXPECT_FALSE(dc->hasService("987654"));
}



//main that runs all the tests
int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}


