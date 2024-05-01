RELEASE = etapa3

all: ../$(RELEASE) test
	../$(RELEASE) < test 
	./output2dot.sh < ast.txt > ast.dot
	dot -Tpng -Gbgcolor="#282828" -Nfontcolor=white -Ncolor=white -Ecolor=white ast.dot -o ast.png
	kitten icat ast.png

clean:
	rm ast.txt ast.dot ast.png
