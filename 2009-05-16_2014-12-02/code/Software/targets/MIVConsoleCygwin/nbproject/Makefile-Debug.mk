#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=Cygwin_4.x-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/132981951/CommandLineProcessor.o \
	${OBJECTDIR}/_ext/132981951/DarwinetDomainProxy.o \
	${OBJECTDIR}/_ext/132981951/DarwinetEngineProxy.o \
	${OBJECTDIR}/_ext/132981951/DarwinetMIVProxy.o \
	${OBJECTDIR}/_ext/132981951/DarwinetViewProxy.o \
	${OBJECTDIR}/_ext/132981951/MIVConsoleCygwin.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=--std=c++0x
CXXFLAGS=--std=c++0x

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=C\:/subversion/darwinet/trunk/Software/projects/InProcStaticDarwinetEngine/dist/Debug/Cygwin_4.x-Windows/libinprocstaticdarwinetengine.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mivconsolecygwin.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mivconsolecygwin.exe: /cygdrive/C/subversion/darwinet/trunk/Software/projects/InProcStaticDarwinetEngine/dist/Debug/Cygwin_4.x-Windows/libinprocstaticdarwinetengine.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mivconsolecygwin.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mivconsolecygwin ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/132981951/CommandLineProcessor.o: /cygdrive/C/subversion/darwinet/trunk/Software/projects/MIVConsoleCygwin/src/CommandLineProcessor.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/132981951
	${RM} $@.d
	$(COMPILE.cc) -g -I/cygdrive/C/subversion/darwinet/trunk/Software/projects/InProcStaticDarwinetEngine/inc -I/cygdrive/C/subversion/darwinet/trunk/Software/externals/boost_1_53_0 -I/cygdrive/C/subversion/darwinet/trunk/Software/projects/DarwinetRADLib/inc --std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/132981951/CommandLineProcessor.o /cygdrive/C/subversion/darwinet/trunk/Software/projects/MIVConsoleCygwin/src/CommandLineProcessor.cpp

${OBJECTDIR}/_ext/132981951/DarwinetDomainProxy.o: /cygdrive/C/subversion/darwinet/trunk/Software/projects/MIVConsoleCygwin/src/DarwinetDomainProxy.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/132981951
	${RM} $@.d
	$(COMPILE.cc) -g -I/cygdrive/C/subversion/darwinet/trunk/Software/projects/InProcStaticDarwinetEngine/inc -I/cygdrive/C/subversion/darwinet/trunk/Software/externals/boost_1_53_0 -I/cygdrive/C/subversion/darwinet/trunk/Software/projects/DarwinetRADLib/inc --std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/132981951/DarwinetDomainProxy.o /cygdrive/C/subversion/darwinet/trunk/Software/projects/MIVConsoleCygwin/src/DarwinetDomainProxy.cpp

${OBJECTDIR}/_ext/132981951/DarwinetEngineProxy.o: /cygdrive/C/subversion/darwinet/trunk/Software/projects/MIVConsoleCygwin/src/DarwinetEngineProxy.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/132981951
	${RM} $@.d
	$(COMPILE.cc) -g -I/cygdrive/C/subversion/darwinet/trunk/Software/projects/InProcStaticDarwinetEngine/inc -I/cygdrive/C/subversion/darwinet/trunk/Software/externals/boost_1_53_0 -I/cygdrive/C/subversion/darwinet/trunk/Software/projects/DarwinetRADLib/inc --std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/132981951/DarwinetEngineProxy.o /cygdrive/C/subversion/darwinet/trunk/Software/projects/MIVConsoleCygwin/src/DarwinetEngineProxy.cpp

${OBJECTDIR}/_ext/132981951/DarwinetMIVProxy.o: /cygdrive/C/subversion/darwinet/trunk/Software/projects/MIVConsoleCygwin/src/DarwinetMIVProxy.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/132981951
	${RM} $@.d
	$(COMPILE.cc) -g -I/cygdrive/C/subversion/darwinet/trunk/Software/projects/InProcStaticDarwinetEngine/inc -I/cygdrive/C/subversion/darwinet/trunk/Software/externals/boost_1_53_0 -I/cygdrive/C/subversion/darwinet/trunk/Software/projects/DarwinetRADLib/inc --std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/132981951/DarwinetMIVProxy.o /cygdrive/C/subversion/darwinet/trunk/Software/projects/MIVConsoleCygwin/src/DarwinetMIVProxy.cpp

${OBJECTDIR}/_ext/132981951/DarwinetViewProxy.o: /cygdrive/C/subversion/darwinet/trunk/Software/projects/MIVConsoleCygwin/src/DarwinetViewProxy.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/132981951
	${RM} $@.d
	$(COMPILE.cc) -g -I/cygdrive/C/subversion/darwinet/trunk/Software/projects/InProcStaticDarwinetEngine/inc -I/cygdrive/C/subversion/darwinet/trunk/Software/externals/boost_1_53_0 -I/cygdrive/C/subversion/darwinet/trunk/Software/projects/DarwinetRADLib/inc --std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/132981951/DarwinetViewProxy.o /cygdrive/C/subversion/darwinet/trunk/Software/projects/MIVConsoleCygwin/src/DarwinetViewProxy.cpp

${OBJECTDIR}/_ext/132981951/MIVConsoleCygwin.o: /cygdrive/C/subversion/darwinet/trunk/Software/projects/MIVConsoleCygwin/src/MIVConsoleCygwin.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/132981951
	${RM} $@.d
	$(COMPILE.cc) -g -I/cygdrive/C/subversion/darwinet/trunk/Software/projects/InProcStaticDarwinetEngine/inc -I/cygdrive/C/subversion/darwinet/trunk/Software/externals/boost_1_53_0 -I/cygdrive/C/subversion/darwinet/trunk/Software/projects/DarwinetRADLib/inc --std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/132981951/MIVConsoleCygwin.o /cygdrive/C/subversion/darwinet/trunk/Software/projects/MIVConsoleCygwin/src/MIVConsoleCygwin.cpp

# Subprojects
.build-subprojects:
	cd C\:/subversion/darwinet/trunk/Software/projects/InProcStaticDarwinetEngine && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mivconsolecygwin.exe

# Subprojects
.clean-subprojects:
	cd C\:/subversion/darwinet/trunk/Software/projects/InProcStaticDarwinetEngine && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
