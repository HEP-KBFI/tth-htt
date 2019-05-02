import FWCore.ParameterSet.Config as cms

triggers_mu_cfg_2016 = cms.VPSet(
  cms.PSet(
    path = cms.vstring("HLT_Mu27"),
    cone_minPt = cms.double(45.),
    cone_maxPt = cms.double(100000.),
    jet_minPt = cms.double(30.),
#    pufile    = cms.FileInPath(""), # PU file to be implemented later
    average_prescale = cms.double(143), # prescale factor 143.4 (143.0 from delivery)
    prescale_rand_mc = cms.double(5.),
    is_trigger_1mu = cms.bool(True),
    is_trigger_2mu = cms.bool(False),
    is_trigger_1e = cms.bool(False),
    is_trigger_2e = cms.bool(False)
  ),
  cms.PSet(
    path = cms.vstring("HLT_Mu17"),
    cone_minPt = cms.double(30.),
    cone_maxPt = cms.double(100000.),
    jet_minPt = cms.double(30.),
#    pufile    = cms.FileInPath(""), # PU file to be implemented later
    average_prescale = cms.double(127), # prescale factor 127.0 (127.4 from delivery)
    prescale_rand_mc = cms.double(5.),
    is_trigger_1mu = cms.bool(False),
    is_trigger_2mu = cms.bool(True),
    is_trigger_1e = cms.bool(False),
    is_trigger_2e = cms.bool(False)
  ),
  cms.PSet(
    path = cms.vstring("HLT_Mu8"),
    cone_minPt = cms.double(15.),
    cone_maxPt = cms.double(45.),
    jet_minPt = cms.double(30.),
#    pufile    = cms.FileInPath(""), # PU file to be implemented later
    average_prescale = cms.double(9123), # prescale factor 9123.1 (9081.0 from delivery)
    prescale_rand_mc = cms.double(100.),
    is_trigger_1mu = cms.bool(False),
    is_trigger_2mu = cms.bool(True),
    is_trigger_1e = cms.bool(False),
    is_trigger_2e = cms.bool(False)
  ),
  cms.PSet(
    path = cms.vstring("HLT_Mu3_PFJet40"),
    cone_minPt = cms.double(10.),
    cone_maxPt = cms.double(30.),
    jet_minPt = cms.double(40.),
#    pufile    = cms.FileInPath(""), # PU file to be implemented later
    average_prescale = cms.double(4849), # prescale factor 4849.0 (4863.2 from delivery)
    prescale_rand_mc = cms.double(50.),
    is_trigger_1mu = cms.bool(False),
    is_trigger_2mu = cms.bool(True),
    is_trigger_1e = cms.bool(False),
    is_trigger_2e = cms.bool(False)
  )
)

triggers_e_cfg_2016 = cms.VPSet(
  cms.PSet(
    path = cms.vstring("HLT_Ele17_CaloIdM_TrackIdM_PFJet30"),
    cone_minPt = cms.double(30.),
    cone_maxPt = cms.double(100000.),
    jet_minPt = cms.double(30.),
#    pufile    = cms.FileInPath(""), # PU file to be implemented later
    average_prescale = cms.double(572), # prescale factor 572.4 (573.4 from delivery)
    prescale_rand_mc = cms.double(10.),
    is_trigger_1mu = cms.bool(False),
    is_trigger_2mu = cms.bool(False),
    is_trigger_1e = cms.bool(False),
    is_trigger_2e = cms.bool(True)
  ),
  cms.PSet(
    path = cms.vstring("HLT_Ele12_CaloIdM_TrackIdM_PFJet30"),
    cone_minPt = cms.double(20.),
    cone_maxPt = cms.double(30.),
    jet_minPt = cms.double(30.),
#    pufile    = cms.FileInPath(""), # PU file to be implemented later
    average_prescale = cms.double(2028), # prescale factor 2027.9 (2032.1 from delivery)
    prescale_rand_mc = cms.double(25.),
    is_trigger_1mu = cms.bool(False),
    is_trigger_2mu = cms.bool(False),
    is_trigger_1e = cms.bool(False),
    is_trigger_2e = cms.bool(True)
  )
)

triggers_mu_cfg_2017 = cms.VPSet(
  cms.PSet(
    path = cms.string("HLT_Mu27"),
    cone_minPt = cms.double(45.),
    cone_maxPt = cms.double(100.),
    minRecoPt = cms.double(27.), # added after syncing w/ Giovanni
    jet_minPt = cms.double(30.),
#    pufile    = cms.FileInPath(""), # PU file to be implemented later
    average_prescale = cms.double(225), # prescale factor 224.5 (216.1 from delivery)
    is_trigger_1mu = cms.bool(True),
    is_trigger_2mu = cms.bool(False),
    is_trigger_1e = cms.bool(False),
    is_trigger_2e = cms.bool(False)
  ),
  cms.PSet(
    path = cms.string("HLT_Mu20"),
    cone_minPt = cms.double(32.),
    cone_maxPt = cms.double(100.),
    minRecoPt = cms.double(20.), # added after syncing w/ Giovanni
    jet_minPt = cms.double(30.),
#    pufile    = cms.FileInPath(""), # PU file to be implemented later
    average_prescale = cms.double(72), # prescale factor 72.3 (73.9 from delivery)
    is_trigger_1mu = cms.bool(True),
    is_trigger_2mu = cms.bool(False),
    is_trigger_1e = cms.bool(False),
    is_trigger_2e = cms.bool(False)
  ),
  cms.PSet(
    path = cms.string("HLT_Mu17"),
    cone_minPt = cms.double(32.),
    cone_maxPt = cms.double(100.),
    minRecoPt = cms.double(17.), # added after syncing w/ Giovanni
    jet_minPt = cms.double(30.),
#    pufile    = cms.FileInPath(""), # PU file to be implemented later
    average_prescale = cms.double(593), # prescale factor 592.9 (600.1 from delivery)
    is_trigger_1mu = cms.bool(False),
    is_trigger_2mu = cms.bool(True),
    is_trigger_1e = cms.bool(False),
    is_trigger_2e = cms.bool(False)
  ),
  cms.PSet(
    path = cms.string("HLT_Mu8"),
    cone_minPt = cms.double(15.),
    cone_maxPt = cms.double(45.),
    minRecoPt = cms.double(8.), # added after syncing w/ Giovanni
    jet_minPt = cms.double(30.),
#    pufile    = cms.FileInPath(""), # PU file to be implemented later
    average_prescale = cms.double(15943), # prescale factor 15943.0 (15120.6 from delivery)
    is_trigger_1mu = cms.bool(False),
    is_trigger_2mu = cms.bool(True),
    is_trigger_1e = cms.bool(False),
    is_trigger_2e = cms.bool(False)
  ),
  cms.PSet(
    path = cms.string("HLT_Mu3_PFJet40"),
    cone_minPt = cms.double(10.),
    cone_maxPt = cms.double(32.),
    minRecoPt = cms.double(-1.), # added after syncing w/ Giovanni
    jet_minPt = cms.double(45.),
#    pufile    = cms.FileInPath(""), # PU file to be implemented later
    average_prescale = cms.double(9006), # prescale factor 9005.6 (8870.8 from delivery)
    is_trigger_1mu = cms.bool(True),
    is_trigger_2mu = cms.bool(False),
    is_trigger_1e = cms.bool(False),
    is_trigger_2e = cms.bool(False)
  )
)

triggers_e_cfg_2017 = cms.VPSet(
  cms.PSet(
    path = cms.string("HLT_Ele8_CaloIdM_TrackIdM_PFJet30"),
    cone_minPt = cms.double(15.),
    cone_maxPt = cms.double(45.),
    minRecoPt = cms.double(8.), # added after syncing w/ Giovanni
    jet_minPt = cms.double(30.),
#    pufile    = cms.FileInPath(""), # PU file to be implemented later
    average_prescale = cms.double(11364), # prescale factor 11363.9 (11029.2 from delivery)
    is_trigger_1mu = cms.bool(False),
    is_trigger_2mu = cms.bool(False),
    is_trigger_1e = cms.bool(True),
    is_trigger_2e = cms.bool(False)
  ),
  cms.PSet(
    path = cms.string("HLT_Ele17_CaloIdM_TrackIdM_PFJet30"),
    cone_minPt = cms.double(25.),
    cone_maxPt = cms.double(100.),
    minRecoPt = cms.double(17.), # added after syncing w/ Giovanni
    jet_minPt = cms.double(30.),
#    pufile    = cms.FileInPath(""), # PU file to be implemented later
    average_prescale = cms.double(1167), # prescale factor 1166.8 (1181.3 from delivery)
    is_trigger_1mu = cms.bool(False),
    is_trigger_2mu = cms.bool(False),
    is_trigger_1e = cms.bool(True),
    is_trigger_2e = cms.bool(False)
  ),
  cms.PSet(
    path = cms.string("HLT_Ele23_CaloIdM_TrackIdM_PFJet30"),
    cone_minPt = cms.double(32.),
    cone_maxPt = cms.double(100.),
    minRecoPt = cms.double(23.), # added after syncing w/ Giovanni
    jet_minPt = cms.double(30.),
#    pufile    = cms.FileInPath(""), # PU file to be implemented later
    average_prescale = cms.double(1087), # prescale factor 1086.7 (1101.5 from delivery)
    is_trigger_1mu = cms.bool(False),
    is_trigger_2mu = cms.bool(False),
    is_trigger_1e = cms.bool(True),
    is_trigger_2e = cms.bool(False)
  )
)

triggers_mu_cfg_2018 = cms.VPSet(
  cms.PSet(
    path = cms.string("HLT_Mu27"),
    cone_minPt = cms.double(45.),
    cone_maxPt = cms.double(100.),
    minRecoPt = cms.double(27.),
    jet_minPt = cms.double(30.),
#    pufile    = cms.FileInPath(""), # PU file to be implemented later
    average_prescale = cms.double(475), # prescale factor 475.0 (464.6 from delivery)
    is_trigger_1mu = cms.bool(True),
    is_trigger_2mu = cms.bool(False),
    is_trigger_1e = cms.bool(False),
    is_trigger_2e = cms.bool(False)
  ),
  cms.PSet(
    path = cms.string("HLT_Mu20"),
    cone_minPt = cms.double(32.),
    cone_maxPt = cms.double(100.),
    minRecoPt = cms.double(20.),
    jet_minPt = cms.double(30.),
#    pufile    = cms.FileInPath(""), # PU file to be implemented later
    average_prescale = cms.double(1081), # prescale factor 1080.8 (1082.1 from delivery)
    is_trigger_1mu = cms.bool(True),
    is_trigger_2mu = cms.bool(False),
    is_trigger_1e = cms.bool(False),
    is_trigger_2e = cms.bool(False)
  ),
  cms.PSet(
    path = cms.string("HLT_Mu17"),
    cone_minPt = cms.double(32.),
    cone_maxPt = cms.double(100.),
    minRecoPt = cms.double(17.),
    jet_minPt = cms.double(30.),
#    pufile    = cms.FileInPath(""), # PU file to be implemented later
    average_prescale = cms.double(1305), # prescale factor 1304.9 (1307.1 from delivery)
    is_trigger_1mu = cms.bool(False),
    is_trigger_2mu = cms.bool(True),
    is_trigger_1e = cms.bool(False),
    is_trigger_2e = cms.bool(False)
  ),
  cms.PSet(
    path = cms.string("HLT_Mu8"),
    cone_minPt = cms.double(15.),
    cone_maxPt = cms.double(45.),
    minRecoPt = cms.double(8.),
    jet_minPt = cms.double(30.),
#    pufile    = cms.FileInPath(""), # PU file to be implemented later
    average_prescale = cms.double(6990), # prescale factor 6990.5 (6981.9 from delivery)
    is_trigger_1mu = cms.bool(False),
    is_trigger_2mu = cms.bool(True),
    is_trigger_1e = cms.bool(False),
    is_trigger_2e = cms.bool(False)
  ),
  cms.PSet(
    path = cms.string("HLT_Mu3_PFJet40"),
    cone_minPt = cms.double(10.),
    cone_maxPt = cms.double(32.),
    minRecoPt = cms.double(-1.),
    jet_minPt = cms.double(45.),
#    pufile    = cms.FileInPath(""), # PU file to be implemented later
    average_prescale = cms.double(22160), # prescale factor 22160.5 (22182.4 from delivery)
    is_trigger_1mu = cms.bool(True),
    is_trigger_2mu = cms.bool(False),
    is_trigger_1e = cms.bool(False),
    is_trigger_2e = cms.bool(False)
  )
)

triggers_e_cfg_2018 = cms.VPSet(
  cms.PSet(
    path = cms.string("HLT_Ele8_CaloIdM_TrackIdM_PFJet30"),
    cone_minPt = cms.double(15.),
    cone_maxPt = cms.double(45.),
    minRecoPt = cms.double(8.),
    jet_minPt = cms.double(30.),
#    pufile    = cms.FileInPath(""), # PU file to be implemented later
    average_prescale = cms.double(9318), # prescale factor 9318.5 (9325.6 from delivery)
    is_trigger_1mu = cms.bool(False),
    is_trigger_2mu = cms.bool(False),
    is_trigger_1e = cms.bool(True),
    is_trigger_2e = cms.bool(False)
  ),
  cms.PSet(
    path = cms.string("HLT_Ele17_CaloIdM_TrackIdM_PFJet30"),
    cone_minPt = cms.double(25.),
    cone_maxPt = cms.double(100.),
    minRecoPt = cms.double(17.),
    jet_minPt = cms.double(30.),
#    pufile    = cms.FileInPath(""), # PU file to be implemented later
    average_prescale = cms.double(1537), # prescale factor 1537.3 (1538.9 from delivery)
    is_trigger_1mu = cms.bool(False),
    is_trigger_2mu = cms.bool(False),
    is_trigger_1e = cms.bool(True),
    is_trigger_2e = cms.bool(False)
  ),
  cms.PSet(
    path = cms.string("HLT_Ele23_CaloIdM_TrackIdM_PFJet30"),
    cone_minPt = cms.double(32.),
    cone_maxPt = cms.double(100.),
    minRecoPt = cms.double(23.),
    jet_minPt = cms.double(30.),
#    pufile    = cms.FileInPath(""), # PU file to be implemented later
    average_prescale = cms.double(1537), # prescale factor 1536.7 (1538.4 from delivery)
    is_trigger_1mu = cms.bool(False),
    is_trigger_2mu = cms.bool(False),
    is_trigger_1e = cms.bool(True),
    is_trigger_2e = cms.bool(False)
  )
)
