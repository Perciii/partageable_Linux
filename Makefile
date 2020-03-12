all: test

test: install
	cd bin; \
	LD_LIBRARY_PATH=.; \
       	./main Composant1 2 6; \
	./main Composant2 2 6;

install:
	cd main && ${MAKE} install

clean:
	cd main && ${MAKE} clean
