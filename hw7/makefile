#makefile

all: HW7-1 HW7-2 Matrix for_each

HW7-1: HW7-1.cpp
	g++ -std=c++11 -o HW7-1 HW7-1.cpp -pthread
	
HW7-2: HW7-2.cpp
	g++ -std=c++11 -o HW7-2 HW7-2.cpp -pthread

Matrix: Matrix.cpp
	g++ -std=c++11 -o Matrix Matrix.cpp -fopenmp -pthread
	
#Note, the executable is named for_each_test, not for_each(1)
for_each: for_each.cpp
	g++ -std=c++11 -o for_each for_each.cpp
	
