#ifndef CPPUNIT_EXTENSIONS_HELPERMACROS_H
#include <cppunit/extensions/HelperMacros.h>
#endif

#include <sstream>
#include <iostream>

#include "enlighten.h"
#include <string>
////////////////////////////////////////////////////////////////////////////////

using namespace enlighten;
////////////////////////////////////////////////////////////////////////////////

class EnlightenTest : public CPPUNIT_NS::TestFixture
{
   CPPUNIT_TEST_SUITE(EnlightenTest);
		CPPUNIT_TEST(testGivenWhenThen);
		CPPUNIT_TEST(testStringsPassedAreMappedToAStep);
		CPPUNIT_TEST(testStringsPassedThatNotMapToAStepShouldThrow);
		CPPUNIT_TEST(testPassingNotPrimitiveParametersToSteps);
      /*CPPUNIT_TEST(testGivenWhenThen);
      CPPUNIT_TEST(testGivenComUmParametroInteiro);*/ 
   CPPUNIT_TEST_SUITE_END();

public:
   void setUp() {
	}
   void tearDown() {}

	bool wasCalled;
public:

	void testStringsPassedAreMappedToAStep()
	{	
		wasCalled= false;
		WHEN << "a string " << lit("any descriptive requisit") << "mapped to a step was formed" << OK;
		THEN << "the step should be called" << OK;
	}

	void testStringsPassedThatNotMapToAStepShouldThrow()
	{
		try {
			WHEN << "a string passed didnt have a method mapped" << OK;
			THEN << "that line should not be executed" << OK;

		} catch (std::runtime_error &) {
			THEN << "it should throw a exception" << OK;
		}
	}

	struct DummyClass {};

	void testPassingNotPrimitiveParametersToSteps()
	{
		//static setup
		//given << "i have a step with a not primitive parameter" << ok;
		DummyClass notPrimitiveParameter; 

		WHEN << "i describe a string passing a" << notPrimitiveParameter << OK;
		THEN << "the step called should have received the parameter" << notPrimitiveParameter << OK;
	}

	STEP1("i describe a string passing a", EnlightenTest, iDescribeAStringPassingA, EnlightenTest::DummyClass&)
	void iDescribeAStringPassingA( EnlightenTest::DummyClass &p1)
	{
		//TODO: verificar porque nao esta encontrando o step
		//e verificar se o parametro esta chegando direito
		
	}

	STEP1("the step called should have received the parameter", EnlightenTest
		, theStepCalledShouldHaveReceivedTheParameter,  EnlightenTest::DummyClass&)
	void theStepCalledShouldHaveReceivedTheParameter( EnlightenTest::DummyClass &p1)

	{   
	}

	STEP("the step should be called", EnlightenTest, theStepShouldBeCalled)
	void theStepShouldBeCalled()
	{
		CPPUNIT_ASSERT(wasCalled);
	}

	STEP("any descriptive requisit", EnlightenTest, anyDescriptiveRequisit)
	void anyDescriptiveRequisit() 
	{
		wasCalled= true;
	}

	STEP1("a string mapped to a step was formed", EnlightenTest, aStringMappedToAStepWasFormed, std::string)
	void aStringMappedToAStepWasFormed(std::string p1)
	{
		GIVEN << p1.c_str() << OK;
	}

	STEP("a string passed didnt have a method mapped", EnlightenTest, aStringPassedDidntHaveAMethodMapped)
	void aStringPassedDidntHaveAMethodMapped()
	{
		WHEN << "a unknow string" << OK;
	}

	STEP("it should throw a exception", EnlightenTest, itShouldThrowAException)
	void itShouldThrowAException()
	{
		CPPUNIT_ASSERT(true);
	}

	STEP("that line should not be executed", EnlightenTest, thatLineShouldNotBeExecuted)
	void thatLineShouldNotBeExecuted()
	{
		CPPUNIT_ASSERT(false);
	}

   void testGivenWhenThen()
   {
      GIVEN << "i have " << 1 << "apple" << OK;
      WHEN << "i buy " << 2 << "apple(s)" << OK;
      THEN << "i should have " << 3 << "apples" << OK;
   }

	int apples;

	STEP1("i have apple", EnlightenTest, iHaveApple, int)
	void iHaveApple(int p1)
	{
		apples = p1;
	}

	STEP1("i buy apple(s)", EnlightenTest, iBuyApple, int)
	void iBuyApple(int p1)
	{
		apples+= p1;	
	}
	STEP1("i should have apples", EnlightenTest, iShouldHaveapples, int)
	void iShouldHaveapples(int p1)
	{
		CPPUNIT_ASSERT_EQUAL((int)p1, apples);
	}
};

////////////////////////////////////////////////////////////////////////////////

CPPUNIT_TEST_SUITE_REGISTRATION(EnlightenTest);