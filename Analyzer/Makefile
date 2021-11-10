COMPILER=$(shell root-config --cxx)
FLAGS=$(shell root-config --cflags --libs)

ntuple: postproc.cxx
		$(COMPILER) -g -O3 -Wall -Wextra -Wpedantic -o postproc postproc.cxx $(FLAGS) -lGenVector

clean:
		rm -rf core postproc *.o
