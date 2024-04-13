RELEASE = etapa2

IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =../lib

LIBS=-lm

_DEPS = 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = lex.yy.o parser.tab.o main.o  
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(RELEASE): $(OBJ) 
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(ODIR)/%.o: %.c $(DEPS) | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR): 
	mkdir $@ 

parser.tab.c: parser.y
	bison -d parser.y --report-file=.parser.output --verbose 

lex.yy.c: scanner.l
	flex scanner.l

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ parser.tab.c parser.tab.h lex.yy.c 
