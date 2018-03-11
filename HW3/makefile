all: main

main: main.o
	g++ -std=c++11 main.o -o exe

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

run: exe
	./exe

clean:
	rm *.o exe
