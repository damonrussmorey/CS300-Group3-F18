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


TEST(AddressTest, AddressSetting)
{
	string street_ad("12345 SprucePineMaine St.");
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


TEST_F(DataCenterTest, confirmConsultBad)
{
	string mem = "Chris Gilmore";
	string prov = "Dr. Nick";
	string serv_code = "549567";

	EXPECT_FALSE(dc->confirmConsultation(mem, prov, serv_code));
}

TEST_F(DataCenterTest, confirmConsultGood)
{
	string mem = "Chris Gilmore";
	string prov = "Chris Grimjack";
	string serv_code = "549567";

	EXPECT_TRUE(dc->confirmConsultation(mem, prov, serv_code));
}

/*
TEST_F(DataCenterTest, addService)
{
	dc.
}

TEST_F(DataCenterTest, addService)
{
	dc.
}

TEST_F(DataCenterTest, addService)
{
	dc.
}

TEST_F(DataCenterTest, addService)
{
	dc.
}
*/

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


int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}


