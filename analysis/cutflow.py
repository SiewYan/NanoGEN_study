import ROOT
from ROOT import gROOT , gStyle
import os, sys
import time
from collections import OrderedDict

cwd = os.getcwd()
#lumi="35.92"
#lumi="41.53"
#lumi="59.74"
lumi="137.19"
wp="LepCut2l__ele_mva_90p_Iso2016__mu_cut_Tight80x*LepCut2l__ele_mu_HWW_ttHMVA*LepSF2l__ele_mu_HWW_ttHMVA"
commonMC="%s*SFweight2l*XSWeight*METFilter_MC*GenLepMatch2l*%s" %( lumi , wp )

df = ROOT.ROOT.RDataFrame( "Signals" , [ "../processor/output/sshwminus012j.root" , "../processor/output/sshwplus012j.root" ] )
df = df.Define( "weights" , commonMC )

dataframe=OrderedDict()

########### presel
print(" --> Preselection <--")
df_presel = df\
            .Filter( "1==1"   , "All raw event" )\
            .Filter( "mll>12" , "mll>12" )\
            .Filter( "Lepton_pt[0]>25 && Lepton_pt[1]>20" , "Lepton_pt[0]>25 && Lepton_pt[1]>20" )\
            .Filter( "bVeto==1", "bVeto==1" )\
            .Filter( "PuppiMET_pt > 30" , "PuppiMET_pt > 30" )
dataframe['presel'] = df_presel
report_presel = df_presel.Report()
report_presel.Print()
print("")

########### e-mu 1jet
print(" --> e-mu 1jet <-- " )
df_emu1jet = df_presel\
             .Filter( "(Lepton_pdgId[0]*Lepton_pdgId[1] == 11*13)" , "(Lepton_pdgId[0]*Lepton_pdgId[1] == 11*13)" )\
             .Filter( "nLepton==2" , "nLepton==2")\
             .Filter( "(nCleanJet >= 1 && CleanJet_pt[0] > 30 )" , "Alt$(CleanJet_pt[0],0)>30" )\
             .Filter( "(nCleanJet >= 2 && CleanJet_pt[1] < 30 )" , "Alt$(CleanJet_pt[1],0)<30" )\
             .Filter( "abs(Lepton_eta[0] - Lepton_eta[1])<2.0" , "abs(Lepton_eta[0] - Lepton_eta[1])<2.0" )\
             .Filter( "mlljj20_whss > 50" , "mlljj20_whss > 50" )
dataframe['emu1jet'] = df_emu1jet
report_emu1jet = df_emu1jet.Report()
report_emu1jet.Print()
print("")
########### e-mu 2jet
print(" --> e-mu 2jet <-- " )
df_emu2jet = df_presel\
             .Filter( "(Lepton_pdgId[0]*Lepton_pdgId[1] == 11*13)" , "(Lepton_pdgId[0]*Lepton_pdgId[1] == 11*13)" )\
             .Filter( "nLepton==2" , "nLepton==2")\
             .Filter( "(nCleanJet >= 1 && CleanJet_pt[0] > 30 )" , "Alt$(CleanJet_pt[0],0)>30" )\
             .Filter( "(nCleanJet >= 2 && CleanJet_pt[1] > 30 )" , "Alt$(CleanJet_pt[1],0)>30" )\
             .Filter( "mjj < 100" , "mjj < 100" )\
             .Filter( "abs(Lepton_eta[0] - Lepton_eta[1])<2.0" , "abs(Lepton_eta[0] - Lepton_eta[1])<2.0" )\
             .Filter( "mlljj20_whss > 50" , "mlljj20_whss > 50" )
dataframe['emu2jet'] = df_emu2jet
report_emu2jet = df_emu2jet.Report()
report_emu2jet.Print()
print("")

########### mu-mu 1jet
print(" --> mu-mu 1jet <-- " )
df_mumu1jet = df_presel\
             .Filter( "(Lepton_pdgId[0]*Lepton_pdgId[1] == 13*13)" , "(Lepton_pdgId[0]*Lepton_pdgId[1] == 13*13)" )\
             .Filter( "nLepton==2" , "nLepton==2")\
             .Filter( "(nCleanJet >= 1 && CleanJet_pt[0] > 30 )" , "Alt$(CleanJet_pt[0],0)>30" )\
             .Filter( "(nCleanJet >= 2 && CleanJet_pt[1] < 30 )" , "Alt$(CleanJet_pt[1],0)<30" )\
             .Filter( "abs(mll-91.2)>15" , "abs(mll-91.2)>15" )\
             .Filter( "abs(Lepton_eta[0] - Lepton_eta[1])<2.0" , "abs(Lepton_eta[0] - Lepton_eta[1])<2.0" )\
             .Filter( "mlljj20_whss > 50" , "mlljj20_whss > 50" )
dataframe['mumu1jet'] = df_mumu1jet
report_mumu1jet = df_mumu1jet.Report()
report_mumu1jet.Print()
print("")
########### mu-mu 2jet
print(" --> mu-mu 2jet <-- " )
df_mumu2jet = df_presel\
             .Filter( "(Lepton_pdgId[0]*Lepton_pdgId[1] == 13*13)" , "(Lepton_pdgId[0]*Lepton_pdgId[1] == 13*13)" )\
             .Filter( "nLepton==2" , "nLepton==2")\
             .Filter( "(nCleanJet >= 1 && CleanJet_pt[0] > 30 )" , "Alt$(CleanJet_pt[0],0)>30" )\
             .Filter( "(nCleanJet >= 2 && CleanJet_pt[1] > 30 )" , "Alt$(CleanJet_pt[1],0)>30" )\
             .Filter( "abs(mll-91.2)>15" , "abs(mll-91.2)>15" )\
             .Filter( "mjj < 100" , "mjj < 100" )\
             .Filter( "abs(Lepton_eta[0] - Lepton_eta[1])<2.0" , "abs(Lepton_eta[0] - Lepton_eta[1])<2.0" )\
             .Filter( "mlljj20_whss > 50" , "mlljj20_whss > 50" )
dataframe['mumu2jet'] = df_mumu2jet
report_mumu2jet = df_mumu2jet.Report()
report_mumu2jet.Print()
print("")

########### e-e 1jet
print(" --> e-e 1jet <-- " )
df_ee1jet = df_presel\
             .Filter( "(Lepton_pdgId[0]*Lepton_pdgId[1] == 11*11)" , "(Lepton_pdgId[0]*Lepton_pdgId[1] == 11*11)" )\
             .Filter( "nLepton==2" , "nLepton==2")\
             .Filter( "(nCleanJet >= 1 && CleanJet_pt[0] > 30 )" , "Alt$(CleanJet_pt[0],0)>30" )\
             .Filter( "(nCleanJet >= 2 && CleanJet_pt[1] < 30 )" , "Alt$(CleanJet_pt[1],0)<30" )\
             .Filter( "abs(mll-91.2)>15" , "abs(mll-91.2)>15" )\
             .Filter( "abs(Lepton_eta[0] - Lepton_eta[1])<2.0" , "abs(Lepton_eta[0] - Lepton_eta[1])<2.0" )\
             .Filter( "mlljj20_whss > 50" , "mlljj20_whss > 50" )
dataframe['ee1jet'] = df_ee1jet
report_ee1jet = df_ee1jet.Report()
report_ee1jet.Print()
print("")
########### e-e 2jet
print(" --> e-e 2jet <-- " )
df_ee2jet = df_presel\
             .Filter( "(Lepton_pdgId[0]*Lepton_pdgId[1] == 11*11)" , "(Lepton_pdgId[0]*Lepton_pdgId[1] == 11*11)" )\
             .Filter( "nLepton==2" , "nLepton==2")\
             .Filter( "(nCleanJet >= 1 && CleanJet_pt[0] > 30 )" , "Alt$(CleanJet_pt[0],0)>30" )\
             .Filter( "(nCleanJet >= 2 && CleanJet_pt[1] > 30 )" , "Alt$(CleanJet_pt[1],0)>30" )\
             .Filter( "abs(mll-91.2)>15" , "abs(mll-91.2)>15" )\
             .Filter( "mjj < 100" , "mjj < 100" )\
             .Filter( "abs(Lepton_eta[0] - Lepton_eta[1])<2.0" , "abs(Lepton_eta[0] - Lepton_eta[1])<2.0" )\
             .Filter( "mlljj20_whss > 50" , "mlljj20_whss > 50" )
dataframe['ee2jet'] = df_ee2jet
report_ee2jet = df_ee2jet.Report()
report_ee2jet.Print()
print("")

