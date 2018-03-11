#include<iostream>
#include<fstream>
#include<string>

const int MAXSIZE = 20;

using namespace std;

typedef enum {
empty,
p1,
p2,
connectedX,
connectedO,
unusable
}cell;

typedef enum{
	PvP,
	PvC
}gameType;

void initBoard(cell board[][MAXSIZE],const int &size); // Creates a board and fills the board with empty cells
int isLegalSize(const int &size); // Checks whether the user's input size is legal
int isLegalCol(int colNum,const int &size); // Checks whether the user's input column is on board
int isLegalPos(int i,int j,const int &size);// Checks the coordinates on the board is legal
void printBoard(cell board [][MAXSIZE],const int &size);// Print current game board
int isColFull(cell board[][MAXSIZE],int colNum,const int &size);//Checks whether the selected column is full
int isBoardFull(cell board[][MAXSIZE],const int &size);//Checks whether there is a empty cell in the game board
void putLetter(cell board[][MAXSIZE],int colNum,int size,int player);//In the PvP game, the moves made by the players are placed on the board.
int inputCol(int player,int &size,cell board[][MAXSIZE],gameType game,int &sequence,int &gameOpt);//Take input column from user1 or user2 
int checkHorizon(cell board[][MAXSIZE],int size,int player);//Checks whether the four same cells are neighbor horizontally
int checkVertical(cell board[][MAXSIZE],int size,int player);//Checks whether the four same cells are neighbor horizontally vertically 
int checkDiaLeft(cell board[][MAXSIZE],int size,int player);//Checks whether the four same cells are neighbor in left cross 
int checkDiaRight(cell board[][MAXSIZE],int size,int player);//Checks whether the four same cells are neighbor in right cross
int checkAll(cell board[][MAXSIZE],int size,int player,int computer);// Checks every position for finding four neighbor cells
void defaultOne(cell board[][MAXSIZE],int size);//if there are not any neighbor cells to move,moves to empty column;
int isOne(cell board[][MAXSIZE],int size);//Adds a neighbor cell to a single cell of the computer
int isTwo(cell board[][MAXSIZE],int size);//Adds a neighbor cell to two cells of the computer
int isThree(cell board[][MAXSIZE],int size,int cnt);//Adds a neighbor cell to three cells of the computer
int Defend3(cell board[][MAXSIZE],int size);//Prevents the opponent from winning by preventing four same cells from coming together
void playGame();//Includes game loop and initializations
char gameMenu();//Asks user to play PvP or PvC
int checkSave(const string &col,string &fileName);//Checks whether the user's input is SAVE
int checkLoad(const string &col,string &fileName);//Checks whether the user's input is LOAD
int saveBoard(const string &fileName,int size,cell board[][MAXSIZE],int player,gameType game);//Saves the current board,sequences,size,and game type to file
int loadBoard(const string &fileName,cell board[][MAXSIZE],int &size,int &sequence,int &gameOpt);//Read file and load the saved game 
void continueGame(cell board[][MAXSIZE],int &size,int sequence,int gameOpt);//Continues the game  after loading the board
int playerInput(int size,cell board[][MAXSIZE],gameType game,int sequence,int gameOpt,int player);//Acts according to return values of Input function
int computerInput(int size,cell board[][MAXSIZE],int cnt = 1);//Includes computer's all moves


void initBoard(cell board[][MAXSIZE],const int &size)
{
	for(int i=0;i<size;++i)
		for(int j=0;j<size;++j)
			board[i][j] = empty;		
}

int isLegalSize(const int &size)
{
	auto status = 0;
	
	if(size >= 4 && size <= MAXSIZE && size % 2 == 0) //Take size even number between 4-20
		status = 1;
	else
		status = 0;
	
	return status;
}


int isLegalCol(int colNum,const int &size)
{
	if(colNum <size && colNum >= 0)
		return 1;
	else
		return 0;
}

int isLegalPos(int i,int j,const int &size)	
{
	if(i >=0 && i< size && j >= 0 && j<size) // Prevents reach out of matrix
		return 1;
	else
		return 0;
}

void printBoard(cell board [][MAXSIZE],const int &size)
{
	char c;
	
	for(int i=0;i<size;++i){	//Prints letters row
		c = 'A'+i;
		cout<<c<<"  ";
	}
		cout<<endl;

	for(int i=0;i<size;++i){
		for(int j=0;j<size;++j){
			if(board[i][j] == empty)
				cout<<".  ";
			else if(board[i][j] == p1)
				cout<<"X  ";
			else if(board[i][j] == p2)
				cout<<"O  ";
			else if(board[i][j] == connectedX)
				cout<<"x  ";
			else if(board[i][j] == connectedO)
				cout<<"o  ";
		}			
		cout<<endl<<endl;	
	}			
}


int isColFull(cell board[][MAXSIZE],int colNum,const int &size)
{
	auto a = 0;

	for(int i=size - 1;i>=0;--i){
		for(int j=size - 1;j>=0;--j){
			if(j == colNum && board[i][j] != empty)
				a++;	
		}
	}
	if(a == size)	
		return 0;
	else
		return 1;
}

int isBoardFull(cell board[][MAXSIZE],const int &size)
{
	auto a = 0;

	for(int i=size - 1;i>=0;--i){
		for(int j=size - 1;j>=0;--j){
			if(board[i][j] != empty)
				a++;
		}
	}

	if(a == size * size){ // if there is not empty column to continue game,the game will end in a draw.
		cout<<"The game ended in a draw."<<endl;
		return 0;
	}
	else
		return 1;
}

void putLetter(cell board[][MAXSIZE],int colNum,int size,int player)
{
	for(int i=size - 1;i>=0;--i){
		for(int j=size - 1;j>=0;--j){
			if(j == colNum && player == 1 && board[i][j] == empty){// Puts 'X' if current player is player 1
				board[i][j] = p1;
				return;
			}
			else if(j == colNum && player == 2 && board[i][j] == empty){//Puts 'O' if current player is player 2
				board[i][j] = p2;
				return;
			}
		}
	}
}

int inputCol(int player,int &size,cell board[][MAXSIZE],gameType game,int &sequence,int &gameOpt)
{
	string col,fileName;
	auto colNum = 0;

	cout<<"Player " <<player<< " turn => Choose a column:"; //Indicates who is next
	getline(cin,col);

	if(checkSave(col,fileName)){ //if user's input is SAVE,write to current board to file
		if(saveBoard(fileName,size,board,player,game))
			cout<<"Current game is saving....."<<endl;
		else
			cerr<<"File can not open,try again"<<endl;//Invalid filename
		return 0;
	}
	else if(checkLoad(col,fileName)){//if user's input is LOAD,read game from file
		if(loadBoard(fileName,board,size,sequence,gameOpt))
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
		
		if(!isLegalCol(colNum,size)){	
			cerr<<"Invalid column,try again"<<endl;
			return 0;
		}
		else if(!isColFull(board,colNum,size)){
			cerr<<"This column is full.Please choose another column"<<endl;
			return 0;
		}
		else{									// if there are not any illegal status,puts letter X or O
			putLetter(board,colNum,size,player);
			return 1;
		}
	}	
}


int checkHorizon(cell board[][MAXSIZE],int size,int player)
{
	int count = 0;

	for(int i=size - 1;i>=0;--i){
		for(int j=0;j<size;++j){
			if((board[i][j] == p1 && player == 1) || (board[i][j] == p2 && player == 2))
				++count; // Counts same cells horizontally
			else
				count = 0;
			if(count == 4){	// if there are four same neighbor cells
				for(int a=0;a<4;a++){ // Converts them small case x or o
					if(player == 1)
						board[i][j-a]=connectedX;
					else
						board[i][j-a]=connectedO;	
				}
				return 1;
			}		
		}
		count = 0;
	}
	return 0;
}



int checkVertical(cell board[][MAXSIZE],int size,int player)
{
	int count = 0;

	for(int i=size - 1;i>=0;--i){
		for(int j=0;j<size;++j){
			if((board[j][i] == p1 && player == 1) || (board[j][i] == p2 && player == 2))
				++count; // Counts same cells vertically
			else
				count = 0;
			if(count == 4){ // if there are four same neighbor cells
				for(int a=0;a<4;a++){ // Converts them small case x or o
					if(player == 1)
						board[j-a][i]=connectedX;
					else
						board[j-a][i]=connectedO;	
				}
				return 1;
			}		
		}
		count = 0;
	}
	return 0;
}

int checkDiaRight(cell board[][MAXSIZE],int size,int player)
{
	for(int i=size - 1;i>=0;--i){
		for(int j=0;j<size;++j){
			if(isLegalPos(i-1,j+1,size) && isLegalPos(i-2,j+2,size) && isLegalPos(i-3,j+3,size)){
				if( (board[i][j] == p1 && board[i-1][j+1] == p1 && board[i-2][j+2] == p1 && board[i-3][j+3] == p1) ||
					(board[i][j] == p2 && board[i-1][j+1] == p2 && board[i-2][j+2] == p2 && board[i-3][j+3] == p2) ){	
					for(int b=0;b<4;++b){ // if there are four same neighbor cells in right cross,converts them small case x or o
						if(player == 1 )
							board[i-b][j+b] = connectedX;	
						else if(player == 2)
							board[i-b][j+b] = connectedO;
					}
					return 1;
				}
			}
		}
	}
	return 0;			
}


int checkDiaLeft(cell board[][MAXSIZE],int size,int player)
{
	for(int i=size - 1;i>=0;--i){
		for(int j=size -1;j>=0;--j){
			if(isLegalPos(i-1,j-1,size) && isLegalPos(i-2,j-2,size) && isLegalPos(i-3,j-3,size)){
				if( (board[i][j] == p1 && board[i-1][j-1] == p1 && board[i-2][j-2] == p1 && board[i-3][j-3] == p1) ||
					(board[i][j] == p2 && board[i-1][j-1] == p2 && board[i-2][j-2] == p2 && board[i-3][j-3] == p2) ){	
					for(int b=0;b<4;++b){// if there are four same neighbor cells in left cross,converts them small case x or o
						if(player == 1 )
							board[i-b][j-b] = connectedX;	
						else if(player == 2)
							board[i-b][j-b] = connectedO;
					}
					return 1;
				}
			}
		}
	}
	return 0;
}

int checkAll(cell board[][MAXSIZE],int size,int player,int computer)
{	
	if(checkHorizon(board,size,player)  || // Checks all positions
	   checkVertical(board,size,player) || 
	   checkDiaLeft(board,size,player)  ||
	   checkDiaRight(board,size,player)){

		printBoard(board,size);

		if(computer) //if player 2 is computer,assigns player 3 to computer
			player = 3;

		if(player != 3)
			cout<<"Player "<<player<< " win the game!!!"<<endl;
		else
			cout<<"Computer win the game!!!"<<endl;
			
		return 1;
	}
	else
		return 0;
}


void defaultOne(cell board[][MAXSIZE],int size)
{
	for(int i=size - 1;i>=0;--i){ // if there arent any neighbor,moves empty column
		for(int j=0;j<size;++j){
			if(board[i][j] == empty){
				board[i][j] = p2;
				return;
			}
		}
	}	
}

int isOne(cell board[][MAXSIZE],int size)
{
	for(int i=0;i<size;++i){
		for(int j=size;j>=0;--j){
			if(board[j][i] == p2 && board[j-1][i] == empty && isLegalPos(j-1,i,size)){
				//Checks whether there is a single cell and adds cell vertically
				board[j-1][i] = p2;
			return 1;
			}
			else if(board[i][j] == p2 && board[i][j+1] == empty && (board[i+1][j+1] != empty || i == size -1) && isLegalPos(i,j+1,size)){
				//Checks whether there is a single cell and adds cell in horizontal right side
				board[i][j+1] = p2;
				return 1;
			}
			else if(board[i][j] == p2 && (board[i][j+1] != empty || board[i+1][j+1] == empty) && board[i][j-1] == empty && 
					(i == size - 1 || board[i+1][j-1] != empty) && isLegalPos(i,j-1,size)){
				//Checks whether there is a single cell and adds cell in horizontal left side
				board[i][j-1] = p2;
				return 1;
			}
			else if(board[i][j] == p2 && board[i-1][j+1] == empty && board[i][j+1] != empty && isLegalPos(i-1,j+1,size)){
				board[i-1][j+1] = p2;
				//Checks whether there is a single cell and adds cell in right cross side
				return 1;
			}
			else if(board[i][j] == p2 && board[i-1][j-1] == empty && board[i][j-1] != empty && isLegalPos(i-1,j-1,size)){
				//Checks whether there is a single cell and adds cell in left cross side
				board[i-1][j-1] = p2;
				return 1;
			}
		}	
	}
	return 0;
}



int isTwo(cell board[][MAXSIZE],int size)
{
	for(int i=0;i<size;++i){
			for(int j=size;j>=0;--j){
				if(board[j][i] == p2 && board[j-1][i] == p2 && board[j-2][i] == empty && isLegalPos(j-2,i,size) ){
					//Checks whether there are two neighbor cells and adds cell vertically
					board[j-2][i] = p2;
					return 1;
				}
				else if(board[i][j] == p2 && board[i][j+1] == p2 && board[i][j+2] == empty  &&
						 (board[i+1][j+2] != empty || i == size -1) && isLegalPos(i,j+2,size)){
					//Checks whether there are two neighbor cells and adds cell in horizontal right side
					board[i][j+2] = p2;
					return 1;
				}
				else if(board[i][j] == p2 && board[i][j+1] == p2 && (board[i][j+2] != empty || board[i+1][j+2] == empty) &&
						board[i][j-1] == empty && (i == size -1 || board[i+1][j-1] != empty) && isLegalPos(i,j-1,size)){
					//Checks whether there are two neighbor cells and adds cell in horizontal left side
					board[i][j-1] = p2;
					return 1;
				}	
				else if(board[i][j] == p2 && board[i-1][j+1] == p2 && board[i-2][j+2] == empty && 
						board[i-1][j+2] != empty && isLegalPos(i-2,j+2,size)){
					//Checks whether there are two neighbor cells and adds cell in right cross side
					board[i-2][j+2] = p2;
					return 1;
				}
				else if(board[i][j] == p2 && board[i-1][j-1] == p2 && board[i-2][j-2] == empty &&
					 board[i-1][j-2] != empty && isLegalPos(i-2,j-2,size)){
					//Checks whether there are two neighbor cells and adds cell in leftt cross side
					board[i-2][j-2] = p2;
					return 1;
				}
			}	
		}
		return 0;
}


int isThree(cell board[][MAXSIZE],int size,int cnt)
{
	if(cnt == 0){ //First move
		if(board[size - 1][size/2] == empty)
			board[size - 1][size/2] = p2;
		else
			board[size - 1][(size/2)-1] = p2;
		return 1;
	}
	else{
		 for(int i=0;i<size;++i){
			for(int j=size;j>=0;--j){
				if(board[j][i] == p2 && board[j-1][i] == p2 && board[j-2][i] == p2 && 
					board[j-3][i] == empty && isLegalPos(j-3,i,size)){
					//Checks whether there are three neighbor cells and adds cell vertically
					board[j-3][i] = p2;
					return 1;
				}
				else if(board[i][j] == p2 && board[i][j+1] == p2 && board[i][j+2] == p2 && 
						board[i][j+3] == empty && (board[i+1][j+3] != empty || i == size -1) && isLegalPos(i,j+3,size)){
					//Checks whether there are three neighbor cells and adds cell in horizontal right side
					board[i][j+3] = p2;
					return 1;
				}
				else if(board[i][j] == p2 && board[i][j+1] == p2 && board[i][j+2] == p2 && (board[i][j+3] != empty || board[i+1][j+3] == empty)
						&& board[i][j-1] == empty && (i == size - 1 || board[i+1][j-1] != empty) && isLegalPos(i,j-1,size)){
					//Checks whether there are three neighbor cells and adds cell in horizontal left side
					board[i][j-1] = p2;
					return 1;
				}	
				else if(board[i][j] == p2 && board[i-1][j+1] == p2 && board[i-2][j+2] == p2 && 
						board[i-3][j+3] == empty && board[i-2][j+3] != empty && isLegalPos(i-3,j+3,size)){
					//Checks whether there are three neighbor cells and adds cell in right cross side
					board[i-3][j+3] = p2;
					return 1;
				}
				else if(board[i][j] == p2 && board[i-1][j-1] == p2 && board[i-2][j-2] == p2 && 
						board[i-3][j-3] == empty && board[i-2][j-3] != empty && isLegalPos(i-3,j-3,size)){
					//Checks whether there are three neighbor cells and adds cell in left cross side
					board[i-3][j-3] = p2;
					return 1;
				}
				
			}	
		}
		return 0;
	}
}


int Defend3(cell board[][MAXSIZE],int size)
{	
	//Like isThree function,checks whether there are three opponent's neighbor cells and adds computer's cell around cell
	 for(int i=size - 1;i>=0;--i){
		for(int j=0;j<size;++j){
			if(board[j][i] == p1 && board[j-1][i] == p1 && board[j-2][i] == p1 && board[j-3][i] == empty && isLegalPos(j-3,i,size)){
				board[j-3][i] = p2;
				return 1;
			}
			else if(board[i][j] == p1 && board[i][j+1] == p1 && board[i][j+2] == p1 && board[i][j+3] == empty &&
				 (board[i+1][j+3] != empty || i == size -1) && isLegalPos(i,j+3,size)){
				board[i][j+3] = p2;
				return 1;
			}
			else if(board[i][j] == p1 && board[i][j+1] == p1 && board[i][j+2] == p1 && (board[i][j+3] != empty || board[i+1][j+3] == empty)
				 	&& board[i][j-1] == empty && (i == size -1 || board[i+1][j-1] != empty) && isLegalPos(i,j-1,size)){
				board[i][j-1] = p2;
				return 1;
			}
			else if(board[i][j] == p1 && board[i-1][j+1] == p1 && board[i-2][j+2] == p1 && 
					board[i-3][j+3] == empty && board[i-2][j+3] != empty && isLegalPos(i-3,j+3,size)){
				board[i-3][j+3] = p2;
				return 1;
			}
			else if(board[i][j] == p1 && board[i-1][j-1] == p1 && board[i-2][j-2] == p1 && 
					board[i-3][j-3] == empty && board[i-2][j-3] != empty && isLegalPos(i-3,j-3,size)){
				board[i-3][j-3] = p2;
				return 1;
			}
		}
	}
	return 0;
}

int checkSave(const string &col,string &fileName){

	const string str = "SAVE ";
	auto status = 0,count = 0;

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


int checkLoad(const string &col,string &fileName){

	const string str = "LOAD ";
	auto status = 0,count = 0;

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

int saveBoard(const string &fileName,int size,cell board[][MAXSIZE],int player,gameType game){
	
	int status = 0;
	ofstream myfile;
  	myfile.open(fileName);
 
 	if(myfile){
 		//Writes the current board's size,game type and sequence to file
	  	myfile<<size<<endl;	
	  	myfile<<game<<endl;	
	  	myfile<<player<<endl;
	  	//Writes the current board's to file
	  	for(int i=0;i<size;i++){	
			for(int j=0;j<size;j++){
				myfile<<board[i][j]<<' ';
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

int loadBoard(const string &fileName,cell board[][MAXSIZE],int &size,int &sequence,int &gameOpt){

	int arr[MAXSIZE][MAXSIZE],status = 0; 
	ifstream myfile;
  	myfile.open(fileName);

  	if(myfile){
  		//Reads the  board's size,game type and sequence from file
	  	myfile>>size;
	  	myfile>>gameOpt;
	  	myfile>>sequence;
	  	//Reads the  game board's from file
	  	for(int i=0;i<size;i++){
			for(int j=0;j<size;j++){
				myfile>>arr[i][j];
				board[i][j]=static_cast<cell>(arr[i][j]);
			}
		}
		myfile.close();
		status = 1;
	}
	else
		status = 0;

	  	return status;
}

char gameMenu()
{
	char choice;

	cout<<"Press 'P' to play two players"<<endl;
	cout<<"Press 'C' to play with computer"<<endl;
	cin>>choice;

	while(choice != 'P' && choice != 'C'){
		cerr<<"Wrong choice.Please choose 'P' or 'C':";
		cin>>choice;
	}

	return choice;
}

int playerInput(int size,cell board[][MAXSIZE],gameType game,int sequence,int gameOpt,int player){

	int status = 0;

	status = inputCol(player,size,board,game,sequence,gameOpt);
	while(status == 0)//Contiunes taking input until the input is valid
		status = inputCol(player,size,board,game,sequence,gameOpt);
	if(status == 2){//if input is load,continues the game
		continueGame(board,size,sequence,gameOpt);
		return 1;
	}
	else
		return 0;
}


int computerInput(int size,cell board[][MAXSIZE],int cnt){
	// first priority is winning motion and second priority is defend yourself
	if(isThree(board,size,cnt)); 
	else if(Defend3(board,size));
	else if(isTwo(board,size));
	else if(isOne(board,size));
	else
		defaultOne(board,size);

	cout<<"Computer's Turn:"<<endl;
				
	if(checkAll(board,size,2,1))
		return 1;
	else
		return 0;
			
}

void continueGame(cell board[][MAXSIZE],int &size,int sequence,int gameOpt){

	int cnt = 0;

	cout<<"Saved game is loading......"<<endl;
	printBoard(board,size);

	while(isBoardFull(board,size)){
		if(gameOpt == 0){//Checks the game type is PvP
			if(sequence == 1 ){//Checks the sequence
				if(playerInput(size,board,PvP,sequence,gameOpt,1))//if player's input is load,terminates current game
					return;
				if(checkAll(board,size,1,0)) //Checks after all inputs
					break;
				
				printBoard(board,size);
				sequence = 2;
			}
			if(sequence == 2){
				if(playerInput(size,board,PvP,sequence,gameOpt,2))
					return;
				if(checkAll(board,size,2,0))
					break;

				printBoard(board,size);
				sequence = 1;
			}
		}
		else if(gameOpt == 1){//Checks the game type is PvC

			if(playerInput(size,board,PvC,sequence,gameOpt,1))
				return;
			printBoard(board,size);

			cnt = 1;//Indıcates that move is not first move
			if(computerInput(size,board,cnt))
				break;
			printBoard(board,size);
		}	
	}
}

void playGame()
{	
	int size;
	decltype(size) cnt = 0,sequence = 0,gameOpt = 0;
	char choice;
	cell board[MAXSIZE][MAXSIZE];

	 for(int i=0;i<MAXSIZE;i++)		//Fills the board and prepares the board for the game
		for(int j=0;j<MAXSIZE;j++)
			board[i][j] = unusable;

	cout<<"Please enter the size of the board:";
	cin>>size;
		
	while(cin.fail() || !isLegalSize(size)){//Checks input types and it is legal
		cin.clear();
		cin.ignore();
		cerr<<"Wrong size! Please enter a even number between 4 and 20:";
		cin>>size;
	}

	initBoard(board,size);
	choice = gameMenu();
	printBoard(board,size);	
	
	cin.ignore();
	while(isBoardFull(board,size)){
		
		if(choice == 'P'){
			if(playerInput(size,board,PvP,sequence,gameOpt,1))
				return;
		}
		else{
			if(playerInput(size,board,PvC,sequence,gameOpt,1))
				return;
		}
			
		if(checkAll(board,size,1,0)) //Checks after all inputs
			break;
		printBoard(board,size);

		if(choice == 'P'){//if game is PvP,player2 will be user
			if(playerInput(size,board,PvP,sequence,gameOpt,2))
				return;
				
			if(checkAll(board,size,2,0))
				break;
		}
		else{ 
			if(computerInput(size,board,cnt))
				break;
			cnt = 1;
		}
		printBoard(board,size);
	}
}	
		
int main()
{	
	playGame();
	return 0;
}
