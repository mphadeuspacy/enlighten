## What's this? ##

Enlighten is a behaviour driven development library for c++ inspired in Cucumber, GivWhenZen and GWT4Cpp (cppfitnesse trunk).

What enlighten is about?
  * a design tool
  * a tiny framework that transforms high-level meaningful sentences in calls for methods (steps)
  * a BDD style tool direct in unit tests

and yes! BDD is about sintatic sugar!

**Updated! Added support to Igloo BDD Framework**

Tested with:

  * cppunit light
  * [google test](http://code.google.com/p/googletest/)
  * [igloo](http://igloo-testing.org/)


## One-minute Tutorial ##

1. write the test in a natural language

```
void testBuyApplesScenario()
{
   GIVEN << "i have " << 1 << "apple" << OK;
   WHEN << "i buy " << 2 << "apples " << OK;
   THEN << "i should have "<< 3 << "apples" << OK;
}

```

2. compiles and run should fail with this output:

```
- you must define the step:

i have apple

you can implement the step definition with this snippet:

STEP1("i have apple", AppleTest, iHaveApple, int)
void iHaveApple(int p1)
{
pending
}

```

3. create the step with the snippet. Should fail with the others steps. Fix all.

4. write the code that does what the step describe.

5. repeat until you have the feature