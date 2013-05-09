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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/ABOUT.o \
	${OBJECTDIR}/src/ApplicationEnvironment.o \
	${OBJECTDIR}/src/ApplicationProperties.o \
	${OBJECTDIR}/src/BusinessLogFormUnit.o \
	${OBJECTDIR}/src/BusinessLogUnit.o \
	${OBJECTDIR}/src/DataRepresentationFrameWork.o \
	${OBJECTDIR}/src/DateAndTimeFramework.o \
	${OBJECTDIR}/src/EditPropertiesFormUnit.o \
	${OBJECTDIR}/src/EditPropertiesFrameUnit.o \
	${OBJECTDIR}/src/FilePathFramework.o \
	${OBJECTDIR}/src/IDEInterfacedSource.o \
	${OBJECTDIR}/src/PathsFramework.o \
	${OBJECTDIR}/src/ThreadHiveFrameWork.o \
	${OBJECTDIR}/src/VersionInfo/versioninfo.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libdarwinetradlib.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libdarwinetradlib.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libdarwinetradlib.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libdarwinetradlib.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libdarwinetradlib.a

${OBJECTDIR}/src/ABOUT.o: src/ABOUT.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ABOUT.o src/ABOUT.cpp

${OBJECTDIR}/src/ApplicationEnvironment.o: src/ApplicationEnvironment.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ApplicationEnvironment.o src/ApplicationEnvironment.cpp

${OBJECTDIR}/src/ApplicationProperties.o: src/ApplicationProperties.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ApplicationProperties.o src/ApplicationProperties.cpp

${OBJECTDIR}/src/BusinessLogFormUnit.o: src/BusinessLogFormUnit.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/BusinessLogFormUnit.o src/BusinessLogFormUnit.cpp

${OBJECTDIR}/src/BusinessLogUnit.o: src/BusinessLogUnit.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/BusinessLogUnit.o src/BusinessLogUnit.cpp

${OBJECTDIR}/src/DataRepresentationFrameWork.o: src/DataRepresentationFrameWork.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/DataRepresentationFrameWork.o src/DataRepresentationFrameWork.cpp

${OBJECTDIR}/src/DateAndTimeFramework.o: src/DateAndTimeFramework.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/DateAndTimeFramework.o src/DateAndTimeFramework.cpp

${OBJECTDIR}/src/EditPropertiesFormUnit.o: src/EditPropertiesFormUnit.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/EditPropertiesFormUnit.o src/EditPropertiesFormUnit.cpp

${OBJECTDIR}/src/EditPropertiesFrameUnit.o: src/EditPropertiesFrameUnit.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/EditPropertiesFrameUnit.o src/EditPropertiesFrameUnit.cpp

${OBJECTDIR}/src/FilePathFramework.o: src/FilePathFramework.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/FilePathFramework.o src/FilePathFramework.cpp

${OBJECTDIR}/src/IDEInterfacedSource.o: src/IDEInterfacedSource.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/IDEInterfacedSource.o src/IDEInterfacedSource.cpp

${OBJECTDIR}/src/PathsFramework.o: src/PathsFramework.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/PathsFramework.o src/PathsFramework.cpp

${OBJECTDIR}/src/ThreadHiveFrameWork.o: src/ThreadHiveFrameWork.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ThreadHiveFrameWork.o src/ThreadHiveFrameWork.cpp

${OBJECTDIR}/src/VersionInfo/versioninfo.o: src/VersionInfo/versioninfo.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/VersionInfo
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/VersionInfo/versioninfo.o src/VersionInfo/versioninfo.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/newsimpletest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} 


${TESTDIR}/tests/newsimpletest.o: tests/newsimpletest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -O2 -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/newsimpletest.o tests/newsimpletest.cpp


${OBJECTDIR}/src/ABOUT_nomain.o: ${OBJECTDIR}/src/ABOUT.o src/ABOUT.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/ABOUT.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ABOUT_nomain.o src/ABOUT.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/ABOUT.o ${OBJECTDIR}/src/ABOUT_nomain.o;\
	fi

${OBJECTDIR}/src/ApplicationEnvironment_nomain.o: ${OBJECTDIR}/src/ApplicationEnvironment.o src/ApplicationEnvironment.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/ApplicationEnvironment.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ApplicationEnvironment_nomain.o src/ApplicationEnvironment.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/ApplicationEnvironment.o ${OBJECTDIR}/src/ApplicationEnvironment_nomain.o;\
	fi

${OBJECTDIR}/src/ApplicationProperties_nomain.o: ${OBJECTDIR}/src/ApplicationProperties.o src/ApplicationProperties.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/ApplicationProperties.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ApplicationProperties_nomain.o src/ApplicationProperties.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/ApplicationProperties.o ${OBJECTDIR}/src/ApplicationProperties_nomain.o;\
	fi

${OBJECTDIR}/src/BusinessLogFormUnit_nomain.o: ${OBJECTDIR}/src/BusinessLogFormUnit.o src/BusinessLogFormUnit.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/BusinessLogFormUnit.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/BusinessLogFormUnit_nomain.o src/BusinessLogFormUnit.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/BusinessLogFormUnit.o ${OBJECTDIR}/src/BusinessLogFormUnit_nomain.o;\
	fi

${OBJECTDIR}/src/BusinessLogUnit_nomain.o: ${OBJECTDIR}/src/BusinessLogUnit.o src/BusinessLogUnit.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/BusinessLogUnit.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/BusinessLogUnit_nomain.o src/BusinessLogUnit.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/BusinessLogUnit.o ${OBJECTDIR}/src/BusinessLogUnit_nomain.o;\
	fi

${OBJECTDIR}/src/DataRepresentationFrameWork_nomain.o: ${OBJECTDIR}/src/DataRepresentationFrameWork.o src/DataRepresentationFrameWork.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/DataRepresentationFrameWork.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/DataRepresentationFrameWork_nomain.o src/DataRepresentationFrameWork.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/DataRepresentationFrameWork.o ${OBJECTDIR}/src/DataRepresentationFrameWork_nomain.o;\
	fi

${OBJECTDIR}/src/DateAndTimeFramework_nomain.o: ${OBJECTDIR}/src/DateAndTimeFramework.o src/DateAndTimeFramework.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/DateAndTimeFramework.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/DateAndTimeFramework_nomain.o src/DateAndTimeFramework.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/DateAndTimeFramework.o ${OBJECTDIR}/src/DateAndTimeFramework_nomain.o;\
	fi

${OBJECTDIR}/src/EditPropertiesFormUnit_nomain.o: ${OBJECTDIR}/src/EditPropertiesFormUnit.o src/EditPropertiesFormUnit.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/EditPropertiesFormUnit.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/EditPropertiesFormUnit_nomain.o src/EditPropertiesFormUnit.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/EditPropertiesFormUnit.o ${OBJECTDIR}/src/EditPropertiesFormUnit_nomain.o;\
	fi

${OBJECTDIR}/src/EditPropertiesFrameUnit_nomain.o: ${OBJECTDIR}/src/EditPropertiesFrameUnit.o src/EditPropertiesFrameUnit.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/EditPropertiesFrameUnit.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/EditPropertiesFrameUnit_nomain.o src/EditPropertiesFrameUnit.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/EditPropertiesFrameUnit.o ${OBJECTDIR}/src/EditPropertiesFrameUnit_nomain.o;\
	fi

${OBJECTDIR}/src/FilePathFramework_nomain.o: ${OBJECTDIR}/src/FilePathFramework.o src/FilePathFramework.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/FilePathFramework.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/FilePathFramework_nomain.o src/FilePathFramework.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/FilePathFramework.o ${OBJECTDIR}/src/FilePathFramework_nomain.o;\
	fi

${OBJECTDIR}/src/IDEInterfacedSource_nomain.o: ${OBJECTDIR}/src/IDEInterfacedSource.o src/IDEInterfacedSource.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/IDEInterfacedSource.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/IDEInterfacedSource_nomain.o src/IDEInterfacedSource.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/IDEInterfacedSource.o ${OBJECTDIR}/src/IDEInterfacedSource_nomain.o;\
	fi

${OBJECTDIR}/src/PathsFramework_nomain.o: ${OBJECTDIR}/src/PathsFramework.o src/PathsFramework.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/PathsFramework.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/PathsFramework_nomain.o src/PathsFramework.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/PathsFramework.o ${OBJECTDIR}/src/PathsFramework_nomain.o;\
	fi

${OBJECTDIR}/src/ThreadHiveFrameWork_nomain.o: ${OBJECTDIR}/src/ThreadHiveFrameWork.o src/ThreadHiveFrameWork.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/ThreadHiveFrameWork.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ThreadHiveFrameWork_nomain.o src/ThreadHiveFrameWork.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/ThreadHiveFrameWork.o ${OBJECTDIR}/src/ThreadHiveFrameWork_nomain.o;\
	fi

${OBJECTDIR}/src/VersionInfo/versioninfo_nomain.o: ${OBJECTDIR}/src/VersionInfo/versioninfo.o src/VersionInfo/versioninfo.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/VersionInfo
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/VersionInfo/versioninfo.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/VersionInfo/versioninfo_nomain.o src/VersionInfo/versioninfo.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/VersionInfo/versioninfo.o ${OBJECTDIR}/src/VersionInfo/versioninfo_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libdarwinetradlib.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
