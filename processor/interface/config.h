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
        "GenLepMatch2l",
	"nLepton" ,
	"Lepton_pt",
	"Lepton_eta" ,
	"Lepton_phi" ,
	"Lepton_pdgId" ,
	"nCleanJet" ,
	"CleanJet_pt" ,
	"CleanJet_eta" ,
	"CleanJet_phi" ,
	"PuppiMET_pt" ,
	"mlljj20_whss" ,
	"mjj" ,
	"mll" ,
        "gen_promptmatch",
	"LepCut2l__ele_mu_HWW_ttHMVA" , 
	"LepSF2l__ele_mu_HWW_ttHMVA"
      }
    }
  };
  
};

#endif
