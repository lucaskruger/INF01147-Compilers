ETAPA = etapa1	
IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =../lib

LIBS=-lm

_DEPS = tokens.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o lex.yy.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

make: $(OBJ) 
	$(CC) -o $(ETAPA)  $^ $(CFLAGS) $(LIBS)

$(ODIR)/%.o: %.c $(DEPS) lex.yy.c
	$(CC) -c -o $@ $< $(CFLAGS)

lex.yy.c: scanner.l
	flex scanner.l 

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ lex.yy.c	 
