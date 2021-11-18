COMPILER=$(shell root-config --cxx)
FLAGS=$(shell root-config --cflags --libs)

all: clean dict postproc

dict:
		rootcling -v4 -f mydict.cxx  -rmf libmydict.rootmap -rml libmydict.so  LinkDef.h
		g++ -shared -fPIC -o libmydict.so mydict.cxx $(FLAGS)

postproc: postproc.cxx
		$(COMPILER) -g -O3 -Wall -Wextra -Wpedantic -o postproc postproc.cxx $(FLAGS)

clean:
		rm -rf core postproc *.o mydict.cxx *.rootmap *.so *.pcm
