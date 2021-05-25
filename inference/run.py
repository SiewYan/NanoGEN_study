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

    # neutrinos kinematics
    ["v1_Pt" ,"neutrino1.Pt()[0]"  , "1==1" , 50 , 0. , 300. , True , "P_{t}(#nu_{1}) [GeV]", "A.U." if NORM2AU else "#frac{1}{#sigma} #frac{dN}{dPt}"  , 1 ] ,
    ["v1_Eta","neutrino1.Eta()[0]" , "1==1" , 50 , -5., 5.   , True , "#eta(#nu_{1})"       , "A.U." if NORM2AU else "#frac{1}{#sigma} #frac{dN}{d#eta}", 1 ] ,
    ["v1_Phi","neutrino1.Phi()[0]" , "1==1" , 28 , 0. , 3.15 , True , "#phi(#nu_{1})"       , "A.U." if NORM2AU else "#frac{1}{#sigma} #frac{dN}{d#phi}", 1 ] ,

    ["v2_Pt" ,"neutrino2.Pt()[0]"  , "1==1" , 50 , 0. , 300. , True , "P_{t}(#nu_{2}) [GeV]", "A.U." if NORM2AU else "#frac{1}{#sigma} #frac{dN}{dPt}"  , 1 ] ,
    ["v2_Eta","neutrino2.Eta()[0]" , "1==1" , 50 , -5., 5.   , True , "#eta(#nu_{2})"       , "A.U." if NORM2AU else "#frac{1}{#sigma} #frac{dN}{d#eta}", 1 ] ,
    ["v2_Phi","neutrino2.Phi()[0]" , "1==1" , 28 , 0. , 3.15 , True , "#phi(#nu_{2})"       , "A.U." if NORM2AU else "#frac{1}{#sigma} #frac{dN}{d#phi}", 1 ] ,

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
    #Associated W system
    ["an_W1_Lep1_dPhi","deltaPhi(Wboson.Phi()[0],lepton1.Phi()[0])" ,"1==1" , 31 , 0. , 3.15 , False, "#Delta#phi(W1,Lepton1)", "A.U." , 1 ],
    ["an_W1_Lep1_dR"  ,"deltaR(Wboson.Phi()[0],Wboson.Eta()[0],lepton1.Phi()[0],lepton1.Eta()[0])" ,"1==1",60 , 0. , 5 , True, "#DeltaR(W1,Lepton1)", "A.U." ,1],

    ["an_Lep1_v1_dPhi","deltaPhi(lepton1.Phi()[0],neutrino1.Phi()[0])" ,"1==1" , 31 , 0. , 3.15 , False, "#Delta#phi(Lepton1,#nu_{1})", "A.U." , 1 ],
    ["an_Lep1_v1_dR"  ,"deltaR(lepton1.Phi()[0],lepton1.Eta()[0],neutrino1.Phi()[0],neutrino1.Eta()[0])" ,"1==1",60 , 0. , 5 , True, "#DeltaR(Lepton1,#nu_{1})", "A.U." ,1],

    #Associated W+H system
    ["an_W1_H_dPhi","deltaPhi(Wboson.Phi()[0],Hboson.Phi()[0])" ,"1==1" , 28 , 0. , 3.15 , True, "#Delta#phi(W1,H)", "A.U." , 1 ],
    ["an_W1_H_dR"  ,"deltaR(Wboson.Phi()[0],Wboson.Eta()[0],Hboson.Phi()[0],Hboson.Eta()[0])" ,"1==1",60 , 0. , 5 , True, "#DeltaR(W1,H)", "A.U." ,1],
    
    #W1W2 system
    ["an_W1_W2_dPhi","deltaPhi(Wboson.Phi()[0],WHboson.Phi()[0])" ,"1==1" , 28 , 0. , 3.15 , True, "#Delta#phi(W1,W2)", "A.U." , 1 ],
    ["an_W1_W2_dR"  ,"deltaR(Wboson.Phi()[0],Wboson.Eta()[0],WHboson.Phi()[0],WHboson.Eta()[0])" ,"1==1",60 , 0. , 5 , True, "#DeltaR(W1,W2)", "A.U." ,1],
    
    #W2W3 system
    ["an_W2_W3_dPhi","deltaPhi(WHboson.Phi()[0],WHboson.Phi()[1])" ,"1==1" , 28 , 0. , 3.15 , True, "#Delta#phi(W2,W3)", "A.U." , 1 ],
    ["an_W2_W3_dR"  ,"deltaR(WHboson.Phi()[0],WHboson.Eta()[0],WHboson.Phi()[1],WHboson.Eta()[1])" ,"1==1",60 , 0. , 5 , True, "#DeltaR(W2,W3)", "A.U." ,1],
    ["an_H_W2W3_dR_2D","deltaR(WHboson.Phi()[0],WHboson.Eta()[0],WHboson.Phi()[1],WHboson.Eta()[1]):Hboson.Pt()[0]" ,"",[28,50] , [0.,0.] , [3.,800.] , True, "#Delta R(W2,W3) : H Pt [GeV]", "A.U." , 2],
    ["an_H_l2v2j1j2_dR_2D","deltaR(l2v2.Phi()[0],l2v2.Eta()[0],dijets.Phi()[1],dijets.Eta()[1]):Hboson.Pt()[0]" ,"",[28,50] , [0.,0.] , [3.,800.] , True, "#Delta R(l2v2,jij2) : H Pt [GeV]", "A.U." , 2],

    # lepton1 and lepton2 system
    ["an_Lep1_Lep2_dPhi","deltaPhi(lepton1.Phi()[0],lepton2.Phi()[0])" ,"1==1" , 28 , 0. , 3.15 , True, "#Delta#phi(Lepton1,Lepton2)", "A.U." , 1 ],
    ["an_Lep1_Lep2_dEta","deltaEta(lepton1.Eta()[0],lepton2.Eta()[0])" ,"1==1" , 30 , 0. , 4.0 , True, "#Delta#eta(Lepton1,Lepton2)", "A.U." , 1 ],
    ["an_Lep1_Lep2_dR"  ,"deltaR(lepton1.Phi()[0],lepton1.Eta()[0],lepton2.Phi()[0],lepton2.Eta()[0])" ,"1==1",60 , 0. , 5 , True, "#DeltaR(Lepton1,Lepton2)", "A.U." ,1],

    ["an_Lep2_v2_dPhi","deltaPhi(lepton2.Phi()[0],neutrino2.Phi()[0])" ,"1==1" , 28 , 0. , 3.15 , True, "#Delta#phi(Lepton2,#nu_{2})", "A.U." , 1 ],
    ["an_Lep2_v2_dR"  ,"deltaR(lepton2.Phi()[0],lepton2.Eta()[0],neutrino2.Phi()[0],neutrino2.Eta()[0])" ,"1==1",60 , 0. , 5 , True, "#DeltaR(Lepton2,#nu_{2})", "A.U." ,1],

    # lepton1 and MET system
    ["an_Lep1_MET_dPhi","deltaPhi(lepton1.Phi()[0],MET.Phi()[0])" ,"1==1" , 28 , 0. , 3.15 , True, "#Delta#phi(Lepton1,MET)", "A.U." , 1 ],
    # lepton2 and MET system
    ["an_Lep2_MET_dPhi","deltaPhi(lepton2.Phi()[0],MET.Phi()[0])" ,"1==1" , 28 , 0. , 3.15 , True, "#Delta#phi(Lepton2,MET)", "A.U." , 1 ],

    # lepton1 and GenJet1 system
    ["an_Lep1_j1_dPhi","deltaPhi(lepton1.Phi()[0],genjet.Phi()[0])" ,"1==1" , 28 , 0. , 3.15 , True, "#Delta#phi(Lepton1,j1)", "A.U." , 1 ],
    ["an_Lep1_j1_dR"  ,"deltaR(lepton1.Phi()[0],lepton1.Eta()[0],genjet.Phi()[0],genjet.Eta()[0])" ,"1==1",60 , 0. , 5 , True, "#DeltaR(Lepton1,j1)", "A.U." ,1],

    ["an_Lep1_j2_dPhi","deltaPhi(lepton1.Phi()[0],genjet.Phi()[1])" ,"Length$(genjet)>=2" , 28 , 0. , 3.15 , True, "#Delta#phi(Lepton1,j2)", "A.U." , 1 ],
    ["an_Lep1_j2_dR"  ,"deltaR(lepton1.Phi()[0],lepton1.Eta()[0],genjet.Phi()[1],genjet.Eta()[1])" ,"Length$(genjet)>=2",60 , 0. , 5 , True, "#DeltaR(Lepton1,j2)", "A.U." ,1],

    # lepton2 and GenJet1 system
    ["an_Lep2_j1_dPhi","deltaPhi(lepton2.Phi()[0],genjet.Phi()[0])" ,"1==1" , 28 , 0. , 3.15 , True, "#Delta#phi(Lepton2,j1)", "A.U." , 1 ],
    ["an_Lep2_j1_dR"  ,"deltaR(lepton2.Phi()[0],lepton2.Eta()[0],genjet.Phi()[0],genjet.Eta()[0])" ,"1==1",60 , 0. , 5 , True, "#DeltaR(Lepton2,j1)", "A.U." ,1],

    ["an_Lep2_j2_dPhi","deltaPhi(lepton2.Phi()[0],genjet.Phi()[1])" ,"Length$(genjet)>=2" , 28 , 0. , 3.15 , True, "#Delta#phi(Lepton2,j2)", "A.U." , 1 ],
    ["an_Lep2_j2_dR"  ,"deltaR(lepton2.Phi()[0],lepton2.Eta()[0],genjet.Phi()[1],genjet.Eta()[1])" ,"Length$(genjet)>=2",60 , 0. , 5 , True, "#DeltaR(Lepton2,j2)", "A.U." ,1],
    
    # GenJet system
    ["an_mjj","dijets.M()[0]" ,"Length$(genjet)>=2" , 30 , 0. , 200 , True, "M(j1,j2)", "A.U." , 1 ],
    ["an_j1_j2_dPhi","deltaPhi(genjet.Phi()[0],genjet.Phi()[1])" ,"Length$(genjet)>=2" , 28 , 0. , 3.15 , True, "#Delta#phi(j1,j2)", "A.U." , 1 ],
    ["an_j1_j2_dR"  ,"deltaR(genjet.Phi()[0],genjet.Eta()[0],genjet.Phi()[1],genjet.Eta()[1])" ,"Length$(genjet)>=2",60 , 0. , 5 , True, "#DeltaR(j1,j2)", "A.U." ,1],

    # dilepton - dijet system
    ["an_dilepton","dileptons.M()[0]" ,"1==1" , 30 , 0. , 200 , True, "M(l1,l2)", "A.U." , 1 ],
    ["an_mll_mjj_dPhi","deltaPhi(dileptons.Phi()[0],dijets.Phi()[0])" ,"Length$(genjet)>=2" , 28 , 0. , 3.15 , True, "#Delta#phi(ll,jj)", "A.U." , 1 ],
    ["an_mll_mjj_dR"  ,"deltaR(dileptons.Phi()[0],dileptons.Eta()[0],dijets.Phi()[0],dijets.Eta()[0])" ,"Length$(genjet)>=2",60 , 0. , 5 , True, "#DeltaR(ll,jj)", "A.U." ,1],

    # l2v2 -- dijet system
    ["an_l2v2_jj_dPhi","deltaPhi(l2v2.Phi()[0],dijets.Phi()[0])" ,"Length$(genjet)>=2" , 31 , 0. , 3.15 , False, "#Delta#phi(l2v2,jj)", "A.U." , 1 ],
    ["an_l2v2_jj_dR"  ,"deltaR(l2v2.Phi()[0],l2v2.Eta()[0],dijets.Phi()[0],dijets.Eta()[0])" ,"Length$(genjet)>=2",60 , 0. , 5 , True, "#DeltaR(l2v2,jj)", "A.U." ,1],

    # l2 -- dijet system
    ["an_l2_jj_dPhi","deltaPhi(lepton2.Phi()[0],dijets.Phi()[0])" ,"Length$(genjet)>=2" , 31 , 0. , 3.15 , False, "#Delta#phi(l_{2},jj)", "A.U." , 1 ],
    
    #showing off-shell effect
    ["an_l2v2_mass"  ,"l2v2.M()[0]" ,"1==1", 100 , 0. , 110 , False, "M( l_{2} , #nu_{2} ) [GeV/c^{2}]", "A.U." ,1],
    ["an_l1v1_mass"  ,"l1v1.M()[0]" ,"1==1", 100 , 0. , 110 , False, "M( l_{1} , #nu_{1} ) [GeV/c^{2}]", "A.U." ,1],
    #["an_l2v2jj_mass"  ,"(l2v2+dijets)[0].M()" ,"1==1", 100 , 0. , 150 , False, "M( l_{2}#nu_{2}jj ) [GeV/c^{2}]", "A.U." ,1],
    ["an_l2v2_offshell_dPhi"  ,"deltaPhi(lepton2.Phi()[0],neutrino2.Phi()[0])" ,"l2v2.M()[0]<50", 31 , 0. , 3.15 , False, "#Delta#phi( l_{2} , #nu_{2} )", "A.U." ,1],
    ["an_j1j2_offshell_dPhi"  ,"deltaPhi(genjet.Phi()[0],genjet.Phi()[1])" ,"l2v2.M()[0]>50", 31 , 0. , 3.15 , False, "#Delta#phi( Genjet_{1} , Genjet_{2} )", "A.U." ,1],
    #system l1v1 + lv2jet
    ["an_l1v1_lv2jets_dPhi"  ,"deltaPhi(l1v1.Phi()[0],lv2jets.Phi()[0])" ,"Length$(dijets)>=1", 31 , 0. , 3.15 , False, "#Delta#phi( l_{1}#nu_{1} , l_{2}#nu_{2}j_{1}j_{2} )", "A.U." ,1],

    # correlation plot y:x
    # between W1 and H
    ["an_W1_H_pt_2D","Wboson.Pt()[0]:Hboson.Pt()[0]" ,"",[50,50] , [0.,0.] , [400,400] , True, "W1 Pt [GeV] : H Pt [GeV]", "A.U." , 2],
    # between W1 and deltaPhi(H,W)
    ["an_W1_pt_HW1_dPhi_2D","deltaPhi(Hboson.Phi()[0],Wboson.Phi()[0]):Wboson.Pt()[0]" ,"",[28,50] , [0.,0.] , [3.15,400] , True, "#Delta#phi(W1,H) : W1 Pt [GeV]", "A.U." , 2],
    # between W1 and lv1 decay product
    ["an_W1_pt_lv1_dPhi_2D","deltaPhi(neutrino1.Phi()[0],lepton1.Phi()[0]):Wboson.Pt()[0]" ,"",[28,50] , [0.,0.] , [3.15,400] , True, "#Delta#phi(l1,v1) : W1 Pt [GeV]", "A.U." , 2],
    # between l2v2 and jj decay product
    ["an_l2v2_mjj_pt_2D","l2v2.Pt()[0]:dijets.Pt()[0]" ,"", [30,30] , [0.,0.] , [200,200] , True, "l2v2 Pt [GeV] : jj Pt [GeV]", "A.U." , 2],
    # between l1v1 and l2v2 deltaphi
    ["an_l1v1_pt_l2v2_dPhi_2D","l1v1.Pt()[0]:deltaPhi(lepton2.Phi()[0],neutrino2.Phi()[0])" ,"", [50,28] , [0.,0.] , [300,3.15] , True, "l1v1 Pt [GeV] : #Delta#phi(l2,v2)","A.U.", 2],
    ["an_H_pt_l2v2_dPhi_2D","deltaPhi(lepton2.Phi()[0],neutrino2.Phi()[0]):Hboson.Pt()[0]" ,"l2v2.M()[0]<50", [28,50] , [0.,0.] , [3.15,300] , True, "#Delta#phi(l2,v2) : H Pt [GeV]","A.U.", 2],
    # between l1v1 and jj deltaphi
    ["an_l1v1_pt_jj_dPhi_2D","l1v1.Pt()[0]:deltaPhi(genjet.Phi()[0],genjet.Phi()[1])" ,"", [50,28] , [0.,0.] , [300,3.15] , True, "l1v1 Pt [GeV] : #Delta#phi(j1,j2)","A.U.", 2],
    ["an_H_pt_jj_dPhi_2D","deltaPhi(genjet.Phi()[0],genjet.Phi()[1]):Hboson.Pt()[0]" ,"", [28,50] , [0.,0.] , [3.15,300] , True, "#Delta#phi(j1,j2) : H Pt [GeV]","A.U.", 2],

]

for lhe in Lhefiles:
    lhe = lhe.split('.')[0]
    for v in var:
        p = multiprocessing.Process( target=plot, args=([lhe],v[0],v[1],v[2],v[3],v[4],v[5],v[6],v[7],v[8],v[9]) )
        p.start()


