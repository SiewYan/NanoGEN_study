#!/bin/bash

# SUS-RunIISummer20UL18wmLHEGEN-00038_get_test

export HOME=${PWD}
source inputs.sh

source /cvmfs/cms.cern.ch/cmsset_default.sh

# Generate random seeds                                                                                               
RANDOMSEED=`od -vAn -N4 -tu4 < /dev/urandom`

#Sometimes the RANDOMSEED is too long                                                                                 
RANDOMSEED=`echo $RANDOMSEED | rev | cut -c 3- | rev`


# GEN Script begin
rm -f request_fragment_check.py
wget -q https://raw.githubusercontent.com/cms-sw/genproductions/master/bin/utils/request_fragment_check.py
chmod +x request_fragment_check.py
./request_fragment_check.py --bypass_status --prepid SUS-RunIISummer20UL18wmLHEGEN-00038
GEN_ERR=$?
if [ $GEN_ERR -ne 0 ]; then
  echo "GEN Checking Script returned exit code $GEN_ERR which means there are $GEN_ERR errors"
  echo "Validation WILL NOT RUN"
  echo "Please correct errors in the request and run validation again"
  exit $GEN_ERR
fi
echo "Running VALIDATION. GEN Request Checking Script returned no errors"
# GEN Script end

export SCRAM_ARCH=slc7_amd64_gcc700

source /cvmfs/cms.cern.ch/cmsset_default.sh
if [ -r CMSSW_10_6_19_patch3/src ] ; then
  echo release CMSSW_10_6_19_patch3 already exists
else
  scram p CMSSW CMSSW_10_6_19_patch3
fi
cd CMSSW_10_6_19_patch3/src
eval `scram runtime -sh`

# Download fragment from McM
curl -s -k https://cms-pdmv.cern.ch/mcm/public/restapi/requests/get_fragment/SUS-RunIISummer20UL18wmLHEGEN-00038 --retry 3 --create-dirs -o Configuration/GenProduction/python/SUS-RunIISummer20UL18wmLHEGEN-00038-fragment.py
[ -s Configuration/GenProduction/python/SUS-RunIISummer20UL18wmLHEGEN-00038-fragment.py ] || exit $?;

# Check if fragment contais gridpack path ant that it is in cvmfs
if grep -q "gridpacks" Configuration/GenProduction/python/SUS-RunIISummer20UL18wmLHEGEN-00038-fragment.py; then
  if ! grep -q "/cvmfs/cms.cern.ch/phys_generator/gridpacks" Configuration/GenProduction/python/SUS-RunIISummer20UL18wmLHEGEN-00038-fragment.py; then
    echo "Gridpack inside fragment is not in cvmfs."
    exit -1
  fi
fi
scram b
cd ../..

# Maximum validation duration: 28800s
# Margin for validation duration: 30%
# Validation duration with margin: 28800 * (1 - 0.30) = 20160s
# Time per event for each sequence: 3.3075s
# Threads for each sequence: 1
# Time per event for single thread for each sequence: 1 * 3.3075s = 3.3075s
# Which adds up to 3.3075s per event
# Single core events that fit in validation duration: 20160s / 3.3075s = 6095
# Produced events limit in McM is 10000
# According to 1.0000 efficiency, validation should run 10000 / 1.0000 = 10000 events to reach the limit of 10000
# Take the minimum of 6095 and 10000, but more than 0 -> 6095
# It is estimated that this validation will produce: 6095 * 1.0000 = 6095 events
EVENTS=${NEVENT}


# cmsDriver command
cmsDriver.py Configuration/GenProduction/python/SUS-RunIISummer20UL18wmLHEGEN-00038-fragment.py \
    --step LHE,GEN,NANOGEN \
    --mc \
    --datatier NANOAOD \
    --eventcontent NANOAODGEN \
    --conditions 106X_upgrade2018_realistic_v15_L1v1 \
    --beamspot Realistic25ns13TeVEarly2018Collision \
    --geometry DB:Extended \
    --era Run2_2018 \
    --python_filename SUS-RunIISummer20UL18wmLHEGEN-00038_1_cfg.py \
    --fileout file:powheg_WW2L2Nu_${RANDOMSEED}.root \
    --nThreads 4 \
    -n ${EVENTS} \
    --customise_commands process.RandomNumberGeneratorService.generator.initialSeed=${RANDOMSEED} \
    --customise_commands process.source.numberEventsInLuminosityBlock="cms.untracked.uint32(100)" \
    --customise Configuration/DataProcessing/Utils.addMonitoring \
    --no_exec

# Run generated config
REPORT_NAME=SUS-RunIISummer20UL18wmLHEGEN-00038_report.xml
# Run the cmsRun
cmsRun -e -j $REPORT_NAME SUS-RunIISummer20UL18wmLHEGEN-00038_1_cfg.py || exit $? ;

# Parse values from SUS-RunIISummer20UL18wmLHEGEN-00038_report.xml report
processedEvents=$(grep -Po "(?<=<Metric Name=\"NumberEvents\" Value=\")(.*)(?=\"/>)" $REPORT_NAME | tail -n 1)
producedEvents=$(grep -Po "(?<=<TotalEvents>)(\d*)(?=</TotalEvents>)" $REPORT_NAME | tail -n 1)
threads=$(grep -Po "(?<=<Metric Name=\"NumberOfThreads\" Value=\")(.*)(?=\"/>)" $REPORT_NAME | tail -n 1)
peakValueRss=$(grep -Po "(?<=<Metric Name=\"PeakValueRss\" Value=\")(.*)(?=\"/>)" $REPORT_NAME | tail -n 1)
peakValueVsize=$(grep -Po "(?<=<Metric Name=\"PeakValueVsize\" Value=\")(.*)(?=\"/>)" $REPORT_NAME | tail -n 1)
totalSize=$(grep -Po "(?<=<Metric Name=\"Timing-tstoragefile-write-totalMegabytes\" Value=\")(.*)(?=\"/>)" $REPORT_NAME | tail -n 1)
totalSizeAlt=$(grep -Po "(?<=<Metric Name=\"Timing-file-write-totalMegabytes\" Value=\")(.*)(?=\"/>)" $REPORT_NAME | tail -n 1)
totalJobTime=$(grep -Po "(?<=<Metric Name=\"TotalJobTime\" Value=\")(.*)(?=\"/>)" $REPORT_NAME | tail -n 1)
totalJobCPU=$(grep -Po "(?<=<Metric Name=\"TotalJobCPU\" Value=\")(.*)(?=\"/>)" $REPORT_NAME | tail -n 1)
eventThroughput=$(grep -Po "(?<=<Metric Name=\"EventThroughput\" Value=\")(.*)(?=\"/>)" $REPORT_NAME | tail -n 1)
avgEventTime=$(grep -Po "(?<=<Metric Name=\"AvgEventTime\" Value=\")(.*)(?=\"/>)" $REPORT_NAME | tail -n 1)
if [ -z "$threads" ]; then
  echo "Could not find NumberOfThreads in report, defaulting to 1"
  threads=1
fi
if [ -z "$eventThroughput" ]; then
  eventThroughput=$(bc -l <<< "scale=4; 1 / ($avgEventTime / $threads)")
fi
if [ -z "$totalSize" ]; then
  totalSize=$totalSizeAlt
fi
if [ -z "$processedEvents" ]; then
  processedEvents=$EVENTS
fi
echo "Validation report of SUS-RunIISummer20UL18wmLHEGEN-00038 sequence 1/1"
echo "Processed events: $processedEvents"
echo "Produced events: $producedEvents"
echo "Threads: $threads"
echo "Peak value RSS: $peakValueRss MB"
echo "Peak value Vsize: $peakValueVsize MB"
echo "Total size: $totalSize MB"
echo "Total job time: $totalJobTime s"
echo "Total CPU time: $totalJobCPU s"
echo "Event throughput: $eventThroughput"
echo "CPU efficiency: "$(bc -l <<< "scale=2; ($totalJobCPU * 100) / ($threads * $totalJobTime)")" %"
echo "Size per event: "$(bc -l <<< "scale=4; ($totalSize * 1024 / $producedEvents)")" kB"
echo "Time per event: "$(bc -l <<< "scale=4; (1 / $eventThroughput)")" s"
echo "Filter efficiency percent: "$(bc -l <<< "scale=8; ($producedEvents * 100) / $processedEvents")" %"
echo "Filter efficiency fraction: "$(bc -l <<< "scale=10; ($producedEvents) / $processedEvents")

xrdcp powheg_WW2L2Nu_${RANDOMSEED}.root  root://eosuser.cern.ch//eos/user/s/shoh/NANOAD_private/Powheg_WW2L2Nu_events/powheg_WW2L2Nu_${RANDOMSEED}.root
