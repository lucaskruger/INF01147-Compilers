RELEASE = etapa3

all: ../$(RELEASE) test saida
	../$(RELEASE) < test > saida
	./output2dot.sh < saida > ast.dot
	dot -Tpng -Gbgcolor="#282828" -Nfontcolor=white -Ncolor=white -Ecolor=white ast.dot -o ast.png
	kitty + kitten icat ast.png

clean:
	rm ast.dot ast.png
