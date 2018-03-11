all: HW5

HW5: Cell.o ConnectFourAbstract.o ConnectFourPlus.o ConnectFourDiag.o ConnectFourPlusUndo.o main.o
	g++ Cell.o ConnectFourAbstract.o ConnectFourPlus.o ConnectFourDiag.o ConnectFourPlusUndo.o main.o -o exe

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

Cell.o: Cell.cpp
	g++ -std=c++11 -c Cell.cpp

ConnectFourAbstract.o:ConnectFourAbstract.cpp
	g++ -std=c++11 -c ConnectFourAbstract.cpp

ConnectFourPlus.o:ConnectFourPlus.cpp
	g++ -std=c++11 -c ConnectFourPlus.cpp

ConnectFourPlusUndo.o:ConnectFourPlusUndo.cpp
	g++ -std=c++11 -c ConnectFourPlusUndo.cpp

ConnectFourDiag.o:ConnectFourDiag.cpp
	g++ -std=c++11 -c ConnectFourDiag.cpp

run: exe
	./exe

clean:
	rm *.o exe
