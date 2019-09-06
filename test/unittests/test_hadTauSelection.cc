#include <cppunit/extensions/HelperMacros.h> // CppUnit::TestFixture, CPPUNIT_ASSERT_*

#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorFakeable.h"
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h"

#define SELECTOR_ERA kEra_2017
#define SELECTOR_DBG true

#define FAKEABLE_DR03MVA "dR03mvaVLoose"
#define FAKEABLE_DEEPVSJ "deepVSjVVVLoose"

class Test_tthHadTauSelection
  : public CppUnit::TestFixture
{

  CPPUNIT_TEST_SUITE(Test_tthHadTauSelection);
  //
  CPPUNIT_TEST(test_set_dR03mvaVVLoose);
  CPPUNIT_TEST(test_set_dR03mvaVLoose);
  CPPUNIT_TEST(test_set_dR03mvaLoose);
  CPPUNIT_TEST(test_set_dR03mvaMedium);
  CPPUNIT_TEST(test_set_dR03mvaTight);
  CPPUNIT_TEST(test_set_dR03mvaVTight);
  CPPUNIT_TEST(test_set_dR03mvaVVTight);
  //
  CPPUNIT_TEST(test_set_deepVSjVVVLoose);
  CPPUNIT_TEST(test_set_deepVSjVVLoose);
  CPPUNIT_TEST(test_set_deepVSjVLoose);
  CPPUNIT_TEST(test_set_deepVSjLoose);
  CPPUNIT_TEST(test_set_deepVSjMedium);
  CPPUNIT_TEST(test_set_deepVSjTight);
  CPPUNIT_TEST(test_set_deepVSjVTight);
  CPPUNIT_TEST(test_set_deepVSjVVTight);
  //
  CPPUNIT_TEST(test_set_if_looser_dR03mvaVVLoose);
  CPPUNIT_TEST(test_set_if_looser_dR03mvaVLoose);
  CPPUNIT_TEST(test_set_if_looser_dR03mvaLoose);
  CPPUNIT_TEST(test_set_if_looser_dR03mvaMedium);
  CPPUNIT_TEST(test_set_if_looser_dR03mvaTight);
  CPPUNIT_TEST(test_set_if_looser_dR03mvaVTight);
  CPPUNIT_TEST(test_set_if_looser_dR03mvaVVTight);
  //
  CPPUNIT_TEST(test_set_if_looser_deepVSjVVVLoose);
  CPPUNIT_TEST(test_set_if_looser_deepVSjVVLoose);
  CPPUNIT_TEST(test_set_if_looser_deepVSjVLoose);
  CPPUNIT_TEST(test_set_if_looser_deepVSjLoose);
  CPPUNIT_TEST(test_set_if_looser_deepVSjMedium);
  CPPUNIT_TEST(test_set_if_looser_deepVSjTight);
  CPPUNIT_TEST(test_set_if_looser_deepVSjVTight);
  CPPUNIT_TEST(test_set_if_looser_deepVSjVVTight);
  //
  CPPUNIT_TEST(test_set_dR03mvaVVLooseORdR05mvaVVLooseORdeepVSjVVVLoose);
  CPPUNIT_TEST(test_set_if_looser_dR03mvaVVLooseORdR05mvaVVLooseORdeepVSjVVVLoose);
  //
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

  //

  void
  test_set_dR03mvaVVLoose()
  {
    RecoHadTauCollectionSelectorFakeable selector(SELECTOR_ERA, -1, SELECTOR_DBG);
    selector.set("dR03mvaVVLoose");
    CPPUNIT_ASSERT(selector.getSelector().get() == "dR03mvaVVLoose");
  }

  void
  test_set_dR03mvaVLoose()
  {
    RecoHadTauCollectionSelectorFakeable selector(SELECTOR_ERA, -1, SELECTOR_DBG);
    selector.set("dR03mvaVLoose");
    CPPUNIT_ASSERT(selector.getSelector().get() == "dR03mvaVLoose");
  }

  void
  test_set_dR03mvaLoose()
  {
    RecoHadTauCollectionSelectorFakeable selector(SELECTOR_ERA, -1, SELECTOR_DBG);
    selector.set("dR03mvaLoose");
    CPPUNIT_ASSERT(selector.getSelector().get() == "dR03mvaLoose");
  }

  void
  test_set_dR03mvaMedium()
  {
    RecoHadTauCollectionSelectorFakeable selector(SELECTOR_ERA, -1, SELECTOR_DBG);
    selector.set("dR03mvaMedium");
    CPPUNIT_ASSERT(selector.getSelector().get() == "dR03mvaMedium");
  }

  void
  test_set_dR03mvaTight()
  {
    RecoHadTauCollectionSelectorFakeable selector(SELECTOR_ERA, -1, SELECTOR_DBG);
    selector.set("dR03mvaTight");
    CPPUNIT_ASSERT(selector.getSelector().get() == "dR03mvaTight");
  }

  void
  test_set_dR03mvaVTight()
  {
    RecoHadTauCollectionSelectorFakeable selector(SELECTOR_ERA, -1, SELECTOR_DBG);
    selector.set("dR03mvaVTight");
    CPPUNIT_ASSERT(selector.getSelector().get() == "dR03mvaVTight");
  }

  void
  test_set_dR03mvaVVTight()
  {
    RecoHadTauCollectionSelectorFakeable selector(SELECTOR_ERA, -1, SELECTOR_DBG);
    selector.set("dR03mvaVVTight");
    CPPUNIT_ASSERT(selector.getSelector().get() == "dR03mvaVVTight");
  }

  //

  void
  test_set_deepVSjVVVLoose()
  {
    RecoHadTauCollectionSelectorFakeable selector(SELECTOR_ERA, -1, SELECTOR_DBG);
    selector.set("deepVSjVVVLoose");
    CPPUNIT_ASSERT(selector.getSelector().get() == "deepVSjVVVLoose");
  }

  void
  test_set_deepVSjVVLoose()
  {
    RecoHadTauCollectionSelectorFakeable selector(SELECTOR_ERA, -1, SELECTOR_DBG);
    selector.set("deepVSjVVLoose");
    CPPUNIT_ASSERT(selector.getSelector().get() == "deepVSjVVLoose");
  }

  void
  test_set_deepVSjVLoose()
  {
    RecoHadTauCollectionSelectorFakeable selector(SELECTOR_ERA, -1, SELECTOR_DBG);
    selector.set("deepVSjVLoose");
    CPPUNIT_ASSERT(selector.getSelector().get() == "deepVSjVLoose");
  }

  void
  test_set_deepVSjLoose()
  {
    RecoHadTauCollectionSelectorFakeable selector(SELECTOR_ERA, -1, SELECTOR_DBG);
    selector.set("deepVSjLoose");
    CPPUNIT_ASSERT(selector.getSelector().get() == "deepVSjLoose");
  }

  void
  test_set_deepVSjMedium()
  {
    RecoHadTauCollectionSelectorFakeable selector(SELECTOR_ERA, -1, SELECTOR_DBG);
    selector.set("deepVSjMedium");
    CPPUNIT_ASSERT(selector.getSelector().get() == "deepVSjMedium");
  }

  void
  test_set_deepVSjTight()
  {
    RecoHadTauCollectionSelectorFakeable selector(SELECTOR_ERA, -1, SELECTOR_DBG);
    selector.set("deepVSjTight");
    CPPUNIT_ASSERT(selector.getSelector().get() == "deepVSjTight");
  }

  void
  test_set_deepVSjVTight()
  {
    RecoHadTauCollectionSelectorFakeable selector(SELECTOR_ERA, -1, SELECTOR_DBG);
    selector.set("deepVSjVTight");
    CPPUNIT_ASSERT(selector.getSelector().get() == "deepVSjVTight");
  }

  void
  test_set_deepVSjVVTight()
  {
    RecoHadTauCollectionSelectorFakeable selector(SELECTOR_ERA, -1, SELECTOR_DBG);
    selector.set("deepVSjVVTight");
    CPPUNIT_ASSERT(selector.getSelector().get() == "deepVSjVVTight");
  }

  //

  void
  test_set_if_looser_dR03mvaVVLoose()
  {
    RecoHadTauCollectionSelectorFakeable selector(SELECTOR_ERA, -1, SELECTOR_DBG);
    selector.set_if_looser("dR03mvaVVLoose");
    CPPUNIT_ASSERT(selector.getSelector().get() == "dR03mvaVVLoose");
  }

  void
  test_set_if_looser_dR03mvaVLoose()
  {
    RecoHadTauCollectionSelectorFakeable selector(SELECTOR_ERA, -1, SELECTOR_DBG);
    selector.set_if_looser("dR03mvaVLoose");
    CPPUNIT_ASSERT(selector.getSelector().get() == FAKEABLE_DR03MVA);
  }

  void
  test_set_if_looser_dR03mvaLoose()
  {
    RecoHadTauCollectionSelectorFakeable selector(SELECTOR_ERA, -1, SELECTOR_DBG);
    selector.set_if_looser("dR03mvaLoose");
    CPPUNIT_ASSERT(selector.getSelector().get() == FAKEABLE_DR03MVA);
  }

  void
  test_set_if_looser_dR03mvaMedium()
  {
    RecoHadTauCollectionSelectorFakeable selector(SELECTOR_ERA, -1, SELECTOR_DBG);
    selector.set_if_looser("dR03mvaMedium");
    CPPUNIT_ASSERT(selector.getSelector().get() == FAKEABLE_DR03MVA);
  }

  void
  test_set_if_looser_dR03mvaTight()
  {
    RecoHadTauCollectionSelectorFakeable selector(SELECTOR_ERA, -1, SELECTOR_DBG);
    selector.set_if_looser("dR03mvaTight");
    CPPUNIT_ASSERT(selector.getSelector().get() == FAKEABLE_DR03MVA);
  }

  void
  test_set_if_looser_dR03mvaVTight()
  {
    RecoHadTauCollectionSelectorFakeable selector(SELECTOR_ERA, -1, SELECTOR_DBG);
    selector.set_if_looser("dR03mvaVTight");
    CPPUNIT_ASSERT(selector.getSelector().get() == FAKEABLE_DR03MVA);
  }

  void
  test_set_if_looser_dR03mvaVVTight()
  {
    RecoHadTauCollectionSelectorFakeable selector(SELECTOR_ERA, -1, SELECTOR_DBG);
    selector.set_if_looser("dR03mvaVVTight");
    CPPUNIT_ASSERT(selector.getSelector().get() == FAKEABLE_DR03MVA);
  }

  //

  void
  test_set_if_looser_deepVSjVVVLoose()
  {
    RecoHadTauCollectionSelectorFakeable selector(SELECTOR_ERA, -1, SELECTOR_DBG);
    selector.set_if_looser("deepVSjVVVLoose");
    CPPUNIT_ASSERT(selector.getSelector().get() == FAKEABLE_DEEPVSJ);
  }

  void
  test_set_if_looser_deepVSjVVLoose()
  {
    RecoHadTauCollectionSelectorFakeable selector(SELECTOR_ERA, -1, SELECTOR_DBG);
    selector.set_if_looser("deepVSjVVLoose");
    CPPUNIT_ASSERT(selector.getSelector().get() == FAKEABLE_DEEPVSJ);
  }

  void
  test_set_if_looser_deepVSjVLoose()
  {
    RecoHadTauCollectionSelectorFakeable selector(SELECTOR_ERA, -1, SELECTOR_DBG);
    selector.set_if_looser("deepVSjVLoose");
    CPPUNIT_ASSERT(selector.getSelector().get() == FAKEABLE_DEEPVSJ);
  }

  void
  test_set_if_looser_deepVSjLoose()
  {
    RecoHadTauCollectionSelectorFakeable selector(SELECTOR_ERA, -1, SELECTOR_DBG);
    selector.set_if_looser("deepVSjLoose");
    CPPUNIT_ASSERT(selector.getSelector().get() == FAKEABLE_DEEPVSJ);
  }

  void
  test_set_if_looser_deepVSjMedium()
  {
    RecoHadTauCollectionSelectorFakeable selector(SELECTOR_ERA, -1, SELECTOR_DBG);
    selector.set_if_looser("deepVSjMedium");
    CPPUNIT_ASSERT(selector.getSelector().get() == FAKEABLE_DEEPVSJ);
  }

  void
  test_set_if_looser_deepVSjTight()
  {
    RecoHadTauCollectionSelectorFakeable selector(SELECTOR_ERA, -1, SELECTOR_DBG);
    selector.set_if_looser("deepVSjTight");
    CPPUNIT_ASSERT(selector.getSelector().get() == FAKEABLE_DEEPVSJ);
  }

  void
  test_set_if_looser_deepVSjVTight()
  {
    RecoHadTauCollectionSelectorFakeable selector(SELECTOR_ERA, -1, SELECTOR_DBG);
    selector.set_if_looser("deepVSjVTight");
    CPPUNIT_ASSERT(selector.getSelector().get() == FAKEABLE_DEEPVSJ);
  }

  void
  test_set_if_looser_deepVSjVVTight()
  {
    RecoHadTauCollectionSelectorFakeable selector(SELECTOR_ERA, -1, SELECTOR_DBG);
    selector.set_if_looser("deepVSjVVTight");
    CPPUNIT_ASSERT(selector.getSelector().get() == FAKEABLE_DEEPVSJ);
  }

  //

  void
  test_set_dR03mvaVVLooseORdR05mvaVVLooseORdeepVSjVVVLoose()
  {
    RecoHadTauCollectionSelectorFakeable selector(SELECTOR_ERA, -1, SELECTOR_DBG);
    selector.set("dR03mvaVVLoose&dR05mvaVVLoose&deepVSjVVVLoose");
    CPPUNIT_ASSERT(selector.getSelector().get() == "dR03mvaVVLoose&dR05mvaVVLoose&deepVSjVVVLoose");
  }

  void
  test_set_if_looser_dR03mvaVVLooseORdR05mvaVVLooseORdeepVSjVVVLoose()
  {
    RecoHadTauCollectionSelectorFakeable selector(SELECTOR_ERA, -1, SELECTOR_DBG);
    selector.set_if_looser("dR03mvaVVLoose&dR05mvaVVLoose&deepVSjVVVLoose");
    CPPUNIT_ASSERT(selector.getSelector().get() == "dR03mvaVVLoose&dR05mvaVVLoose&deepVSjVVVLoose");
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(Test_tthHadTauSelection);

