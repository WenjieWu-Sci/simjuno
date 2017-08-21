# echo "setup PhysiSim v0 in /afs/ihep.ac.cn/users/w/wenjie/junofs/juno_trunk/offline/Simulation/DetSimV2"

if test "${CMTROOT}" = ""; then
  CMTROOT=/afs/ihep.ac.cn/soft/juno/JUNO-ALL-SLC6/Release/J16v1r1/ExternalLibs/CMT/v1r26; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
cmtPhysiSimtempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then cmtPhysiSimtempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt setup -sh -pack=PhysiSim -version=v0 -path=/afs/ihep.ac.cn/users/w/wenjie/junofs/juno_trunk/offline/Simulation/DetSimV2  -no_cleanup $* >${cmtPhysiSimtempfile}
if test $? != 0 ; then
  echo >&2 "${CMTROOT}/mgr/cmt setup -sh -pack=PhysiSim -version=v0 -path=/afs/ihep.ac.cn/users/w/wenjie/junofs/juno_trunk/offline/Simulation/DetSimV2  -no_cleanup $* >${cmtPhysiSimtempfile}"
  cmtsetupstatus=2
  /bin/rm -f ${cmtPhysiSimtempfile}
  unset cmtPhysiSimtempfile
  return $cmtsetupstatus
fi
cmtsetupstatus=0
. ${cmtPhysiSimtempfile}
if test $? != 0 ; then
  cmtsetupstatus=2
fi
/bin/rm -f ${cmtPhysiSimtempfile}
unset cmtPhysiSimtempfile
return $cmtsetupstatus

