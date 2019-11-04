FLAGS = -Wall -std=c++11

all: hw07-orig hw07

hw07-orig: hw07-orig.cpp
	g++ ${FLAGS} -o hw07-orig hw07-orig.cpp

hw07: hw07.cpp Nobles.h Nobles.cpp Protectors.h Protectors.cpp
	g++ ${FLAGS} -o hw07 hw07.cpp Nobles.cpp Protectors.cpp

clean:
	rm -f hw07-orig hw07