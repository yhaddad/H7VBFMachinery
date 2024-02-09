#!/bin/bash
source /afs/cern.ch/user/y/yhaddad/work/genpack/HERWIG7/local/bin/activate
export RIVET_ANALYSIS_PATH=$PWD

echo " -- filename : ", $1 
echo " -- index    : ", $2
echo "... start job at" `date "+%Y-%m-%d %H:%M:%S"`
lhefile=$1
echo " -- memory"
free -m -h

NEVT=$(cat $1 | grep "</event>" | wc -l)
echo " -- number of events : ", $NEVT

echo "----- run card -------"
sed -i 's+LHEINPUTFILE+'$lhefile'+g' LHE-POWHEG.in
sed -i 's+NEVENTS+'$NEVT'+g' LHE-POWHEG.in

cat LHE-POWHEG.in
echo "----- compiling rivet:"
rivet-buildplugin HiggsTemplateCrossSections.cc -std=c++11

echo "----- directory before running:"
ls -l .
Herwig read LHE-POWHEG.in
Herwig run LHE.run

echo "----- what do we have after running :"
ls -l .
mv HJET_STXS.csv LHE-STXS-$2.csv 
xrdcp -s -f LHE-STXS-$2.csv /eos/user/y/yhaddad/GEN/HEPMC/HJETS/powheg-herwig7

echo "----- directory after everthing :"
ls -l 

echo " ------ THE END (everyone dies !) ----- "
