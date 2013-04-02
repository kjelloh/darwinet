# Overall makefile for Darwinet.


.phony: all clean engine cpp test %_clean %_test %_make

all: engine

clean: utils/cpp_clean engine_clean

test: utils/cpp_test engine_test

engine: engine_make

engine_make: utils/cpp_make

cpp: utils/cpp_make

%_clean:
	$(MAKE) -C $* clean

%_test:
	$(MAKE) -C $* test

%_make:
	$(MAKE) -C $* 


