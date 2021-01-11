import ROOT, sys
from collections import OrderedDict

ROOT.gStyle.SetPaintTextFormat("4.2f")

year="2016"

process={
    'top'        : [ "histo_top" ],
    'WW'         : [ "histo_WW" , "histo_ggWW" , "histo_WWewk" ],
    'non-prompt' : [ "histo_Fake_em" , "histo_Fake_mm" ],
    'DY'         : [ "histo_DY" ],
    'VVV'        : [ "histo_VVV" ],
    'ZZ'         : [ "histo_ZZ" ],
    'WZ'         : [ "histo_WZ" ],
    'Vg'         : [ "histo_Wg" , "histo_Zg" ],
    'VgS'        : [ "histo_WgS" , "histo_ZgS" ],
    'Higgs'      : [ "histo_ggH_hww", "histo_qqH_hww", "histo_ZH_hww", "histo_ggZH_hww", "histo_WH_hww", "histo_qqH_htt", "histo_ggH_htt", "histo_WH_htt", "histo_ZH_htt" ] #"histo_ttH_hww"
}

groupList={
    'top'        : { 'fillcolor' : 400 , 'fillstyle' : 1001 , 'linecolor' : 1   , 'linestyle' : 1 , 'linewidth' : 1 },
    'WW'         : { 'fillcolor' : 851 , 'fillstyle' : 1001 , 'linecolor' : 1   , 'linestyle' : 1 , 'linewidth' : 1 },
    'non-prompt' : { 'fillcolor' : 921 , 'fillstyle' : 1001 , 'linecolor' : 1   , 'linestyle' : 1 , 'linewidth' : 1 },
    'DY'         : { 'fillcolor' : 418 , 'fillstyle' : 1001 , 'linecolor' : 1   , 'linestyle' : 1 , 'linewidth' : 1 },
    'VVV'        : { 'fillcolor' : 857 , 'fillstyle' : 1001 , 'linecolor' : 1   , 'linestyle' : 1 , 'linewidth' : 1 },
    'ZZ'         : { 'fillcolor' : 617 , 'fillstyle' : 1001 , 'linecolor' : 1   , 'linestyle' : 1 , 'linewidth' : 1 },
    'WZ'         : { 'fillcolor' : 619 , 'fillstyle' : 1001 , 'linecolor' : 1   , 'linestyle' : 1 , 'linewidth' : 1 },
    'Vg'         : { 'fillcolor' : 810 , 'fillstyle' : 1001 , 'linecolor' : 1   , 'linestyle' : 1 , 'linewidth' : 1 },
    'VgS'        : { 'fillcolor' : 412 , 'fillstyle' : 1001 , 'linecolor' : 1   , 'linestyle' : 1 , 'linewidth' : 1 },
    'Higgs'      : { 'fillcolor' : 632 , 'fillstyle' : 0    , 'linecolor' : 632 , 'linestyle' : 1 , 'linewidth' : 2 },
    'DATA'       : { 'fillcolor' : 1   , 'fillstyle' : 1    , 'linecolor' : 1   , 'linestyle' : 1 , 'linewidth' : 1 }
}


variables=[
    "mlljj20_whss",
    "mlljj20_whss_bin2",
    "mlljj20_whss_bin3",
    "mlljj20_whss_bin4",
    "event"
]

filter_label={
    'cut0_all' : 'None',
    'cut1_mll12' : 'mll > 12', 
    'cut2_lepPt'  : 'Lepton cuts', 
    'cut3_bVeto'  : 'b-tag Veto', 
    #'cut4_metcut' : 'E_{T}^{miss} > 30 GeV',
    'cut4_metcut' : 'Pre-selection',
    'cut5_SS_inclusive' : 'Same sign',
    'cut6_SS_inclusive_1j' : 'njet >= 1',
    'cut7_SS_inclusive_1j_deta2' : '#Delta#eta(l_{1},l_{2}) < 2.0',
    'cut8_SS_inclusive_1j_mlljj50' : 'mlljj > 50',

    'cut6_SS_inclusive_2j' : 'njet >= 2',
    'cut7_SS_inclusive_2j_mjj100' : 'mjj < 100' ,
    'cut8_SS_inclusive_2j_deta2' : '#Delta#eta(l_{1},l_{2}) < 2.0',
    'cut9_SS_inclusive_2j_mlljj50' : 'mlljj > 50',

    'cut5_SFuu' : 'Same Sign #mu-#mu',
    'cut6_SFuu_nLep2' : 'nLep == 2',
    'cut7_SFuu_1j'    : 'njet >= 1',
    'cut8_SFuu_1j_deta2' : '#Delta#eta(l_{1},l_{2}) < 2.0',
    'cut9_SFuu_1j_Zveto' : 'abs(mll-91.2)>15',
    'cut10_SFuu_1j_mlljj50' : 'mlljj > 50',

    'cut7_SFuu_2j'    : 'njet >= 2',
    'cut8_SFuu_2j_mjj100' : 'mjj < 100' ,
    'cut9_SFuu_2j_deta2'  : '#Delta#eta(l_{1},l_{2}) < 2.0' ,
    'cut10_SFuu_2j_Zveto' : 'abs(mll-91.2)>15',
    'cut11_SFuu_2j_mlljj50' : 'mlljj > 50',
    
    'cut5_OFeu' : 'same sign e-#mu',
    'cut6_OFeu_nLep2' : 'nLep == 2',
    'cut7_OFeu_1j' : 'njet >= 1',
    'cut8_OFeu_1j_deta2' : '#Delta#eta(l_{1},l_{2}) < 2.0' ,
    'cut9_OFeu_1j_mlljj50' : 'mlljj > 50',
    
    'cut7_OFeu_2j' : 'njet >= 2',
    'cut8_OFeu_2j_mjj100' : 'mjj < 100',
    'cut9_OFeu_2j_deta2' : '#Delta#eta(l_{1},l_{2}) < 2.0' ,
    'cut10_OFeu_2j_mlljj50' : 'mlljj > 50'
}

var="events"
#var="mlljj20_whss_bin3"

#template_yield =OrderedDict({'nS' : 0. , 'nB' : 0. , 'bkgs' : {} , 'data' : 0. , 'sig' : 0. })
#cutflow_incl_1j = [ 'cut0_all' , 'cut1_mll12', 'cut2_lepPt', 'cut3_bVeto', 'cut4_metcut', 'cut5_SS_inclusive', 'cut6_SS_inclusive_1j', 'cut7_SS_inclusive_1j_deta2', 'cut8_SS_inclusive_1j_mlljj50' ]
#cutflow_incl_2j = [ 'cut0_all' , 'cut1_mll12', 'cut2_lepPt', 'cut3_bVeto', 'cut4_metcut', 'cut5_SS_inclusive', 'cut6_SS_inclusive_2j', 'cut7_SS_inclusive_2j_mjj100' , 'cut8_SS_inclusive_2j_deta2', 'cut9_SS_inclusive_2j_mlljj50' ]
#cutflow_uu_1j = [ 'cut0_all' , 'cut1_mll12', 'cut2_lepPt', 'cut3_bVeto', 'cut4_metcut', 'cut5_SFuu', 'cut6_SFuu_nLep2', 'cut7_SFuu_1j', 'cut8_SFuu_1j_deta2', 'cut9_SFuu_1j_Zveto', 'cut10_SFuu_1j_mlljj50' ]
#cutflow_uu_2j = [ 'cut0_all' , 'cut1_mll12', 'cut2_lepPt', 'cut3_bVeto', 'cut4_metcut', 'cut5_SFuu', 'cut6_SFuu_nLep2', 'cut7_SFuu_2j', 'cut8_SFuu_2j_mjj100', 'cut9_SFuu_2j_deta2', 'cut10_SFuu_2j_Zveto', 'cut11_SFuu_2j_mlljj50' ] 
#cutflow_eu_1j = [ 'cut0_all' , 'cut1_mll12', 'cut2_lepPt', 'cut3_bVeto', 'cut4_metcut', 'cut5_OFeu', 'cut6_OFeu_nLep2', 'cut7_OFeu_1j', 'cut8_OFeu_1j_deta2', 'cut9_OFeu_1j_mlljj50' ]
#cutflow_eu_2j = [ 'cut0_all' , 'cut1_mll12', 'cut2_lepPt', 'cut3_bVeto', 'cut4_metcut', 'cut5_OFeu', 'cut6_OFeu_nLep2', 'cut7_OFeu_2j', 'cut8_OFeu_2j_mjj100', 'cut9_OFeu_2j_deta2', 'cut10_OFeu_2j_mlljj50' ]

## preselection - cuts 
cutflow_incl_1j = [ 'cut4_metcut', 'cut5_SS_inclusive', 'cut6_SS_inclusive_1j', 'cut7_SS_inclusive_1j_deta2', 'cut8_SS_inclusive_1j_mlljj50' ]
cutflow_incl_2j = [ 'cut4_metcut', 'cut5_SS_inclusive', 'cut6_SS_inclusive_2j', 'cut7_SS_inclusive_2j_mjj100' , 'cut8_SS_inclusive_2j_deta2', 'cut9_SS_inclusive_2j_mlljj50' ]
cutflow_uu_1j = [ 'cut4_metcut', 'cut5_SFuu', 'cut6_SFuu_nLep2', 'cut7_SFuu_1j', 'cut8_SFuu_1j_deta2', 'cut9_SFuu_1j_Zveto', 'cut10_SFuu_1j_mlljj50' ]
cutflow_uu_2j = [ 'cut4_metcut', 'cut5_SFuu', 'cut6_SFuu_nLep2', 'cut7_SFuu_2j', 'cut8_SFuu_2j_mjj100', 'cut9_SFuu_2j_deta2', 'cut10_SFuu_2j_Zveto', 'cut11_SFuu_2j_mlljj50' ]
cutflow_eu_1j = [ 'cut4_metcut', 'cut5_OFeu', 'cut6_OFeu_nLep2', 'cut7_OFeu_1j', 'cut8_OFeu_1j_deta2', 'cut9_OFeu_1j_mlljj50' ]
cutflow_eu_2j = [ 'cut4_metcut', 'cut5_OFeu', 'cut6_OFeu_nLep2', 'cut7_OFeu_2j', 'cut8_OFeu_2j_mjj100', 'cut9_OFeu_2j_deta2', 'cut10_OFeu_2j_mlljj50' ]


workflow=OrderedDict()
#prepare structure
for icfname , icutflow in zip( [ "incl_1j" , "incl_2j" , "uu1j" , "uu2j" , "eu1j" , "eu2j" ], [ cutflow_incl_1j , cutflow_incl_2j , cutflow_uu_1j , cutflow_uu_2j , cutflow_eu_1j , cutflow_eu_2j ] ):
    workflow[icfname] = dict.fromkeys( icutflow , {} )

#load
fin="plots_Cutflow_WHSS%s_final_ttHMVASF_standalone.root" %year
f = ROOT.TFile( fin , "read" )

# loop on workflow
for icutflow in workflow:
    process_ = OrderedDict()
    for icut in workflow[icutflow].keys():
        #print(icut)
        process_ = {}
        #for iproc in process:
        #    for jproc in process[iproc]:
        #        print( '%s/%s/%s' %( icut , var , jproc ) )
        for iproc in process: process_[iproc] = sum( map(lambda x : f.Get( '%s/%s/%s' %( icut , var , x) ).Integral() , process[iproc] ) )
        nS = process_.pop('Higgs')
        nB = sum( map(lambda x : process_[x] , process_ ) )
        template_yield = OrderedDict(
            {
                'nS' : nS , 
                'nB' : nB , 
                'bkgs' : process_ , 
                'data' : f.Get( '%s/%s/histo_DATA'%( icut , var ) ).Integral() , 
                # http://tid.uio.no/epf/seminar/slides/simpleopt.pdf
                'sig' : (nS)/ROOT.TMath.Sqrt(nB+nS) # optimize power (sensitivity) of analysis
                #'sig' : (nS)/ROOT.TMath.Sqrt(nB)   # optimize significance of signal
            }
        )
        workflow[icutflow][icut] = template_yield
###############################################################################################
canvas={}
useDATA=False
#exclusive=False
#gap=0
#if exclusive:
#    gap=3

# each cutflow one histogram
for icutflow in workflow:
    xlabels = list(workflow[icutflow].keys())
    #xlabels_ = []
    #if exclusive:
    #    for icut in xlabels:
    #        if int(icut.split('_')[0].split('cut')[-1]) <3 : continue
    #        print(icut)
    #        xlabels_.append(icut)
    #xlabels = xlabels_
    nbins = len(xlabels)
    hist=OrderedDict()
    
    # declare histogram
    for iproc in process: 
        #if iproc == 'Higgs': continue #exclude signal
        hist[iproc] = ROOT.TH1D( "hist_%s_%s" %( icutflow , iproc ) , "cutflow %s" %icutflow , nbins , 0 , nbins )
        # set label
        for ibin in range(1,nbins+1) : hist[iproc].GetXaxis().SetBinLabel( ibin , filter_label[xlabels[ibin-1]] )

    #DATA
    if useDATA:
        hist_data = ROOT.TH1D( "hist_%s_DATA" %icutflow , "cutflow %s" %icutflow , nbins , 0 , nbins )
        for ibin in range(1,nbins+1) : hist_data.GetXaxis().SetBinLabel( ibin , filter_label[xlabels[ibin-1]] )

    hist_signal = hist.pop('Higgs')
    
    # iterate cut and fill histogram of background composition
    for icut, ibin in zip( workflow[icutflow] , range(0,nbins) ):
        #if exclusive:
        #    if int(icut.split('_')[0].split('cut')[-1]) <gap : continue 
        for ihist in hist: hist[ihist].Fill( ibin , workflow[icutflow][icut]['bkgs'][ihist] )
        hist_signal.Fill( ibin , workflow[icutflow][icut]['nS'] )
        if useDATA: hist_data.Fill( ibin , workflow[icutflow][icut]['data'] )
        
    # create stack histogram
    bkg = ROOT.THStack( "bkg", "%s %s; ; Events" %( fin.split('_')[2] , icutflow ) )
    for ihist in hist: 
        hist[ihist].SetFillColor(groupList[ihist]['fillcolor'])
        hist[ihist].SetFillStyle(groupList[ihist]['fillstyle'])
        hist[ihist].SetLineColor(groupList[ihist]['linecolor'])
        hist[ihist].SetLineStyle(groupList[ihist]['linestyle'])
        hist[ihist].SetLineWidth(groupList[ihist]['linewidth'])
        bkg.Add(hist[ihist])
    bkg.SetMaximum( bkg.GetMaximum()*3.0 )
    bkg.SetMinimum( 5.e-1 )

    hist_signal.SetFillColor(groupList['Higgs']['fillcolor'])
    hist_signal.SetFillStyle(groupList['Higgs']['fillstyle'])
    hist_signal.SetLineColor(groupList['Higgs']['linecolor'])
    hist_signal.SetLineStyle(groupList['Higgs']['linestyle'])
    hist_signal.SetLineWidth(groupList['Higgs']['linewidth'])

    if useDATA:
        hist_data.SetFillColor(groupList['DATA']['fillcolor'])
        hist_data.SetFillStyle(groupList['DATA']['fillstyle'])
        hist_data.SetLineColor(groupList['DATA']['linecolor'])
        hist_data.SetLineStyle(groupList['DATA']['linestyle'])
        hist_data.SetLineWidth(groupList['DATA']['linewidth'])
        hist_data.SetMarkerStyle(20)
        hist_data.SetMarkerSize(1.25)

    # legend
    nleg = len(hist)
    leg = ROOT.TLegend(0.7, 0.9-0.05*nleg, 0.95, 0.9) ; #leg.SetNColumns(2)
    leg.SetBorderSize(0)
    leg.SetFillStyle(0) #1001
    leg.SetFillColor(0)

    #for i, s in reversed(hist.keys()): leg.AddEntry( hist[s] , s , "f")
    for ihist in hist.keys() : leg.AddEntry( hist[ihist] , "%s" %ihist , "f" )
    leg.AddEntry( hist_signal , "Higgs" , "l" )
    if useDATA: leg.AddEntry( hist_data , "DATA" , "pl" )

    # Display
    canvas[icutflow] = ROOT.TCanvas( "c_%s" %icutflow , icutflow , 800, 600 )
    canvas[icutflow].SetLogy()

    latex = ROOT.TLatex()
    #latex.SetNDC()
    latex.SetTextAlign(12)
    latex.SetTextColor(1)
    latex.SetTextFont(72)
    latex.SetTextSize(0.02)

    bkg.Draw("HIST") # stack
    hist_signal.Scale(1) # scale signal
    
    for icut, ibin in zip( workflow[icutflow] , range(0,nbins)): latex.DrawLatex( ibin , hist_signal.GetBinContent(ibin+1)*1.6 , 'S/#sqrt{B+S} = %.2f' %workflow[icutflow][icut]['sig'] ) # S/#sqrt{B}=%.2f
    
    hist_signal.Draw("SAME, HIST") # sum of bkg
    if useDATA: hist_data.Draw("SAME, PE")
    leg.Draw()

    canvas[icutflow].Update()

    canvas[icutflow].SaveAs( "%s_%s_%s.png" %( fin.split('_')[1] , fin.split('_')[2] , icutflow ) )
