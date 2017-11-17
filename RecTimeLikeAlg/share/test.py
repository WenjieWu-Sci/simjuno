#!/usr/bin/python

import Sniper
task = Sniper.Task("task")
task.asTop()
task.setLogLevel(3)

import os
import RecTimeLikeAlg
alg = task.createAlg("RecTimeLikeAlg/rec_timelike")
alg.property("TotalPMT").set(18306)
alg.property("PMT_R").set(18.750)
alg.property("Ball_R").set(18.496)
alg.property("Energy_Scale").set(3414.5454)
alg.property("File_path").set( 
                os.path.join(os.environ["RECTIMELIKEALGROOT"],"share",""))
alg.setLogLevel(2)

import BufferMemMgr
bufMgr = task.createSvc("BufferMemMgr")
bufMgr.property("TimeWindow").set([-0.01, 0.01]);

import DataRegistritionSvc
task.property("svcs").append("DataRegistritionSvc")

import RootIOSvc
roSvc = task.createSvc("RootOutputSvc/OutputSvc")
roSvc.property("OutputStreams").set({"/Event/Rec": "recOut.root", "/Event/Calib":"recOut.root"})

if os.path.exists("recIn.root") : 
    riSvc = task.createSvc("RootInputSvc/InputSvc")
    riSvc.property("InputFile").set(["recIn.root"])
#else :
    #alg.property("CreateInputFlag").set(1)


import Geometry
geom = task.createSvc("RecGeomSvc")
geom.property("GeomFile").set("default")

task.setEvtMax(10)
task.show()
task.run()
