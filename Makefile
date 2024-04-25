#SUBDIRS = src tests
RELEASE = etapa3

all:
	make -C ./src

clean: 
	make -C ./src clean
	rm ./$(RELEASE) 

tar: 
	tar --exclude='.[^/]*' -cvzf $(RELEASE).tgz .

test: 
	make -C ./tests
