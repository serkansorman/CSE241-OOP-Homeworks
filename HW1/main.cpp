#include<iostream>

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

void initBoard(cell board[][MAXSIZE],int size); // Creates a board and fills the board with empty cells
int isLegalSize(int size); // Checks whether the user's input size is legal
int isLegalCol(int colNum,int size); // Checks whether the user's input column is on board
int isLegalPos(int i,int j,int size);// Checks the coordinates on the board is legal
void printBoard(cell board [][MAXSIZE],int size);// Print current game board
int isColFull(cell board[][MAXSIZE],int colNum,int size);//Checks whether the selected column is full
int isBoardFull(cell board[][MAXSIZE],int size);//Checks whether there is a empty cell in the game board
void putLetter(cell board[][MAXSIZE],int colNum,int size,int player);//In the PvP game, the moves made by the players are placed on the board.
int inputCol(int player,int size,cell board[][MAXSIZE]);//Take input column from user1 or user2 
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


void initBoard(cell board[][MAXSIZE],int size)
{
	for(int i=0;i<size;++i)
		for(int j=0;j<size;++j)
			board[i][j] = empty;		
}

int isLegalSize(int size)
{
	int status = 0;
	
	if(size >= 4 && size <= MAXSIZE && size % 2 == 0) //Take size even number between 4-20
		status = 1;
	else
		status = 0;
	
	return status;
}


int isLegalCol(int colNum,int size)
{
	if(colNum <size && colNum >= 0)
		return 1;
	else
		return 0;
}

int isLegalPos(int i,int j,int size)	
{
	if(i >=0 && i< size && j >= 0 && j<size) // Prevents reach out of matrix
		return 1;
	else
		return 0;
}

void printBoard(cell board [][MAXSIZE],int size)
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


int isColFull(cell board[][MAXSIZE],int colNum,int size)
{
	int a = 0;

	for(int i=size - 1;i>=0;--i)
		for(int j=size - 1;j>=0;--j)
			if(j == colNum && board[i][j] != empty)
				a++;	
	if(a == size)	
		return 0;
	else
		return 1;
}

int isBoardFull(cell board[][MAXSIZE],int size)
{
	int a = 0;

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


int inputCol(int player,int size,cell board[][MAXSIZE])
{
	char col[255],colNum;

	cout<<"Player " <<player<< " turn => Choose a column: "; //Indicates who is next
	cin>>col;

	if(col[0]>='A' && col[0] <= 'Z') //Checks the input column and converts to number
		colNum = col[0] - 'A';
	else
		colNum = col[0] - 'a';

	
	if(!isLegalCol(colNum,size)){	
		cout<<"Invalid column,try again"<<endl;
		return 0;
	}
	else if(!isColFull(board,colNum,size)){
		cout<<"This column is full.Please choose another column"<<endl;
		return 0;
	}
	else{									// if there are not any illegal status,puts letter X or O
		putLetter(board,colNum,size,player);
		return 1;
	}
		
}


int checkHorizon(cell board[][MAXSIZE],int size,int player)
{
	int count = 0,a;

	for(int i=size - 1;i>=0;--i){
		for(int j=0;j<size;++j){
			if((board[i][j] == p1 && player == 1) || (board[i][j] == p2 && player == 2))
				++count; // Counts same cells horizontally
			else
				count = 0;
			if(count == 4){	// if there are four same neighbor cells
				for(a=0;a<4;a++){ // Converts them small case x or o
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
	int count = 0,a;

	for(int i=size - 1;i>=0;--i){
		for(int j=0;j<size;++j){
			if((board[j][i] == p1 && player == 1) || (board[j][i] == p2 && player == 2))
				++count; // Counts same cells vertically
			else
				count = 0;
			if(count == 4){ // if there are four same neighbor cells
				for(a=0;a<4;a++){ // Converts them small case x or o
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
			else if(board[i][j] == p2 && board[i][j+1] == empty && board[i+1][j+1] != empty && isLegalPos(i,j+1,size)){
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
						 board[i+1][j+2] != empty && isLegalPos(i,j+2,size)){
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
						board[i][j+3] == empty && board[i+1][j+3] != empty && isLegalPos(i,j+3,size)){
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
				 board[i+1][j+3] != empty && isLegalPos(i,j+3,size)){
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

char gameMenu()
{
	char choice;

	cout<<"Press 'P' to play two players"<<endl;
	cout<<"Press 'C' to play with computer"<<endl;
	cin>>choice;

	while(choice != 'P' && choice != 'C'){
		cout<<"Wrong choice.Please choose 'P' or 'C':";
		cin>>choice;
	}

	return choice;
}

void playGame()
{
	int size,cnt = 0;
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
		cout<<"Wrong size! Please enter a even number between 4 and 20:";
		cin>>size;
	}

	initBoard(board,size);

	choice = gameMenu();	

	printBoard(board,size);	
		
	while(isBoardFull(board,size)){
			
		while(!inputCol(1,size,board));
				
		if(checkAll(board,size,1,0)) //Checks after all inputs
			break;

		printBoard(board,size);

		if(choice == 'P'){//if game is PvP,player2 will be user
			while(!inputCol(2,size,board));
				
			if(checkAll(board,size,2,0))
				break;
		}
		else{ // if game is PvC,player2 will be computer

			// first priority is winning motion and second priority is defend yourself
			if(isThree(board,size,cnt)); 
			else if(Defend3(board,size));
			else if(isTwo(board,size));
			else if(isOne(board,size));
			else
				defaultOne(board,size);

			cout<<"Computer's Turn:"<<endl;
				
			cnt = 1;

			if(checkAll(board,size,2,1)){
				break;
			}
		}
		printBoard(board,size);
	}
}	
		
int main()
{	
	playGame();
	return 0;
}
