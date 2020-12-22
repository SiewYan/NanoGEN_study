#ifndef CONFIG_H
#define CONFIG_H


typedef std::map<std::string, std::map<std::string, std::map<std::string, std::map<std::string, std::list<std::string>>>>> nested_dict;
typedef std::map<std::string,std::string> Lep_dict;

/*
 * configuration for ntuple
 */
struct config_t {
  // basic
  bool isMC=false;
  std::string year;
  std::string lumi;
  std::string base;
  nested_dict SF_files_map;
  const unsigned int nlep_SF=2;

  Lep_dict HWW_WP = {
    { "2016" , "LepCut2l__ele_mva_90p_Iso2016__mu_cut_Tight80x" } ,
    { "2017" , "LepCut2l__ele_mvaFall17V1Iso_WP90__mu_cut_Tight_HWWW" } ,
    { "2018" , "LepCut2l__ele_mvaFall17V1Iso_WP90__mu_cut_Tight_HWWW" }
  };

  Lep_dict HWW_WP_SF = {
    { "2016" , "LepSF2l__ele_mva_90p_Iso2016__mu_cut_Tight80x" } ,
    { "2017" , "LepSF2l__ele_mvaFall17V1Iso_WP90__mu_cut_Tight_HWWW" } ,
    { "2018" , "LepSF2l__ele_mvaFall17V1Iso_WP90__mu_cut_Tight_HWWW" }
  };

  // SingleElectron
  // 2016 : HLT Ele27 WPTight Gsf v* || HLT Ele25 eta2p1 WPTight Gsf v*
  // 2017 : HLT Ele35 WPTight Gsf v*
  // 2018 : EGamma : HLT Ele32 WPTight Gsf v* || HLT Ele35 WPTight Gsf v* || HLT Ele23 Ele12 CaloIdL TrackIdL IsoVL v*
  Lep_dict SingleElectron_leptrigPt = {
    { "2016" , "32" }, // 27+5
    { "2017" , "40" }, // 35+5
    { "2018" , "37" }  // 32+5
  };

  // DoubleEG
  // 2016 : HLT Ele23 Ele12 CaloIdL TrackIdL IsoVL DZ v*
  // 2017 : HLT Ele23 Ele12 CaloIdL TrackIdL IsoVL v*
  // 2018 : EGamma : HLT Ele32 WPTight Gsf v* || HLT Ele35 WPTight Gsf v* || HLT Ele23 Ele12 CaloIdL TrackIdL IsoVL v*
  Lep_dict DoubleEG_leptrigPt = {
    { "2016" , "28" }, // 23+5
    { "2017" , "28" }, // 23+5
    { "2018" , "37" }  // 32+5
  };

  std::vector<TH2D> h_SF_ele {};
  std::vector<TH2D> h_SF_ele_ttHMVA {};
  
  std::vector<TH2D> h_SF_mu_Id {};
  std::vector<TH2D> h_SF_mu_Iso {};
  std::vector<TH2D> h_SF_mu_ttHMVA {};

  size_t listSize;

  std::map< const std::string , std::vector<std::string> > outBranch = {
    {
      "mc",{
        "PrefireWeight",
        "SFweight2l",
        "METFilter_MC",
        "XSWeight",
	"baseW" ,
        "GenLepMatch2l",
	"bVeto" ,
	"nLepton" ,
	"Lepton_pt",
	"Lepton_eta" ,
	"Lepton_phi" ,
	"Lepton_pdgId" ,
	"nCleanJet" ,
	"nJet" ,
	"CleanJet_pt" ,
	"CleanJet_eta" ,
	"CleanJet_phi" ,
	"CleanJet_jetIdx" ,
	"Jet_genJetIdx" ,
	"PuppiMET_pt" ,
	"mlljj20_whss" ,
	"mjj" ,
	"mll" ,
	"ptll" ,
	"dphill" ,
	"drll" ,
	"dphilljet" ,
	"dphilljetjet" ,
	"dphillmet" ,
	"dphilmet" ,
	"detajj" ,
	"dphijet1met" ,
	"dphijet2met" ,
	"dphijjmet" ,
	"dphilep1jet1" , 
	"dphilep1jet2" ,
	"dphilep2jet1" ,
	"dphilep2jet2" ,
	"mindetajl" ,
	"detall" ,
	"dphijj" ,
	"maxdphilepjj" ,
	"dphilep1jj" ,
	"dphilep2jj" ,
	"pTWW" ,
	"WlepPt_whss" , 
	"WlepMt_whss" ,
        "gen_promptmatch",
	"nGenJet" ,
	"GenJet_pt" ,
	"GenJet_eta" , 
	"GenJet_phi" ,
	"GenJet_mass" ,
	"GenJet_partonFlavour" ,
	"GenJet_hadronFlavour" ,
	"GenMET_phi" ,
	"GenMET_pt" ,
	"nLeptonGen" ,
	"LeptonGen_pdgId" ,
	"LeptonGen_status" ,
	"LeptonGen_pt" ,
	"LeptonGen_eta" ,
	"LeptonGen_phi" ,
	"LeptonGen_mass" ,
	"LeptonGen_fromHardProcess" ,
	"LeptonGen_isDirectHadronDecayProduct" ,
	"LeptonGen_isDirectPromptTauDecayProduct" ,
	"LeptonGen_isPrompt" ,
	"LeptonGen_isTauDecayProduct" ,
	"LeptonGen_MotherPID" ,
	"LeptonGen_MotherStatus" ,
	"Lepton_genmatched" ,
	"Lepton_promptgenmatched" ,
	"nGenPart" ,
	"GenPart_pt" ,
	"GenPart_eta" ,
	"GenPart_phi" ,
	"GenPart_mass" ,
	"GenPart_pdgId" ,
	"GenPart_status" ,
	"GenPart_genPartIdxMother" ,
	"GenPart_statusFlags" ,
	"higgsGenMass",
	"higgsGenPhi" ,
	"higgsGenEta" ,
	"higgsGenPt" ,
	"genVPt" ,
	"LepCut2l__ele_mu_HWW_ttHMVA" , 
	"LepSF2l__ele_mu_HWW_ttHMVA"
      }
    }
  };
  
};

#endif
