#SUBDIRS = src tests
RELEASE = etapa2

all:
	make -C ./src

clean: 
	make -C ./src clean
	rm ./$(RELEASE) 

tar: 
	tar --exclude='.[^/]*' -cvzf $(RELEASE).tgz .

test: 
	make -C ./tests
