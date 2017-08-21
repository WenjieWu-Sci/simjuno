#-- start of make_header -----------------

#====================================
#  Library PhysiSim
#
#   Generated Mon Apr 17 12:57:18 2017  by wenjie
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_PhysiSim_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_PhysiSim_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_PhysiSim

PhysiSim_tag = $(tag)

#cmt_local_tagfile_PhysiSim = $(PhysiSim_tag)_PhysiSim.make
cmt_local_tagfile_PhysiSim = $(bin)$(PhysiSim_tag)_PhysiSim.make

else

tags      = $(tag),$(CMTEXTRATAGS)

PhysiSim_tag = $(tag)

#cmt_local_tagfile_PhysiSim = $(PhysiSim_tag).make
cmt_local_tagfile_PhysiSim = $(bin)$(PhysiSim_tag).make

endif

include $(cmt_local_tagfile_PhysiSim)
#-include $(cmt_local_tagfile_PhysiSim)

ifdef cmt_PhysiSim_has_target_tag

cmt_final_setup_PhysiSim = $(bin)setup_PhysiSim.make
cmt_dependencies_in_PhysiSim = $(bin)dependencies_PhysiSim.in
#cmt_final_setup_PhysiSim = $(bin)PhysiSim_PhysiSimsetup.make
cmt_local_PhysiSim_makefile = $(bin)PhysiSim.make

else

cmt_final_setup_PhysiSim = $(bin)setup.make
cmt_dependencies_in_PhysiSim = $(bin)dependencies.in
#cmt_final_setup_PhysiSim = $(bin)PhysiSimsetup.make
cmt_local_PhysiSim_makefile = $(bin)PhysiSim.make

endif

#cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)PhysiSimsetup.make

#PhysiSim :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'PhysiSim'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = PhysiSim/
#PhysiSim::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

${CMTROOT}/src/Makefile.core : ;
ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------
#-- start of libary_header ---------------

PhysiSimlibname   = $(bin)$(library_prefix)PhysiSim$(library_suffix)
PhysiSimlib       = $(PhysiSimlibname).a
PhysiSimstamp     = $(bin)PhysiSim.stamp
PhysiSimshstamp   = $(bin)PhysiSim.shstamp

PhysiSim :: dirs  PhysiSimLIB
	$(echo) "PhysiSim ok"

cmt_PhysiSim_has_prototypes = 1

#--------------------------------------

ifdef cmt_PhysiSim_has_prototypes

PhysiSimprototype :  ;

endif

PhysiSimcompile : $(bin)DsG4Scintillation.o $(bin)DsG4NNDCCaptureGammas.o $(bin)DsG4Cerenkov.o $(bin)DsPhysConsElectroNu.o $(bin)DsG4RadioactiveDecaymessenger.o $(bin)DsG4NeutronHPCapture.o $(bin)DsG4OpAbsReemit.o $(bin)DsG4OpRayleigh.o $(bin)DsG4ScintSimple.o $(bin)DsPhysConsIon.o $(bin)DsPhysConsGeneral.o $(bin)DsG4MuNuclearInteraction.o $(bin)DsG4NNDCNeutronHPCaptureFS.o $(bin)DsG4GdCaptureGammas.o $(bin)DsG4OpBoundaryProcess.o $(bin)DsG4NeutronHPThermalScattering.o $(bin)Li9He8Decay.o $(bin)DsG4NeutronHPThermalScatteringNames.o $(bin)DsG4NeutronHPThermalScatteringData.o $(bin)DsPhysConsOptical.o $(bin)DsG4GdNeutronHPCaptureFS.o $(bin)DsG4RadioactiveDecay.o $(bin)DsPhysConsHadron.o $(bin)DsPhysConsEM.o ;

#-- end of libary_header ----------------
#-- start of libary ----------------------

PhysiSimLIB :: $(PhysiSimlib) $(PhysiSimshstamp)
	$(echo) "PhysiSim : library ok"

$(PhysiSimlib) :: $(bin)DsG4Scintillation.o $(bin)DsG4NNDCCaptureGammas.o $(bin)DsG4Cerenkov.o $(bin)DsPhysConsElectroNu.o $(bin)DsG4RadioactiveDecaymessenger.o $(bin)DsG4NeutronHPCapture.o $(bin)DsG4OpAbsReemit.o $(bin)DsG4OpRayleigh.o $(bin)DsG4ScintSimple.o $(bin)DsPhysConsIon.o $(bin)DsPhysConsGeneral.o $(bin)DsG4MuNuclearInteraction.o $(bin)DsG4NNDCNeutronHPCaptureFS.o $(bin)DsG4GdCaptureGammas.o $(bin)DsG4OpBoundaryProcess.o $(bin)DsG4NeutronHPThermalScattering.o $(bin)Li9He8Decay.o $(bin)DsG4NeutronHPThermalScatteringNames.o $(bin)DsG4NeutronHPThermalScatteringData.o $(bin)DsPhysConsOptical.o $(bin)DsG4GdNeutronHPCaptureFS.o $(bin)DsG4RadioactiveDecay.o $(bin)DsPhysConsHadron.o $(bin)DsPhysConsEM.o
	$(lib_echo) "static library $@"
	$(lib_silent) [ ! -f $@ ] || \rm -f $@
	$(lib_silent) $(ar) $(PhysiSimlib) $(bin)DsG4Scintillation.o $(bin)DsG4NNDCCaptureGammas.o $(bin)DsG4Cerenkov.o $(bin)DsPhysConsElectroNu.o $(bin)DsG4RadioactiveDecaymessenger.o $(bin)DsG4NeutronHPCapture.o $(bin)DsG4OpAbsReemit.o $(bin)DsG4OpRayleigh.o $(bin)DsG4ScintSimple.o $(bin)DsPhysConsIon.o $(bin)DsPhysConsGeneral.o $(bin)DsG4MuNuclearInteraction.o $(bin)DsG4NNDCNeutronHPCaptureFS.o $(bin)DsG4GdCaptureGammas.o $(bin)DsG4OpBoundaryProcess.o $(bin)DsG4NeutronHPThermalScattering.o $(bin)Li9He8Decay.o $(bin)DsG4NeutronHPThermalScatteringNames.o $(bin)DsG4NeutronHPThermalScatteringData.o $(bin)DsPhysConsOptical.o $(bin)DsG4GdNeutronHPCaptureFS.o $(bin)DsG4RadioactiveDecay.o $(bin)DsPhysConsHadron.o $(bin)DsPhysConsEM.o
	$(lib_silent) $(ranlib) $(PhysiSimlib)
	$(lib_silent) cat /dev/null >$(PhysiSimstamp)

#------------------------------------------------------------------
#  Future improvement? to empty the object files after
#  storing in the library
#
##	  for f in $?; do \
##	    rm $${f}; touch $${f}; \
##	  done
#------------------------------------------------------------------

#
# We add one level of dependency upon the true shared library 
# (rather than simply upon the stamp file)
# this is for cases where the shared library has not been built
# while the stamp was created (error??) 
#

$(PhysiSimlibname).$(shlibsuffix) :: $(PhysiSimlib) requirements $(use_requirements) $(PhysiSimstamps)
	$(lib_echo) "shared library $@"
	$(lib_silent) if test "$(makecmd)"; then QUIET=; else QUIET=1; fi; QUIET=$${QUIET} bin="$(bin)" ld="$(shlibbuilder)" ldflags="$(shlibflags)" suffix=$(shlibsuffix) libprefix=$(library_prefix) libsuffix=$(library_suffix) $(make_shlib) "$(tags)" PhysiSim $(PhysiSim_shlibflags)
	$(lib_silent) cat /dev/null >$(PhysiSimshstamp)

$(PhysiSimshstamp) :: $(PhysiSimlibname).$(shlibsuffix)
	$(lib_silent) if test -f $(PhysiSimlibname).$(shlibsuffix) ; then cat /dev/null >$(PhysiSimshstamp) ; fi

PhysiSimclean ::
	$(cleanup_echo) objects PhysiSim
	$(cleanup_silent) /bin/rm -f $(bin)DsG4Scintillation.o $(bin)DsG4NNDCCaptureGammas.o $(bin)DsG4Cerenkov.o $(bin)DsPhysConsElectroNu.o $(bin)DsG4RadioactiveDecaymessenger.o $(bin)DsG4NeutronHPCapture.o $(bin)DsG4OpAbsReemit.o $(bin)DsG4OpRayleigh.o $(bin)DsG4ScintSimple.o $(bin)DsPhysConsIon.o $(bin)DsPhysConsGeneral.o $(bin)DsG4MuNuclearInteraction.o $(bin)DsG4NNDCNeutronHPCaptureFS.o $(bin)DsG4GdCaptureGammas.o $(bin)DsG4OpBoundaryProcess.o $(bin)DsG4NeutronHPThermalScattering.o $(bin)Li9He8Decay.o $(bin)DsG4NeutronHPThermalScatteringNames.o $(bin)DsG4NeutronHPThermalScatteringData.o $(bin)DsPhysConsOptical.o $(bin)DsG4GdNeutronHPCaptureFS.o $(bin)DsG4RadioactiveDecay.o $(bin)DsPhysConsHadron.o $(bin)DsPhysConsEM.o
	$(cleanup_silent) /bin/rm -f $(patsubst %.o,%.d,$(bin)DsG4Scintillation.o $(bin)DsG4NNDCCaptureGammas.o $(bin)DsG4Cerenkov.o $(bin)DsPhysConsElectroNu.o $(bin)DsG4RadioactiveDecaymessenger.o $(bin)DsG4NeutronHPCapture.o $(bin)DsG4OpAbsReemit.o $(bin)DsG4OpRayleigh.o $(bin)DsG4ScintSimple.o $(bin)DsPhysConsIon.o $(bin)DsPhysConsGeneral.o $(bin)DsG4MuNuclearInteraction.o $(bin)DsG4NNDCNeutronHPCaptureFS.o $(bin)DsG4GdCaptureGammas.o $(bin)DsG4OpBoundaryProcess.o $(bin)DsG4NeutronHPThermalScattering.o $(bin)Li9He8Decay.o $(bin)DsG4NeutronHPThermalScatteringNames.o $(bin)DsG4NeutronHPThermalScatteringData.o $(bin)DsPhysConsOptical.o $(bin)DsG4GdNeutronHPCaptureFS.o $(bin)DsG4RadioactiveDecay.o $(bin)DsPhysConsHadron.o $(bin)DsPhysConsEM.o) $(patsubst %.o,%.dep,$(bin)DsG4Scintillation.o $(bin)DsG4NNDCCaptureGammas.o $(bin)DsG4Cerenkov.o $(bin)DsPhysConsElectroNu.o $(bin)DsG4RadioactiveDecaymessenger.o $(bin)DsG4NeutronHPCapture.o $(bin)DsG4OpAbsReemit.o $(bin)DsG4OpRayleigh.o $(bin)DsG4ScintSimple.o $(bin)DsPhysConsIon.o $(bin)DsPhysConsGeneral.o $(bin)DsG4MuNuclearInteraction.o $(bin)DsG4NNDCNeutronHPCaptureFS.o $(bin)DsG4GdCaptureGammas.o $(bin)DsG4OpBoundaryProcess.o $(bin)DsG4NeutronHPThermalScattering.o $(bin)Li9He8Decay.o $(bin)DsG4NeutronHPThermalScatteringNames.o $(bin)DsG4NeutronHPThermalScatteringData.o $(bin)DsPhysConsOptical.o $(bin)DsG4GdNeutronHPCaptureFS.o $(bin)DsG4RadioactiveDecay.o $(bin)DsPhysConsHadron.o $(bin)DsPhysConsEM.o) $(patsubst %.o,%.d.stamp,$(bin)DsG4Scintillation.o $(bin)DsG4NNDCCaptureGammas.o $(bin)DsG4Cerenkov.o $(bin)DsPhysConsElectroNu.o $(bin)DsG4RadioactiveDecaymessenger.o $(bin)DsG4NeutronHPCapture.o $(bin)DsG4OpAbsReemit.o $(bin)DsG4OpRayleigh.o $(bin)DsG4ScintSimple.o $(bin)DsPhysConsIon.o $(bin)DsPhysConsGeneral.o $(bin)DsG4MuNuclearInteraction.o $(bin)DsG4NNDCNeutronHPCaptureFS.o $(bin)DsG4GdCaptureGammas.o $(bin)DsG4OpBoundaryProcess.o $(bin)DsG4NeutronHPThermalScattering.o $(bin)Li9He8Decay.o $(bin)DsG4NeutronHPThermalScatteringNames.o $(bin)DsG4NeutronHPThermalScatteringData.o $(bin)DsPhysConsOptical.o $(bin)DsG4GdNeutronHPCaptureFS.o $(bin)DsG4RadioactiveDecay.o $(bin)DsPhysConsHadron.o $(bin)DsPhysConsEM.o)
	$(cleanup_silent) cd $(bin); /bin/rm -rf PhysiSim_deps PhysiSim_dependencies.make

#-----------------------------------------------------------------
#
#  New section for automatic installation
#
#-----------------------------------------------------------------

install_dir = ${CMTINSTALLAREA}/$(tag)/lib
PhysiSiminstallname = $(library_prefix)PhysiSim$(library_suffix).$(shlibsuffix)

PhysiSim :: PhysiSiminstall ;

install :: PhysiSiminstall ;

PhysiSiminstall :: $(install_dir)/$(PhysiSiminstallname)
ifdef CMTINSTALLAREA
	$(echo) "installation done"
endif

$(install_dir)/$(PhysiSiminstallname) :: $(bin)$(PhysiSiminstallname)
ifdef CMTINSTALLAREA
	$(install_silent) $(cmt_install_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(PhysiSiminstallname)" \
	    -out "$(install_dir)" \
	    -cmd "$(cmt_installarea_command)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

##PhysiSimclean :: PhysiSimuninstall

uninstall :: PhysiSimuninstall ;

PhysiSimuninstall ::
ifdef CMTINSTALLAREA
	$(cleanup_silent) $(cmt_uninstall_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(PhysiSiminstallname)" \
	    -out "$(install_dir)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

#-- end of libary -----------------------
#-- start of dependencies ------------------
ifneq ($(MAKECMDGOALS),PhysiSimclean)
ifneq ($(MAKECMDGOALS),uninstall)
ifneq ($(MAKECMDGOALS),PhysiSimprototype)

$(bin)PhysiSim_dependencies.make : $(use_requirements) $(cmt_final_setup_PhysiSim)
	$(echo) "(PhysiSim.make) Rebuilding $@"; \
	  $(build_dependencies) -out=$@ -start_all $(src)DsG4Scintillation.cc $(src)DsG4NNDCCaptureGammas.cc $(src)DsG4Cerenkov.cc $(src)DsPhysConsElectroNu.cc $(src)DsG4RadioactiveDecaymessenger.cc $(src)DsG4NeutronHPCapture.cc $(src)DsG4OpAbsReemit.cc $(src)DsG4OpRayleigh.cc $(src)DsG4ScintSimple.cc $(src)DsPhysConsIon.cc $(src)DsPhysConsGeneral.cc $(src)DsG4MuNuclearInteraction.cc $(src)DsG4NNDCNeutronHPCaptureFS.cc $(src)DsG4GdCaptureGammas.cc $(src)DsG4OpBoundaryProcess.cc $(src)DsG4NeutronHPThermalScattering.cc $(src)Li9He8Decay.cc $(src)DsG4NeutronHPThermalScatteringNames.cc $(src)DsG4NeutronHPThermalScatteringData.cc $(src)DsPhysConsOptical.cc $(src)DsG4GdNeutronHPCaptureFS.cc $(src)DsG4RadioactiveDecay.cc $(src)DsPhysConsHadron.cc $(src)DsPhysConsEM.cc -end_all $(includes) $(app_PhysiSim_cppflags) $(lib_PhysiSim_cppflags) -name=PhysiSim $? -f=$(cmt_dependencies_in_PhysiSim) -without_cmt

-include $(bin)PhysiSim_dependencies.make

endif
endif
endif

PhysiSimclean ::
	$(cleanup_silent) \rm -rf $(bin)PhysiSim_deps $(bin)PhysiSim_dependencies.make
#-- end of dependencies -------------------
#-- start of cpp_library -----------------

ifneq (,)

ifneq ($(MAKECMDGOALS),PhysiSimclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)DsG4Scintillation.d

$(bin)$(binobj)DsG4Scintillation.d :

$(bin)$(binobj)DsG4Scintillation.o : $(cmt_final_setup_PhysiSim)

$(bin)$(binobj)DsG4Scintillation.o : $(src)DsG4Scintillation.cc
	$(cpp_echo) $(src)DsG4Scintillation.cc
	$(cpp_silent) $(cppcomp)  -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsG4Scintillation_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsG4Scintillation_cppflags) $(DsG4Scintillation_cc_cppflags)  $(src)DsG4Scintillation.cc
endif
endif

else
$(bin)PhysiSim_dependencies.make : $(DsG4Scintillation_cc_dependencies)

$(bin)PhysiSim_dependencies.make : $(src)DsG4Scintillation.cc

$(bin)$(binobj)DsG4Scintillation.o : $(DsG4Scintillation_cc_dependencies)
	$(cpp_echo) $(src)DsG4Scintillation.cc
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsG4Scintillation_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsG4Scintillation_cppflags) $(DsG4Scintillation_cc_cppflags)  $(src)DsG4Scintillation.cc

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (,)

ifneq ($(MAKECMDGOALS),PhysiSimclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)DsG4NNDCCaptureGammas.d

$(bin)$(binobj)DsG4NNDCCaptureGammas.d :

$(bin)$(binobj)DsG4NNDCCaptureGammas.o : $(cmt_final_setup_PhysiSim)

$(bin)$(binobj)DsG4NNDCCaptureGammas.o : $(src)DsG4NNDCCaptureGammas.cc
	$(cpp_echo) $(src)DsG4NNDCCaptureGammas.cc
	$(cpp_silent) $(cppcomp)  -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsG4NNDCCaptureGammas_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsG4NNDCCaptureGammas_cppflags) $(DsG4NNDCCaptureGammas_cc_cppflags)  $(src)DsG4NNDCCaptureGammas.cc
endif
endif

else
$(bin)PhysiSim_dependencies.make : $(DsG4NNDCCaptureGammas_cc_dependencies)

$(bin)PhysiSim_dependencies.make : $(src)DsG4NNDCCaptureGammas.cc

$(bin)$(binobj)DsG4NNDCCaptureGammas.o : $(DsG4NNDCCaptureGammas_cc_dependencies)
	$(cpp_echo) $(src)DsG4NNDCCaptureGammas.cc
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsG4NNDCCaptureGammas_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsG4NNDCCaptureGammas_cppflags) $(DsG4NNDCCaptureGammas_cc_cppflags)  $(src)DsG4NNDCCaptureGammas.cc

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (,)

ifneq ($(MAKECMDGOALS),PhysiSimclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)DsG4Cerenkov.d

$(bin)$(binobj)DsG4Cerenkov.d :

$(bin)$(binobj)DsG4Cerenkov.o : $(cmt_final_setup_PhysiSim)

$(bin)$(binobj)DsG4Cerenkov.o : $(src)DsG4Cerenkov.cc
	$(cpp_echo) $(src)DsG4Cerenkov.cc
	$(cpp_silent) $(cppcomp)  -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsG4Cerenkov_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsG4Cerenkov_cppflags) $(DsG4Cerenkov_cc_cppflags)  $(src)DsG4Cerenkov.cc
endif
endif

else
$(bin)PhysiSim_dependencies.make : $(DsG4Cerenkov_cc_dependencies)

$(bin)PhysiSim_dependencies.make : $(src)DsG4Cerenkov.cc

$(bin)$(binobj)DsG4Cerenkov.o : $(DsG4Cerenkov_cc_dependencies)
	$(cpp_echo) $(src)DsG4Cerenkov.cc
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsG4Cerenkov_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsG4Cerenkov_cppflags) $(DsG4Cerenkov_cc_cppflags)  $(src)DsG4Cerenkov.cc

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (,)

ifneq ($(MAKECMDGOALS),PhysiSimclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)DsPhysConsElectroNu.d

$(bin)$(binobj)DsPhysConsElectroNu.d :

$(bin)$(binobj)DsPhysConsElectroNu.o : $(cmt_final_setup_PhysiSim)

$(bin)$(binobj)DsPhysConsElectroNu.o : $(src)DsPhysConsElectroNu.cc
	$(cpp_echo) $(src)DsPhysConsElectroNu.cc
	$(cpp_silent) $(cppcomp)  -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsPhysConsElectroNu_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsPhysConsElectroNu_cppflags) $(DsPhysConsElectroNu_cc_cppflags)  $(src)DsPhysConsElectroNu.cc
endif
endif

else
$(bin)PhysiSim_dependencies.make : $(DsPhysConsElectroNu_cc_dependencies)

$(bin)PhysiSim_dependencies.make : $(src)DsPhysConsElectroNu.cc

$(bin)$(binobj)DsPhysConsElectroNu.o : $(DsPhysConsElectroNu_cc_dependencies)
	$(cpp_echo) $(src)DsPhysConsElectroNu.cc
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsPhysConsElectroNu_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsPhysConsElectroNu_cppflags) $(DsPhysConsElectroNu_cc_cppflags)  $(src)DsPhysConsElectroNu.cc

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (,)

ifneq ($(MAKECMDGOALS),PhysiSimclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)DsG4RadioactiveDecaymessenger.d

$(bin)$(binobj)DsG4RadioactiveDecaymessenger.d :

$(bin)$(binobj)DsG4RadioactiveDecaymessenger.o : $(cmt_final_setup_PhysiSim)

$(bin)$(binobj)DsG4RadioactiveDecaymessenger.o : $(src)DsG4RadioactiveDecaymessenger.cc
	$(cpp_echo) $(src)DsG4RadioactiveDecaymessenger.cc
	$(cpp_silent) $(cppcomp)  -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsG4RadioactiveDecaymessenger_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsG4RadioactiveDecaymessenger_cppflags) $(DsG4RadioactiveDecaymessenger_cc_cppflags)  $(src)DsG4RadioactiveDecaymessenger.cc
endif
endif

else
$(bin)PhysiSim_dependencies.make : $(DsG4RadioactiveDecaymessenger_cc_dependencies)

$(bin)PhysiSim_dependencies.make : $(src)DsG4RadioactiveDecaymessenger.cc

$(bin)$(binobj)DsG4RadioactiveDecaymessenger.o : $(DsG4RadioactiveDecaymessenger_cc_dependencies)
	$(cpp_echo) $(src)DsG4RadioactiveDecaymessenger.cc
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsG4RadioactiveDecaymessenger_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsG4RadioactiveDecaymessenger_cppflags) $(DsG4RadioactiveDecaymessenger_cc_cppflags)  $(src)DsG4RadioactiveDecaymessenger.cc

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (,)

ifneq ($(MAKECMDGOALS),PhysiSimclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)DsG4NeutronHPCapture.d

$(bin)$(binobj)DsG4NeutronHPCapture.d :

$(bin)$(binobj)DsG4NeutronHPCapture.o : $(cmt_final_setup_PhysiSim)

$(bin)$(binobj)DsG4NeutronHPCapture.o : $(src)DsG4NeutronHPCapture.cc
	$(cpp_echo) $(src)DsG4NeutronHPCapture.cc
	$(cpp_silent) $(cppcomp)  -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsG4NeutronHPCapture_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsG4NeutronHPCapture_cppflags) $(DsG4NeutronHPCapture_cc_cppflags)  $(src)DsG4NeutronHPCapture.cc
endif
endif

else
$(bin)PhysiSim_dependencies.make : $(DsG4NeutronHPCapture_cc_dependencies)

$(bin)PhysiSim_dependencies.make : $(src)DsG4NeutronHPCapture.cc

$(bin)$(binobj)DsG4NeutronHPCapture.o : $(DsG4NeutronHPCapture_cc_dependencies)
	$(cpp_echo) $(src)DsG4NeutronHPCapture.cc
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsG4NeutronHPCapture_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsG4NeutronHPCapture_cppflags) $(DsG4NeutronHPCapture_cc_cppflags)  $(src)DsG4NeutronHPCapture.cc

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (,)

ifneq ($(MAKECMDGOALS),PhysiSimclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)DsG4OpAbsReemit.d

$(bin)$(binobj)DsG4OpAbsReemit.d :

$(bin)$(binobj)DsG4OpAbsReemit.o : $(cmt_final_setup_PhysiSim)

$(bin)$(binobj)DsG4OpAbsReemit.o : $(src)DsG4OpAbsReemit.cc
	$(cpp_echo) $(src)DsG4OpAbsReemit.cc
	$(cpp_silent) $(cppcomp)  -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsG4OpAbsReemit_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsG4OpAbsReemit_cppflags) $(DsG4OpAbsReemit_cc_cppflags)  $(src)DsG4OpAbsReemit.cc
endif
endif

else
$(bin)PhysiSim_dependencies.make : $(DsG4OpAbsReemit_cc_dependencies)

$(bin)PhysiSim_dependencies.make : $(src)DsG4OpAbsReemit.cc

$(bin)$(binobj)DsG4OpAbsReemit.o : $(DsG4OpAbsReemit_cc_dependencies)
	$(cpp_echo) $(src)DsG4OpAbsReemit.cc
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsG4OpAbsReemit_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsG4OpAbsReemit_cppflags) $(DsG4OpAbsReemit_cc_cppflags)  $(src)DsG4OpAbsReemit.cc

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (,)

ifneq ($(MAKECMDGOALS),PhysiSimclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)DsG4OpRayleigh.d

$(bin)$(binobj)DsG4OpRayleigh.d :

$(bin)$(binobj)DsG4OpRayleigh.o : $(cmt_final_setup_PhysiSim)

$(bin)$(binobj)DsG4OpRayleigh.o : $(src)DsG4OpRayleigh.cc
	$(cpp_echo) $(src)DsG4OpRayleigh.cc
	$(cpp_silent) $(cppcomp)  -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsG4OpRayleigh_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsG4OpRayleigh_cppflags) $(DsG4OpRayleigh_cc_cppflags)  $(src)DsG4OpRayleigh.cc
endif
endif

else
$(bin)PhysiSim_dependencies.make : $(DsG4OpRayleigh_cc_dependencies)

$(bin)PhysiSim_dependencies.make : $(src)DsG4OpRayleigh.cc

$(bin)$(binobj)DsG4OpRayleigh.o : $(DsG4OpRayleigh_cc_dependencies)
	$(cpp_echo) $(src)DsG4OpRayleigh.cc
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsG4OpRayleigh_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsG4OpRayleigh_cppflags) $(DsG4OpRayleigh_cc_cppflags)  $(src)DsG4OpRayleigh.cc

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (,)

ifneq ($(MAKECMDGOALS),PhysiSimclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)DsG4ScintSimple.d

$(bin)$(binobj)DsG4ScintSimple.d :

$(bin)$(binobj)DsG4ScintSimple.o : $(cmt_final_setup_PhysiSim)

$(bin)$(binobj)DsG4ScintSimple.o : $(src)DsG4ScintSimple.cc
	$(cpp_echo) $(src)DsG4ScintSimple.cc
	$(cpp_silent) $(cppcomp)  -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsG4ScintSimple_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsG4ScintSimple_cppflags) $(DsG4ScintSimple_cc_cppflags)  $(src)DsG4ScintSimple.cc
endif
endif

else
$(bin)PhysiSim_dependencies.make : $(DsG4ScintSimple_cc_dependencies)

$(bin)PhysiSim_dependencies.make : $(src)DsG4ScintSimple.cc

$(bin)$(binobj)DsG4ScintSimple.o : $(DsG4ScintSimple_cc_dependencies)
	$(cpp_echo) $(src)DsG4ScintSimple.cc
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsG4ScintSimple_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsG4ScintSimple_cppflags) $(DsG4ScintSimple_cc_cppflags)  $(src)DsG4ScintSimple.cc

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (,)

ifneq ($(MAKECMDGOALS),PhysiSimclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)DsPhysConsIon.d

$(bin)$(binobj)DsPhysConsIon.d :

$(bin)$(binobj)DsPhysConsIon.o : $(cmt_final_setup_PhysiSim)

$(bin)$(binobj)DsPhysConsIon.o : $(src)DsPhysConsIon.cc
	$(cpp_echo) $(src)DsPhysConsIon.cc
	$(cpp_silent) $(cppcomp)  -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsPhysConsIon_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsPhysConsIon_cppflags) $(DsPhysConsIon_cc_cppflags)  $(src)DsPhysConsIon.cc
endif
endif

else
$(bin)PhysiSim_dependencies.make : $(DsPhysConsIon_cc_dependencies)

$(bin)PhysiSim_dependencies.make : $(src)DsPhysConsIon.cc

$(bin)$(binobj)DsPhysConsIon.o : $(DsPhysConsIon_cc_dependencies)
	$(cpp_echo) $(src)DsPhysConsIon.cc
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsPhysConsIon_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsPhysConsIon_cppflags) $(DsPhysConsIon_cc_cppflags)  $(src)DsPhysConsIon.cc

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (,)

ifneq ($(MAKECMDGOALS),PhysiSimclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)DsPhysConsGeneral.d

$(bin)$(binobj)DsPhysConsGeneral.d :

$(bin)$(binobj)DsPhysConsGeneral.o : $(cmt_final_setup_PhysiSim)

$(bin)$(binobj)DsPhysConsGeneral.o : $(src)DsPhysConsGeneral.cc
	$(cpp_echo) $(src)DsPhysConsGeneral.cc
	$(cpp_silent) $(cppcomp)  -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsPhysConsGeneral_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsPhysConsGeneral_cppflags) $(DsPhysConsGeneral_cc_cppflags)  $(src)DsPhysConsGeneral.cc
endif
endif

else
$(bin)PhysiSim_dependencies.make : $(DsPhysConsGeneral_cc_dependencies)

$(bin)PhysiSim_dependencies.make : $(src)DsPhysConsGeneral.cc

$(bin)$(binobj)DsPhysConsGeneral.o : $(DsPhysConsGeneral_cc_dependencies)
	$(cpp_echo) $(src)DsPhysConsGeneral.cc
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsPhysConsGeneral_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsPhysConsGeneral_cppflags) $(DsPhysConsGeneral_cc_cppflags)  $(src)DsPhysConsGeneral.cc

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (,)

ifneq ($(MAKECMDGOALS),PhysiSimclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)DsG4MuNuclearInteraction.d

$(bin)$(binobj)DsG4MuNuclearInteraction.d :

$(bin)$(binobj)DsG4MuNuclearInteraction.o : $(cmt_final_setup_PhysiSim)

$(bin)$(binobj)DsG4MuNuclearInteraction.o : $(src)DsG4MuNuclearInteraction.cc
	$(cpp_echo) $(src)DsG4MuNuclearInteraction.cc
	$(cpp_silent) $(cppcomp)  -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsG4MuNuclearInteraction_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsG4MuNuclearInteraction_cppflags) $(DsG4MuNuclearInteraction_cc_cppflags)  $(src)DsG4MuNuclearInteraction.cc
endif
endif

else
$(bin)PhysiSim_dependencies.make : $(DsG4MuNuclearInteraction_cc_dependencies)

$(bin)PhysiSim_dependencies.make : $(src)DsG4MuNuclearInteraction.cc

$(bin)$(binobj)DsG4MuNuclearInteraction.o : $(DsG4MuNuclearInteraction_cc_dependencies)
	$(cpp_echo) $(src)DsG4MuNuclearInteraction.cc
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsG4MuNuclearInteraction_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsG4MuNuclearInteraction_cppflags) $(DsG4MuNuclearInteraction_cc_cppflags)  $(src)DsG4MuNuclearInteraction.cc

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (,)

ifneq ($(MAKECMDGOALS),PhysiSimclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)DsG4NNDCNeutronHPCaptureFS.d

$(bin)$(binobj)DsG4NNDCNeutronHPCaptureFS.d :

$(bin)$(binobj)DsG4NNDCNeutronHPCaptureFS.o : $(cmt_final_setup_PhysiSim)

$(bin)$(binobj)DsG4NNDCNeutronHPCaptureFS.o : $(src)DsG4NNDCNeutronHPCaptureFS.cc
	$(cpp_echo) $(src)DsG4NNDCNeutronHPCaptureFS.cc
	$(cpp_silent) $(cppcomp)  -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsG4NNDCNeutronHPCaptureFS_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsG4NNDCNeutronHPCaptureFS_cppflags) $(DsG4NNDCNeutronHPCaptureFS_cc_cppflags)  $(src)DsG4NNDCNeutronHPCaptureFS.cc
endif
endif

else
$(bin)PhysiSim_dependencies.make : $(DsG4NNDCNeutronHPCaptureFS_cc_dependencies)

$(bin)PhysiSim_dependencies.make : $(src)DsG4NNDCNeutronHPCaptureFS.cc

$(bin)$(binobj)DsG4NNDCNeutronHPCaptureFS.o : $(DsG4NNDCNeutronHPCaptureFS_cc_dependencies)
	$(cpp_echo) $(src)DsG4NNDCNeutronHPCaptureFS.cc
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsG4NNDCNeutronHPCaptureFS_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsG4NNDCNeutronHPCaptureFS_cppflags) $(DsG4NNDCNeutronHPCaptureFS_cc_cppflags)  $(src)DsG4NNDCNeutronHPCaptureFS.cc

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (,)

ifneq ($(MAKECMDGOALS),PhysiSimclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)DsG4GdCaptureGammas.d

$(bin)$(binobj)DsG4GdCaptureGammas.d :

$(bin)$(binobj)DsG4GdCaptureGammas.o : $(cmt_final_setup_PhysiSim)

$(bin)$(binobj)DsG4GdCaptureGammas.o : $(src)DsG4GdCaptureGammas.cc
	$(cpp_echo) $(src)DsG4GdCaptureGammas.cc
	$(cpp_silent) $(cppcomp)  -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsG4GdCaptureGammas_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsG4GdCaptureGammas_cppflags) $(DsG4GdCaptureGammas_cc_cppflags)  $(src)DsG4GdCaptureGammas.cc
endif
endif

else
$(bin)PhysiSim_dependencies.make : $(DsG4GdCaptureGammas_cc_dependencies)

$(bin)PhysiSim_dependencies.make : $(src)DsG4GdCaptureGammas.cc

$(bin)$(binobj)DsG4GdCaptureGammas.o : $(DsG4GdCaptureGammas_cc_dependencies)
	$(cpp_echo) $(src)DsG4GdCaptureGammas.cc
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsG4GdCaptureGammas_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsG4GdCaptureGammas_cppflags) $(DsG4GdCaptureGammas_cc_cppflags)  $(src)DsG4GdCaptureGammas.cc

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (,)

ifneq ($(MAKECMDGOALS),PhysiSimclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)DsG4OpBoundaryProcess.d

$(bin)$(binobj)DsG4OpBoundaryProcess.d :

$(bin)$(binobj)DsG4OpBoundaryProcess.o : $(cmt_final_setup_PhysiSim)

$(bin)$(binobj)DsG4OpBoundaryProcess.o : $(src)DsG4OpBoundaryProcess.cc
	$(cpp_echo) $(src)DsG4OpBoundaryProcess.cc
	$(cpp_silent) $(cppcomp)  -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsG4OpBoundaryProcess_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsG4OpBoundaryProcess_cppflags) $(DsG4OpBoundaryProcess_cc_cppflags)  $(src)DsG4OpBoundaryProcess.cc
endif
endif

else
$(bin)PhysiSim_dependencies.make : $(DsG4OpBoundaryProcess_cc_dependencies)

$(bin)PhysiSim_dependencies.make : $(src)DsG4OpBoundaryProcess.cc

$(bin)$(binobj)DsG4OpBoundaryProcess.o : $(DsG4OpBoundaryProcess_cc_dependencies)
	$(cpp_echo) $(src)DsG4OpBoundaryProcess.cc
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsG4OpBoundaryProcess_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsG4OpBoundaryProcess_cppflags) $(DsG4OpBoundaryProcess_cc_cppflags)  $(src)DsG4OpBoundaryProcess.cc

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (,)

ifneq ($(MAKECMDGOALS),PhysiSimclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)DsG4NeutronHPThermalScattering.d

$(bin)$(binobj)DsG4NeutronHPThermalScattering.d :

$(bin)$(binobj)DsG4NeutronHPThermalScattering.o : $(cmt_final_setup_PhysiSim)

$(bin)$(binobj)DsG4NeutronHPThermalScattering.o : $(src)DsG4NeutronHPThermalScattering.cc
	$(cpp_echo) $(src)DsG4NeutronHPThermalScattering.cc
	$(cpp_silent) $(cppcomp)  -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsG4NeutronHPThermalScattering_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsG4NeutronHPThermalScattering_cppflags) $(DsG4NeutronHPThermalScattering_cc_cppflags)  $(src)DsG4NeutronHPThermalScattering.cc
endif
endif

else
$(bin)PhysiSim_dependencies.make : $(DsG4NeutronHPThermalScattering_cc_dependencies)

$(bin)PhysiSim_dependencies.make : $(src)DsG4NeutronHPThermalScattering.cc

$(bin)$(binobj)DsG4NeutronHPThermalScattering.o : $(DsG4NeutronHPThermalScattering_cc_dependencies)
	$(cpp_echo) $(src)DsG4NeutronHPThermalScattering.cc
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsG4NeutronHPThermalScattering_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsG4NeutronHPThermalScattering_cppflags) $(DsG4NeutronHPThermalScattering_cc_cppflags)  $(src)DsG4NeutronHPThermalScattering.cc

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (,)

ifneq ($(MAKECMDGOALS),PhysiSimclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)Li9He8Decay.d

$(bin)$(binobj)Li9He8Decay.d :

$(bin)$(binobj)Li9He8Decay.o : $(cmt_final_setup_PhysiSim)

$(bin)$(binobj)Li9He8Decay.o : $(src)Li9He8Decay.cc
	$(cpp_echo) $(src)Li9He8Decay.cc
	$(cpp_silent) $(cppcomp)  -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(Li9He8Decay_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(Li9He8Decay_cppflags) $(Li9He8Decay_cc_cppflags)  $(src)Li9He8Decay.cc
endif
endif

else
$(bin)PhysiSim_dependencies.make : $(Li9He8Decay_cc_dependencies)

$(bin)PhysiSim_dependencies.make : $(src)Li9He8Decay.cc

$(bin)$(binobj)Li9He8Decay.o : $(Li9He8Decay_cc_dependencies)
	$(cpp_echo) $(src)Li9He8Decay.cc
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(Li9He8Decay_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(Li9He8Decay_cppflags) $(Li9He8Decay_cc_cppflags)  $(src)Li9He8Decay.cc

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (,)

ifneq ($(MAKECMDGOALS),PhysiSimclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)DsG4NeutronHPThermalScatteringNames.d

$(bin)$(binobj)DsG4NeutronHPThermalScatteringNames.d :

$(bin)$(binobj)DsG4NeutronHPThermalScatteringNames.o : $(cmt_final_setup_PhysiSim)

$(bin)$(binobj)DsG4NeutronHPThermalScatteringNames.o : $(src)DsG4NeutronHPThermalScatteringNames.cc
	$(cpp_echo) $(src)DsG4NeutronHPThermalScatteringNames.cc
	$(cpp_silent) $(cppcomp)  -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsG4NeutronHPThermalScatteringNames_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsG4NeutronHPThermalScatteringNames_cppflags) $(DsG4NeutronHPThermalScatteringNames_cc_cppflags)  $(src)DsG4NeutronHPThermalScatteringNames.cc
endif
endif

else
$(bin)PhysiSim_dependencies.make : $(DsG4NeutronHPThermalScatteringNames_cc_dependencies)

$(bin)PhysiSim_dependencies.make : $(src)DsG4NeutronHPThermalScatteringNames.cc

$(bin)$(binobj)DsG4NeutronHPThermalScatteringNames.o : $(DsG4NeutronHPThermalScatteringNames_cc_dependencies)
	$(cpp_echo) $(src)DsG4NeutronHPThermalScatteringNames.cc
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsG4NeutronHPThermalScatteringNames_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsG4NeutronHPThermalScatteringNames_cppflags) $(DsG4NeutronHPThermalScatteringNames_cc_cppflags)  $(src)DsG4NeutronHPThermalScatteringNames.cc

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (,)

ifneq ($(MAKECMDGOALS),PhysiSimclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)DsG4NeutronHPThermalScatteringData.d

$(bin)$(binobj)DsG4NeutronHPThermalScatteringData.d :

$(bin)$(binobj)DsG4NeutronHPThermalScatteringData.o : $(cmt_final_setup_PhysiSim)

$(bin)$(binobj)DsG4NeutronHPThermalScatteringData.o : $(src)DsG4NeutronHPThermalScatteringData.cc
	$(cpp_echo) $(src)DsG4NeutronHPThermalScatteringData.cc
	$(cpp_silent) $(cppcomp)  -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsG4NeutronHPThermalScatteringData_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsG4NeutronHPThermalScatteringData_cppflags) $(DsG4NeutronHPThermalScatteringData_cc_cppflags)  $(src)DsG4NeutronHPThermalScatteringData.cc
endif
endif

else
$(bin)PhysiSim_dependencies.make : $(DsG4NeutronHPThermalScatteringData_cc_dependencies)

$(bin)PhysiSim_dependencies.make : $(src)DsG4NeutronHPThermalScatteringData.cc

$(bin)$(binobj)DsG4NeutronHPThermalScatteringData.o : $(DsG4NeutronHPThermalScatteringData_cc_dependencies)
	$(cpp_echo) $(src)DsG4NeutronHPThermalScatteringData.cc
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsG4NeutronHPThermalScatteringData_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsG4NeutronHPThermalScatteringData_cppflags) $(DsG4NeutronHPThermalScatteringData_cc_cppflags)  $(src)DsG4NeutronHPThermalScatteringData.cc

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (,)

ifneq ($(MAKECMDGOALS),PhysiSimclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)DsPhysConsOptical.d

$(bin)$(binobj)DsPhysConsOptical.d :

$(bin)$(binobj)DsPhysConsOptical.o : $(cmt_final_setup_PhysiSim)

$(bin)$(binobj)DsPhysConsOptical.o : $(src)DsPhysConsOptical.cc
	$(cpp_echo) $(src)DsPhysConsOptical.cc
	$(cpp_silent) $(cppcomp)  -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsPhysConsOptical_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsPhysConsOptical_cppflags) $(DsPhysConsOptical_cc_cppflags)  $(src)DsPhysConsOptical.cc
endif
endif

else
$(bin)PhysiSim_dependencies.make : $(DsPhysConsOptical_cc_dependencies)

$(bin)PhysiSim_dependencies.make : $(src)DsPhysConsOptical.cc

$(bin)$(binobj)DsPhysConsOptical.o : $(DsPhysConsOptical_cc_dependencies)
	$(cpp_echo) $(src)DsPhysConsOptical.cc
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsPhysConsOptical_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsPhysConsOptical_cppflags) $(DsPhysConsOptical_cc_cppflags)  $(src)DsPhysConsOptical.cc

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (,)

ifneq ($(MAKECMDGOALS),PhysiSimclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)DsG4GdNeutronHPCaptureFS.d

$(bin)$(binobj)DsG4GdNeutronHPCaptureFS.d :

$(bin)$(binobj)DsG4GdNeutronHPCaptureFS.o : $(cmt_final_setup_PhysiSim)

$(bin)$(binobj)DsG4GdNeutronHPCaptureFS.o : $(src)DsG4GdNeutronHPCaptureFS.cc
	$(cpp_echo) $(src)DsG4GdNeutronHPCaptureFS.cc
	$(cpp_silent) $(cppcomp)  -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsG4GdNeutronHPCaptureFS_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsG4GdNeutronHPCaptureFS_cppflags) $(DsG4GdNeutronHPCaptureFS_cc_cppflags)  $(src)DsG4GdNeutronHPCaptureFS.cc
endif
endif

else
$(bin)PhysiSim_dependencies.make : $(DsG4GdNeutronHPCaptureFS_cc_dependencies)

$(bin)PhysiSim_dependencies.make : $(src)DsG4GdNeutronHPCaptureFS.cc

$(bin)$(binobj)DsG4GdNeutronHPCaptureFS.o : $(DsG4GdNeutronHPCaptureFS_cc_dependencies)
	$(cpp_echo) $(src)DsG4GdNeutronHPCaptureFS.cc
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsG4GdNeutronHPCaptureFS_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsG4GdNeutronHPCaptureFS_cppflags) $(DsG4GdNeutronHPCaptureFS_cc_cppflags)  $(src)DsG4GdNeutronHPCaptureFS.cc

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (,)

ifneq ($(MAKECMDGOALS),PhysiSimclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)DsG4RadioactiveDecay.d

$(bin)$(binobj)DsG4RadioactiveDecay.d :

$(bin)$(binobj)DsG4RadioactiveDecay.o : $(cmt_final_setup_PhysiSim)

$(bin)$(binobj)DsG4RadioactiveDecay.o : $(src)DsG4RadioactiveDecay.cc
	$(cpp_echo) $(src)DsG4RadioactiveDecay.cc
	$(cpp_silent) $(cppcomp)  -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsG4RadioactiveDecay_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsG4RadioactiveDecay_cppflags) $(DsG4RadioactiveDecay_cc_cppflags)  $(src)DsG4RadioactiveDecay.cc
endif
endif

else
$(bin)PhysiSim_dependencies.make : $(DsG4RadioactiveDecay_cc_dependencies)

$(bin)PhysiSim_dependencies.make : $(src)DsG4RadioactiveDecay.cc

$(bin)$(binobj)DsG4RadioactiveDecay.o : $(DsG4RadioactiveDecay_cc_dependencies)
	$(cpp_echo) $(src)DsG4RadioactiveDecay.cc
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsG4RadioactiveDecay_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsG4RadioactiveDecay_cppflags) $(DsG4RadioactiveDecay_cc_cppflags)  $(src)DsG4RadioactiveDecay.cc

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (,)

ifneq ($(MAKECMDGOALS),PhysiSimclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)DsPhysConsHadron.d

$(bin)$(binobj)DsPhysConsHadron.d :

$(bin)$(binobj)DsPhysConsHadron.o : $(cmt_final_setup_PhysiSim)

$(bin)$(binobj)DsPhysConsHadron.o : $(src)DsPhysConsHadron.cc
	$(cpp_echo) $(src)DsPhysConsHadron.cc
	$(cpp_silent) $(cppcomp)  -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsPhysConsHadron_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsPhysConsHadron_cppflags) $(DsPhysConsHadron_cc_cppflags)  $(src)DsPhysConsHadron.cc
endif
endif

else
$(bin)PhysiSim_dependencies.make : $(DsPhysConsHadron_cc_dependencies)

$(bin)PhysiSim_dependencies.make : $(src)DsPhysConsHadron.cc

$(bin)$(binobj)DsPhysConsHadron.o : $(DsPhysConsHadron_cc_dependencies)
	$(cpp_echo) $(src)DsPhysConsHadron.cc
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsPhysConsHadron_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsPhysConsHadron_cppflags) $(DsPhysConsHadron_cc_cppflags)  $(src)DsPhysConsHadron.cc

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (,)

ifneq ($(MAKECMDGOALS),PhysiSimclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)DsPhysConsEM.d

$(bin)$(binobj)DsPhysConsEM.d :

$(bin)$(binobj)DsPhysConsEM.o : $(cmt_final_setup_PhysiSim)

$(bin)$(binobj)DsPhysConsEM.o : $(src)DsPhysConsEM.cc
	$(cpp_echo) $(src)DsPhysConsEM.cc
	$(cpp_silent) $(cppcomp)  -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsPhysConsEM_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsPhysConsEM_cppflags) $(DsPhysConsEM_cc_cppflags)  $(src)DsPhysConsEM.cc
endif
endif

else
$(bin)PhysiSim_dependencies.make : $(DsPhysConsEM_cc_dependencies)

$(bin)PhysiSim_dependencies.make : $(src)DsPhysConsEM.cc

$(bin)$(binobj)DsPhysConsEM.o : $(DsPhysConsEM_cc_dependencies)
	$(cpp_echo) $(src)DsPhysConsEM.cc
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(PhysiSim_pp_cppflags) $(lib_PhysiSim_pp_cppflags) $(DsPhysConsEM_pp_cppflags) $(use_cppflags) $(PhysiSim_cppflags) $(lib_PhysiSim_cppflags) $(DsPhysConsEM_cppflags) $(DsPhysConsEM_cc_cppflags)  $(src)DsPhysConsEM.cc

endif

#-- end of cpp_library ------------------
#-- start of cleanup_header --------------

clean :: PhysiSimclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(PhysiSim.make) $@: No rule for such target" >&2
else
.DEFAULT::
	$(error PEDANTIC: $@: No rule for such target)
endif

PhysiSimclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_library -------------
	$(cleanup_echo) library PhysiSim
	-$(cleanup_silent) cd $(bin) && \rm -f $(library_prefix)PhysiSim$(library_suffix).a $(library_prefix)PhysiSim$(library_suffix).$(shlibsuffix) PhysiSim.stamp PhysiSim.shstamp
#-- end of cleanup_library ---------------
