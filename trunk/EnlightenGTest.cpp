#ifndef USING_CPPUNIT

#include <gtest/gtest.h>

#include <enlighten.h>

using namespace enlighten;

struct dummy {};

class FooTest : public testing::Test {
protected:
	virtual void SetUp() { }

	
	STEP1("i have a foo", FooTest, iHaveAFoo, dummy)
	void iHaveAFoo(dummy p1)
	{
		std::cout << "passei aqui";
	}
};

TEST_F(FooTest, InitializesCorrectly) {

	dummy d;
	GIVEN << "i have a foo" << d << OK;	
}

#endif