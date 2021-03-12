CXX=clang++
#CXX=g++

FLAGS = -O3 -std=c++14 -g 


#mainMain: main.o polygon.o
#	${CXX}  main.cpp
all:
	${CXX} ${FLAGS} *.cpp

clean:
	/bin/rm -f ${CXX}  *.o 