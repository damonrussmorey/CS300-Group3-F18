/*
Damon Morey, Philip Prater, Samuel Shippey, Son Vu, Yves Wienecke 2018©
ManagerTerminal.cpp
*/

#include "../include/ManagerTerminal.h"
#include <iostream>
#include <gtest/gtest.h>
/*"lib/googletest-master/googletest/include/gtest/"*/

struct ManagerTerminalTest : test::Testing
{
	DataCenter dc;
	ManagerTerminal manT(&dc);

	/*
	ManagerTerminalTest(){
		dc = new DataCenter;
		manT = new ManagerTerminal(dc);
	}

	~ManagerTerminalTest(){
		delete manT;
		delete dc;
	}
	*/
};


/*
TEST_F(ManagerTerminalTest, printtest)
{
	manT.dc-> printServiceList();
	EXPECT_TRUE();
	EXPECT_TRUE();
}
*/

/*
TEST_F(ManagerTerminalTest, addmember)
{
	EXPECT_TRUE();
}

TEST_F(ManagerTerminalTest, removemember)
{
	EXPECT_TRUE();
}

TEST_F(ManagerTerminalTest, addprovider)
{
	EXPECT_TRUE();
}

TEST_F(ManagerTerminalTest, removeprovider)
{
	EXPECT_TRUE();
}

TEST_F(ManagerTerminalTest, addservice)
{
	EXPECT_TRUE();
}

TEST_F(ManagerTerminalTest, removeservice)
{
	EXPECT_TRUE();
}

TEST_F(ManagerTerminalTest, )
{
}

TEST_F(ManagerTerminalTest, )
{
}
*/
