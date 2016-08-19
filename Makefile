# 
# ellipticalstability.h
# 
# Copyright (C) 2015,2016 Bernardo <b.b.monteiro@gmail.com>
#
# This file is released under the GPLv2
#

IDIR = .
CC=g++
CFLAGS=-I$(IDIR) -Wall -pedantic

ODIR=obj

LIBS=

_DEPS = rocket.h ellipticalfins.h dpe-common.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = rocket.o finoptimizer.o ellipticalfins.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

debug:
	echo ${OBJ}; echo ${DEPS}


$(ODIR)/%.o: %.cc $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

main: main.cc $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
 
dpe-c: dpe-c.cc $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

dpe-b: dpe-b.cc $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

dpe-d: dpe-d.cc $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

dpe-e: dpe-e.cc $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

agua: agua.cc $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
		rm $(ODIR)/*.o *~ core $(INCDIR)/*~ 

