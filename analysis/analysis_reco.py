import ROOT
from ROOT import gROOT , gStyle , TDirectory, TFile
import os, sys
import time
from collections import OrderedDict

ROOT.ROOT.EnableImplicitMT(12)

cwd = os.getcwd()
lumi="35.92"
#lumi="41.53"
#lumi="59.74"
#lumi="137.19"
wp="LepCut2l__ele_mva_90p_Iso2016__mu_cut_Tight80x*LepCut2l__ele_mu_HWW_ttHMVA*LepSF2l__ele_mu_HWW_ttHMVA"
commonMC="%s*SFweight2l*XSWeight*METFilter_MC*GenLepMatch2l*%s" %( lumi , wp )

print("lumi : ", lumi )
print("wp : ", wp )
print("commonMC : ", commonMC )

dfout = TFile( "WHSS_reco.root" , "recreate" )
t_top =	dfout.mkdir("whss")

# hard-coded variables                                                                                                                                                                   
def PrepareVariable( df_in , name ):
    
    tfolder = dfout.mkdir(name)
    tfolder.cd()
    
    # Define
    df_in = df_in\
            .Define( 'Lepton1_eta' , 'Lepton_eta[0]' ).Define( 'Lepton2_eta' , 'Lepton_eta[1]' )\
            .Define( 'Lepton1_pt' , 'Lepton_pt[0]' ).Define( 'Lepton2_pt' , 'Lepton_pt[1]' )\
            .Define( 'deltaLep_Eta'      , 'abs(Lepton_eta[0] - Lepton_eta[1])' )\
            .Define( 'deltaCleanJet_Eta' , 'abs(CleanJet_eta[0] - CleanJet_eta[1])' )\
            .Define( 'deltaLep_Phi'      , 'abs(Lepton_eta[0] - Lepton_eta[1])' )

    h = OrderedDict() ; weight_ = 'weights'
    h['Lepton1_eta']  = df_in.Histo1D( ( 'Lepton1_eta'  , '%s ; Lepton1 eta        ; Events' %( name ) , 10 , -2.5 , 2.5 ) , 'Lepton1_eta'  , weight_ )
    h['Lepton2_eta']  = df_in.Histo1D( ( 'Lepton2_eta'  , '%s ; Lepton2 eta        ; Events' %( name ) , 10 , -2.5 , 2.5 ) , 'Lepton2_eta'  , weight_ )
    h['Lepton1_pt']   = df_in.Histo1D( ( 'Lepton1_pt'   , '%s ; Lepton1 Pt [GeV]   ; Events' %( name ) , 40 , 0. , 200.  ) , 'Lepton1_pt'   , weight_ )
    h['Lepton2_pt']   = df_in.Histo1D( ( 'Lepton2_pt'   , '%s ; Lepton2 Pt [GeV]   ; Events' %( name ) , 40 , 0. , 200.  ) , 'Lepton2_pt'   , weight_ )
    h['mlljj20_whss'] = df_in.Histo1D( ( 'mlljj20_whss' , '%s ; mlljj20_whss [GeV] ; Events' %( name ) , 50 , 0. , 200.  ) , 'mlljj20_whss' , weight_ )
    
    map(lambda x: h[x].Write() , h)
    print("Final yield : %.2f" %df_in.Sum(weight_).GetValue() )
    t_top.cd()
pass

def report( df_in ):
    report = df_in.Report()
    report.Print()
    print("")
pass

df = ROOT.ROOT.RDataFrame( "Signals" , [ "../processor/output/sshwminus012j.root" , "../processor/output/sshwplus012j.root" ] )
df = df.Define( "weights" , commonMC )

########### no selection
PrepareVariable( df , "Raw" )

########### presel
print(" --> Preselection <--")
df_presel = df\
            .Filter( "mll>12" , "mll>12" )\
            .Filter( "Lepton_pt[0]>25 && Lepton_pt[1]>20" , "Lepton_pt[0]>25 && Lepton_pt[1]>20" )\
            .Filter( "bVeto==1", "bVeto==1" )\
            .Filter( "PuppiMET_pt > 30" , "PuppiMET_pt > 30" )
PrepareVariable( df_presel , "Preselection" )
report( df_presel )

########### e-mu 1jet
print(" --> e-mu 1jet <-- " )
df_emu1jet = df_presel\
             .Filter( "(Lepton_pdgId[0]*Lepton_pdgId[1] == 11*13)" , "(Lepton_pdgId[0]*Lepton_pdgId[1] == 11*13)" )\
             .Filter( "nLepton==2" , "nLepton==2")\
             .Filter( "(nCleanJet >= 1 && CleanJet_pt[0] > 30 )" , "Alt$(CleanJet_pt[0],0)>30" )\
             .Filter( "(nCleanJet >= 2 && CleanJet_pt[1] < 30 )" , "Alt$(CleanJet_pt[1],0)<30" )\
             .Filter( "abs(Lepton_eta[0] - Lepton_eta[1])<2.0" , "abs(Lepton_eta[0] - Lepton_eta[1])<2.0" )\
             .Filter( "mlljj20_whss > 50" , "mlljj20_whss > 50" )
PrepareVariable( df_emu1jet , "emu1jet" )
report( df_emu1jet )

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
PrepareVariable( df_emu2jet , "emu2jet" )
report( df_emu2jet )

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
PrepareVariable( df_mumu1jet , "mumu1jet" )
report( df_mumu1jet )

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
PrepareVariable( df_mumu2jet , "mumu2jet" )
report( df_mumu2jet )

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
PrepareVariable( df_ee1jet , "ee1jet" )
report( df_ee1jet )

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
PrepareVariable( df_ee2jet , "ee2jet" )
report( df_ee2jet )

dfout.Close()
