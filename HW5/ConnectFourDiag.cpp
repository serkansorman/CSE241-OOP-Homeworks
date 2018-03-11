#include<iostream>
#include<fstream>
#include<string>
#include "ConnectFourDiag.h"

using namespace std;

namespace SORMAN{
	ConnectFourDiag::ConnectFourDiag()//The no parameter constructor creates a 5x5 game board
		:ConnectFourAbstract()
	{
		
	}

	ConnectFourDiag::ConnectFourDiag(int newRow,int newCol)//Takes number of rows and columns as parameters and creates game
		:ConnectFourAbstract(newRow,newCol)
	{
		
	}


	ConnectFourDiag::ConnectFourDiag(const ConnectFourDiag &game)//Copy constructor
		:ConnectFourAbstract(game){
	}

	const ConnectFourDiag &ConnectFourDiag::operator = (const ConnectFourDiag &game){//Assignment operator

		ConnectFourAbstract::operator = (game);

	}

	bool ConnectFourDiag::checkAll()
	{	
		if(checkDiaLeft()  ||  checkDiaRight()){// Checks board diagonally

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


	bool ConnectFourDiag::isThree()//Checks are there any three neighbor diagonal cell
	{
		if(key){ //First move of computer
			if(gameBoard[rowSize - 1][colSize/2].getType()== '*'){
				gameBoard[rowSize - 1][colSize/2].setType('O');
			}
			else{//if first position is not available
				gameBoard[rowSize - 1][(colSize/2)-1].setType('O');
			}
			return true;
		}
		else{
			 for(int i=rowSize - 1;i>=0;--i){
				for(int j=0;j<colSize;++j){
					if(isLegalPos(i-3,j+3) && isLegalPos(i,j)){
						if(gameBoard[i][j].getType() == 'O' && gameBoard[i-1][j+1].getType()== 'O' && gameBoard[i-2][j+2].getType()== 'O' && 
								gameBoard[i-3][j+3].getType()== '*' && gameBoard[i-2][j+3].getType()!= '*' && isLegalPos(i-3,j+3)){
							//Checks whether there are three neighbor cells and adds cell in right cross side
							gameBoard[i-3][j+3].setType('O');
							return true;
						}
					}
					if(isLegalPos(i-3,j-3) && isLegalPos(i,j)){
						if(gameBoard[i][j].getType() == 'O' && gameBoard[i-1][j-1].getType()== 'O' && gameBoard[i-2][j-2].getType()== 'O' && 
								gameBoard[i-3][j-3].getType()== '*' && gameBoard[i-2][j-3].getType()!= '*' && isLegalPos(i-3,j-3)){
							//Checks whether there are three neighbor cells and adds cell in left cross side
							gameBoard[i-3][j-3].setType('O');
							return true;
						}
					}
				}	
			}
			return false;
		}
	}


	bool ConnectFourDiag::isTwo()//Checks are there any two neighbor diagonal cell
	{
		for(int i=rowSize - 1;i>=0;--i){
			for(int j=0;j<colSize;++j){
				if(isLegalPos(i-2,j+2) && isLegalPos(i,j)){
					if(gameBoard[i][j].getType() == 'O' && gameBoard[i-1][j+1].getType() == 'O' && 
						gameBoard[i-2][j+2].getType() == '*' && gameBoard[i-1][j+2].getType() != '*' ){
						gameBoard[i-2][j+2].setType('O');
						//Checks whether there are two neighbor cells and adds cell in right cross side
						return true;
					}
				}
				if(isLegalPos(i-2,j-2) && isLegalPos(i,j)){
					if(gameBoard[i][j].getType() == 'O' && gameBoard[i-1][j-1].getType() == 'O' && 
						gameBoard[i-2][j-2].getType() == '*' && gameBoard[i-1][j-2].getType() != '*'){
						//Checks whether there are two neighbor cells and adds cell in left cross side
						gameBoard[i-2][j-2].setType('O');
						return true;
					}
				}
			}	
		}
		return false;
	}
	
	bool ConnectFourDiag::Defend3()//Checks are there any three neighbor diagonal 'X' cell
	{	
		//Like isThree function,checks whether there are three opponent's neighbor cells and adds computer's cell around cell
		 for(int i=rowSize - 1;i>=0;--i){
			for(int j=0;j<colSize;++j){
				if(isLegalPos(i-3,j+3)&& isLegalPos(i,j)){
					if(gameBoard[i][j].getType() == 'X' && gameBoard[i-1][j+1].getType()== 'X' && gameBoard[i-2][j+2].getType()== 'X'
						&& gameBoard[i-3][j+3].getType()== '*' && gameBoard[i-2][j+3].getType()!= '*' && isLegalPos(i-3,j+3)){
						//Checks whether there are three neighbor cells and adds cell in right cross side
						gameBoard[i-3][j+3].setType('O');
						return true;
					}
				}
				if(isLegalPos(i-3,j-3)&& isLegalPos(i,j)){
					if(gameBoard[i][j].getType() == 'X' && gameBoard[i-1][j-1].getType()== 'X' && gameBoard[i-2][j-2].getType()== 'X'
						&& gameBoard[i-3][j-3].getType()== '*' && gameBoard[i-2][j-3].getType()!= '*' && isLegalPos(i-3,j-3)){
						//Checks whether there are three neighbor cells and adds cell in left cross side
						gameBoard[i-3][j-3].setType('O');
						return true;
					}
				}
			}
		}
		return false;
	}

	bool ConnectFourDiag::play(){
		//Redefine the function for playing computer diagonally
		if(isThree()); //First priority is win and second priority is defense
		else if(Defend3());
		else if(isTwo());
		else if(isOne());
		else
			defaultOne();

		cout<<"Computer's Turn:"<<endl;
		
		setPlayer(2);//Computer plays in second sequence
		isComputer = 1;//Indicates player is computer
		if(checkAll()){
			statusEnd = 1;//Indicates the game ended
			return true;
		}
		else
			return false;
				
	}
}