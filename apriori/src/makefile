#-----------------------------------------------------------------------
# File    : makefile
# Contents: build apriori program (on Unix systems)
#-----------------------------------------------------------------------
# For large file support (> 2GB) compile with
#   make ADDFLAGS=-D_FILE_OFFSET_BITS=64
#-----------------------------------------------------------------------

SHELL    = /bin/bash
THISDIR  = ../../apriori/src
UTILDIR  = ../../util/src
MATHDIR  = ../../math/src
TRACTDIR = ../../tract/src

CC       = gcc -std=c99
# CC       = g++
CFBASE   = -Wall -Wextra -Wno-unused-parameter -Wconversion \
           -pedantic $(ADDFLAGS)
CFLAGS   = $(CFBASE) -DNDEBUG -O3 -funroll-loops
# CFLAGS   = $(CFBASE) -DNDEBUG -O3 -funroll-loops -DALIGN8
# CFLAGS   = $(CFBASE) -DNDEBUG -O3 -funroll-loops -DBENCH
# CFLAGS   = $(CFBASE) -g
# CFLAGS   = $(CFBASE) -g -DSTORAGE
# CFLAGS   = $(CFBASE) -g -DALIGN8
INCS     = -I$(UTILDIR) -I$(MATHDIR) -I$(TRACTDIR)

LD       = gcc
LDFLAGS  = $(ADDFLAGS)
LIBS     = -lm

# ADDOBJS  = $(UTILDIR)/storage.o

HDRS     = $(UTILDIR)/arrays.h   $(UTILDIR)/symtab.h  \
           $(UTILDIR)/escape.h   $(UTILDIR)/tabread.h \
           $(UTILDIR)/tabwrite.h $(UTILDIR)/scanner.h \
           $(MATHDIR)/gamma.h    $(MATHDIR)/chi2.h    \
           $(MATHDIR)/ruleval.h  $(TRACTDIR)/tract.h  \
           $(TRACTDIR)/patspec.h $(TRACTDIR)/report.h \
           istree.h
OBJS     = $(UTILDIR)/arrays.o   $(UTILDIR)/idmap.o   \
           $(UTILDIR)/escape.o   $(UTILDIR)/tabread.o \
           $(UTILDIR)/tabwrite.o $(UTILDIR)/scform.o  \
           $(MATHDIR)/gamma.o    $(MATHDIR)/chi2.o    \
           $(MATHDIR)/ruleval.o  $(TRACTDIR)/tatree.o \
           $(TRACTDIR)/patspec.o $(TRACTDIR)/report.o \
           isttat.o $(ADDOBJS)
PRGS     = apriori apriacc

#-----------------------------------------------------------------------
# Build Programs
#-----------------------------------------------------------------------
all:       $(PRGS)

apriori:   $(OBJS) apriori.o makefile
	$(LD) $(LDFLAGS) $(OBJS) apriori.o $(LIBS) -o $@

apriacc:   $(OBJS) apriacc.o makefile
	$(LD) $(LDFLAGS) $(OBJS) apriacc.o $(LIBS) -o $@

#-----------------------------------------------------------------------
# Main Programs
#-----------------------------------------------------------------------
apriori.o: $(HDRS) apriori.h
apriori.o: apriori.c makefile
	$(CC) $(CFLAGS) $(INCS) -DAPR_MAIN -c apriori.c -o $@

apriacc.o: $(HDRS) apriori.h
apriacc.o: apriori.c makefile
	$(CC) $(CFLAGS) $(INCS) -DAPR_MAIN -DAPRIACC -c apriori.c -o $@

#-----------------------------------------------------------------------
# Item Set Tree Management
#-----------------------------------------------------------------------
istree.o:  $(HDRS)
istree.o:  istree.c makefile
	$(CC) $(CFLAGS) $(INCS) -c istree.c -o $@

isttat.o:  $(HDRS)
isttat.o:  istree.c makefile
	$(CC) $(CFLAGS) $(INCS) -DTATREEFN -c istree.c -o $@

#-----------------------------------------------------------------------
# External Modules
#-----------------------------------------------------------------------
$(UTILDIR)/arrays.o:
	cd $(UTILDIR);  $(MAKE) arrays.o  ADDFLAGS="$(ADDFLAGS)"
$(UTILDIR)/idmap.o:
	cd $(UTILDIR);  $(MAKE) idmap.o   ADDFLAGS="$(ADDFLAGS)"
$(UTILDIR)/escape.o:
	cd $(UTILDIR);  $(MAKE) escape.o  ADDFLAGS="$(ADDFLAGS)"
$(UTILDIR)/tabread.o:
	cd $(UTILDIR);  $(MAKE) tabread.o ADDFLAGS="$(ADDFLAGS)"
$(UTILDIR)/scform.o:
	cd $(UTILDIR);  $(MAKE) scform.o  ADDFLAGS="$(ADDFLAGS)"
$(UTILDIR)/storage.o:
	cd $(UTILDIR);  $(MAKE) storage.o ADDFLAGS="$(ADDFLAGS)"
$(MATHDIR)/gamma.o:
	cd $(MATHDIR);  $(MAKE) gamma.o   ADDFLAGS="$(ADDFLAGS)"
$(MATHDIR)/chi2.o:
	cd $(MATHDIR);  $(MAKE) chi2.o    ADDFLAGS="$(ADDFLAGS)"
$(MATHDIR)/ruleval.o:
	cd $(MATHDIR);  $(MAKE) ruleval.o ADDFLAGS="$(ADDFLAGS)"
$(TRACTDIR)/tatree.o:
	cd $(TRACTDIR); $(MAKE) tatree.o  ADDFLAGS="$(ADDFLAGS)"
$(TRACTDIR)/patspec.o:
	cd $(TRACTDIR); $(MAKE) patspec.o ADDFLAGS="$(ADDFLAGS)"
$(TRACTDIR)/report.o:
	cd $(TRACTDIR); $(MAKE) report.o  ADDFLAGS="$(ADDFLAGS)"

#-----------------------------------------------------------------------
# Source Distribution Packages
#-----------------------------------------------------------------------
dist:
	$(MAKE) clean
	cd ../..; rm -f apriori.zip apriori.tar.gz; \
        zip -rq apriori.zip apriori/{src,ex,doc} \
          tract/src/{tract.[ch],patspec.[ch],report.[ch]} \
          tract/src/{makefile,tract.mak} tract/doc \
          math/src/{gamma.[ch],chi2.[ch],ruleval.[ch]} \
          math/src/{makefile,math.mak} math/doc \
          util/src/{fntypes.h,error.h} \
          util/src/{arrays.[ch],escape.[ch],symtab.[ch]} \
          util/src/{tabread.[ch],tabwrite.[ch],scanner.[ch]} \
          util/src/{makefile,util.mak} util/doc; \
        tar cfz apriori.tar.gz apriori/{src,ex,doc} \
          tract/src/{tract.[ch],patspec.[ch],report.[ch]} \
          tract/src/{makefile,tract.mak} tract/doc \
          math/src/{gamma.[ch],chi2.[ch],ruleval.[ch]} \
          math/src/{makefile,math.mak} math/doc \
          util/src/{fntypes.h,error.h} \
          util/src/{arrays.[ch],escape.[ch],symtab.[ch]} \
          util/src/{tabread.[ch],tabwrite.[ch],scanner.[ch]} \
          util/src/{makefile,util.mak} util/doc

#-----------------------------------------------------------------------
# Installation
#-----------------------------------------------------------------------
install:
	cp $(PRGS) $(HOME)/bin

#-----------------------------------------------------------------------
# Clean up
#-----------------------------------------------------------------------
localclean:
	rm -f *.o *~ *.flc core $(PRGS)

clean:
	$(MAKE) localclean
	cd $(TRACTDIR); $(MAKE) localclean
	cd $(MATHDIR);  $(MAKE) clean
	cd $(UTILDIR);  $(MAKE) clean
