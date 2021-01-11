from ROOT import TLatex

def drawCMS(year, text, onTop=False):
    lumis={
        '2016' : "35.9",
        '2017' : "41.5",
        '2018' : "59.74",
    }
    lumi = lumis[year]
    latex = TLatex()
    latex.SetNDC()
    latex.SetTextSize(0.04)
    latex.SetTextColor(1)
    latex.SetTextFont(42)
    latex.SetTextAlign(33)
    if (type(lumi) is float or type(lumi) is int) and float(lumi) > 0: latex.DrawLatex(0.95, 0.985, "%.1f fb^{-1}  (13 TeV)" % (float(lumi)/1000.) )
    elif type(lumi) is str: latex.DrawLatex( 0.92 , 0.94 , "%s fb^{-1}  (13 TeV)" % lumi)
    if not onTop: latex.SetTextAlign(11)
    latex.SetTextFont(62)
    latex.SetTextSize(0.05 if len(text)>0 else 0.06)
    if not onTop: latex.DrawLatex(0.15, 0.87 if len(text)>0 else 0.84, "CMS")
    else: latex.DrawLatex( 0.20 , 0.94 , "CMS" )
    latex.SetTextSize(0.04)
    latex.SetTextFont(52)
    if not onTop: latex.DrawLatex( 0.15 , 0.83 , text)
    else: latex.DrawLatex( 0.42 , 0.93 , text)
    pass

def drawRegion(channel, left=False):
    region = { 
        "incl_1j" : "Inclusive 1j", 
        "incl_2j" : "Inclusive 2j", 
        "uu1j" : "#mu^{#pm}#mu^{#pm} 1j", 
        "uu2j" : "#mu^{#pm}#mu^{#pm} 2j", 
        "eu1j" : "e^{#pm}#mu^{#pm} 1j", 
        "eu2j" : "e^{#pm}#mu^{#pm} 2j"
    }
    text = ""
    if channel in region: text = region[channel]

    latex = TLatex()
    latex.SetNDC()
    latex.SetTextFont(52) #52
    latex.SetTextSize(0.035)
    if left: latex.DrawLatex(0.15, 0.75, text)
    else:
        latex.SetTextAlign(22)
        latex.DrawLatex( 0.5 , 0.75 , text )
    pass
