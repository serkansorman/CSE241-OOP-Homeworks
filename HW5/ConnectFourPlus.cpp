#include<iostream>
#include<fstream>
#include<string>
#include "ConnectFourPlus.h"

using namespace std;
namespace SORMAN{

	ConnectFourPlus::ConnectFourPlus():ConnectFourAbstract(){//The no parameter constructor creates a 5x5 game board
			
	}

	ConnectFourPlus::ConnectFourPlus(int newRow,int newCol):ConnectFourAbstract(newRow,newCol){//Takes number of rows and columns as parameters and creates game
		
	}


	ConnectFourPlus::ConnectFourPlus(const ConnectFourPlus &game)//Copy constructor
		:ConnectFourAbstract(game)
	{
		
	}

	const ConnectFourPlus &ConnectFourPlus::operator = (const ConnectFourPlus &game){//Assignment operator

		ConnectFourAbstract::operator = (game);

	}

	bool ConnectFourPlus::checkAll()
	{	
		if(checkHorizon()  || checkVertical()){ // Checks board vertically and horizontally

			printBoard();

			if(isComputer) //if player 2 is computer,assigns player 3 to computer
				setPlayer(3);

			if(player != 3)//if player is user
				cout<<"Player "<<player<< " win the game!!!"<<endl;
			else
				cout<<"Computer win the game!!!"<<endl;
				
			return true;
		}
		else
			return false;
	}
}