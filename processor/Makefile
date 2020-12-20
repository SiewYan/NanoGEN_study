COMPILER=$(shell root-config --cxx)
FLAGS=$(shell root-config --cflags --libs)

ntuple: processor.cxx
		$(COMPILER) -g -O3 -Wall -Wextra -Wpedantic -o processor processor.cxx $(FLAGS)

clean:
		rm -rf core processor *.o
