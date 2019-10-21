FLAGS = -Wall -std=c++11

all: rec07-orig rec07

rec07-orig: rec07-orig.cpp
	g++ ${FLAGS} -o rec07-orig rec07-orig.cpp

rec07: rec07.cpp Course.h Course.cpp Student.h Student.cpp Registrar.h Registrar.cpp
	g++ ${FLAGS} -o rec07 rec07.cpp Course.cpp Student.cpp Registrar.cpp

clear:
	rm -f rec07-orig