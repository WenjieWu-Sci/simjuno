#!/usr/bin/env python
# -*- coding:utf-8 -*-
#
# Author: ZHANG Kun - zhangkun@ihep.ac.cn
# Last modified: 2013-11-12 00:48
# Filename: test.py
# Description:

import os
import sys
sys.setdlopenflags( 0x100 | 0x2 )    # RTLD_GLOBAL | RTLD_NOW

import libSniperMgr
import libSniperPython as sp

mgr = libSniperMgr.SniperMgr()
mgr.setProp("EvtMax", 5)
mgr.setProp("InputSvc", "NONE")
mgr.setProp("LogLevel", 1)
sp.setProperty("Sniper", "Dlls", ["RecTimeLikeAlg","RecEvent", "SimEvent", "Geometry", "TopAlg", "DetSimResultCnv", "PmtRec"])

mgr.configure()

svcMgr = sp.SvcMgr.instance()
algMgr = sp.AlgMgr.instance()

#get the DataBuffer service
bufsvc=sp.SvcMgr.get("DataBufSvc", True)
svcMgr.add(bufsvc.name())

vp=["/Event/Sim/Test", "/Event/Rec/Test", "/Event/Ana/Test",
        "/Event/Rec/RecHeader", "/Event/Calib/CalibHeader",
        "/Event/Sim/SimHeader",

        "/Topology/TopHeader"]
bufsvc.setProp("ValidPaths", vp)
op=["/Event/Rec/RecHeader",
        "/Event/Calib/CalibHeader",
        "/Event/Sim/SimHeader",
        ]
bufsvc.setProp("OutputItems", op)
ip=[]
bufsvc.setProp("InputItems", ip)

# IO service
sios=sp.SvcMgr.get("SniperIOSvc", True)
svcMgr.add(sios.name())
#sios.setProp("InputFile",["input.root"])
sios.setProp("OutputFile","recEvtOut.root")

#Geometry service
geom=sp.SvcMgr.get("RecGeomSvc", True)
svcMgr.add(geom.name())
geom.setProp("GeomFile", "sim_old.root");
#To use default geometry in CdGeom/share/
#geom.setProp("GeomFile", "default");

#alg
topalg = sp.AlgMgr.get("TopAlg", True)
algMgr.add(topalg.name())

x = sp.AlgMgr.get("TupleToSimHeader/x",True)
x.setProp("InputRootFile", "sim_old.root")
x.setProp("InputTreeName", "evt")
algMgr.add(x.name())

pullSimAlg = sp.AlgMgr.get("PullSimHeaderAlg", True)
algMgr.add(pullSimAlg.name())

recalg = sp.AlgMgr.get("RecTimeLikeAlg", True)
algMgr.add(recalg.name())
recalg.setProp("TotalPMT",16720)
recalg.setProp("PMT_R",18.750)
recalg.setProp("Ball_R",18.496)
recalg.setProp("Energy_Scale",3414.5454)
recalg.setProp("File_Path", 
                os.path.join(os.environ["RECTIMELIKEALGROOT"],"share",""))


# begin to run
if mgr.initialize():
    mgr.run()
mgr.finalize()
