#include<iostream>
#include<vector>
#include<fstream>
#include<string>

using namespace std;


class ConnectFour{
	
	class Cell{//Includes information of every cells in board
		public:
			Cell();
			Cell(const int &newPos);
			Cell(const int &newRow,const int &newPos);
			inline void setType(const char &token) {type = token;}//Set the cell's type
			inline char getType()const {return type;}//Access the cell's type
		private:
			char position;
			int row;
			char type;//Includes information of cells:Empty,User1,User2(or computer)
	};
	public:
		//Constructs new game
		ConnectFour();
		ConnectFour(const int &newRow);
		ConnectFour(const int &newRow,const int &newCol);
		void gameMenu(char &gameChoice);//Ask user height and width,game type
		void playGame();//Plays PvP or PvC in one game
		int playMode2();//Plays multi game simultaneously
		bool isEnd()const;// Checks both is board full and any players win
		bool CompareObj(const ConnectFour &game) const; //Compare two game.The case of the draw game did not take into account
	private:
		int rowSize;
		int colSize;
		int key;//Indıcates whether computer's move is first or not
		int player;
		char gameMode;//Indicates single or multi
		int gameType;//Indicates PvP or PvC
		int isComputer;//Whether computer's sequence or not
		int statusEnd;//Indicates are there any endede games in all games
		static int livingCells;
		vector< vector<Cell> > gameCells;//Board of the game
		void initBoard(); // Creates a board and fills the board with empty cells
		void printBoard() const;// Print current game board

		void setSize(const int &row,const int &col);//Set the height and width
		void setGame(const int &game);//Set the game types are PvP or PvC
		void setPlayer(const int &sequence);//Set the current player

		inline int getRow() const {return rowSize;}//Access the height of current board
		inline int getCol() const {return colSize;}//Access the width of current board
		inline int getStatus() const {return statusEnd;}//Access the control of end game

		bool isLegalSize(const int &row,const int &col) const; // Checks whether the user's input height and width are legal
		bool isLegalCol(const int &colNum) const;// Checks whether the user's input column is on board
		bool isLegalPos(const int &CoordX,const int &CoordY) const;// Checks the coordinates on the board is legal
		bool isColFull(const int &colNum) const ;//Checks whether the selected column is full
		bool isBoardFull() const;//Checks whether there is a empty cell in the game board
		
		int getCurrentLiving() const;//Returns number of total living cells in current object

		int inputCol(const char &column);//Take input column from user1 or user2
		bool play();//Plays the computer
		bool play(const char &position);//Plays the user
		void putLetter(const int &colNum);//In the PvP game, the moves made by the players are placed on the board.

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
		bool compareVertical(const ConnectFour &game) const;//Compare two game vertically acccording to three neighbor cells
		
		int checkSave(const string &col,string &fileName)const;//Checks whether the user's input is SAVE
		int checkLoad(const string &col,string &fileName)const;//Checks whether the user's input is LOAD
		int saveBoard(const string &fileName)const;//Saves the current board,player,size,living cells and game type to file
		int loadBoard(const string &fileName);//Read file and loads the saved game 

		void continueGame();//Continues the game  after loading the board
		static int getLivingCells();//Returns number of played cells in all games
};

int ConnectFour::livingCells = 0;

ConnectFour::ConnectFour(){
	colSize = 0;
	rowSize = 0;
}

ConnectFour::ConnectFour(const int &newRow){
	rowSize = newRow;
}

ConnectFour::ConnectFour(const int &newRow,const int &newCol){
	rowSize = newRow;
	colSize = newCol;
}

ConnectFour::Cell::Cell(){
	position = 'A';
	row = 0;
}
ConnectFour::Cell::Cell(const int &newPos){
	position = newPos;
}

ConnectFour::Cell::Cell(const int &newRow,const int &newPos){
	row = newRow;
	position = newPos;
}

void ConnectFour::setGame(const int &game){
	gameType = game;
}

void ConnectFour::setPlayer(const int &sequence){
	player = sequence;
}

void ConnectFour::setSize(const int &row,const int &col){
	rowSize = row;
	colSize = col;
}

void ConnectFour::initBoard(){

	Cell c;			//Create a object which types is cell and fill the vector with this object
	c.setType('.');

	for(int i=0;i<rowSize;i++){
	    gameCells.push_back(vector<Cell>());
	    for(int j=0;j<colSize;j++){   
	        gameCells[i].push_back(c);
	    }
	}

}

bool ConnectFour::isLegalPos(const int &CoordX,const int &CoordY) const
{
	if(CoordX >=0 && CoordX< rowSize && CoordY >= 0 && CoordY<colSize) // Prevents reach out of matrix
		return true;
	else
		return false;
}

bool ConnectFour::isLegalSize(const int &row,const int &col) const {
	if(row >= 4 && row < 27 && col >= 4 && col < 27){
		return true;
	}
	else
		return false;
}

bool ConnectFour::isLegalCol(const int &colNum) const{
	if(colNum <colSize && colNum >= 0)
		return true;
	else
		return false;
}

bool ConnectFour::isColFull(const int &colNum)const{
	int a = 0;

	for(int i=rowSize - 1;i>=0;--i){
		for(int j=colSize - 1;j>=0;--j){
			if(j == colNum && gameCells[i][j].getType() != '.')
				a++;	
		}
	}
	if(a == rowSize)	
		return false;
	else
		return true;
}

bool ConnectFour::isBoardFull()const{
	int a = 0;

	for(int i=rowSize - 1;i>=0;--i){
		for(int j=colSize - 1;j>=0;--j){
			if(gameCells[i][j].getType() != '.')
				a++;
		}
	}

	if(a == rowSize * colSize){ // if there is not empty column to continue game,the game will end in a draw.
		cout<<"The game ended in a draw."<<endl;
		return true;
	}
	else
		return false;
}


bool ConnectFour::isEnd()const{
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
	    for(int j=0;j<colSize;j++){ 
	        cout<<gameCells[i][j].getType()<<"  ";
	    }
	    cout<<endl<<endl;
	}
}



void ConnectFour::putLetter(const int &colNum)
{
	for(int i=rowSize - 1;i>=0;--i){
		for(int j=colSize - 1;j>=0;--j){
			if(j == colNum && gameCells[i][j].getType() == '.' && player == 1){// Puts 'X' Or 'O' according to current player
				gameCells[i][j].setType('X');
				return;
			}
			else if(j == colNum && gameCells[i][j].getType() == '.' && player == 2){
				gameCells[i][j].setType('O');
				return;
			}
		}
	}
}

int ConnectFour::getCurrentLiving() const{

	int count = 0;

	for(int i=getRow() - 1;i>=0;--i){
		for(int j=getCol() - 1;j>=0;--j){
			if(gameCells[i][j].getType() != '.')
				++count;
		}
	}
	return count;

}

int ConnectFour::inputCol(const char &column)
{
	string col,fileName;
	int colNum = 0;

	cout<<"Player " <<player<< " turn => Choose a column:"; //Indicates who is next
	getline(cin,col);

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

bool ConnectFour::play(const char &position){
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
	isComputer = 1;
	if(checkAll()){
		statusEnd = 1;
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
			if((gameCells[i][j].getType() == 'X' && player == 1) || (gameCells[i][j].getType() == 'O' && player == 2))
				++count; // Counts same cells horizontally
			else
				count = 0;
			if(count == 4){	// if there are four same neighbor cells
				for(int a=0;a<4;a++){ // Converts them small case x or o
					if(player == 1)
						gameCells[i][j-a].setType('x');
					else
						gameCells[i][j-a].setType('o');
							
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
				if((gameCells[j][i].getType() == 'X' && player == 1) || (gameCells[j][i].getType() == 'O' && player == 2))
					++count; // Counts same cells vertically
				else
					count = 0;
				if(count == 4){ // if there are four same neighbor cells
					for(int a=0;a<4;a++){ // Converts them small case x or o
						if(player == 1)
							gameCells[j+a][i].setType('x');
						else
							gameCells[j+a][i].setType('o');
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
				if( (gameCells[i][j].getType() == 'X' && gameCells[i-1][j+1].getType() == 'X'
					 && gameCells[i-2][j+2].getType() == 'X' && gameCells[i-3][j+3].getType() == 'X') ||

					(gameCells[i][j].getType() == 'O' && gameCells[i-1][j+1].getType() == 'O'
					 && gameCells[i-2][j+2].getType() == 'O' && gameCells[i-3][j+3].getType() == 'O')){	
					for(int b=0;b<4;++b){ // if there are four same neighbor cells in right cross,converts them small case x or o
						if(player == 1)
						gameCells[i-b][j+b].setType('x');
						else
							gameCells[i-b][j+b].setType('o');
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
				if( (gameCells[i][j].getType() == 'X' && gameCells[i-1][j-1].getType() == 'X'
					 && gameCells[i-2][j-2].getType() == 'X' && gameCells[i-3][j-3].getType() == 'X') ||

					(gameCells[i][j].getType() == 'O' && gameCells[i-1][j-1].getType() == 'O'
					 && gameCells[i-2][j-2].getType() == 'O' && gameCells[i-3][j-3].getType() == 'O')){	
					for(int b=0;b<4;++b){ // if there are four same neighbor cells in right cross,converts them small case x or o
						if(player == 1)
						gameCells[i-b][j-b].setType('x');
						else
							gameCells[i-b][j-b].setType('o');
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

		if(player != 3)
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
				if(gameCells[j][i].getType() == 'O' && gameCells[j-1][i].getType() == '.'){
					//Checks whether there is a single cell and adds cell vertically
					gameCells[j-1][i].setType('O');
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
				if(gameCells[j][i].getType() == 'O' && gameCells[j-1][i].getType() == 'O' && gameCells[j-2][i].getType() == '.' ){
					//Checks whether there are two neigbor cells and adds cell vertically
					gameCells[j-2][i].setType('O');
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
				if(gameCells[j][i].getType() == 'O' && gameCells[j-1][i].getType() == 'O'  && gameCells[j-2][i].getType() == 'O' && gameCells[j-3][i].getType() == '.' ){
					//Checks whether there are three neigbor cell and adds cell vertically
					gameCells[j-3][i].setType('O');
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
				if(gameCells[j][i].getType() == 'X' && gameCells[j-1][i].getType() == 'X'  && gameCells[j-2][i].getType() == 'X' && gameCells[j-3][i].getType() == '.' ){
					//Checks whether there are three neighbor opponent's cell and adds 'X' vertically
					gameCells[j-3][i].setType('O');
				return true;
				}
			}
		}
	}
	return false;
}

bool ConnectFour::defaultOne()
{
	for(int i=rowSize - 1;i>=0;--i){ // if there arent any neighbor,moves '.' column
		for(int j=0;j<colSize;++j){
			if(gameCells[i][j].getType() == '.'){
				gameCells[i][j].setType('O');
				return true;
			}
		}
	}	
}

bool ConnectFour::isOne()
{
	for(int i=rowSize - 1;i>=0;--i){
		for(int j=0;j<colSize;++j){
			if(isLegalPos(i,j+1) && isLegalPos(i,j)){
				if(gameCells[i][j].getType() == 'O' && gameCells[i][j+1].getType() == '.'
				 &&  i == rowSize -1){
					//Checks whether there is a single cell and adds cell in horizontal right side
					gameCells[i][j+1].setType('O');
					return true;
				}
			}
			if(isLegalPos(i+1,j+1) && isLegalPos(i,j)){
				if(gameCells[i][j].getType() == 'O' && gameCells[i][j+1].getType() == '.' &&  
					gameCells[i+1][j+1].getType() != '.'){
					//Checks whether there is a single cell and adds cell in horizontal right side
					gameCells[i][j+1].setType('O');
					return true;
				}
			}
			if(isLegalPos(i,j+1)&& isLegalPos(i,j)){
				if(gameCells[i][j].getType() == 'O' && gameCells[i][j+1].getType() != '.' &&
				 gameCells[i][j-1].getType() == '.' && 
					i == rowSize - 1 ){
					//Checks whether there is a single cell and adds cell in horizontal left side
					gameCells[i][j-1].setType('O');
					return true;
				}
			}
			if(isLegalPos(i+1,j+1)&& isLegalPos(i,j)){
				if(gameCells[i][j].getType() == 'O' && gameCells[i][j+1].getType() != '.' 
					&& gameCells[i][j-1].getType() == '.' && 
					 gameCells[i+1][j-1].getType() != '.'){
					//Checks whether there is a single cell and adds cell in horizontal left side
					gameCells[i][j-1].setType('O');
					return true;
				}
			}
			if(isLegalPos(i-1,j+1)&& isLegalPos(i,j)){
				if(gameCells[i][j].getType() == 'O' && gameCells[i-1][j+1].getType() == '.' &&
				 gameCells[i][j+1].getType() != '.' && isLegalPos(i-1,j+1)){
					gameCells[i-1][j+1].setType('O');
					//Checks whether there is a single cell and adds cell in right cross side
					return true;
				}
			}
			if(isLegalPos(i-1,j-1)&& isLegalPos(i,j)){
				if(gameCells[i][j].getType() == 'O' && gameCells[i-1][j-1].getType() == '.' && 
					gameCells[i][j-1].getType() != '.' && isLegalPos(i-1,j-1)){
					//Checks whether there is a single cell and adds cell in left cross side
					gameCells[i-1][j-1].setType('O');
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
				if(gameCells[i][j].getType() == 'O' && gameCells[i][j+1].getType() == 'O' &&
				 gameCells[i][j+2].getType() == '.' && i == rowSize -1 ){
					//Checks whether there are two neighbor cells and adds cell in horizontal right side
					gameCells[i][j+2].setType('O');
					return true;
				}
			}
			if(isLegalPos(i+1,j+2) && isLegalPos(i,j)){
				if(gameCells[i][j].getType() == 'O' && gameCells[i][j+1].getType() == 'O' &&
				 gameCells[i][j+2].getType() == '.' && gameCells[i+1][j+2].getType() != '.'){
					//Checks whether there are two neighbor cells and adds cell in horizontal right side
					gameCells[i][j+2].setType('O');
					return true;
				}
			}
			if(isLegalPos(i,j+2) && isLegalPos(i,j)){
				if(gameCells[i][j].getType() == 'O' && gameCells[i][j+1].getType() == 'O' && 
					gameCells[i][j+2].getType() != '.' && gameCells[i][j-1].getType() == '.' && 
					i == rowSize - 1 ){
					//Checks whether there are two neighbor cells and adds cell in horizontal left side
					gameCells[i][j-1].setType('O');
					return true;
				}
			}
			if(isLegalPos(i+1,j+2) && isLegalPos(i,j)){
				if(gameCells[i][j].getType() == 'O' && gameCells[i][j+1].getType() == 'O' && 
					gameCells[i][j+2].getType() != '.' && gameCells[i][j-1].getType() == '.' && 
					 gameCells[i+1][j-1].getType() != '.'){
					//Checks whether there are two neighbor cells and adds cell in horizontal left side
					gameCells[i][j-1].setType('O');
					return true;
				}
			}
			if(isLegalPos(i-2,j+2) && isLegalPos(i,j)){
				if(gameCells[i][j].getType() == 'O' && gameCells[i-1][j+1].getType() == 'O' && 
					gameCells[i-2][j+2].getType() == '.' && gameCells[i-1][j+2].getType() != '.' ){
					gameCells[i-2][j+2].setType('O');
					//Checks whether there are two neighbor cells and adds cell in right cross side
					return true;
				}
			}
			if(isLegalPos(i-2,j-2) && isLegalPos(i,j)){
				if(gameCells[i][j].getType() == 'O' && gameCells[i-1][j-1].getType() == 'O' && 
					gameCells[i-2][j-2].getType() == '.' && gameCells[i-1][j-2].getType() != '.'){
					//Checks whether there are two neighbor cells and adds cell in left cross side
					gameCells[i-2][j-2].setType('O');
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
		if(gameCells[rowSize - 1][colSize/2].getType()== '.')
			gameCells[rowSize - 1][colSize/2].setType('O');
		else
			gameCells[rowSize - 1][(colSize/2)-1].setType('O');
		return true;
	}
	else{
		 for(int i=rowSize - 1;i>=0;--i){
			for(int j=0;j<colSize;++j){
				if(isLegalPos(i,j+3) && isLegalPos(i,j)){
					if(gameCells[i][j].getType() == 'O' && gameCells[i][j+1].getType() == 'O' && 
						gameCells[i][j+2].getType() == 'O' && gameCells[i][j+3].getType() == '.' && i == rowSize -1 ){
						//Checks whether there are three neighbor cells and adds cell in horizontal right side
						gameCells[i][j+3].setType('O');
						return true;
					}
				}
				if(isLegalPos(i+1,j+3) && isLegalPos(i,j)){
					if(gameCells[i][j].getType() == 'O' && gameCells[i][j+1].getType() == 'O' &&
					 gameCells[i][j+2].getType() == 'O' && gameCells[i][j+3].getType() == '.' && gameCells[i+1][j+3].getType() != '.'){
						//Checks whether there are three neighbor cells and adds cell in horizontal right side
						gameCells[i][j+3].setType('O');
						return true;
					}
				}
				if(isLegalPos(i,j+3) && isLegalPos(i,j)){
					if(gameCells[i][j].getType() == 'O' && gameCells[i][j+1].getType() == 'O' && 
						gameCells[i][j+2].getType() == 'O'&& gameCells[i][j+3].getType() != '.' && gameCells[i][j-1].getType() == '.' && 
						i == rowSize - 1 ){
						//Checks whether there are three neighbor cells and adds cell in horizontal left side
						gameCells[i][j-1].setType('O');
						return true;
					}
				}
				if(isLegalPos(i+1,j+3) && isLegalPos(i,j)){
					if(gameCells[i][j].getType() == 'O' && gameCells[i][j+1].getType() == 'O' && gameCells[i][j+2].getType() == 'O' &&
						gameCells[i][j+3].getType() != '.' && gameCells[i][j-1].getType() == '.' && 
						 gameCells[i+1][j-1].getType() != '.'){
						//Checks whether there are three neighbor cells and adds cell in horizontal left side
						gameCells[i][j-1].setType('O');
						return true;
					}
				}
				if(isLegalPos(i-3,j+3) && isLegalPos(i,j)){
					if(gameCells[i][j].getType() == 'O' && gameCells[i-1][j+1].getType()== 'O' && gameCells[i-2][j+2].getType()== 'O' && 
							gameCells[i-3][j+3].getType()== '.' && gameCells[i-2][j+3].getType()!= '.' && isLegalPos(i-3,j+3)){
						//Checks whether there are three neighbor cells and adds cell in right cross side
						gameCells[i-3][j+3].setType('O');
						return true;
					}
				}
				if(isLegalPos(i-3,j-3) && isLegalPos(i,j)){
					if(gameCells[i][j].getType() == 'O' && gameCells[i-1][j-1].getType()== 'O' && gameCells[i-2][j-2].getType()== 'O' && 
							gameCells[i-3][j-3].getType()== '.' && gameCells[i-2][j-3].getType()!= '.' && isLegalPos(i-3,j-3)){
						//Checks whether there are three neighbor cells and adds cell in left cross side
						gameCells[i-3][j-3].setType('O');
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
				if(gameCells[i][j].getType() == 'X' && gameCells[i][j+1].getType() == 'X' && 
					gameCells[i][j+2].getType() == 'X' && gameCells[i][j+3].getType() == '.' && i == rowSize -1 ){
					//Checks whether there is a single cell and adds cell in horizontal right side
					gameCells[i][j+3].setType('O');
					return true;
				}
			}
			if(isLegalPos(i+1,j+3)&& isLegalPos(i,j)){
				if(gameCells[i][j].getType() == 'X' && gameCells[i][j+1].getType() == 'X' && gameCells[i][j+2].getType() == 'X'
					&& gameCells[i][j+3].getType() == '.' && gameCells[i+1][j+3].getType() != '.'){
					//Checks whether there is a single cell and adds cell in horizontal right side
					gameCells[i][j+3].setType('O');
					return true;
				}
			}
			if(isLegalPos(i,j+3)&& isLegalPos(i,j)){
				if(gameCells[i][j].getType() == 'X' && gameCells[i][j+1].getType() == 'X' && gameCells[i][j+2].getType() == 'X'
					&& gameCells[i][j+3].getType() != '.' && gameCells[i][j-1].getType() == '.' && i == rowSize - 1 ){
					//Checks whether there is a single cell and adds cell in horizontal left side
					gameCells[i][j-1].setType('O');
					return true;
				}
			}
			if(isLegalPos(i+1,j+3)&& isLegalPos(i,j)){
				if(gameCells[i][j].getType() == 'X' && gameCells[i][j+1].getType() == 'X' && gameCells[i][j+2].getType() == 'X'
					&&gameCells[i][j+3].getType() != '.' && gameCells[i][j-1].getType() == '.' && gameCells[i+1][j-1].getType() != '.'){
					//Checks whether there is a single cell and adds cell in horizontal left side
					gameCells[i][j-1].setType('O');
					return true;
				}
			}
			if(isLegalPos(i-3,j+3)&& isLegalPos(i,j)){
				if(gameCells[i][j].getType() == 'X' && gameCells[i-1][j+1].getType()== 'X' && gameCells[i-2][j+2].getType()== 'X'
					&& gameCells[i-3][j+3].getType()== '.' && gameCells[i-2][j+3].getType()!= '.' && isLegalPos(i-3,j+3)){
					//Checks whether there are three neighbor cells and adds cell in right cross side
					gameCells[i-3][j+3].setType('O');
					return true;
				}
			}
			if(isLegalPos(i-3,j-3)&& isLegalPos(i,j)){
				if(gameCells[i][j].getType() == 'X' && gameCells[i-1][j-1].getType()== 'X' && gameCells[i-2][j-2].getType()== 'X'
					&& gameCells[i-3][j-3].getType()== '.' && gameCells[i-2][j-3].getType()!= '.' && isLegalPos(i-3,j-3)){
					//Checks whether there are three neighbor cells and adds cell in left cross side
					gameCells[i-3][j-3].setType('O');
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
				myfile<<gameCells[i][j].getType();
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
  		//Reads the  board's size,living cells,game type and sequence from file
	  	myfile>>rowSize>>colSize;
	  	myfile>>gameType;
	  	myfile>>player;
	  	if(gameMode == 'M'){
	  		myfile>>tempLiving;
	  		livingCells = tempLiving + livingCells -currLive;
	  	}
	  	else
	  		myfile>>livingCells;
	  		
	  	char temp[rowSize][colSize];
	  	initBoard();
	  	
	  	//Reads the  game board's from file
	  	for(int i=0;i<rowSize;i++){
			for(int j=0;j<colSize;j++){
				myfile>>temp[i][j];
				gameCells[i][j].setType(temp[i][j]);
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
	int tempRow,tempCol;

	cout<<"Please enter the height of the board:";
	cin>>tempRow;
	if(cin.fail()){
		cin.clear();
		cin.ignore();
	}
	cout<<"Please enter the width of the board:";
	cin>>tempCol;
	
	while(cin.fail() || !isLegalSize(tempRow,tempCol)){//Checks input types and it is legal
		cin.clear();
		cin.ignore();
		cerr<<"Wrong size! Please enter a width and height between 4-27:";
		cin>>tempRow;
		cin>>tempCol;
	}
	setSize(tempRow,tempCol);

	cout<<"Press 'P' to play two players"<<endl;
	cout<<"Press 'C' to play with computer"<<endl;
	cin>>gameChoice;

	while(gameChoice != 'P' && gameChoice != 'C'){
		cerr<<"Wrong gameChoice.Please choose 'P' or 'C':";
		cin>>gameChoice;
	}

	if(gameChoice == 'P')
		setGame(1);
	else
		setGame(2);

	statusEnd = 0;
	initBoard();			//Resize the board
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

	gameMenu(gameChoice);
	initBoard();
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

bool ConnectFour::compareVertical(const ConnectFour &game) const{

	bool status = false;
	//Compares two games vertically like CompareObj function 
	for(int i=0;i<colSize;++i){
		for(int j=rowSize-1;j>=0;--j){
			if(isLegalPos(j-2,i) && isLegalPos(j,i)){
				if(gameType != 2 && gameCells[j][i].getType() == 'X' && gameCells[j-1][i].getType() == 'X'  && gameCells[j-2][i].getType() == 'X')
					status = true;
				else if(gameCells[j][i].getType() == 'X' && gameCells[j-1][i].getType() == 'X')
					status = true;
				
			}
		}
	}
	for(int i=0;i<game.colSize;++i){
		for(int j=game.rowSize-1;j>=0;--j){
			if(isLegalPos(j-2,i) && isLegalPos(j,i)){
				if(game.gameCells[j][i].getType() == 'X' && game.gameCells[j-1][i].getType() == 'X' 
					&& game.gameCells[j-2][i].getType() == 'X')
					status = false;
			}
		}
	}
	
	return status;
}

bool ConnectFour::CompareObj(const ConnectFour &game) const{

	bool status = false;

	if(compareVertical(game))
		status = true;

	/*Compares two game in all positions except vertical.if game 1 has more cell than game2,
	  it returns true,otherwise,status = false.The case of the draw game did not take into account*/
	for(int i=rowSize - 1;i>=0;--i){
		for(int j=0;j<colSize;++j){
			if(isLegalPos(i,j+2) && isLegalPos(i,j)){
				if(gameType != 2 && gameCells[i][j].getType() == 'X' && gameCells[i][j+1].getType() == 'X' && gameCells[i][j+2].getType() == 'X')
					status = true;
				else if(gameCells[i][j].getType() == 'X' && gameCells[i][j+1].getType() == 'X')
					status = true;
			}
			else if(isLegalPos(i-2,j+2) && isLegalPos(i,j)){
				if(gameType != 2 && gameCells[i][j].getType() == 'X' && gameCells[i-1][j+1].getType()== 'X' &&
					 gameCells[i-2][j+2].getType()== 'X'){
					status = true;
				}
				else if(gameCells[i][j].getType() == 'X' && gameCells[i-1][j+1].getType()== 'X'){
					status = true;
				}
			}
			else if(isLegalPos(i-2,j+2) && isLegalPos(i,j)){
				if(gameType != 2 && gameCells[i][j].getType() == 'X' && gameCells[i-1][j-1].getType()== 'X' && 
					gameCells[i-2][j-2].getType()== 'X'){
					status = true;
				}
				else if(gameType != 2 && gameCells[i][j].getType() == 'X' && gameCells[i-1][j-1].getType()== 'X'){
					status = true;
				}
			}
		}
	}
	for(int i=game.rowSize - 1;i>=0;--i){
		for(int j=0;j<game.colSize;++j){
			if(isLegalPos(i,j+2) && isLegalPos(i,j)){
				if(game.gameCells[i][j].getType() == 'X' && game.gameCells[i][j+1].getType() == 'X' &&
					game.gameCells[i][j+2].getType() == 'X')
					status = false;
			}
			else if(isLegalPos(i-2,j+2) && isLegalPos(i,j)){
				if(game.gameCells[i][j].getType() == 'X' && game.gameCells[i-1][j+1].getType()== 'X' &&
					 game.gameCells[i-2][j+2].getType()== 'X')
					status = false;
			}
			else if(isLegalPos(i-2,j+2) && isLegalPos(i,j)){
				if(game.gameCells[i][j].getType() == 'X' && game.gameCells[i-1][j-1].getType()== 'X' &&
					game.gameCells[i-2][j-2].getType()== 'X')
					status = false;
			}
		}
	}
		return status;	
}
int ConnectFour::playMode2(){// Plays the game in two steps

	key = 1;
    char column;

	printBoard();
	setPlayer(1);
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
	ConnectFour singleGame;

	while(modeChoice != 'S' && modeChoice != 'M'){
		cout<<"Choose the game mode 'S' or 'M':";
		cin>>modeChoice;
	}
	if(modeChoice == 'M'){

		char gameChoice;
		int object;
		ConnectFour game1,game2,game3,game4,game5;//Creates five games

		//Take all necassary inputs for all games
		game1.gameMenu(gameChoice);
		game2.gameMenu(gameChoice);
		game3.gameMenu(gameChoice);
		game4.gameMenu(gameChoice);
		game5.gameMenu(gameChoice);


		//Until all games are finished the game continues
		while(!(game1.isEnd()) || !(game2.isEnd()) || !(game3.isEnd())
			 || !(game4.isEnd()) || !(game5.isEnd())){

			cout<<"Choose a object:";
			cin>>object;

			if(cin.fail()){
				cin.clear();
				cin.ignore();
			}
			if(object == 1 && !(game1.isEnd()))
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

			if(game1.CompareObj(game2) && !(game1.isEnd()) && !(game2.isEnd()))//Compare two games
				cout<<"Game 1 is better than Game 2 for you."<<endl;		
		}
		cout<<"All games are finished."<<endl;	
	}
	else
		singleGame.playGame();//Begins single game.PvP or PvC
	

	return 0;
}
