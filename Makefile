.PHONY: all test docs clean

all:
	

docs:
	@ cd include; doxygen doxyfile
	-@ rm -r docs/api/*
	@ mv -f docs/html/* docs/api
	@ rm -r docs/html

