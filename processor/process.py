#! /usr/bin/env python

from optparse import OptionParser
import os, sys, time

cwd = os.getcwd()
output="%s/output" %(cwd)

lumi="35.867"
MC_path="/media/shoh/02A1ACF427292FC0/nanov5/Private_signal/Summer16_102X_nAODv5_Full2016v6/MCl1loose2016__MCCorr2016v6__l2loose__l2tightOR2016v6"

if not os.path.exists(output)   : os.system( "mkdir -p %s" %output   )

os.system("make")
for iproc in [ "sshwminus012j" , "sshwplus012j" ] :
    cmd="./processor "
    input="%s/data/filelists/%s.txt" %( cwd , iproc )
    cmd+=" %s %s %s/%s.root" %( iproc , input , output , iproc )
    
    tproc = time.time();

    print(cmd)
    os.system(cmd)

    print("--- running on %s took : %.3f seconds (%.3f minutes) ---" % ( iproc , (time.time() - tproc) , (time.time() - tproc)/60. ) )
