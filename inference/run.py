import os
from drawer import *
from tdrstyle import *

NORM2AU=True
 
Lhefiles=[ 'WHSS.root' ]

# variables
var =[
    # MET
    [ "MET_Pt"  , "MET.Pt()[0]"  , "1==1" , 50 , 0. , 200. , True , "P_{t}(MET) [GeV]", "A.U." if NORM2AU else "#frac{1}{#sigma} #frac{dN}{dPt}"  , 1 ] ,
    [ "MET_Phi" , "MET.Phi()[0]" , "1==1" , 28 , 0. , 3.15 , True , "#phi(MET)"       , "A.U." if NORM2AU else "#frac{1}{#sigma} #frac{dN}{d#phi}", 1 ] ,

    # Leptons kinematics
    ["Lepton1_Pt" ,"lepton1.Pt()[0]"  , "1==1" , 50 , 0. , 300. , True , "P_{t}(lepton1) [GeV]", "A.U." if NORM2AU else "#frac{1}{#sigma} #frac{dN}{dPt}"  , 1 ] ,
    ["Lepton1_Eta","lepton1.Eta()[0]" , "1==1" , 50 , -5., 5.   , True , "#eta(lepton1)"       , "A.U." if NORM2AU else "#frac{1}{#sigma} #frac{dN}{d#eta}", 1 ] ,
    ["Lepton1_Phi","lepton1.Phi()[0]" , "1==1" , 28 , 0. , 3.15 , True , "#phi(lepton1)"       , "A.U." if NORM2AU else "#frac{1}{#sigma} #frac{dN}{d#phi}", 1 ] ,
    
    ["Lepton2_Pt" ,"lepton2.Pt()[0]"  , "1==1" , 50 , 0. , 300. , True , "P_{t}(lepton2) [GeV]", "A.U." if NORM2AU else "#frac{1}{#sigma} #frac{dN}{dPt}"  , 1 ] ,
    ["Lepton2_Eta","lepton2.Eta()[0]" , "1==1" , 50 , -5., 5.   , True , "#eta(lepton2)"       , "A.U." if NORM2AU else "#frac{1}{#sigma} #frac{dN}{d#eta}", 1 ] ,
    ["Lepton2_Phi","lepton2.Phi()[0]" , "1==1" , 28 , 0. , 3.15 , True , "#phi(lepton2)"       , "A.U." if NORM2AU else "#frac{1}{#sigma} #frac{dN}{d#Phi}", 1 ] ,
    
    # boson kinematics
    ["Wboson1_Pt" ,"Wboson.Pt()[0]"  , "1==1" , 50 , 0. , 400. , True , "P_{t}(W boson1) [GeV]", "A.U." if NORM2AU else "#frac{1}{#sigma} #frac{dN}{dPt}"  , 1 ] ,
    ["Wboson1_Eta","Wboson.Eta()[0]" , "1==1" , 50 , -5., 5.   , True , "#eta(W boson1)"       , "A.U." if NORM2AU else "#frac{1}{#sigma} #frac{dN}{d#eta}", 1 ] ,
    ["Wboson1_Phi","Wboson.Phi()[0]" , "1==1" , 28 , 0. , 3.15 , True , "#phi(W boson1)"       , "A.U." if NORM2AU else "#frac{1}{#sigma} #frac{dN}{d#Phi}", 1 ] ,

    ["WHboson1_Pt" ,"WHboson.Pt()[0]"  , "1==1" , 50 , 0. , 400. , True , "P_{t}(W boson2) [GeV]", "A.U." if NORM2AU else "#frac{1}{#sigma} #frac{dN}{dPt}"  , 1 ] ,
    ["WHboson1_Eta","WHboson.Eta()[0]" , "1==1" , 50 , -5., 5.   , True , "#eta(W boson2)"       , "A.U." if NORM2AU else "#frac{1}{#sigma} #frac{dN}{d#eta}", 1 ] ,
    ["WHboson1_Phi","WHboson.Phi()[0]" , "1==1" , 28 , 0. , 3.15 , True , "#phi(W boson2)"       , "A.U." if NORM2AU else "#frac{1}{#sigma} #frac{dN}{d#Phi}", 1 ] ,

    ["WHboson2_Pt" ,"WHboson.Pt()[1]"  , "1==1" , 50 , 0. , 400. , True , "P_{t}(W boson3) [GeV]", "A.U." if NORM2AU else "#frac{1}{#sigma} #frac{dN}{dPt}"  , 1 ] ,
    ["WHboson2_Eta","WHboson.Eta()[1]" , "1==1" , 50 , -5., 5.   , True , "#eta(W boson3)"       , "A.U." if NORM2AU else "#frac{1}{#sigma} #frac{dN}{d#eta}", 1 ] ,
    ["WHboson2_Phi","WHboson.Phi()[1]" , "1==1" , 28 , 0. , 3.15 , True , "#phi(W boson3)"       , "A.U." if NORM2AU else "#frac{1}{#sigma} #frac{dN}{d#Phi}", 1 ] ,

    ["Hboson_Pt" ,"Hboson.Pt()[0]"  , "1==1" , 50 , 0. , 400. , True , "P_{t}(H boson) [GeV]", "A.U." if NORM2AU else "#frac{1}{#sigma} #frac{dN}{dPt}"  , 1 ] ,
    ["Hboson_Eta","Hboson.Eta()[0]" , "1==1" , 50 , -5., 5.   , True , "#eta(H boson)"       , "A.U." if NORM2AU else "#frac{1}{#sigma} #frac{dN}{d#eta}", 1 ] ,
    ["Hboson_Phi","Hboson.Phi()[0]" , "1==1" , 28 , 0. , 3.15 , True , "#phi(H boson)"       , "A.U." if NORM2AU else "#frac{1}{#sigma} #frac{dN}{d#Phi}", 1 ] ,

    # quark kinematics
    ["Wquark1_Pt" ,"Wquark.Pt()[0]"  , "1==1" , 60 , 0. , 600. , True , "P_{t}(quark1) [GeV]", "A.U." if NORM2AU else "#frac{1}{#sigma} #frac{dN}{dPt}"  , 1 ] ,
    ["Wquark1_Eta","Wquark.Eta()[0]" , "1==1" , 50 , -5., 5.   , True , "#eta(quark1)"       , "A.U." if NORM2AU else "#frac{1}{#sigma} #frac{dN}{d#eta}", 1 ] ,
    ["Wquark1_Phi","Wquark.Phi()[0]" , "1==1" , 28 , 0. , 3.15 , True , "#phi(quark1)"       , "A.U." if NORM2AU else "#frac{1}{#sigma} #frac{dN}{d#Phi}", 1 ] ,

    ["Wquark2_Pt" ,"Wquark.Pt()[1]"  , "1==1" , 60 , 0. , 600. , True , "P_{t}(quark2) [GeV]", "A.U." if NORM2AU else "#frac{1}{#sigma} #frac{dN}{dPt}"  , 1 ] ,
    ["Wquark2_Eta","Wquark.Eta()[1]" , "1==1" , 50 , -5., 5.   , True , "#eta(quark2)"       , "A.U." if NORM2AU else "#frac{1}{#sigma} #frac{dN}{d#eta}", 1 ] ,
    ["Wquark2_Phi","Wquark.Phi()[1]" , "1==1" , 28 , 0. , 3.15 , True , "#phi(quark2)"       , "A.U." if NORM2AU else "#frac{1}{#sigma} #frac{dN}{d#Phi}", 1 ] ,

    # GenJet kinematics
    ["GenJet1_Pt" ,"genjet.Pt()[0]"  , "1==1" , 50 , 0. , 200. , True , "P_{t}(GenJet1) [GeV]", "A.U." if NORM2AU else "#frac{1}{#sigma} #frac{dN}{dPt}"  , 1 ] ,
    ["GenJet1_Eta","genjet.Eta()[0]" , "1==1" , 50 , -5., 5.   , True , "#eta(GenJet1)"       , "A.U." if NORM2AU else "#frac{1}{#sigma} #frac{dN}{d#eta}", 1 ] ,
    ["GenJet1_Phi","genjet.Phi()[0]" , "1==1" , 28 , 0. , 3.15 , True , "#phi(GenJet1)"       , "A.U." if NORM2AU else "#frac{1}{#sigma} #frac{dN}{d#Phi}", 1 ] ,

    ["GenJet2_Pt" ,"genjet.Pt()[1]"  , "1==1" , 50 , 0. , 200. , True , "P_{t}(GenJet2) [GeV]", "A.U." if NORM2AU else "#frac{1}{#sigma} #frac{dN}{dPt}"  , 1 ] ,
    ["GenJet2_Eta","genjet.Eta()[1]" , "1==1" , 50 , -5., 5.   , True , "#eta(GenJet2)"       , "A.U." if NORM2AU else "#frac{1}{#sigma} #frac{dN}{d#eta}", 1 ] ,
    ["GenJet2_Phi","genjet.Phi()[1]" , "1==1" , 28 , 0. , 3.15 , True , "#phi(GenJet2)"       , "A.U." if NORM2AU else "#frac{1}{#sigma} #frac{dN}{d#Phi}", 1 ] ,

    #analysis
    #Associated W system DeltaPhi(W,lepton) 
    ["an_W1_Lep1_dPhi","deltaPhi(Wboson.Phi()[0],lepton1.Phi()[0])" ,"1==1" , 28 , 0. , 3.15 , True, "DeltaPhi(W1,Lepton1)", "A.U." , 1 ],
]

for lhe in Lhefiles:
    lhe = lhe.split('.')[0]
    for v in var:
        p = multiprocessing.Process( target=plot, args=([lhe],v[0],v[1],v[2],v[3],v[4],v[5],v[6],v[7],v[8],v[9]) )
        p.start()


