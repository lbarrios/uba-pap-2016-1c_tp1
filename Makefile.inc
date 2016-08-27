# Default vars
UNAME:=$(shell uname)

ifeq ($(UNAME),FreeBSD)
	CC=g++6
	MAKE=gmake
endif

ifeq ($(UNAME),Linux)
	CC=g++
	MAKE=make
endif

ifeq ($(MAKE),)
	MAKE=make
endif

ifeq ($(CC),)
	CC=g++
endif

ifeq ($(CC),g++-4.6)
	C11_FLAG=c++0x
	C14_FLAG=c++0y
else
	C11_FLAG=c++11
	C14_FLAG=c++14
endif

#CC=g++ # setear CC manualmente con "setenv CC ..."
#-Wall: All Warnings
#-pedantic: pedantic warnings
#-std=...: set C standard to:...
#-O0: without optimizations
#-g: for debugging
CFLAGS=-Wall -pedantic -std=$(C14_FLAG) -O0

ifeq ($(EXE),)
	EXE=$(notdir $(shell pwd))
endif

# Default targets
.PHONY: all clean tests
all: $(EXE)

$(EXE): $(EXE).cpp
	$(CC) $(CFLAGS) -o $(EXE) $(EXE).cpp

clean:
	rm -f $(EXE)

tests:
	./run_tests.sh
