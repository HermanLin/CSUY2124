FLAGS = -Wall -std=c++11

all: testRational rec08

testRational: testRational.cpp
	g++ ${FLAGS} -o testRational testRational.cpp

rec08: rec08.cpp Rational.cpp Rational.h
	g++ ${FLAGS} -o rec08 rec08.cpp Rational.cpp

clear:
	rm -f testRational rec08