RELEASE = etapa3

all: ../$(RELEASE) test
	../$(RELEASE) < test

display: ../$(RELEASE) output.dot
	dot -Tpng -Gbgcolor="#282828" -Nfontcolor=white -Ncolor=white -Ecolor=white saida.dot -o output.png
	kitten icat output.png

clean:
	rm output
