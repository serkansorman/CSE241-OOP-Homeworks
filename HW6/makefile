all: HW6

HW6: GTUSetBase.o GTUSet.o GTUIterator.o GTUMap.o main.o
	g++ GTUSetBase.o GTUSet.o GTUIterator.o GTUMap.o main.o -o exe

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

GTUSetBase.o: GTUSetBase.cpp
	g++ -std=c++11 -c GTUSetBase.cpp

GTUSet.o:GTUSet.cpp
	g++ -std=c++11 -c GTUSet.cpp

GTUIterator.o:GTUIterator.cpp
	g++ -std=c++11 -c GTUIterator.cpp

GTUMap.o:GTUMap.cpp
	g++ -std=c++11 -c GTUMap.cpp

run: exe
	./exe

clean:
	rm *.o exe
