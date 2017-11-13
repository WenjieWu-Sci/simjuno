#!/bin/bash

work_path="/sps/hep/juno/qihuang/simjuno/_BUILD/jobs"
if [ ! -d "${work_path}" ];then
    mkdir "${work_path}"
    echo "create folder ${work_path}"
fi

r1=3
r2=7
njob=50
nevt=200

for i in `seq 1 "${njob}"`; do
    tee <<- EOF > "${work_path}/basic_${i}.mac"

# This macro just runs one single particle
# to prove that the application works
#
# Run it using "./task macros/basic.mac"
/run/initialize
/tracking/verbose 1
/random/setSeeds $r1 $r2
/gun/position 0 0 0 cm
/gun/particle e-
/gun/direction 0 0 1
/gun/energy 1 MeV
/run/beamOn $nevt
EOF

    tee <<- EOF > "${work_path}/launch_${i}.sh"
#!/bin/bash

cd ${work_path}
source ${work_path}/../env_run.sh
pushd "\${TMPDIR}" &> /dev/null
${work_path}/../simjuno ${work_path}/basic_${i}.mac &> record.txt
mv "simjunotest.root" ${work_path}/basic_${i}.root
mv record.txt ${work_path}/basic_${i}.log
popd &> /dev/null

echo "Submit job $i, random seeds are $r1 $r2"; echo
EOF

let r1=r1+1
let r2=r2+1

done


for i in `seq 1 "${njob}"`; do
    qsub -P P_juno -l sps=1,ct=3000,vmem=3G,fsize=8G -e ${work_path}/basic_${i}.err -o ${work_path}/basic_${i}.out ${work_path}/launch_${i}.sh
done

exit 0
