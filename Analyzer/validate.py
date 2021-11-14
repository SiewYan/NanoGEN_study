
import argparse, os, sys
import ROOT
import numpy as np
from collections import OrderedDict
#from ROOT import array

ROOT.gROOT.SetBatch(True)
ROOT.ROOT.EnableImplicitMT(10)
ROOT.TH1.SetDefaultSumw2()
ROOT.gStyle.SetOptStat(0)

# inputfile for comparison
dataframes= OrderedDict({
    'sherpa' : './sherpa.root',
    'powheg' : './powheg.root'
})

# the four momentum
fp_template = OrderedDict({ 
    'Pt' : [ ( 50  , 0.   , 500 ) , "XXX p_{T} [GeV]"] , 
    'Eta': [ ( 120 , -3.0 , 3.0 ) , "XXX #eta" ] ,
    'Phi': [ ( 120 , 0.   , 3.5 ) , "XXX #Phi" ] , 
    'M'  : [ ( 50  , 0.   , 500 ) , "XXX Mass [GeV/c^2]" ]
})

# helper function
def bookHistogram( df , variable , range_ , lumi=None ):
    match="mcTrue*weight" #*tag_TightHWW_SF*probe_TightHWW_SF"
    #probe="probe_Ele_eta > 0 && probe_Ele_eta < 0.8 && probe_Ele_pt > 50 && probe_Ele_pt < 100"
    probe="1==1"
    #flag="passingprobeEleTightHWW==1"
    flag="1==1"
    # what is plotweight
    WEIGHT = match + "*" + lumi if lumi is not None else "1."
    print( "WEIGHT : ", WEIGHT )
    return df.Define( "weights" , WEIGHT )\
             .Filter( "Tag_pt > 32 && abs(Tag_eta) < 2.17 && Tag_charge*Probe_charge < 0" , "Nominal cut" )\
             .Filter( flag , "passing flag" )\
             .Filter( probe , "probe low eta high pt cut" )\
             .Histo1D( ROOT.ROOT.RDF.TH1DModel(variable, variable, range_[0], range_[1], range_[2]), variable, "weights" )
pass


if __name__ == "__main__":
    # Initialization
    for key, value in dataframes.items(): 
        dataframes[key] = ROOT.ROOT.RDataFrame( 'gen' , value )
        
    # Book histogram
    for variable in variables: hists[variable] = bookHistogram( df , variable , ranges[variable][0] , Lumi_ )


#auto histo1 = df1.Histo1D("x");
#auto histo2 = df2.Histo1D("y");
