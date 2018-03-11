#include<iostream>
#include<fstream>
#include<string>
#include "ConnectFourPlusUndo.h"

using namespace std;

namespace SORMAN{
	ConnectFourPlusUndo::ConnectFourPlusUndo(){//The no parameter constructor creates a 5x5 game board

		ConnectFourPlus();
	}

	ConnectFourPlusUndo::ConnectFourPlusUndo(int newRow,int newCol){//Takes number of rows and columns as parameters and creates game

		ConnectFourPlus(newRow,newCol);
	}


	ConnectFourPlusUndo::ConnectFourPlusUndo(const ConnectFourPlusUndo &game)//Copies one game to anothor new game
		:ConnectFourPlus(game)
	{

	}

	const ConnectFourPlusUndo &ConnectFourPlusUndo::operator = (const ConnectFourPlusUndo &game){//Assignment operator

		ConnectFourPlus::operator = (game);

	}

	int ConnectFourPlusUndo::inputCol(char column)
	{
		string col,fileName;
		int colNum = 0;

		cout<<"Player " <<player<< " turn => Choose a column:"<<endl; //Indicates who is next
		getline(cin,col);
		if(col.length() == 0)
			exit(1);

		if(checkSave(col,fileName)){ //if user's input is SAVE,write to current board to file
			if(saveBoard(fileName))
				cout<<"Current game is saving....."<<endl;
			else
				cerr<<"File can not open,try again"<<endl;//Invalid filename
			return 0;
		}
		else if(checkLoad(col,fileName)){//if user's input is LOAD,read game from file
			if(loadBoard(fileName))
				return 2;
			else{
				cerr<<"File can not found,try again"<<endl;//Invalid filename
				return 0;
			}
		}
		else if(checkUndo(col)){ //if user's input is UNDO
			if(oldMoves.empty()){//if there are not any move in records,UNDO key word will not execute
				cout<<"There aren't any moves to be taken back!"<<endl;//
				return 0;
			}
			undoLetter();//Undo one move
			cout<<"One move is undoing..."<<endl;
			return 1;
		}
		else{
			if(col[0]>='A' && col[0] <= 'Z'){//Checks the input column and converts to number
				colNum = col[0] - 'A';
				oldMoves.push_back(col[0]);
			}

			if(!isLegalCol(colNum)){	
				cerr<<"Invalid column,try again"<<endl;
				return 0;
			}
			else if(!isColFull(colNum)){
				cerr<<"This column is full.Please choose another column"<<endl;
				return 0;
			}
			else{									// if there are not any illegal status,puts letter X or O
				putLetter(colNum);
				return 1;
			}
		}

	}


	void ConnectFourPlusUndo::undoLetter(){
		for(int i=0;i<rowSize;++i){
			for(int j=0;j<colSize;++j){
				//Undo the last move of user or computer according to last played column
				if(j == ( oldMoves[oldMoves.length() - 1] - 'A' ) && gameBoard[i][j].getType() != '*'){
					gameBoard[i][j].setType('*'); //Makes empty the cell
					oldMoves.resize(oldMoves.length() - 1);//Resize the records,therefore last played columns letter is deleted
					return;
				}
			}
		}
	}



	int ConnectFourPlusUndo::checkUndo(const string &col)const{

		const string str = "UNDO";
		int status = 0,count = 0;

		if(col.length() != 4)//for example if user's input UNDOO or UNDOAB.key words are not valid
			return 0;

		for(int i=0;i < col.length();++i){
			if(col[i] == str[i])
				++count;
			if(count == 4)//if input is UNDO
				status = 1;
		}

		return status;
	}


	int ConnectFourPlusUndo::saveBoard(const string &fileName)const{
		int status = 0;
		ofstream myfile;
	  	myfile.open(fileName);
	 
	 	if(myfile){
	 		//Writes the current board's size,game type and sequence to file
		  	myfile<<rowSize<<' '<<colSize<<endl;	
		  	myfile<<gameType<<endl;	
		  	myfile<<player<<endl;
		  	//Writes the records of all moves to file
		  	myfile<<oldMoves<<endl;
		  	//Writes the current board's to file
		  	for(int i=0;i<rowSize;i++){	
				for(int j=0;j<colSize;j++){
					myfile<<gameBoard[i][j].getType();
				}
				myfile<<endl;
			}
			myfile.close();
			status = 1;
		}
		else
			status = 0;

		return status;
	}

	int ConnectFourPlusUndo::loadBoard(const string &fileName){

		int status = 0;
		ifstream myfile;
	  	myfile.open(fileName);

	  	if(myfile){
	  		
	  		for(int i = 0; i < rowSize; ++i)//Deallocates old games board
			    delete[] gameBoard[i];   
			delete[] gameBoard;
			
			//Reads the  board's size,game type and sequence from file
		  	myfile>>rowSize>>colSize;	
		  	myfile>>gameType;	
		  	myfile>>player;
		  	//Reads the records of all moves from file
		  	myfile>>oldMoves;

		  	string temp;
		  	resizeBoard();//Allocates new places for the new board

		  	string ignore;
		  	getline(myfile,ignore);
		  	//Reads the  game board's from file
		  	for(int i=0;i<rowSize;i++){
		  		getline(myfile,temp);
				for(int j=0;j<colSize;j++){
					gameBoard[i][j].setType(temp[j]);
				}
			}
			myfile.close();
			status = 1;
		}
		else
			status = 0;

		  	return status;
	}

	bool ConnectFourPlusUndo::isOneVertical(){
		for(int i=0;i<colSize;++i){
			for(int j=rowSize-1;j>=0;--j){
				if(isLegalPos(j-1,i) && isLegalPos(j,i)){
					if(gameBoard[j][i].getType() == 'O' && gameBoard[j-1][i].getType() == '*'){
						//Checks whether there is a single cell and adds cell vertically
						gameBoard[j-1][i].setType('O');
						oldMoves.push_back(i+'A');//Records move
						return true;
					}
				}
			}
		}	
		return false;
	}

	bool ConnectFourPlusUndo::isTwoVertical(){
		for(int i=0;i<colSize;++i){
			for(int j=rowSize-1;j>=0;--j){
				if(isLegalPos(j-2,i) && isLegalPos(j,i)){
					if(gameBoard[j][i].getType() == 'O' && gameBoard[j-1][i].getType() == 'O' && gameBoard[j-2][i].getType() == '*' ){
						//Checks whether there are two neigbor cells and adds cell vertically
						gameBoard[j-2][i].setType('O');
						oldMoves.push_back(i+'A');//Records move
						return true;
					}
				}
			}
		}
		return false;
	}


	bool ConnectFourPlusUndo::isThreeVertical(){
		for(int i=0;i<colSize;++i){
			for(int j=rowSize-1;j>=0;--j){
				if(isLegalPos(j-3,i) && isLegalPos(j,i)){
					if(gameBoard[j][i].getType() == 'O' && gameBoard[j-1][i].getType() == 'O'  && gameBoard[j-2][i].getType() == 'O' && gameBoard[j-3][i].getType() == '*' ){
						//Checks whether there are three neigbor cell and adds cell vertically
						gameBoard[j-3][i].setType('O');
						oldMoves.push_back(i+'A');//Records move
						return true;
					}
				}
			}
		}
		return false;
	}

	bool ConnectFourPlusUndo::defend3Vertical(){
		for(int i=0;i<colSize;++i){
			for(int j=rowSize-1;j>=0;--j){
				if(isLegalPos(j-3,i) && isLegalPos(j,i)){
					if(gameBoard[j][i].getType() == 'X' && gameBoard[j-1][i].getType() == 'X'  && gameBoard[j-2][i].getType() == 'X' && gameBoard[j-3][i].getType() == '*' ){
						//Checks whether there are three neighbor opponent's cell and adds 'X' vertically
						gameBoard[j-3][i].setType('O');
						oldMoves.push_back(i+'A');//Records move
						return true;
					}
				}
			}
		}
		return false;
	}

	bool ConnectFourPlusUndo::defaultOne()
	{
		for(int i=rowSize - 1;i>=0;--i){ // if there arent any neighbor,moves empty '*' column
			for(int j=0;j<colSize;++j){
				if(gameBoard[i][j].getType() == '*'){
					gameBoard[i][j].setType('O');
					oldMoves.push_back(j+'A');//Records move
					return true;
				}
			}
		}

		return true;	
	}

	bool ConnectFourPlusUndo::isOne()
	{
		for(int i=rowSize - 1;i>=0;--i){
			for(int j=0;j<colSize;++j){
				if(isLegalPos(i,j+1) && isLegalPos(i,j)){
					if(gameBoard[i][j].getType() == 'O' && gameBoard[i][j+1].getType() == '*'
					 &&  i == rowSize -1){
						//Checks whether there is a single cell and adds cell in horizontal right side
						gameBoard[i][j+1].setType('O');
						oldMoves.push_back(j+1+'A');//Records move
						return true;
					}
				}
				if(isLegalPos(i+1,j+1) && isLegalPos(i,j)){
					if(gameBoard[i][j].getType() == 'O' && gameBoard[i][j+1].getType() == '*' &&  
						gameBoard[i+1][j+1].getType() != '*'){
						//Checks whether there is a single cell and adds cell in horizontal right side
						gameBoard[i][j+1].setType('O');
						oldMoves.push_back(j+1+'A');//Records move
						return true;
					}
				}
				if(isLegalPos(i,j+1)&& isLegalPos(i,j)){
					if(gameBoard[i][j].getType() == 'O' && gameBoard[i][j+1].getType() != '*' &&
					 gameBoard[i][j-1].getType() == '*' && 
						i == rowSize - 1 ){
						//Checks whether there is a single cell and adds cell in horizontal left side
						gameBoard[i][j-1].setType('O');
						oldMoves.push_back(j-1+'A');//Records move
						return true;
					}
				}
				if(isLegalPos(i+1,j+1)&& isLegalPos(i,j)){
					if(gameBoard[i][j].getType() == 'O' && gameBoard[i][j+1].getType() != '*' 
						&& gameBoard[i][j-1].getType() == '*' && 
						 gameBoard[i+1][j-1].getType() != '*'){
						//Checks whether there is a single cell and adds cell in horizontal left side
						gameBoard[i][j-1].setType('O');
						oldMoves.push_back(j-1+'A');
						return true;
					}
				}
			}	
		}
		return false;
	}

	bool ConnectFourPlusUndo::isTwo()//Checks are there any two neighbor horizontal cell
	{
		for(int i=rowSize - 1;i>=0;--i){
			for(int j=0;j<colSize;++j){
				if(isLegalPos(i,j+2) && isLegalPos(i,j)){
					if(gameBoard[i][j].getType() == 'O' && gameBoard[i][j+1].getType() == 'O' &&
					 gameBoard[i][j+2].getType() == '*' && i == rowSize -1 ){
						//Checks whether there are two neighbor cells and adds cell in horizontal right side
						gameBoard[i][j+2].setType('O');
						oldMoves.push_back(j+2+'A');//Records move
						return true;
					}
				}
				if(isLegalPos(i+1,j+2) && isLegalPos(i,j)){
					if(gameBoard[i][j].getType() == 'O' && gameBoard[i][j+1].getType() == 'O' &&
					 gameBoard[i][j+2].getType() == '*' && gameBoard[i+1][j+2].getType() != '*'){
						//Checks whether there are two neighbor cells and adds cell in horizontal right side
						gameBoard[i][j+2].setType('O');
						oldMoves.push_back(j+2+'A');//Records move
						return true;
					}
				}
				if(isLegalPos(i,j+2) && isLegalPos(i,j)){
					if(gameBoard[i][j].getType() == 'O' && gameBoard[i][j+1].getType() == 'O' && 
						gameBoard[i][j+2].getType() != '*' && gameBoard[i][j-1].getType() == '*' && 
						i == rowSize - 1 ){
						//Checks whether there are two neighbor cells and adds cell in horizontal left side
						gameBoard[i][j-1].setType('O');
						oldMoves.push_back(j-1+'A');
						return true;
					}
				}
				if(isLegalPos(i+1,j+2) && isLegalPos(i,j)){
					if(gameBoard[i][j].getType() == 'O' && gameBoard[i][j+1].getType() == 'O' && 
						gameBoard[i][j+2].getType() != '*' && gameBoard[i][j-1].getType() == '*' && 
						 gameBoard[i+1][j-1].getType() != '*'){
						//Checks whether there are two neighbor cells and adds cell in horizontal left side
						gameBoard[i][j-1].setType('O');
						oldMoves.push_back(j-1+'A');
						return true;
					}
				}
			}	
		}
		return false;
	}

	bool ConnectFourPlusUndo::isThree()//Checks are there any three neighbor horizontal cell
	{
		if(key){ //First move of computer
			if(gameBoard[rowSize - 1][colSize/2].getType()== '*'){
				gameBoard[rowSize - 1][colSize/2].setType('O');
				oldMoves.push_back((colSize/2)+'A');
			}
			else{//if first position is not available
				gameBoard[rowSize - 1][(colSize/2)-1].setType('O');
				oldMoves.push_back((colSize/2 - 1)+'A');
			}
			return true;
		}
		else{
			 for(int i=rowSize - 1;i>=0;--i){
				for(int j=0;j<colSize;++j){
					if(isLegalPos(i,j+3) && isLegalPos(i,j)){
						if(gameBoard[i][j].getType() == 'O' && gameBoard[i][j+1].getType() == 'O' && 
							gameBoard[i][j+2].getType() == 'O' && gameBoard[i][j+3].getType() == '*' && i == rowSize -1 ){
							//Checks whether there are three neighbor cells and adds cell in horizontal right side
							gameBoard[i][j+3].setType('O');
							oldMoves.push_back(j+3+'A');//Records move
							return true;
						}
					}
					if(isLegalPos(i+1,j+3) && isLegalPos(i,j)){
						if(gameBoard[i][j].getType() == 'O' && gameBoard[i][j+1].getType() == 'O' &&
						 gameBoard[i][j+2].getType() == 'O' && gameBoard[i][j+3].getType() == '*' && gameBoard[i+1][j+3].getType() != '*'){
							//Checks whether there are three neighbor cells and adds cell in horizontal right side
							gameBoard[i][j+3].setType('O');
							oldMoves.push_back(j+3+'A');//Records move
							return true;
						}
					}
					if(isLegalPos(i,j+3) && isLegalPos(i,j)){
						if(gameBoard[i][j].getType() == 'O' && gameBoard[i][j+1].getType() == 'O' && 
							gameBoard[i][j+2].getType() == 'O'&& gameBoard[i][j+3].getType() != '*' && gameBoard[i][j-1].getType() == '*' && 
							i == rowSize - 1 ){
							//Checks whether there are three neighbor cells and adds cell in horizontal left side
							gameBoard[i][j-1].setType('O');
							oldMoves.push_back(j-1+'A');
							return true;
						}
					}
					if(isLegalPos(i+1,j+3) && isLegalPos(i,j)){
						if(gameBoard[i][j].getType() == 'O' && gameBoard[i][j+1].getType() == 'O' && gameBoard[i][j+2].getType() == 'O' &&
							gameBoard[i][j+3].getType() != '*' && gameBoard[i][j-1].getType() == '*' && 
							 gameBoard[i+1][j-1].getType() != '*'){
							//Checks whether there are three neighbor cells and adds cell in horizontal left side
							gameBoard[i][j-1].setType('O');
							oldMoves.push_back(j-1+'A');
							return true;
						}
					}
				}	
			}
			return false;
		}
	}

	bool ConnectFourPlusUndo::Defend3()
	{	
		//Like isThree function,checks whether there are three opponent's neighbor cells and adds computer's cell around cell
		 for(int i=rowSize - 1;i>=0;--i){
			for(int j=0;j<colSize;++j){
				if(isLegalPos(i,j+3)&& isLegalPos(i,j)){
					if(gameBoard[i][j].getType() == 'X' && gameBoard[i][j+1].getType() == 'X' && 
						gameBoard[i][j+2].getType() == 'X' && gameBoard[i][j+3].getType() == '*' && i == rowSize -1 ){
						//Checks whether there is a single cell and adds cell in horizontal right side
						gameBoard[i][j+3].setType('O');
						oldMoves.push_back(j+3+'A');//Records move
						return true;
					}
				}
				if(isLegalPos(i+1,j+3)&& isLegalPos(i,j)){
					if(gameBoard[i][j].getType() == 'X' && gameBoard[i][j+1].getType() == 'X' && gameBoard[i][j+2].getType() == 'X'
						&& gameBoard[i][j+3].getType() == '*' && gameBoard[i+1][j+3].getType() != '*'){
						//Checks whether there is a single cell and adds cell in horizontal right side
						gameBoard[i][j+3].setType('O');
						oldMoves.push_back(j+3+'A');//Records move
						return true;
					}
				}
				if(isLegalPos(i,j+3)&& isLegalPos(i,j)){
					if(gameBoard[i][j].getType() == 'X' && gameBoard[i][j+1].getType() == 'X' && gameBoard[i][j+2].getType() == 'X'
						&& gameBoard[i][j+3].getType() != '*' && gameBoard[i][j-1].getType() == '*' && i == rowSize - 1 ){
						//Checks whether there is a single cell and adds cell in horizontal left side
						gameBoard[i][j-1].setType('O');
						oldMoves.push_back(j-1+'A');
						return true;
					}
				}
				if(isLegalPos(i+1,j+3)&& isLegalPos(i,j)){
					if(gameBoard[i][j].getType() == 'X' && gameBoard[i][j+1].getType() == 'X' && gameBoard[i][j+2].getType() == 'X'
						&&gameBoard[i][j+3].getType() != '*' && gameBoard[i][j-1].getType() == '*' && gameBoard[i+1][j-1].getType() != '*'){
						//Checks whether there is a single cell and adds cell in horizontal left side
						gameBoard[i][j-1].setType('O');
						oldMoves.push_back(j-1+'A');
						return true;
					}
				}
			}
		}
		return false;
	}
}