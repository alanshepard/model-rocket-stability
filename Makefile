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

_DEPS = rocket.h ellipticalfins.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = rocket.o finoptimizer.o ellipticalfins.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

debug:
	echo ${OBJ}; echo ${DEPS}


$(ODIR)/%.o: %.cc $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

main: main.cc $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
		rm $(ODIR)/*.o *~ core $(INCDIR)/*~ 

