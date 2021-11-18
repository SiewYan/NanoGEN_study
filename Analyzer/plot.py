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
    'Phi': [ ( 120 , 0.  , 3.5  ) , "XXX #Phi"           ] , 
    'M'  : [ ( 50  , 0.  , 500. ) , "XXX Mass [GeV/c^2]" ]
})

# additional variable
addvar = OrderedDict({
    'pdgId' : [ ( 50 , 30. , -30. ) , "XXX PdgId"        ]
})
##

# helper function
def bookHistogram( df_ , name_ , xbin_ , title_ ):
    histModel = ROOT.ROOT.RDF.TH1DModel(  name_ , title_ , xbin_[0], xbin_[1], xbin_[2] )
    return df_.Histo1D( histModel , name_ )
    #return df_.Define( name_ , fpvar_ ).Histo1D( histModel , name_ )
pass

# plot
def compare( hist_ref_ , hist_ , PNGname_ ):

    hist_ref = hist_ref_.GetPtr()
    hist = hist_.GetPtr()
 
    canvas = ROOT.TCanvas("canvas")
    
    ratio = hist.Clone()
    ratio.Divide(hist_ref)
    ratio.SetLineColor(ROOT.kRed)

    pad1 = ROOT.TPad("pad1","pad1",0,0.3,1,1)
    pad1.SetBottomMargin(0)
    pad1.SetLogy(True)
    pad1.Draw()
    pad1.cd()

    hist_ref.Draw("h")
    hist.Draw("h SAME")

    # pad1 style
    hist_ref.SetTitle("")
    hist_ref.GetXaxis().SetLabelSize(0)
    hist_ref.GetXaxis().SetTitleSize(0)
    hist_ref.GetYaxis().SetTitleSize(0.05)

    # description (if any)
    latex = ROOT.TLatex()
    latex.SetNDC()
    latex.SetTextSize(0.06)
    latex.DrawText(0.7 ,0.83 , "Run 2018" )
    latex.SetTextSize(0.04)
    latex.DrawText(0.7 ,0.77 , " WWjets NLO events" )

    # legend     
    legend = ROOT.TLegend(0.7 ,0.6 ,0.85 ,0.75)
    legend.AddEntry( hist_ref , "Powheg" )
    legend.AddEntry( hist , "Sherpa" )
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
    ratio.GetYaxis().SetTitleSize(0.15)
    ratio.GetYaxis().SetTitle("Sherpa / Powheg")
    ratio.GetYaxis().SetTitleOffset(0.3)

    ratio.GetYaxis().SetRangeUser(0.5 ,1.5)
    ratio.GetYaxis().SetNdivisions(207)

    line = ROOT.TLine(50.e3 ,1 ,200.e3 ,1)
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
        for var in [ 'Lepton' , 'GenJetAK4' , 'GenJetAK8' ]:
            # 4 momentum var
            for ivar, xb in {**fp_template, **addvar}.items():
                
                #if ivar in [ 'Pt' , 'Eta' , 'Phi' , 'M' ]: continue
                
                # number 
                for i in range(0,3):
                    name = "%s%s_%s" %(var,i+1,ivar)
                    #fpvar = "%s[%s].%s()" %(var,i,ivar) \
                    #        if ivar in [ 'Pt' , 'Eta' , 'Phi' , 'M' ] \
                    #           else "%s_%s[%s]" %(var,ivar,i)
                    
                    xbin = xb[0];
                    title = "%s ; Events" %( xb[-1].replace( 'XXX' , var ) );
                    varlist['%s_%s' %(sample,name)] = bookHistogram( df , name, xbin , title )
        hist[sample] = varlist

    # action: plot
    hrefs = hist['powheg'] ; htests = hist['sherpa']
    for ipair in list(zip(hrefs, htests)):
        name = '%s_%s.png' % ( ipair[0].split('_')[1] , ipair[0].split('_')[2] )
        compare( hrefs[ipair[0]] , htests[ipair[1]] , name )
