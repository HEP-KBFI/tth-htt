#include <cppunit/extensions/HelperMacros.h> // CppUnit::TestFixture, CPPUNIT_ASSERT_*

#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorFakeable.h"
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h"

#define SELECTOR_ERA kEra_2017
#define SELECTOR_DBG true

class Test_tthHadTauSelection
  : public CppUnit::TestFixture
{

  CPPUNIT_TEST_SUITE(Test_tthHadTauSelection);
  CPPUNIT_TEST(test_dR03mvaVLoose);
  CPPUNIT_TEST(test_dR03mvaLoose);
  CPPUNIT_TEST(test_dR03mvaMedium);
  CPPUNIT_TEST(test_dR03mvaTight);
  CPPUNIT_TEST(test_dR03mvaVTight);
  CPPUNIT_TEST(test_dR03mvaVVTight);
  CPPUNIT_TEST_SUITE_END();

public:

  void
  setUp() override
  {
    /* empty */
  }

  void
  tearDown() override
  {
    /* empty */
  }

  void
  test_dR03mvaVVLoose()
  {
    RecoHadTauCollectionSelectorFakeable selector(SELECTOR_ERA, -1, SELECTOR_DBG);
    selector.set_if_looser("dR03mvaVVLoose");
    CPPUNIT_ASSERT(selector.getSelector().get() == "dR03mvaVVLoose");
  }

  void
  test_dR03mvaVLoose()
  {
    RecoHadTauCollectionSelectorFakeable selector(SELECTOR_ERA, -1, SELECTOR_DBG);
    selector.set_if_looser("dR03mvaVLoose");
    CPPUNIT_ASSERT(selector.getSelector().get() == "dR03mvaVLoose");
  }

  void
  test_dR03mvaLoose()
  {
    RecoHadTauCollectionSelectorFakeable selector(SELECTOR_ERA, -1, SELECTOR_DBG);
    selector.set_if_looser("dR03mvaLoose");
    CPPUNIT_ASSERT(selector.getSelector().get() == "dR03mvaVLoose");
  }

  void
  test_dR03mvaMedium()
  {
    RecoHadTauCollectionSelectorFakeable selector(SELECTOR_ERA, -1, SELECTOR_DBG);
    selector.set_if_looser("dR03mvaMedium");
    CPPUNIT_ASSERT(selector.getSelector().get() == "dR03mvaVLoose");
  }

  void
  test_dR03mvaTight()
  {
    RecoHadTauCollectionSelectorFakeable selector(SELECTOR_ERA, -1, SELECTOR_DBG);
    selector.set_if_looser("dR03mvaTight");
    CPPUNIT_ASSERT(selector.getSelector().get() == "dR03mvaVLoose");
  }

  void
  test_dR03mvaVTight()
  {
    RecoHadTauCollectionSelectorFakeable selector(SELECTOR_ERA, -1, SELECTOR_DBG);
    selector.set_if_looser("dR03mvaVTight");
    CPPUNIT_ASSERT(selector.getSelector().get() == "dR03mvaVLoose");
  }

  void
  test_dR03mvaVVTight()
  {
    RecoHadTauCollectionSelectorFakeable selector(SELECTOR_ERA, -1, SELECTOR_DBG);
    selector.set_if_looser("dR03mvaVVTight");
    CPPUNIT_ASSERT(selector.getSelector().get() == "dR03mvaVLoose");
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(Test_tthHadTauSelection);

