COMP = clang
CXXFLAGS = -O2 -std=c++0x -lboost_graph

main: mech.o
	${COMP} ${CXXFLAGS} -o main main.cpp

mech.o:
	${COMP} ${CXXFLAGS} -c mech.cpp

clean:
	rm *.o main
