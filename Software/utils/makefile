# Makefile for Darwinet utility class library.

SYSTEM    := $(shell uname -o)
CPPC      := g++
AR        := ar -crus
RM        := rm -rf
CPP_FLAGS := -Wall -g -Iinc
LN_FLAGS  := 
OBJ_DIR   := build
DEPS_DIR  := deps
LIBS_DIR  := libs
CPP_FILES := $(shell ls src/*.cpp 2> /dev/null)
OBJ_FILES := $(patsubst src/%.cpp,$(OBJ_DIR)/%.opp,$(CPP_FILES))
DEP_FILES := $(patsubst src/%.cpp,$(DEPS_DIR)/%.dpp,$(CPP_FILES))
TARGET    := libdarwinet_utils.a

ifeq ($(SYSTEM),Cygwin)
    CPP_FLAGS += -DCYGWIN
endif


.PHONY: all clean 

all: $(LIBS_DIR)/$(TARGET)

clean:
	$(RM) $(OBJ_DIR) $(DEPS_DIR) $(LIBS_DIR)

$(LIBS_DIR)/$(TARGET): $(OBJ_FILES)
	@if [ ! -d $(LIBS_DIR) ]; then $(RM) $(LIBS_DIR); echo "Creating directory: $(LIBS_DIR)"; mkdir $(LIBS_DIR); fi
	$(AR) $(LIBS_DIR)/$(TARGET) $(OBJ_FILES)

$(OBJ_DIR)/%.opp : src/%.cpp
	@if [ ! -d $(OBJ_DIR) ]; then $(RM) $(OBJ_DIR); echo "Creating directory: $(OBJ_DIR)"; mkdir $(OBJ_DIR); fi
	@if [ ! -d $(DEPS_DIR) ]; then $(RM) $(DEPS_DIR); echo "Creating directory: $(DEPS_DIR)"; mkdir $(DEPS_DIR); fi
	$(CPPC) $(CPP_FLAGS) -MM -MG -MP -MF $(DEPS_DIR)/$*.dpp -MT $@ $<
	$(CPPC) $(CPP_FLAGS) -c -o $@ $<

-include $(DEP_FILES)

