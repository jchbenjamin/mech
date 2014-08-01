CC = g++ 
CXXFLAGS = -O2 -std=c++0x

mechanism: mech.o graph.o
	${CC} ${CXXFLAGS} -o mechanism main.cpp mech.o graph.o

mech.o: graph.o
	${CC} ${CXXFLAGS} -c mech.cpp

graph.o:
	${CC} ${CXXFLAGS} -c graph.cpp

clean:
	rm *.o mechanism 
