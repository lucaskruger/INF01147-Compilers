RELEASE = etapa4

IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR) -g

ODIR=obj
LDIR =../lib

LIBS=-lm

_DEPS = 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = symbol_table.o ast.o parser.tab.o lex.yy.o main.o  
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(RELEASE): $(OBJ) 
	$(CC) -o ../$@ $^ $(CFLAGS) $(LIBS)

$(ODIR)/%.o: %.c $(DEPS) | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR): 
	mkdir $@ 

parser.tab.c: parser.y
	bison -d parser.y --report-file=.parser.output --verbose 

lex.yy.c: scanner.l parser.tab.c
	flex scanner.l

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ parser.tab.c parser.tab.h lex.yy.c $(RELEASE)
