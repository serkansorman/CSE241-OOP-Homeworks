#include<iostream>
#include<fstream>
#include<string>
#include"ConnectFourAbstract.h"

using namespace std;

namespace SORMAN{
	
	ConnectFourAbstract::ConnectFourAbstract(){//The no parameter constructor creates a 5x5 game board

		Cell c;			//Creates a Cell object for fill the board with this object
		c.setType('*'); //Sets the cell type for each cell 
		setSize(5,5);

	    gameBoard = new Cell *[rowSize];

		for(int i=0;i<5;++i)
			gameBoard[i] = new Cell [colSize];

		for(int i=0;i<rowSize;i++)//fills the board with  Cell object
		    for(int j=0;j<colSize;j++)
		    	gameBoard[i][j] = c;
	}

	ConnectFourAbstract::ConnectFourAbstract(int newRow,int newCol){//Takes number of rows and columns as parameters and creates game

		Cell c;			//Creates a Cell object for fill the board with this object
		c.setType('*'); //Sets the cell type for each cell 

		setSize(newRow,newCol);

		gameBoard = new Cell *[rowSize];

		for(int i=0;i<newRow;++i)
			gameBoard[i] = new Cell [colSize];

		for(int i=0;i<rowSize;i++)//fills the board with  Cell object
		    for(int j=0;j<colSize;j++)
		    	gameBoard[i][j] = c;
	}


	ConnectFourAbstract::ConnectFourAbstract(const ConnectFourAbstract &game){//Copy constructor

		//Copies the  parameter object's members to the new object;
		setSize(game.rowSize,game.colSize);
		gameType = game.gameType;
		key = game.key;
		player = game.player;
		isComputer = game.isComputer;
		statusEnd = game.statusEnd;

		Cell c;
		gameBoard = new Cell *[rowSize];//Allocates memory for new board's row
		
		for(int i=0;i<rowSize;++i) //Allocates memory for new board's column
			gameBoard[i] = new Cell [colSize]; 

		for(int i=0;i<rowSize;i++){
		    for(int j=0;j<colSize;j++){
		    	gameBoard[i][j] = c;//Fills the board with a Cell object
		    	//Copies each cell of the board to new object's board
		    	gameBoard[i][j].setType(game.gameBoard[i][j].getType());
		    }
		}

	}

	ConnectFourAbstract::~ConnectFourAbstract(){
		for(int i = 0; i < rowSize; ++i)//Deallocates the places that allocated for board before
		    delete[] gameBoard[i];   

		delete[] gameBoard;
	 }


	void ConnectFourAbstract::setGame(int game){//Set the game type (PvP = 1,PvC = 2)
		gameType = game;
	}

	void ConnectFourAbstract::setPlayer(int sequence){//Indıcates sequence
		player = sequence;
	}

	void ConnectFourAbstract::setSize(int row,int col){
		rowSize = row;
		colSize = col;
	}

	bool ConnectFourAbstract::operator == (const ConnectFourAbstract &game)const{
		
		//Compare two object according to height,width and game type
		if(rowSize == game.rowSize && colSize == game.colSize && gameType == game.gameType){

			//if these three features are same,compares each cells in these boards
			for(int i=0;i<rowSize;i++){	
				for(int j=0;j<colSize;j++){
					if(gameBoard[i][j].getType() != game.gameBoard[i][j].getType())//if cell is not same return false
						return false;
				}
			}
			return true;
		}
		else
			return false;

	}

	bool ConnectFourAbstract::operator != (const ConnectFourAbstract &game)const{

		return ! (game == *this);//Compare whether two cells are different or not
	}

	const ConnectFourAbstract &ConnectFourAbstract::operator = (const ConnectFourAbstract &game){

		if(this == &game)//if parameter object and current object are same,returns current object.
			return *this;
		else{

			for(int i = 0; i < rowSize; ++i)//Deallocates the places that allocated for left side object
		    delete[] gameBoard[i];   

			delete[] gameBoard;
			gameBoard = nullptr;

			//Assigns the  parameter object's members to left side object;
			rowSize = game.rowSize;
			colSize = game.colSize;
			gameType = game.gameType;

			Cell c;
			gameBoard = new Cell *[rowSize];//Allocates memory for new board's row
			
			for(int i=0;i<rowSize;++i)
				gameBoard[i] = new Cell [colSize]; //Allocates memory for new board's column

			for(int i=0;i<rowSize;i++){
			    for(int j=0;j<colSize;j++){
			    	gameBoard[i][j] = c;//Fills the board with a Cell object
			    	//Assigns each cell of the board to left object's board
			    	gameBoard[i][j].setType(game.gameBoard[i][j].getType());
			    }
			}

			return *this;
		}

	}

	void ConnectFourAbstract::resizeBoard(){//Resize the board according to new row and column number

		Cell c;
		
		gameBoard = new Cell *[rowSize];
		
		for(int i=0;i<rowSize;++i)
			gameBoard[i] = new Cell [colSize];

		for(int i=0;i<rowSize;i++)//fills the board with  Cell object
		    for(int j=0;j<colSize;j++)
		    	gameBoard[i][j] = c;
	}


	bool ConnectFourAbstract::isLegalSize(const int &row,const int &col) const {//Checks height and width are legal
		if(row >= 4 && row < 27 && col >= 4 && col < 27){
			return true;
		}
		else
			return false;
	}

	bool ConnectFourAbstract::isLegalPos(int CoordX,int CoordY) const
	{
		if(CoordX >=0 && CoordX< rowSize && CoordY >= 0 && CoordY<colSize) // Prevents reach out of matrix
			return true;
		else
			return false;
	}


	bool ConnectFourAbstract::isLegalCol(int colNum) const{
		if(colNum <colSize && colNum >= 0)//Check whether the column is on the board
			return true;
		else
			return false;
	}

	bool ConnectFourAbstract::isColFull(int colNum)const{
		int a = 0;

		for(int i=rowSize - 1;i>=0;--i){
			for(int j=colSize - 1;j>=0;--j){
				if(j == colNum && gameBoard[i][j].getType() != '*')
					a++;	//Counts filled cell in chosen column
			}
		}
		if(a == rowSize)	//if height of board equal to numbers of filled cell in column.The column is full
			return false;
		else
			return true;
	}

	bool ConnectFourAbstract::isBoardFull()const{
		int a = 0;

		for(int i=rowSize - 1;i>=0;--i){
			for(int j=colSize - 1;j>=0;--j){
				if(gameBoard[i][j].getType() != '*')
					a++; //Counts filled cell in board
			}
		}

		if(a == rowSize * colSize){ // if there is not empty column to continue game,the game will end in a draw.
			cout<<"The game ended in a draw."<<endl;
			return true;
		}
		else
			return false;
	}


	bool ConnectFourAbstract::isEnd()const{//Checks board is full or game ended
		if(isBoardFull() || statusEnd)
			return true;
		else
			return false;
	}


	void ConnectFourAbstract::printBoard() const{

		for(int i=0;i<colSize;i++)
			cout<<static_cast<char>('A'+i)<<"  ";  //Prints letters row
		cout<<endl;

		for(int i=0;i<rowSize;i++){
		    for(int j=0;j<colSize;j++)
		        	cout<<gameBoard[i][j].getType()<<"  ";
		    cout<<endl<<endl;
		}
	}



	void ConnectFourAbstract::putLetter(int colNum)
	{
		for(int i=rowSize - 1;i>=0;--i){
			for(int j=colSize - 1;j>=0;--j){
				if(j == colNum && gameBoard[i][j].getType() == '*' && player == 1){// Puts 'X' Or 'O' to the board according to current player
					gameBoard[i][j].setType('X');
					return;
				}
				else if(j == colNum && gameBoard[i][j].getType() == '*' && player == 2){
					gameBoard[i][j].setType('O');
					return;
				}
			}
		}
	}

	int ConnectFourAbstract::inputCol(char column)
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
		else{
			if(col[0]>='A' && col[0] <= 'Z') //Checks the input column and converts to number
				colNum = col[0] - 'A';

			else
				colNum = col[0] - 'a';

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

	bool ConnectFourAbstract::play(char position){
		int status = 0;

		status = inputCol(position);
		while(status == 0)//Contiunes taking input until the input is valid
			status = inputCol(position);
		if(status == 2){//if input is load,continues the game
			continueGame();
			return true;
		}
		else
			return false;	
	}

	bool ConnectFourAbstract::play(){
		// first priority is winning motion and second priority is defend yourself
		if(isThreeVertical() || isThree()); 
		else if(defend3Vertical() || Defend3());
		else if( isTwoVertical()  || isTwo());
		else if(isOneVertical() || isOne());
		else
			defaultOne();

		cout<<"Computer's Turn:"<<endl;
		
		setPlayer(2);//Computer plays in second sequence
		isComputer = 1;//Indicate player is computer
		if(checkAll()){
			statusEnd = 1;//Indicates the game ended
			return true;
		}
		else
			return false;
				
	}
	bool ConnectFourAbstract::checkHorizon()
	{
		int count = 0;

		for(int i=rowSize - 1;i>=0;--i){
			for(int j=0;j<colSize;++j){
				if((gameBoard[i][j].getType() == 'X' && player == 1) || (gameBoard[i][j].getType() == 'O' && player == 2))
					++count; // Counts same cells horizontally
				else
					count = 0;
				if(count == 4){	// if there are four same neighbor cells
					for(int a=0;a<4;a++){ // Converts them small case x or o
						if(player == 1)
							gameBoard[i][j-a].setType('x');
						else
							gameBoard[i][j-a].setType('o');
								
					}
					return true;
				}		
			}
			count = 0;
		}
		return false;
	}



	bool ConnectFourAbstract::checkVertical()
	{
		int count = 0;
		
		for(int i=colSize - 1;i>=0;--i){
			for(int j=rowSize-1;j>=0;--j){
				if(isLegalPos(j,i)){
					if((gameBoard[j][i].getType() == 'X' && player == 1) || (gameBoard[j][i].getType() == 'O' && player == 2))
						++count; // Counts same cells vertically
					else
						count = 0;
					if(count == 4){ // if there are four same neighbor cells
						for(int a=0;a<4;a++){ // Converts them small case x or o
							if(player == 1)
								gameBoard[j+a][i].setType('x');
							else
								gameBoard[j+a][i].setType('o');
						}
						return true;
					}
				}		
			}
			count = 0;
		}
		return false;
	}

	bool ConnectFourAbstract::checkDiaRight()
	{
		for(int i=rowSize - 1;i>=0;--i){
			for(int j=0;j<colSize;++j){
				if(isLegalPos(i-1,j+1) && isLegalPos(i-2,j+2) && isLegalPos(i-3,j+3)){
					if( (gameBoard[i][j].getType() == 'X' && gameBoard[i-1][j+1].getType() == 'X'//Checks right cross for player 1
						 && gameBoard[i-2][j+2].getType() == 'X' && gameBoard[i-3][j+3].getType() == 'X') ||

						(gameBoard[i][j].getType() == 'O' && gameBoard[i-1][j+1].getType() == 'O'//Checks cross for player 2
						 && gameBoard[i-2][j+2].getType() == 'O' && gameBoard[i-3][j+3].getType() == 'O')){	
						for(int b=0;b<4;++b){ // if there are four same neighbor cells in right cross,converts them small case x or o
							if(player == 1)
							gameBoard[i-b][j+b].setType('x');
							else
								gameBoard[i-b][j+b].setType('o');
							}
						return true;
					}
				}
			}
		}
		return false;			
	}


	bool ConnectFourAbstract::checkDiaLeft()
	{
		for(int i=rowSize - 1;i>=0;--i){
			for(int j=0;j<colSize;++j){
				if(isLegalPos(i-1,j-1) && isLegalPos(i-2,j-2) && isLegalPos(i-3,j-3)){
					if( (gameBoard[i][j].getType() == 'X' && gameBoard[i-1][j-1].getType() == 'X'//Checks whether 4 user1 cells are neighbour
						 && gameBoard[i-2][j-2].getType() == 'X' && gameBoard[i-3][j-3].getType() == 'X') ||

						(gameBoard[i][j].getType() == 'O' && gameBoard[i-1][j-1].getType() == 'O'//Checks whether 4 user1 or computer cells are neighbour
						 && gameBoard[i-2][j-2].getType() == 'O' && gameBoard[i-3][j-3].getType() == 'O')){	

						for(int b=0;b<4;++b){ // if there are four same neighbor cells in right cross,converts them small case x or o
							if(player == 1)
							gameBoard[i-b][j-b].setType('x');
							else
								gameBoard[i-b][j-b].setType('o');
							}
						return true;
					}
				}
			}
		}
		return false;	
	}


	
	bool ConnectFourAbstract::isOneVertical(){
		for(int i=0;i<colSize;++i){
			for(int j=rowSize-1;j>=0;--j){
				if(isLegalPos(j-1,i) && isLegalPos(j,i)){
					if(gameBoard[j][i].getType() == 'O' && gameBoard[j-1][i].getType() == '*'){
						//Checks whether there is a single cell and adds cell vertically
						gameBoard[j-1][i].setType('O');
						return true;
					}
				}
			}
		}	
		return false;
	}

	bool ConnectFourAbstract::isTwoVertical(){
		for(int i=0;i<colSize;++i){
			for(int j=rowSize-1;j>=0;--j){
				if(isLegalPos(j-2,i) && isLegalPos(j,i)){
					if(gameBoard[j][i].getType() == 'O' && gameBoard[j-1][i].getType() == 'O' && gameBoard[j-2][i].getType() == '*' ){
						//Checks whether there are two neigbor cells and adds cell vertically
						gameBoard[j-2][i].setType('O');
						return true;
					}
				}
			}
		}
		return false;
	}


	bool ConnectFourAbstract::isThreeVertical(){
		for(int i=0;i<colSize;++i){
			for(int j=rowSize-1;j>=0;--j){
				if(isLegalPos(j-3,i) && isLegalPos(j,i)){
					if(gameBoard[j][i].getType() == 'O' && gameBoard[j-1][i].getType() == 'O'  && gameBoard[j-2][i].getType() == 'O' && gameBoard[j-3][i].getType() == '*' ){
						//Checks whether there are three neigbor cell and adds cell vertically
						gameBoard[j-3][i].setType('O');
						return true;
					}
				}
			}
		}
		return false;
	}

	bool ConnectFourAbstract::defend3Vertical(){
		for(int i=0;i<colSize;++i){
			for(int j=rowSize-1;j>=0;--j){
				if(isLegalPos(j-3,i) && isLegalPos(j,i)){
					if(gameBoard[j][i].getType() == 'X' && gameBoard[j-1][i].getType() == 'X'  && gameBoard[j-2][i].getType() == 'X' && gameBoard[j-3][i].getType() == '*' ){
						//Checks whether there are three neighbor opponent's cell and adds 'X' vertically
						gameBoard[j-3][i].setType('O');
						return true;
					}
				}
			}
		}
		return false;
	}

	bool ConnectFourAbstract::defaultOne()
	{
		for(int i=rowSize - 1;i>=0;--i){ // if there arent any neighbor,moves any empty '*' column
			for(int j=0;j<colSize;++j){
				if(gameBoard[i][j].getType() == '*'){
					gameBoard[i][j].setType('O');
					return true;
				}
			}
		}

		return true;	
	}

	bool ConnectFourAbstract::isOne()
	{
		for(int i=rowSize - 1;i>=0;--i){
			for(int j=0;j<colSize;++j){
				if(isLegalPos(i,j+1) && isLegalPos(i,j)){
					if(gameBoard[i][j].getType() == 'O' && gameBoard[i][j+1].getType() == '*'
					 &&  i == rowSize -1){
						//Checks whether there is a single cell and adds cell in horizontal right side
						gameBoard[i][j+1].setType('O');
						return true;
					}
				}
				if(isLegalPos(i+1,j+1) && isLegalPos(i,j)){
					if(gameBoard[i][j].getType() == 'O' && gameBoard[i][j+1].getType() == '*' &&  
						gameBoard[i+1][j+1].getType() != '*'){
						//Checks whether there is a single cell and adds cell in horizontal right side
						gameBoard[i][j+1].setType('O');
						return true;
					}
				}
				if(isLegalPos(i,j+1)&& isLegalPos(i,j)){
					if(gameBoard[i][j].getType() == 'O' && gameBoard[i][j+1].getType() != '*' &&
					 gameBoard[i][j-1].getType() == '*' && 
						i == rowSize - 1 ){
						//Checks whether there is a single cell and adds cell in horizontal left side
						gameBoard[i][j-1].setType('O');
						return true;
					}
				}
				if(isLegalPos(i+1,j+1)&& isLegalPos(i,j)){
					if(gameBoard[i][j].getType() == 'O' && gameBoard[i][j+1].getType() != '*' 
						&& gameBoard[i][j-1].getType() == '*' && 
						 gameBoard[i+1][j-1].getType() != '*'){
						//Checks whether there is a single cell and adds cell in horizontal left side
						gameBoard[i][j-1].setType('O');
						return true;
					}
				}
				if(isLegalPos(i-1,j+1)&& isLegalPos(i,j)){
					if(gameBoard[i][j].getType() == 'O' && gameBoard[i-1][j+1].getType() == '*' &&
					 gameBoard[i][j+1].getType() != '*' && isLegalPos(i-1,j+1)){
						gameBoard[i-1][j+1].setType('O');
						//Checks whether there is a single cell and adds cell in right cross side
						return true;
					}
				}
				if(isLegalPos(i-1,j-1)&& isLegalPos(i,j)){
					if(gameBoard[i][j].getType() == 'O' && gameBoard[i-1][j-1].getType() == '*' && 
						gameBoard[i][j-1].getType() != '*' && isLegalPos(i-1,j-1)){
						//Checks whether there is a single cell and adds cell in left cross side
						gameBoard[i-1][j-1].setType('O');
						return true;
					}
				}
			}	
		}
		return false;
	}

	bool ConnectFourAbstract::isTwo()
	{
		for(int i=rowSize - 1;i>=0;--i){
			for(int j=0;j<colSize;++j){
				if(isLegalPos(i,j+2) && isLegalPos(i,j)){
					if(gameBoard[i][j].getType() == 'O' && gameBoard[i][j+1].getType() == 'O' &&
					 gameBoard[i][j+2].getType() == '*' && i == rowSize -1 ){
						//Checks whether there are two neighbor cells and adds cell in horizontal right side
						gameBoard[i][j+2].setType('O');
						return true;
					}
				}
				if(isLegalPos(i+1,j+2) && isLegalPos(i,j)){
					if(gameBoard[i][j].getType() == 'O' && gameBoard[i][j+1].getType() == 'O' &&
					 gameBoard[i][j+2].getType() == '*' && gameBoard[i+1][j+2].getType() != '*'){
						//Checks whether there are two neighbor cells and adds cell in horizontal right side
						gameBoard[i][j+2].setType('O');
						return true;
					}
				}
				if(isLegalPos(i,j+2) && isLegalPos(i,j)){
					if(gameBoard[i][j].getType() == 'O' && gameBoard[i][j+1].getType() == 'O' && 
						gameBoard[i][j+2].getType() != '*' && gameBoard[i][j-1].getType() == '*' && 
						i == rowSize - 1 ){
						//Checks whether there are two neighbor cells and adds cell in horizontal left side
						gameBoard[i][j-1].setType('O');
						return true;
					}
				}
				if(isLegalPos(i+1,j+2) && isLegalPos(i,j)){
					if(gameBoard[i][j].getType() == 'O' && gameBoard[i][j+1].getType() == 'O' && 
						gameBoard[i][j+2].getType() != '*' && gameBoard[i][j-1].getType() == '*' && 
						 gameBoard[i+1][j-1].getType() != '*'){
						//Checks whether there are two neighbor cells and adds cell in horizontal left side
						gameBoard[i][j-1].setType('O');
						return true;
					}
				}
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

	bool ConnectFourAbstract::isThree()
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
					if(isLegalPos(i,j+3) && isLegalPos(i,j)){
						if(gameBoard[i][j].getType() == 'O' && gameBoard[i][j+1].getType() == 'O' && 
							gameBoard[i][j+2].getType() == 'O' && gameBoard[i][j+3].getType() == '*' && i == rowSize -1 ){
							//Checks whether there are three neighbor cells and adds cell in horizontal right side
							gameBoard[i][j+3].setType('O');
							return true;
						}
					}
					if(isLegalPos(i+1,j+3) && isLegalPos(i,j)){
						if(gameBoard[i][j].getType() == 'O' && gameBoard[i][j+1].getType() == 'O' &&
						 gameBoard[i][j+2].getType() == 'O' && gameBoard[i][j+3].getType() == '*' && gameBoard[i+1][j+3].getType() != '*'){
							//Checks whether there are three neighbor cells and adds cell in horizontal right side
							gameBoard[i][j+3].setType('O');
							return true;
						}
					}
					if(isLegalPos(i,j+3) && isLegalPos(i,j)){
						if(gameBoard[i][j].getType() == 'O' && gameBoard[i][j+1].getType() == 'O' && 
							gameBoard[i][j+2].getType() == 'O'&& gameBoard[i][j+3].getType() != '*' && gameBoard[i][j-1].getType() == '*' && 
							i == rowSize - 1 ){
							//Checks whether there are three neighbor cells and adds cell in horizontal left side
							gameBoard[i][j-1].setType('O');
							return true;
						}
					}
					if(isLegalPos(i+1,j+3) && isLegalPos(i,j)){
						if(gameBoard[i][j].getType() == 'O' && gameBoard[i][j+1].getType() == 'O' && gameBoard[i][j+2].getType() == 'O' &&
							gameBoard[i][j+3].getType() != '*' && gameBoard[i][j-1].getType() == '*' && 
							 gameBoard[i+1][j-1].getType() != '*'){
							//Checks whether there are three neighbor cells and adds cell in horizontal left side
							gameBoard[i][j-1].setType('O');
							return true;
						}
					}
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

	bool ConnectFourAbstract::Defend3()
	{	
		//Like isThree function,checks whether there are three opponent's neighbor cells and adds computer's cell around cell
		 for(int i=rowSize - 1;i>=0;--i){
			for(int j=0;j<colSize;++j){
				if(isLegalPos(i,j+3)&& isLegalPos(i,j)){
					if(gameBoard[i][j].getType() == 'X' && gameBoard[i][j+1].getType() == 'X' && 
						gameBoard[i][j+2].getType() == 'X' && gameBoard[i][j+3].getType() == '*' && i == rowSize -1 ){
						//Checks whether there is a single cell and adds cell in horizontal right side
						gameBoard[i][j+3].setType('O');
						return true;
					}
				}
				if(isLegalPos(i+1,j+3)&& isLegalPos(i,j)){
					if(gameBoard[i][j].getType() == 'X' && gameBoard[i][j+1].getType() == 'X' && gameBoard[i][j+2].getType() == 'X'
						&& gameBoard[i][j+3].getType() == '*' && gameBoard[i+1][j+3].getType() != '*'){
						//Checks whether there is a single cell and adds cell in horizontal right side
						gameBoard[i][j+3].setType('O');
						return true;
					}
				}
				if(isLegalPos(i,j+3)&& isLegalPos(i,j)){
					if(gameBoard[i][j].getType() == 'X' && gameBoard[i][j+1].getType() == 'X' && gameBoard[i][j+2].getType() == 'X'
						&& gameBoard[i][j+3].getType() != '*' && gameBoard[i][j-1].getType() == '*' && i == rowSize - 1 ){
						//Checks whether there is a single cell and adds cell in horizontal left side
						gameBoard[i][j-1].setType('O');
						return true;
					}
				}
				if(isLegalPos(i+1,j+3)&& isLegalPos(i,j)){
					if(gameBoard[i][j].getType() == 'X' && gameBoard[i][j+1].getType() == 'X' && gameBoard[i][j+2].getType() == 'X'
						&&gameBoard[i][j+3].getType() != '*' && gameBoard[i][j-1].getType() == '*' && gameBoard[i+1][j-1].getType() != '*'){
						//Checks whether there is a single cell and adds cell in horizontal left side
						gameBoard[i][j-1].setType('O');
						return true;
					}
				}
				if(isLegalPos(i-3,j+3)&& isLegalPos(i,j)){
					if(gameBoard[i][j].getType() == 'X' && gameBoard[i-1][j+1].getType()== 'X' && gameBoard[i-2][j+2].getType()== 'X'
						&& gameBoard[i-3][j+3].getType()== '*' && gameBoard[i-2][j+3].getType()!= '*' && isLegalPos(i-3,j+3)){
						//Checks whether there are three neighbor cells and adds cell in right cross side
						return true;
					}
				}
				if(isLegalPos(i-3,j-3)&& isLegalPos(i,j)){
					if(gameBoard[i][j].getType() == 'X' && gameBoard[i-1][j-1].getType()== 'X' && gameBoard[i-2][j-2].getType()== 'X'
						&& gameBoard[i-3][j-3].getType()== '*' && gameBoard[i-2][j-3].getType()!= '*' && isLegalPos(i-3,j-3)){
						//Checks whether there are three neighbor cells and adds cell in left cross side
						return true;
					}
				}
			}
		}
		return false;
	}

	int ConnectFourAbstract::checkSave(const string &col,string &fileName)const{//Checks whether user input is SAVE or not

		const string str = "SAVE ";
		int status = 0,count = 0;

		for(int i=0,j = 0;i < col.length();++i){
			if(col[i] == str[i])
				++count;
			if(count == 5){//if first 5 characters are SAVE and space,the rest of string will be filename
				status = 1;
				fileName += col[i+1];
				++j;
			}
		}

		return status;
	}


	int ConnectFourAbstract::checkLoad(const string &col,string &fileName)const{//Checks whether user input is LOAD or not

		const string str = "LOAD ";
		int status = 0,count = 0;

		for(int i=0;i < col.length();++i){
			if(col[i] == str[i])
				++count;
			if(count == 5){//if first 5 characters are LOAD and space,the rest of string will be filename
				status = 1;
				fileName += col[i+1];
			}
		}

		return status;
	}

	int ConnectFourAbstract::saveBoard(const string &fileName)const{
		
		int status = 0;
		ofstream myfile;
	  	myfile.open(fileName);
	 
	 	if(myfile){
	 		//Writes the current board's size,game type and sequence to file
		  	myfile<<rowSize<<' '<<colSize<<endl;	
		  	myfile<<gameType<<endl;	
		  	myfile<<player<<endl;
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

	int ConnectFourAbstract::loadBoard(const string &fileName){

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

	void ConnectFourAbstract::gameMenu(char &gameChoice)
	{	

		int tempRow,tempCol;

		cout<<"Please enter the height of the board:"<<endl;//Takes board's height and width
		cin>>tempRow;
		if(cin.fail()){
			cin.clear();
			cin.ignore();
		}
		cout<<"Please enter the width of the board:"<<endl;
		cin>>tempCol;
		
		while(cin.fail() || !isLegalSize(tempRow,tempCol)){//Checks input types and it is legal
			cin.clear();
			cin.ignore();
			cerr<<"Wrong size! Please enter a width and height between 4-27:"<<endl;
			cin>>tempRow;
			cin>>tempCol;
		}
		setSize(tempRow,tempCol);
		resizeBoard();//Prepares the board for a new game and resize the board
		
		cout<<"Press 'P' to play two players"<<endl;
		cout<<"Press 'C' to play with computer"<<endl;
		cin>>gameChoice;

		while(gameChoice != 'P' && gameChoice != 'C'){
			cerr<<"Wrong gameChoice.Please choose 'P' or 'C':"<<endl;
			cin>>gameChoice;
		}

		if(gameChoice == 'P')
			setGame(1);//Set game PvP
		else
			setGame(2);//Set game PvC

		statusEnd = 0;//The game is not ended
	}


	void ConnectFourAbstract::continueGame(){

	    key = 1;
	    char column;

		cout<<"Saved game is loading......"<<endl;
		printBoard();

		while(!isBoardFull()){
			if(gameType == 1){//Checks the game type is PvP
				if(player == 1 ){//Checks the sequence
					isComputer = 0;
					if(play(column))//if player's input is load,terminates current game
						return;
					if(checkAll()) //Checks after all inputs
						break;
					printBoard();
					setPlayer(2);
				}
				if(player == 2){
					if(play(column))
						return;
					
					if(checkAll())
						break;
					printBoard();
					setPlayer(1);
				}
			}
			else if(gameType == 2){//Checks the game type is PvC
				setPlayer(1);
				if(play(column))
					return;
				printBoard();

				key = 0;//Indıcates that move is not first move
				if(play())
					break;
				printBoard();
			}	
		}
	}
	void ConnectFourAbstract::playGame()
	{	
		char gameChoice,column;
		key = 1;

		for(int i = 0; i < rowSize; ++i)//Deallocates the 5x5 places that allocated by default constructor
		    delete[] gameBoard[i];   
		delete[] gameBoard;

		gameMenu(gameChoice);
		printBoard();
		
		cin.ignore();
		while(!isBoardFull()){;
			if(gameChoice == 'P'){
				setGame(1);		//Sequence of user1 in PvP game
				setPlayer(1);
				if(play(column))
					return;
			}
			else{
				setGame(2);		//Sequence of user1 in PvC game
				setPlayer(1);
				if(play(column))
					return;
			}
			isComputer = 0;
			if(checkAll()) //Checks after all inputs
				break;
			printBoard();

			if(gameChoice == 'P'){//if game is PvP,player2 will be user
				setGame(1);
				setPlayer(2);
				if(play(column))
					return;
		
				isComputer = 0;//Indıcates this player is not a computer
				if(checkAll())
					break;
			}
			else{
				if(play())	//Sequences of computer
					break;
				key = 0;
			}
			printBoard();
		}
	}
}
