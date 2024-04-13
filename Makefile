#SUBDIRS = src tests

all:
	make -C ./src

clean: 
	make -C ./src clean

tar: 
	tar cvzf etapa2.tgz .

test: 
	make -C ./tests
