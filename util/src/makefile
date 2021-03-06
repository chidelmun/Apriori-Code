#-----------------------------------------------------------------------
# File    : makefile
# Contents: build utility modules (on Unix systems)
#
#-----------------------------------------------------------------------
SHELL   = /bin/bash
THISDIR = ../../util/src

CC      = gcc -std=c99
# CC      = g++
CFBASE  = -Wall -Wextra -Wno-unused-parameter -Wconversion \
          -pedantic $(ADDFLAGS)
CFLAGS  = $(CFBASE) -DNDEBUG -O3 -funroll-loops
# CFLAGS  = $(CFBASE) -g
# CFLAGS  = $(CFBASE) -g -DSTORAGE

LD      = gcc
# LD      = g++
LDFLAGS = $(ADDFLAGS)
LIBS    = 

# ADDOBJS  = $(UTILDIR)/storage.o

PRGS    = sortargs listtest trdtest

#-----------------------------------------------------------------------
# Build Programs
#-----------------------------------------------------------------------
all:        $(PRGS)

sortargs:   sortargs.o makefile
	$(LD) $(LDFLAGS) $(LIBS) sortargs.o -o $@

listtest:   listtest.o makefile
	$(LD) $(LDFLAGS) $(LIBS) listtest.o -o $@

trdtest:    trdtest.o escape.o arrays.o idmap.o makefile
	$(LD) $(LDFLAGS) $(LIBS) escape.o arrays.o idmap.o trdtest.o -o $@

#-----------------------------------------------------------------------
# Programs
#-----------------------------------------------------------------------
sortargs.o: arrays.h fntypes.h
sortargs.o: arrays.c makefile
	$(CC) $(CFLAGS) -DARRAYS_MAIN -c arrays.c -o $@

listtest.o: lists.h fntypes.h
listtest.o: lists.c makefile
	$(CC) $(CFLAGS) -DLISTS_MAIN -c lists.c -o $@

trdtest.o:  tabread.h
trdtest.o:  tabread.c makefile
	$(CC) $(CFLAGS) -DTRD_MAIN -c tabread.c -o $@

#-----------------------------------------------------------------------
# Array Operations
#-----------------------------------------------------------------------
arrays.o:   arrays.h fntypes.h
arrays.o:   arrays.c makefile
	$(CC) $(CFLAGS) -c arrays.c -o $@

#-----------------------------------------------------------------------
# List Operations
#-----------------------------------------------------------------------
lists.o:    lists.h fntypes.h
lists.o:    lists.c makefile
	$(CC) $(CFLAGS) -c lists.c -o $@

#-----------------------------------------------------------------------
# Memory Management System for Objects of Equal Size
#-----------------------------------------------------------------------
memsys.o:   memsys.h
memsys.o:   memsys.c makefile
	$(CC) $(CFLAGS) -c memsys.c -o $@

#-----------------------------------------------------------------------
# Symbol Table Management
#-----------------------------------------------------------------------
symtab.o:   symtab.h fntypes.h
symtab.o:   symtab.c makefile
	$(CC) $(CFLAGS) -c symtab.c -o $@

idmap.o:    symtab.h fntypes.h arrays.h
idmap.o:    symtab.c makefile
	$(CC) $(CFLAGS) -DIDMAPFN -c symtab.c -o $@

#-----------------------------------------------------------------------
# Random Number Generator
#-----------------------------------------------------------------------
random.o:   random.h
random.o:   random.c makefile
	$(CC) $(CFLAGS) -c random.c -o $@

#-----------------------------------------------------------------------
# Numerical Statistics Management
#-----------------------------------------------------------------------
nstats.o:   nstats.h
nstats.o:   nstats.c makefile
	$(CC) $(CFLAGS) -c nstats.c -o $@

nst_pars.o: nstats.h
nst_pars.o: nstats.c makefile
	$(CC) $(CFLAGS) -DNST_PARSE -c nstats.c -o $@

#-----------------------------------------------------------------------
# Escape Character Handling
#-----------------------------------------------------------------------
escape.o:   escape.h
escape.o:   escape.c makefile
	$(CC) $(CFLAGS) -c escape.c -o $@

#-----------------------------------------------------------------------
# Table Reader and Writer Management
#-----------------------------------------------------------------------
tabread.o:  tabread.h escape.h
tabread.o:  tabread.c makefile
	$(CC) $(CFLAGS) -c tabread.c -o $@

tabwrite.o: tabwrite.h escape.h
tabwrite.o: tabwrite.c makefile
	$(CC) $(CFLAGS) -c tabwrite.c -o $@

#-----------------------------------------------------------------------
# Scanner
#-----------------------------------------------------------------------
scform.o:   scanner.h
scform.o:   scanner.c makefile
	$(CC) $(CFLAGS) -c scanner.c -o $@

scanner.o:   scanner.h
scanner.o:   scanner.c makefile
	$(CC) $(CFLAGS) -DSCN_SCAN -c scanner.c -o $@

#-----------------------------------------------------------------------
# Command Line Parameter Retrieval
#-----------------------------------------------------------------------
params.o:   params.h
params.o:   params.c makefile
	$(CC) $(CFLAGS) -c params.c -o $@

#-----------------------------------------------------------------------
# Storage Debugging Utility
#-----------------------------------------------------------------------
storage.o:  storage.h
storage.o:  storage.c makefile
	$(CC) $(CFLAGS) -c storage.c -o $@

#-----------------------------------------------------------------------
# Source Distribution Packages
#-----------------------------------------------------------------------
dist:
	$(MAKE) clean
	cd ../..; rm -f util.zip util.tar.gz; \
        zip -rq util.zip    util/{src,doc}; \
        tar cfz util.tar.gz util/{src,doc}

#-----------------------------------------------------------------------
# Clean up
#-----------------------------------------------------------------------
clean:
	rm -f $(PRGS) *.o *~ *.flc core
