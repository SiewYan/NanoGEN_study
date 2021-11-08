import argparse, os, sys
import ROOT
import numpy as np
from collections import OrderedDict
#from ROOT import array

ROOT.gROOT.SetBatch(True)
ROOT.ROOT.EnableImplicitMT(10)
ROOT.TH1.SetDefaultSumw2()
ROOT.gStyle.SetOptStat(0)

dataframes= OrderedDict()

sherpaPATH="/eos/user/s/shoh/NANOAD_private/Sherpa_WWjets_NLO_events"

dataframes['sherpa'] = map( lambda x : '%s/%s' %( sherpaPATH , x ) , os.listdir( sherpaPATH ) )
dataframes['ref'] = map( lambda x : 'root://xrootd.ba.infn.it//%s' %x , list(np.loadtxt("./data/samplelist_WWjets_powheg.txt", dtype=str, comments="#", delimiter=",", unpack=False) ) )

for key, value in dataframes.items(): dataframes[key] = ROOT.ROOT.RDataFrame( 'Events' , value )



auto histo1 = df1.Histo1D("x");
auto histo2 = df2.Histo1D("y");
