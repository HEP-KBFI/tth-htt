#include <cppunit/extensions/TestFactoryRegistry.h> // CppUnit::TestFactoryRegistry
#include <cppunit/ui/text/TestRunner.h> // CppUnit::TextUi::TestRunner
#include <cppunit/CompilerOutputter.h> // CppUnit::CompilerOutputter, CppUnit::Test

/**
 * @brief The main cppunit test suite
 * @return 0 if the test are successful, 1 otherwise
 *
 * In order to run the tests, you first have to build the project
 *    `scram b -j8`
 * and then run the test suite with
 *    `scram b -j8 runtests`
 * The test results are printed on the screen and can be later looked up from
 *    `$CMSSW_BASE/logs/$SCRAM_ARCH/testing.log`
 */

int
main()
{
  CppUnit::Test * suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(suite);
  runner.setOutputter(new CppUnit::CompilerOutputter(&runner.result(), std::cout));
  const bool wasSuccessful = runner.run();

  return wasSuccessful ? EXIT_SUCCESS : EXIT_FAILURE;
}
