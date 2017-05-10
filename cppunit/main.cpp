#include <iostream>
#include <string>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>


class Adder
{
public:
    int Add(int x, int y)
    {
        return x + y;
    }
};

class TestAdder : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestAdder);
    CPPUNIT_TEST(TestCase_Add);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp() { }
    void tearDown() { }

protected:
    void TestCase_Add()
    {
        Adder a;
        CPPUNIT_ASSERT(3 == a.Add(1, 2));
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestAdder);

int main(int argc, char** argv)
{
    CppUnit::TestResult testresult;

    CppUnit::TestResultCollector collectedresults;
    testresult.addListener(&collectedresults);

    CppUnit::BriefTestProgressListener progress;
    testresult.addListener(&progress);

    CppUnit::TestRunner testrunner;
    testrunner.addTest (CppUnit::TestFactoryRegistry::getRegistry().makeTest());
    testrunner.run(testresult);

    CppUnit::CompilerOutputter compileroutputter(&collectedresults, std::cerr);
    compileroutputter.write();

    std::ofstream xmlFileOut("cppTestBasicMathResults.xml");
    CppUnit::XmlOutputter xmlOut(&collectedresults, xmlFileOut);
    xmlOut.write();

    return collectedresults.wasSuccessful() ? 0 : 1;
}