# echo "setup PhysiSim v0 in /afs/ihep.ac.cn/users/w/wenjie/junofs/juno_trunk/offline/Simulation/DetSimV2"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /afs/ihep.ac.cn/soft/juno/JUNO-ALL-SLC6/Release/J16v1r1/ExternalLibs/CMT/v1r26
endif
source ${CMTROOT}/mgr/setup.csh
set cmtPhysiSimtempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if $status != 0 then
  set cmtPhysiSimtempfile=/tmp/cmt.$$
endif
${CMTROOT}/mgr/cmt setup -csh -pack=PhysiSim -version=v0 -path=/afs/ihep.ac.cn/users/w/wenjie/junofs/juno_trunk/offline/Simulation/DetSimV2  -no_cleanup $* >${cmtPhysiSimtempfile}
if ( $status != 0 ) then
  echo "${CMTROOT}/mgr/cmt setup -csh -pack=PhysiSim -version=v0 -path=/afs/ihep.ac.cn/users/w/wenjie/junofs/juno_trunk/offline/Simulation/DetSimV2  -no_cleanup $* >${cmtPhysiSimtempfile}"
  set cmtsetupstatus=2
  /bin/rm -f ${cmtPhysiSimtempfile}
  unset cmtPhysiSimtempfile
  exit $cmtsetupstatus
endif
set cmtsetupstatus=0
source ${cmtPhysiSimtempfile}
if ( $status != 0 ) then
  set cmtsetupstatus=2
endif
/bin/rm -f ${cmtPhysiSimtempfile}
unset cmtPhysiSimtempfile
exit $cmtsetupstatus

