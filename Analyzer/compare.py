
import argparse, os, sys
import ROOT
import numpy as np
from collections import OrderedDict
from utilities import *
#from ROOT import array

ROOT.gROOT.SetBatch(True)
ROOT.ROOT.EnableImplicitMT(10)
ROOT.TH1.SetDefaultSumw2()
ROOT.gStyle.SetOptStat(0)

# inputfile for comparison
dataframes= OrderedDict({
    'sherpa' : '../Producer/sherpa.root',
    'powheg' : '../Producer/powheg.root'
})

# the four momentum
fp_template = OrderedDict({ 
    'Pt' : [ ( 50  , 0.   , 500 ) , "XXX p_{T} [GeV]"] , 
    'Eta': [ ( 120 , -3.0 , 3.0 ) , "XXX #eta" ] ,
    'Phi': [ ( 120 , 0.   , 3.5 ) , "XXX #Phi" ] , 
    'M'  : [ ( 50  , 0.   , 500 ) , "XXX Mass [GeV/c^2]" ]
})

# additional variable
##
##

# helper function
def bookHistogram( df_, name_, fpvar_ , xbin_ , title_ ):
    histModel = ROOT.ROOT.RDF.TH1DModel( name_, title_ , xbin_[0], xbin_[1], xbin_[2] )
    return df_.Define( name_ , fpvar ).Histo1D( histModel , name_ )
pass


if __name__ == "__main__":
    # Initialization
    hist = OrderedDict();
    for sample, rootfile in dataframes.items(): dataframes[sample] = ROOT.ROOT.RDataFrame( 'gen' , rootfile )
    
    # transformation
    for sample, df in dataframes.items(): 
        varlist = OrderedDict();
        # collection
        for var in [ 'Lepton' , 'GenJetAK4' , 'GenJetAK8' ]:
            # 4 momentum var
            for ivar, xb in fp_template.items():
                # number 
                for i in range(0,3):
                    name = '%s%s_%s' %(var,i+1,ivar)
                    fpvar = '%s[%s].%s()' %(var,i,ivar)
                    xbin = xb[0];
                    title = '%s ; Events' %( xb[-1].replace( 'XXX' , var ) );
                    varlist['%s_%s' %(sample,name)] = bookHistogram( df , name, fpvar , xbin , title )
        hist[sample] = varlist

    # action: plot
    zipped = zip(hist['powheg'], hist['sherpa'])
    for ipair in list(zipped):
        print(ipair)
        #histo1D(  , hist_mc , out_ , variable , "" , Lumi_ , 4 , True )
