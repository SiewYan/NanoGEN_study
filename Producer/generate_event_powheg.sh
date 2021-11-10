#!/bin/bash

set -e

#+++++++++++++++++++++++++++++++++++++++++++++++
#Run on one sherpack for testing, please comment this if run in bunches
#export EOSSPACE="/eos/uscms${eos_input}"
#export EOSSPACE="./inputs"
#+++++++++++++++++++++++++++++++++++++++++++++++
export BASEDIR=${PWD}
# sherpack directory is the same as base directory
#export SHERPACKDIR=${BASEDIR}

#export SCRAMARCH=slc7_amd64_gcc820
#export CMSSWRELEASE=CMSSW_10_6_28
# 100 JOBs x 100 NEVENT = 50k
export NEVENT=500
export NJOBS=100

if [ -e "work_${1}" ];then
    rm -r work_${1}
fi

if [ -e "submit" ];then
    rm -r submit
fi

mkdir submit work_${1}
export SUBMIT_WORKDIR=${PWD}/work_${1}

cat > inputs.sh <<EOF
NEVENT=${NEVENT}
PROCESS=${1}
EOF

source inputs.sh
mv inputs.sh submit
cp ./data/powheg/WW2L2Nu_testscript.sh submit

#if [ -z "$2" ]
#then
#    echo "EVENTGENERATION=1" >> ./submit/inputs.sh
#    echo "You want to produce events for $1. Good luck!"
#else
#    echo "EVENTGENERATION=0" >> ./submit/inputs.sh
#    echo "You want to produce sherpack for $1. Good luck!"
#fi

# copy input files
mkdir -p ./submit/inputs

#for EXT in libs crdE crss logL migr
#do cp ${SHERPACKDIR}/sherpa_${1}_${EXT}.tgz ./submit/inputs ; done
#if [ -e "${SHERPACKDIR}/sherpa_${1}_cfi.py" ]; then cp ${SHERPACKDIR}/sherpa_${1}_cfi.py ./submit/inputs ; fi

voms-proxy-init -voms cms -valid 172:00 --out ${HOME}/private/x509up_u${UID}
cp ${HOME}/private/x509up_u${UID} ${SUBMIT_WORKDIR}/x509up
cp ${HOME}/.gitconfig ./submit/.gitconfig

#creating tarball
echo "Tarring up submit..."
tar -chzf submit.tgz submit 
rm -r ${BASEDIR}/submit
mv ${BASEDIR}/submit.tgz ${SUBMIT_WORKDIR}

cat > exec.sh <<EOF
#!/bin/bash

export X509_USER_PROXY=${PWD}/x509up
export HOMEDIR=${PWD}

tar xvaf submit.tgz
cd submit

. WW2L2Nu_testscript.sh
cd ${HOMEDIR}
rm -r submit

exit 0
EOF

chmod +x exec.sh
mv ${BASEDIR}/exec.sh ${SUBMIT_WORKDIR}

#does everything look okay?
ls -l ${SUBMIT_WORKDIR}

# prepare submit
echo " --> python submit.py work_${PROCESS} ${NJOBS}"
python submit.py work_${PROCESS} ${NJOBS}
