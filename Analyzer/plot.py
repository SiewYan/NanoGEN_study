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
    'sherpa' : '../Producer/sherpa.root',
    'powheg' : '../Producer/powheg.root'
})

# the four momentum
fp_template = OrderedDict({ 
    'Pt' : [ ( 50  , 0.  , 500. ) , "XXX p_{T} [GeV]"    ] , 
    'Eta': [ ( 120 , -3. , 3.   ) , "XXX #eta"           ] ,
    'Phi': [ ( 120 , 0.  , 3.5  ) , "XXX #phi"           ] , 
    'M'  : [ ( 50  , 0.  , 500. ) , "XXX Mass [GeV/c^2]" ]
})

# additional variable
addvar = OrderedDict({
    'pdgId' : [ ( 50 , 30. , -30. ) , "XXX PdgId"        ],
    'n'     : [ ( 15 , 0.  , 15.  ) , "number of XXX"    ]
})
##

# helper function
def bookHistogram( df_ , name_ , xbin_ , title_ ):
    histModel = ROOT.ROOT.RDF.TH1DModel(  name_ , title_ , xbin_[0], xbin_[1], xbin_[2] )
    return df_.Histo1D( histModel , name_ )
pass

# plot
def compare( hist_ref_ , hist_ , PNGname_ , islog=False ):

    hist_ref = hist_ref_.GetPtr()
    hist = hist_.GetPtr()
 
    canvas = ROOT.TCanvas("canvas")
    
    ratio = hist.Clone()
    ratio.Divide(hist_ref)
    ratio.SetLineColor(ROOT.kRed)

    pad1 = ROOT.TPad("pad1","pad1",0,0.3,1,1)
    pad1.SetBottomMargin(0)
    pad1.SetLogy(islog)
    pad1.Draw()
    pad1.cd()
    
    hist_ref.SetLineColor(ROOT.kBlue)
    hist_ref.Draw("HIST")
    hist.SetLineColor(ROOT.kRed)
    hist.Draw("HIST SAME")

    # pad1 style
    #hist_ref.SetTitle("")
    hist_ref.GetXaxis().SetLabelSize(0)
    hist_ref.GetXaxis().SetTitleSize(0)
    hist_ref.GetYaxis().SetTitleSize(0.05)

    hist_ref_min = hist_ref.GetMinimum() ; hist_ref_max = hist_ref.GetMaximum()
    hist_min = hist.GetMinimum() ; hist_max = hist.GetMaximum()

    if ( hist_ref_max < hist_max ):
        hist_ref.SetMaximum(hist_ref.GetMaximum()*(3.0 if islog else 1.5)) #2.5 ; 1.2
    else:
        hist.SetMaximum(hist.GetMaximum()*(3.0 if islog else 1.5)) #2.5 ; 1.2

    if ( hist_ref_min < hist_min ):
        hist_ref.SetMinimum(5.e-1 if islog else 0.)
    else:
        hist.SetMinimum(5.e-1 if islog else 0.)

    # description (if any)
    latex = ROOT.TLatex()
    latex.SetNDC()
    latex.SetTextSize(0.06)
    latex.DrawText(0.7 ,0.83 , "Run 2018" )
    latex.SetTextSize(0.04)
    latex.DrawText(0.7 ,0.77 , " WWjets NLO events" )

    # legend     
    legend = ROOT.TLegend(0.7 ,0.6 ,0.85 ,0.75)
    legend.AddEntry( hist , "Sherpa" )
    legend.AddEntry( hist_ref , "Powheg" )
    legend.SetLineWidth(0)
    legend.Draw("same")


    canvas.cd()
    pad2 = ROOT.TPad("pad2","pad2",0,0.05,1,0.3)
    pad2.SetTopMargin(0)
    pad2.SetBottomMargin(0.25)
    pad2.Draw()
    pad2.cd()
    
    ratio.Draw("pe")

    # ratio style
    ratio.SetTitle("")
    ratio.GetXaxis().SetLabelSize(0.12)
    ratio.GetXaxis().SetTitleSize(0.12)
    ratio.GetYaxis().SetLabelSize(0.1)
    ratio.GetYaxis().SetTitleSize(0.1) #0.15)
    ratio.GetYaxis().SetTitle("Sherpa / Powheg")
    ratio.GetYaxis().SetTitleOffset(0.3)

    ratio.GetYaxis().SetRangeUser(0.5 ,1.5)
    ratio.GetYaxis().SetNdivisions(207)

    xmin = hist_ref.GetXaxis().GetXmin()
    xmax = hist_ref.GetXaxis().GetXmax()
    line = ROOT.TLine(xmin ,1 ,xmax ,1)
    line.SetLineColor(ROOT.kBlack)
    line.SetLineWidth(2)
    line.Draw("same")

    canvas.Print(PNGname_)
    
pass
    

if __name__ == "__main__":
    # Initialization
    hist = OrderedDict();
    for sample, rootfile in dataframes.items(): dataframes[sample] = ROOT.ROOT.RDataFrame( 'gen' , rootfile )
    
    # transformation
    for sample, df in dataframes.items(): 
        varlist = OrderedDict();
        # collection
        for icoll in [ 'Lepton' , 'GenJetAK4' , 'GenJetAK8' , 'DressedLepton' ]:
            # 4 momentum var
            for ivar, xb in {**fp_template, **addvar}.items():

                if ivar == "n":
                    name = "n_%s" %(icoll)
                    xbin = xb[0];
                    title = " ; %s ; Events" %( xb[-1].replace( 'XXX' , icoll ) );
                    varlist['%s_%s' %(sample,name)] = bookHistogram( df , name, xbin , title )
                else:
                    # number 
                    for i in range(0,3):
                        name = "%s%s_%s" %(icoll,i+1,ivar)
                        xbin = xb[0];
                        icoll_ = "%s%s" %(icoll,i+1)
                        title = " ; %s ; Events" %( xb[-1].replace( 'XXX' , icoll_ ) );
                        varlist['%s_%s' %(sample,name)] = bookHistogram( df , name, xbin , title )
        hist[sample] = varlist

    # action: plot
    hrefs = hist['powheg'] ; htests = hist['sherpa']
    for ipair in list(zip(hrefs, htests)):
        name = '%s_%s.png' % ( ipair[0].split('_')[1] , ipair[0].split('_')[2] )
        compare( hrefs[ipair[0]] , htests[ipair[1]] , name )
