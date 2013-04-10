# Makefile for MIVConsole application.

SYSTEM     := $(shell uname -o)
BUILD_TYPE := Debug

# I really really don't like the way output build is done for the other
# libraries. It means we need per-platform custom makefile code like this.
# A common system makefile for such definitions would be useful but still
# doesn't solve the underlying issue.
ifeq ($(SYSTEM),Cygwin)
    LIB_DIST_DIR=dist/$(BUILD_TYPE)/Cygwin_4.x-Windows
else
    LIB_DIST_DIR=ERROR
endif

CPPC      := g++ -std=c++11
AR        := ar -crus
RM        := rm -rf
CPP_FLAGS := -Wall -g -Iinc -I../DarwinetRADLib/inc -I../InProcStaticDarwinetEngine/inc
LN_FLAGS  := -L../DarwinetRADLib/$(LIB_DIST_DIR) -ldarwinetradlib -L../InProcStaticDarwinetEngine/$(LIB_DIST_DIR) -linprocstaticdarwinetengine
OBJ_DIR   := build
DEPS_DIR  := deps
CPP_FILES := $(shell ls src/*.cpp 2> /dev/null)
OBJ_FILES := $(patsubst src/%.cpp,$(OBJ_DIR)/%.opp,$(CPP_FILES))
DEP_FILES := $(patsubst src/%.cpp,$(DEPS_DIR)/%.dpp,$(CPP_FILES))
TARGET    := MIVConsole

ifeq ($(SYSTEM),Cygwin)
    TARGET    := $(patsubst %,%.exe,$(TARGET))
    CPP_FLAGS += -DCYGWIN
endif


.PHONY: all clean

all: $(TARGET)

clean:
	$(RM) $(OBJ_DIR) $(DEPS_DIR) $(TARGET)
	$(RM) *.stackdump

$(TARGET): $(OBJ_FILES)
	$(CPPC) -o $@ $(OBJ_FILES) $(LN_FLAGS)

$(OBJ_DIR)/%.opp : src/%.cpp
	@if [ ! -d $(OBJ_DIR) ]; then $(RM) $(OBJ_DIR); echo "Creating directory: $(OBJ_DIR)"; mkdir $(OBJ_DIR); fi
	@if [ ! -d $(DEPS_DIR) ]; then $(RM) $(DEPS_DIR); echo "Creating directory: $(DEPS_DIR)"; mkdir $(DEPS_DIR); fi
	$(CPPC) $(CPP_FLAGS) -MM -MG -MP -MF $(DEPS_DIR)/$*.dpp -MT $@ $<
	$(CPPC) $(CPP_FLAGS) -c -o $@ $<

-include $(DEP_FILES)

