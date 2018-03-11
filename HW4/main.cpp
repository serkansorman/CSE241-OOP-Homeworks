#include<iostream>
#include<fstream>
#include<string>

using namespace std;

typedef enum{
	empty,
	user1,
	user2,
	computer,
	connectedX,
	connectedO
}cellType;

class ConnectFour{
	
	class Cell{//Includes information of every cells in board
		public:
			Cell();
			Cell(char newType);
			Cell(int newRow,int newPos,char newType);
		
			inline void setType(char token){type = token;}//Set the cell's type
			inline char getType()const {return type;}//Access the cell's type
			bool operator == (const Cell &cell)const;//Compare two cells
			const Cell operator ++(int );//postfix increment.Changes the cell's type
			const Cell operator --(int );//postfix decrement.Changes the cell's type in opposite direction
			const Cell operator ++(); //prefix increment.Changes the cell's type
			const Cell operator --(); //prefix decrement.Changes the cell's type in opposite direction
			friend ostream &operator<<(ostream &out,const Cell &cell);//Overloads the insertion operator for Cell's member
			friend istream &operator>>(istream &in,Cell &cell);//Overloads the extraction operator for Cell's member
		private:
			char position;
			int row;
			char type;//Includes information of cells:Empty,User1,User2(or computer)
			cellType cell;//The variable used for distinguish between User2('O') and computer('O')
	};
	public:
		ConnectFour();
		ConnectFour(int newRow,int newCol);
		ConnectFour(const string &fileName);//Take filename and creates a board.
		ConnectFour(const ConnectFour &game);//Copy constructor
		~ConnectFour();//Deallocates the places that allocated for board before

		inline int getRow() const {return rowSize;}//Access the height of current board
		inline int getCol() const {return colSize;}//Access the width of current board
		inline int getStatus() const {return statusEnd;}//Access the control of end game

		void gameMenu(char &gameChoice);//Ask user height and width,game type
		void playGame();//Plays PvP or PvC in single game
		int playMode2();//Plays multi game simultaneously
		bool isEnd()const;// Checks both is board full and any players win
		
		bool operator == (const ConnectFour &game)const;//Compare two game
		bool operator != (const ConnectFour &game)const;
		const ConnectFour &operator = (const ConnectFour &game);//Assigns game to another game
		friend ostream &operator<<(ostream &out,const Cell &cell);
		friend istream &operator>>(istream &in, Cell &cell);
	private:
		int rowSize;
		int colSize;
		int key;//Indıcates whether computer's move is first or not
		int player;//Indıcates sequence
		char gameMode;//Indicates single or multi
		int gameType;//Indicates PvP or PvC
		int isComputer;//Whether computer's sequence or not
		int statusEnd;//Indicates are there any ended games in all games
		Cell **gameBoard;//Board of the game
		static int livingCells;
		static int getLivingCells();//Returns number of played cells in all games
		void setSize(int row,int col);//Set the height and width
		void setGame(int game);//Set the game types are PvP or PvC(1 pvp 2 pvc)
		void setPlayer(int sequence);//Set the current player
		void resizeBoard(); // Creates a board and fills the board with empty cells
		
		bool isLegalCol(int colNum) const;// Checks whether the user's input column is on board
		bool isLegalPos(int CoordX,int CoordY) const;// Checks the coordinates on the board is legal
		bool isColFull(int colNum) const ;//Checks whether the selected column is full
		bool isBoardFull() const;//Checks whether there is a empty cell in the game board
		
		int getCurrentLiving() const;//Returns number of total living cells in current object
		int inputCol(char column);//Take input column from user1 or user2
		bool play();//Plays the computer
		bool play(char position);//Plays the user
		void putLetter(int colNum);//In the PvP game, the moves made by the players are placed on the board.

		bool checkHorizon();//Checks whether the four same cells are neighbor horizontally
		bool checkVertical();//Checks whether the four same cells are neighbor horizontally vertically 
		bool checkDiaRight();//Checks whether the four same cells are neighbor in right cross
		bool checkDiaLeft() ;//Checks whether the four same cells are neighbor in left cross 
		bool checkAll();// Checks every position for finding four neighbor cells

		bool defaultOne();//if there are not any neighbor cells to move,moves to empty column
		bool isOne();//Adds a neighbor cell to a single cell of the computer
		bool isOneVertical();//Adds a neighbor cell to a single cell of the computer vertically
		bool isTwoVertical();//Adds a neighbor cell to two cells of the computer vertically
		bool isThreeVertical();//Adds a neighbor cell to three cells of the computer vertically
		bool defend3Vertical();//Defends itself from three neighbors cells
		bool isTwo();//Adds a neighbor cell to two cells of the computer
		bool isThree();//Adds a neighbor cell to three cells of the computer
		bool Defend3();//Prevents the opponent from winning by preventing four same cells from coming together
		
		int checkSave(const string &col,string &fileName)const;//Checks whether the user's input is SAVE
		int checkLoad(const string &col,string &fileName)const;//Checks whether the user's input is LOAD
		int saveBoard(const string &fileName)const;//Saves the current board,player,size,living cells and game type to file
		int loadBoard(const string &fileName);//Read file and loads the saved game 
		void printBoard() const;// Print current game board

		void continueGame();//Continues the game  after loading the board
		void initBoard(const string &fileName);//Take filename and creates a board.
};

int ConnectFour::livingCells = 0;
string getboardName();//Global function for taking input from user in main


string getboardName(){//Takes board name from user

	string str;

	cin.ignore();
	cout<<"Please enter board you want to play:"<<endl;
	getline(cin,str);

	return str;

}

ConnectFour::ConnectFour(){//The no parameter constructor creates a 5x5 game board

	Cell c;			//Creates a Cell object for fill the board with this object
	c.setType('*'); //Sets the cell type for each cell 

	rowSize = 5;
	colSize = 5;

    gameBoard = new Cell *[rowSize];

	for(int i=0;i<5;++i)
		gameBoard[i] = new Cell [colSize];

	for(int i=0;i<rowSize;i++)//fills the board with  Cell object
	    for(int j=0;j<colSize;j++)
	    	gameBoard[i][j] = c;
}

ConnectFour::ConnectFour(int newRow,int newCol){//Takes number of rows and columns as parameters and creates game

	Cell c;			//Creates a Cell object for fill the board with this object
	c.setType('*'); //Sets the cell type for each cell 

	rowSize = newRow;
	colSize = newCol;

	gameBoard = new Cell *[rowSize];

	for(int i=0;i<newRow;++i)
		gameBoard[i] = new Cell [colSize];

	for(int i=0;i<rowSize;i++)//fills the board with  Cell object
	    for(int j=0;j<colSize;j++)
	    	gameBoard[i][j] = c;
}


ConnectFour::ConnectFour(const string &fileName){//Take filename and call initBoard and it creates a board.

	initBoard(fileName);

}

ConnectFour::ConnectFour(const ConnectFour &game){//Copy constructor

	//Copies the  parameter object's members to the new object;
	rowSize = game.rowSize;
	colSize = game.colSize;
	gameMode = game.gameMode;
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

ConnectFour::~ConnectFour(){

	for(int i = 0; i < rowSize; ++i)//Deallocates the places that allocated for board before
	    delete[] gameBoard[i];   

	delete[] gameBoard;
 }

ConnectFour::Cell::Cell(){//Creates a default cell
	position = 'A';
	row = 0;
	type = '*';
}
ConnectFour::Cell::Cell(char newType){//Take single paramater for construct type of Cell class
	type = newType;
}

ConnectFour::Cell::Cell(int newRow,int newPos,char newType){ //Take single paramater for construct Cell class
	row = newRow;
	position = newPos;
	type = newType;
}


void ConnectFour::setGame(int game){//Set the game type (PvP = 1,PvC = 2)
	gameType = game;
}

void ConnectFour::setPlayer(int sequence){//Indıcates sequence
	player = sequence;
}

void ConnectFour::setSize(int row,int col){
	rowSize = row;
	colSize = col;
}

ostream &operator<<(ostream &out,const ConnectFour::Cell &cell){//Shows the coordinates and types of cell
	out<<"Height:"<<cell.row<<endl;
	out<<"Width:"<<cell.position<<endl;
	out<<"Type of cell:"<<cell.type<<endl;

	return out;
}

istream &operator>>(istream &in,ConnectFour::Cell &cell){//Takes the coordinates and types for cell

	in>>cell.row;
	in>>cell.position;
	in>>cell.type;

	return in;

}

bool ConnectFour::Cell::operator == (const Cell &cell)const{//Checks whether two cells are same or not
	return(row == cell.row &&
		   position == cell.position &&
		   type == cell.type); 
}

const ConnectFour::Cell ConnectFour::Cell::operator ++(int ignore){

	Cell temp;
	temp.cell = cell;	//Create a temporary cell object  

	if(cell == empty)//Changes the cell type
		cell = user1;
	else if(cell == user1)
		cell = user2;
	else if(cell == user2)
		cell = computer;
	else if(cell == computer)
		cell = empty;

	return temp; //Returns first state of cell(before increment)

}
const ConnectFour::Cell ConnectFour::Cell::operator --(int ignore){

	Cell temp;
	temp.cell = cell; //Create a temporary cell object and 

	if(cell == empty) //Changes the cell type in oppesite direction
		cell = computer;
	else if(cell == computer)
		cell = user2;
	else if(cell == user2)
		cell = user1;
	else if(cell == user1)
		cell = empty;

	return temp;//Returns first state of cell(before decrement)

}
const ConnectFour::Cell ConnectFour::Cell::operator ++(){

	if(cell == empty) //Changes the cell type
		cell = user1;
	else if(cell == user1)
		cell = user2;
	else if(cell == user2)
		cell = computer;
	else if(cell == computer)
		cell = empty;

	return *this;//Returns last state of cell(after increment)
}

const ConnectFour::Cell ConnectFour::Cell::operator --(){

	if(cell == empty) //Changes the cell type in oppesite direction
		cell = computer;
	else if(cell == computer)
		cell = user2;
	else if(cell == user2)
		cell = user1;
	else if(cell == user1)
		cell = empty;

	return *this;//Returns last state of cell(after decrement)
}


bool ConnectFour::operator == (const ConnectFour &game)const{
	
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

bool ConnectFour::operator != (const ConnectFour &game)const{

	return ! (game == *this);//Compare whether two cells are different or not
}

const ConnectFour &ConnectFour::operator = (const ConnectFour &game){

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
		gameMode = game.gameMode;
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

void ConnectFour::initBoard(const string &fileName){

	ifstream myfile;
	int maxWidth;

  	myfile.open(fileName);
  	string line;

	if(myfile){
	  	
	  	getline(myfile,line);	//Finds the maximum width in board
	  	maxWidth = line.length();

	  	int rowNum=0;
	  	while(getline(myfile,line)){//Reads until the end of file
	  		if(line.length()>maxWidth)
	  			maxWidth = line.length();
	  		++rowNum; //Finds the number of row in board
	  	}
	  	setSize(rowNum+1,maxWidth); //Sets the height and width of the board
	  	myfile.close();

	  	gameBoard = new Cell *[rowSize]; //Allocates memory according to row number of board
	  	for(int i =0;i<rowSize;i++)//Allocates memmory according to max width and creates a rectangle board
	  		gameBoard[i] = new Cell [colSize];

	  	myfile.open(fileName); //Reopen the file

	  	for(int i =0;i<rowSize;i++){
	  		getline(myfile,line);	//Takes each line of file
	  		for(int j=0;j<colSize;j++)
	  			gameBoard[i][j].setType(line[j]);//Puts each elements of line to gameBoard.Game board is now ready
	  	}
		myfile.close();	
	}
	else{
		cout<<"File can not found"<<endl;//if file is not exist,exit from the game
		exit(1);
	}

}


void ConnectFour::resizeBoard(){//Resize the board according to new row and column number

	Cell c;
	
	gameBoard = new Cell *[rowSize];
	
	for(int i=0;i<rowSize;++i)
		gameBoard[i] = new Cell [colSize];

	for(int i=0;i<rowSize;i++)//fills the board with  Cell object
	    for(int j=0;j<colSize;j++)
	    	gameBoard[i][j] = c;
}

bool ConnectFour::isLegalPos(int CoordX,int CoordY) const
{
	if(CoordX >=0 && CoordX< rowSize && CoordY >= 0 && CoordY<colSize) // Prevents reach out of matrix
		return true;
	else
		return false;
}


bool ConnectFour::isLegalCol(int colNum) const{
	if(colNum <colSize && colNum >= 0)//Check whether the column is on the board
		return true;
	else
		return false;
}

bool ConnectFour::isColFull(int colNum)const{
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

bool ConnectFour::isBoardFull()const{
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


bool ConnectFour::isEnd()const{//Checks board is full or game ended
	if(isBoardFull() || statusEnd)
		return true;
	else
		return false;
}


void ConnectFour::printBoard() const{

	for(int i=0;i<colSize;i++)
		cout<<static_cast<char>('A'+i)<<"  ";  //Prints letters row
	cout<<endl;

	for(int i=0;i<rowSize;i++){
	    for(int j=0;j<colSize;j++)
	        	cout<<gameBoard[i][j].getType()<<"  ";
	    cout<<endl<<endl;
	}
}



void ConnectFour::putLetter(int colNum)
{
	for(int i=rowSize - 1;i>=0;--i){
		for(int j=colSize - 1;j>=0;--j){
			if(j == colNum && gameBoard[i][j].getType() == '*' && player == 1){// Puts 'X' Or 'O' according to current player
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

int ConnectFour::getCurrentLiving() const{

	int count = 0;

	for(int i=getRow() - 1;i>=0;--i){
		for(int j=getCol() - 1;j>=0;--j){
			if(gameBoard[i][j].getType() == 'X' || gameBoard[i][j].getType() == 'O')
				//Counts the current filled cell on board
				++count;
		}
	}
	return count;

}

int ConnectFour::inputCol(char column)
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

bool ConnectFour::play(char position){
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

bool ConnectFour::play(){
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

bool ConnectFour::checkHorizon()
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



bool ConnectFour::checkVertical()
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

bool ConnectFour::checkDiaRight()
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


bool ConnectFour::checkDiaLeft()
{
	for(int i=rowSize - 1;i>=0;--i){
		for(int j=0;j<colSize;++j){
			if(isLegalPos(i-1,j-1) && isLegalPos(i-2,j-2) && isLegalPos(i-3,j-3)){
				if( (gameBoard[i][j].getType() == 'X' && gameBoard[i-1][j-1].getType() == 'X'
					 && gameBoard[i-2][j-2].getType() == 'X' && gameBoard[i-3][j-3].getType() == 'X') ||

					(gameBoard[i][j].getType() == 'O' && gameBoard[i-1][j-1].getType() == 'O'
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

bool ConnectFour::checkAll()
{	
	if(checkHorizon()  || // Checks all positions
	   checkVertical() || 
	   checkDiaLeft()  ||
	   checkDiaRight()){

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


bool ConnectFour::isOneVertical(){
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

bool ConnectFour::isTwoVertical(){
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


bool ConnectFour::isThreeVertical(){
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

bool ConnectFour::defend3Vertical(){
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

bool ConnectFour::defaultOne()
{
	for(int i=rowSize - 1;i>=0;--i){ // if there arent any neighbor,moves '*' column
		for(int j=0;j<colSize;++j){
			if(gameBoard[i][j].getType() == '*'){
				gameBoard[i][j].setType('O');
				return true;
			}
		}
	}

	return true;	
}

bool ConnectFour::isOne()
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

bool ConnectFour::isTwo()
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

bool ConnectFour::isThree()
{
	if(key){ //First move
		if(gameBoard[rowSize - 1][colSize/2].getType()== '*')
			gameBoard[rowSize - 1][colSize/2].setType('O');
		else
			gameBoard[rowSize - 1][(colSize/2)-1].setType('O');
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

bool ConnectFour::Defend3()
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

int ConnectFour::checkSave(const string &col,string &fileName)const{

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


int ConnectFour::checkLoad(const string &col,string &fileName)const{

	const string str = "LOAD ";
	int status = 0,count = 0;

	for(int i=0,j = 0;i < col.length();++i){
		if(col[i] == str[i])
			++count;
		if(count == 5){//if first 5 characters are LOAD and space,the rest of string will be filename
			status = 1;
			fileName += col[i+1];
			++j;
		}
	}

	return status;
}

int ConnectFour::saveBoard(const string &fileName)const{
	
	int status = 0;
	ofstream myfile;
  	myfile.open(fileName);
 
 	if(myfile){
 		//Writes the current board's size,living cells,game type and sequence to file
	  	myfile<<rowSize<<' '<<colSize<<endl;	
	  	myfile<<gameType<<endl;	
	  	myfile<<player<<endl;
	  	myfile<<livingCells<<endl;
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

int ConnectFour::loadBoard(const string &fileName){

	int status = 0,tempLiving = 0,currLive = 0;
	ifstream myfile;
  	myfile.open(fileName);

  	currLive = getCurrentLiving();

  	if(myfile){
  		
  		for(int i = 0; i < rowSize; ++i)//Deallocates old games board
		    delete[] gameBoard[i];   
		delete[] gameBoard;
		
		//Reads the  board's size,living cells,game type and sequence from file
	  	myfile>>rowSize>>colSize;	
	  	myfile>>gameType;	
	  	myfile>>player;

	  	if(gameMode == 'M'){
	  		myfile>>tempLiving;
	  		livingCells = tempLiving + livingCells -currLive;//Calculates the sum of current living cells
	  	}
	  	else
	  		myfile>>livingCells;
	  		
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

void ConnectFour::gameMenu(char &gameChoice)
{	
	
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

int ConnectFour::getLivingCells(){
	return livingCells;
}

void ConnectFour::continueGame(){

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
				++livingCells;
				printBoard();
				setPlayer(2);
			}
			if(player == 2){
				if(play(column))
					return;
				++livingCells;
				
				if(checkAll())
					break;
				printBoard();
				setPlayer(1);
				cout<<"Living cells:"<<livingCells<<endl;
			}

			if(gameMode == 'M')//if game mode Multi game after load,game will turn the multi game
				break;
		}
		else if(gameType == 2){//Checks the game type is PvC
			setPlayer(1);
			if(play(column))
				return;
			++livingCells;
			printBoard();

			key = 0;//Indıcates that move is not first move
			if(play())
				break;
			++livingCells;
			printBoard();
			cout<<"Living cells:"<<livingCells<<endl;
			if(gameMode == 'M')
				break;
		}	
	}
}
void ConnectFour::playGame()
{	
	char gameChoice,column;
	key = 1;

	for(int i = 0; i < rowSize; ++i)//Deallocates the 5x5 places that allocated by default constructor
	    delete[] gameBoard[i];   
	delete[] gameBoard;

	initBoard(getboardName());
	gameMenu(gameChoice);
	printBoard();
	gameMode ='S';	
	
	cin.ignore();
	while(!isBoardFull()){;
		if(gameChoice == 'P'){
			setGame(1);		//Sequence of user1 in PvP game
			setPlayer(1);
			if(play(column))
				return;
			++livingCells;
		}
		else{
			setGame(2);		//Sequence of user1 in PvC game
			setPlayer(1);
			if(play(column))
				return;
			++livingCells;
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
			++livingCells;
	
			isComputer = 0;//Indıcates this player is not a computer
			if(checkAll())
				break;
		}
		else{
			if(play())	//Sequences of computer
				break;
			++livingCells;
			key = 0;
		}
		printBoard();
		cout<<"Living cells:"<<livingCells<<endl;
	}
}

int ConnectFour::playMode2(){// Plays the game in two steps

	key = 1;
    char column;

	printBoard();
	setPlayer(1);//Sequence of player 1
	gameMode ='M';

	cin.ignore();
	if(gameType == 1){//Checks the game type is PvP
		if(play(column))//if player's input is load,terminates current game
			return 0;
		++livingCells;
		isComputer = 0;
		if(checkAll()){ //Checks after all inputs
			statusEnd = 1;
			return 1;
		}
		printBoard();
		setPlayer(2);

		if(play(column))//if player's input is load,terminates current game
			return 0;
		++livingCells;

		if(checkAll()){ //Checks after all inputs
			statusEnd = 1;
			return 1;
		}
		printBoard();
	}
	else if(gameType == 2){//Checks the game type is PvC
		if(play(column))
			return 0;
		++livingCells;
		if(checkAll()) //Checks after all inputs
			statusEnd = 1;
		printBoard();

		key = 0;//Indıcates that move is not first move
		if(play())
			return 1;
		++livingCells;
		printBoard();
	}
	cout<<"Living cells:"<<livingCells<<endl;
}
	
int main(){

	char modeChoice;

	while(modeChoice != 'S' && modeChoice != 'M'){//Take inputs for the game mode
		cout<<"Choose the game mode 'S' or 'M':"<<endl;
		cin>>modeChoice;
	}

	if(modeChoice == 'M'){

		char gameChoice;
		int object;

		//Creates a board for each game and takes all necassary inputs for all games
		
		ConnectFour game1(getboardName());
		game1.gameMenu(gameChoice);

		ConnectFour game2(getboardName());
		game2.gameMenu(gameChoice);

		ConnectFour game3(getboardName());
		game3.gameMenu(gameChoice);

		ConnectFour game4(getboardName());
		game4.gameMenu(gameChoice);

		ConnectFour game5(getboardName());
		game5.gameMenu(gameChoice);

		//Until all games are finished the game continues
		while(!(game1.isEnd()) || !(game2.isEnd()) || !(game3.isEnd())
			 || !(game4.isEnd()) || !(game5.isEnd())){

			cout<<"Choose a object:"<<endl;
			cin>>object;

			if(cin.fail()){
				cin.clear();
				cin.ignore();
			}
			if(object == 1 && !(game1.isEnd()))//if current game is not ended and object is selected,plays this game
				game1.playMode2();
			else if(object == 2 && !(game2.isEnd()))
				game2.playMode2();
			else if(object == 3 && !(game3.isEnd()))
				game3.playMode2();
			else if(object == 4 && !(game4.isEnd()))
				game4.playMode2();
			else if(object == 5 && !(game5.isEnd()))
				game5.playMode2();
			else if(!(object >= 1) || !(object <= 5))
				cout<<"Wrong choice,try again"<<endl;
			else
				cout<<"This game has already finished,please choose another one."<<endl;

			if(game1 == game2)//Compare two games
				cout<<"Game 1 is equal to Game 2."<<endl;
			else if(game1 != game2)
				cout<<"Game 1 is different from Game 2."<<endl;		
		}
		cout<<"All games are finished."<<endl;	
	}
	else{
		ConnectFour game;
		game.playGame();//Begins single game.PvP or PvC
	}
	
	return 0;
}
