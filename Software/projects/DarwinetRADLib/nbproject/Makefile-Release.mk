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
	${OBJECTDIR}/src/BusinessLogUnit.o \
	${OBJECTDIR}/src/DataRepresentationFrameWork.o \
	${OBJECTDIR}/src/DateAndTimeFramework.o \
	${OBJECTDIR}/src/FilePathFramework.o \
	${OBJECTDIR}/src/IDEInterfacedSource.o \
	${OBJECTDIR}/src/PathsFramework.o \
	${OBJECTDIR}/src/ThreadHiveFrameWork.o


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

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libdarwinetradlib.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
