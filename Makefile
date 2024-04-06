scanner: scanner.l
	flex scanner.l
	gcc -o etapa1 lex.yy.c main.c -lfl
