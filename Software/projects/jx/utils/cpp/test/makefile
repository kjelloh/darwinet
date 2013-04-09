# Makefile for testing utility classes.

SYSTEM      := $(shell uname -o)
CPPC        := g++
AR          := ar -crus
RM          := rm -rf
CPP_FLAGS   := -Wall -g -I../inc
LN_FLAGS    := -L../libs -ldarwinet_utils $(shell libgcrypt-config --libs)
OBJ_DIR     := build
DEPS_DIR    := deps
CPP_FILES   := $(shell ls *.cpp 2> /dev/null)
OBJ_FILES   := $(patsubst %.cpp,$(OBJ_DIR)/%.opp,$(CPP_FILES))
DEP_FILES   := $(patsubst %.cpp,$(DEPS_DIR)/%.dpp,$(CPP_FILES))
TEST_TARGET := ../libs/libdarwinet_utils.a
TARGET      := test

ifeq ($(SYSTEM),Cygwin)
    TARGET    := $(patsubst %,%.exe,$(TARGET))
    CPP_FLAGS += -DCYGWIN
endif


.PHONY: all clean test_exec

all: test_exec

clean:
	$(RM) $(OBJ_DIR) $(DEPS_DIR) $(TARGET)
	$(RM) *.stackdump

test_exec: $(TARGET)
	@echo Executing tests.
	@./$(TARGET)

$(TARGET): $(OBJ_FILES) $(TEST_TARGET)
	$(CPPC) -o $@ $(OBJ_FILES) $(LN_FLAGS)

$(TEST_TARGET):
	$(MAKE) -C ..

$(OBJ_DIR)/%.opp : %.cpp
	@if [ ! -d $(OBJ_DIR) ]; then $(RM) $(OBJ_DIR); echo "Creating directory: $(OBJ_DIR)"; mkdir $(OBJ_DIR); fi
	@if [ ! -d $(DEPS_DIR) ]; then $(RM) $(DEPS_DIR); echo "Creating directory: $(DEPS_DIR)"; mkdir $(DEPS_DIR); fi
	$(CPPC) $(CPP_FLAGS) -MM -MG -MP -MF $(DEPS_DIR)/$*.dpp -MT $@ $<
	$(CPPC) $(CPP_FLAGS) -c -o $@ $<

-include $(DEP_FILES)

