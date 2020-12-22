
def emu1jet( df_presel ) :
    ########### e-mu 1jet
    print(" --> e-mu 1jet <-- " )
    return df_presel\
        .Filter( "(Lepton_pdgId[0]*Lepton_pdgId[1] == 11*13)" , "(Lepton_pdgId[0]*Lepton_pdgId[1] == 11*13)" )\
        .Filter( "nLepton==2" , "nLepton==2")\
        .Filter( "(nCleanJet >= 1 && CleanJet_pt[0] > 30 )" , "Alt$(CleanJet_pt[0],0)>30" )\
        .Filter( "(nCleanJet >= 2 && CleanJet_pt[1] < 30 )" , "Alt$(CleanJet_pt[1],0)<30" )\
        .Filter( "abs(Lepton_eta[0] - Lepton_eta[1])<2.0" , "abs(Lepton_eta[0] - Lepton_eta[1])<2.0" )\
        .Filter( "mlljj20_whss > 50" , "mlljj20_whss > 50" )
#PrepareVariableReco( df_emu1jet , "emu1jet" )
#report( df_emu1jet )
pass

def emu2jet( df_presel ) :
    ########### e-mu 2jet
    print(" --> e-mu 2jet <-- " )
    return df_presel\
        .Filter( "(Lepton_pdgId[0]*Lepton_pdgId[1] == 11*13)" , "(Lepton_pdgId[0]*Lepton_pdgId[1] == 11*13)" )\
        .Filter( "nLepton==2" , "nLepton==2")\
        .Filter( "(nCleanJet >= 1 && CleanJet_pt[0] > 30 )" , "Alt$(CleanJet_pt[0],0)>30" )\
        .Filter( "(nCleanJet >= 2 && CleanJet_pt[1] > 30 )" , "Alt$(CleanJet_pt[1],0)>30" )\
        .Filter( "mjj < 100" , "mjj < 100" )\
        .Filter( "abs(Lepton_eta[0] - Lepton_eta[1])<2.0" , "abs(Lepton_eta[0] - Lepton_eta[1])<2.0" )\
        .Filter( "mlljj20_whss > 50" , "mlljj20_whss > 50" )
#PrepareVariableReco( df_emu2jet , "emu2jet" )
#report( df_emu2jet )
pass

def mumu1jet( df_presel ) :
    ########### mu-mu 1jet
    print(" --> mu-mu 1jet <-- " )
    return df_presel\
        .Filter( "(Lepton_pdgId[0]*Lepton_pdgId[1] == 13*13)" , "(Lepton_pdgId[0]*Lepton_pdgId[1] == 13*13)" )\
        .Filter( "nLepton==2" , "nLepton==2")\
        .Filter( "(nCleanJet >= 1 && CleanJet_pt[0] > 30 )" , "Alt$(CleanJet_pt[0],0)>30" )\
        .Filter( "(nCleanJet >= 2 && CleanJet_pt[1] < 30 )" , "Alt$(CleanJet_pt[1],0)<30" )\
        .Filter( "abs(mll-91.2)>15" , "abs(mll-91.2)>15" )\
        .Filter( "abs(Lepton_eta[0] - Lepton_eta[1])<2.0" , "abs(Lepton_eta[0] - Lepton_eta[1])<2.0" )\
        .Filter( "mlljj20_whss > 50" , "mlljj20_whss > 50" )
#PrepareVariableReco( df_mumu1jet , "mumu1jet" )
#report( df_mumu1jet )
pass

def mumu2jet( df_presel ) :
    ########### mu-mu 2jet
    print(" --> mu-mu 2jet <-- " )
    return df_presel\
        .Filter( "(Lepton_pdgId[0]*Lepton_pdgId[1] == 13*13)" , "(Lepton_pdgId[0]*Lepton_pdgId[1] == 13*13)" )\
        .Filter( "nLepton==2" , "nLepton==2")\
        .Filter( "(nCleanJet >= 1 && CleanJet_pt[0] > 30 )" , "Alt$(CleanJet_pt[0],0)>30" )\
        .Filter( "(nCleanJet >= 2 && CleanJet_pt[1] > 30 )" , "Alt$(CleanJet_pt[1],0)>30" )\
        .Filter( "abs(mll-91.2)>15" , "abs(mll-91.2)>15" )\
        .Filter( "mjj < 100" , "mjj < 100" )\
        .Filter( "abs(Lepton_eta[0] - Lepton_eta[1])<2.0" , "abs(Lepton_eta[0] - Lepton_eta[1])<2.0" )\
        .Filter( "mlljj20_whss > 50" , "mlljj20_whss > 50" )
#PrepareVariableReco( df_mumu2jet , "mumu2jet" )
#report( df_mumu2jet )
pass

def ee1jet( df_presel ) :
    ########### e-e 1jet
    print(" --> e-e 1jet <-- " )
    return df_presel\
        .Filter( "(Lepton_pdgId[0]*Lepton_pdgId[1] == 11*11)" , "(Lepton_pdgId[0]*Lepton_pdgId[1] == 11*11)" )\
        .Filter( "nLepton==2" , "nLepton==2")\
        .Filter( "(nCleanJet >= 1 && CleanJet_pt[0] > 30 )" , "Alt$(CleanJet_pt[0],0)>30" )\
        .Filter( "(nCleanJet >= 2 && CleanJet_pt[1] < 30 )" , "Alt$(CleanJet_pt[1],0)<30" )\
        .Filter( "abs(mll-91.2)>15" , "abs(mll-91.2)>15" )\
        .Filter( "abs(Lepton_eta[0] - Lepton_eta[1])<2.0" , "abs(Lepton_eta[0] - Lepton_eta[1])<2.0" )\
        .Filter( "mlljj20_whss > 50" , "mlljj20_whss > 50" )
#PrepareVariableReco( df_ee1jet , "ee1jet" )
#report( df_ee1jet )
pass

def ee2jet( df_presel ) :
    ########### e-e 2jet
    print(" --> e-e 2jet <-- " )
    return df_presel\
        .Filter( "(Lepton_pdgId[0]*Lepton_pdgId[1] == 11*11)" , "(Lepton_pdgId[0]*Lepton_pdgId[1] == 11*11)" )\
        .Filter( "nLepton==2" , "nLepton==2")\
        .Filter( "(nCleanJet >= 1 && CleanJet_pt[0] > 30 )" , "Alt$(CleanJet_pt[0],0)>30" )\
        .Filter( "(nCleanJet >= 2 && CleanJet_pt[1] > 30 )" , "Alt$(CleanJet_pt[1],0)>30" )\
        .Filter( "abs(mll-91.2)>15" , "abs(mll-91.2)>15" )\
        .Filter( "mjj < 100" , "mjj < 100" )\
        .Filter( "abs(Lepton_eta[0] - Lepton_eta[1])<2.0" , "abs(Lepton_eta[0] - Lepton_eta[1])<2.0" )\
        .Filter( "mlljj20_whss > 50" , "mlljj20_whss > 50" )
#PrepareVariableReco( df_ee2jet , "ee2jet" )
#report( df_ee2jet )
pass
