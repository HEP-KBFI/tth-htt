import FWCore.ParameterSet.Config as cms

import os

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring(),
    
    ##maxEvents = cms.int32(100000),
    maxEvents = cms.int32(-1),
    
    outputEvery = cms.uint32(100000)
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('prepareDatacards.root')
)

process.prepareDatacards = cms.PSet(

    processesToCopy = cms.vstring(
        "data_obs",
	    "DY",
        "DY_fake", 
	    "WJets", 
	    "Singletop", 
	    "Diboson", 
	    "TTbar"
    ),

    sf_signal = cms.double(1.),
    signals = cms.vstring(
        "DY"
    ),

    categories = cms.VPSet(
        cms.PSet(
            input = cms.string("SS/BB_LL"),	
            output = cms.string("SS/BB_LL")            
        )
    ),   
    namedCategories = cms.bool(True),

    histogramToFit = cms.string("mass_ll"),
    histogramToFit_rebin = cms.int32(1),

    setBinsToZeroBelow = cms.double(-1.),

    sysShifts = cms.vstring(
        "CMS_ttHl_electronESBarrelUp",
    	"CMS_ttHl_electronESBarrelDown",
    	"CMS_ttHl_electronESEndcapUp",
	    "CMS_ttHl_electronESEndcapDown",
	    "CMS_ttHl_electronERUp",
	    "CMS_ttHl_electronERDown"
    )
)
