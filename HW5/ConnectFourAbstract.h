#ifndef CONNECTFOURABSTRACT_H
#define CONNECTFOURABSTRACT_H

#include "Cell.h"

using namespace std;

namespace SORMAN{
	
	class ConnectFourAbstract{
		public:
			ConnectFourAbstract();
			ConnectFourAbstract(int newRow,int newCol);
			ConnectFourAbstract(const ConnectFourAbstract &game);//Copy constructor
			~ConnectFourAbstract();//Deallocates the places that allocated for board before

			inline int getRow() const {return rowSize;}//Access the height of current board
			inline int getCol() const {return colSize;}//Access the width of current board
			inline int getStatus() const {return statusEnd;}//Access the control of end game

			void playGame();//Plays PvP or PvC in single game
			
			bool operator == (const ConnectFourAbstract &game)const;//Compare two game
			bool operator != (const ConnectFourAbstract &game)const;
			const ConnectFourAbstract&operator = (const ConnectFourAbstract&game);//Assigns game to another game
		protected:
			int rowSize;
			int colSize;
			int key;//Indıcates whether computer's move is first or not
			int player;//Indıcates sequence
			int gameType;//Indicates PvP or PvC
			int isComputer;//Whether computer's sequence or not
			int statusEnd;//Indicates are there any ended games in all games
			Cell **gameBoard;//Board of the game
			
			void setSize(int row,int col);//Set the height and width
			void setGame(int game);//Set the game types are PvP or PvC(1 pvp 2 pvc)
			void setPlayer(int sequence);//Set the current player

			bool isLegalSize(const int &row,const int &col) const; // Checks whether the user's input height and width are legal
			bool isLegalCol(int colNum) const;// Checks whether the user's input column is on board
			bool isLegalPos(int CoordX,int CoordY) const;// Checks the coordinates on the board is legal
			bool isColFull(int colNum) const ;//Checks whether the selected column is full
			bool isBoardFull() const;//Checks whether there is a empty cell in the game board
			bool isEnd()const;// Checks both is board full and any players win
			
			virtual int inputCol(char column);//Takes input column or SAVE,LOAD,UNDO key words from user1 or user2
			virtual bool play();//Plays the computer
			bool play(char position);//Plays the user
			void putLetter(int colNum);//In the PvP game, the moves made by the players are placed on the board.

			bool checkHorizon();//Checks whether the four same cells are neighbor horizontally
			bool checkVertical();//Checks whether the four same cells are neighbor horizontally vertically 
			bool checkDiaRight();//Checks whether the four same cells are neighbor in right cross
			bool checkDiaLeft() ;//Checks whether the four same cells are neighbor in left cross
			virtual bool checkAll() = 0; //Pure virtual check function

			//Computer's move functions
			virtual bool defaultOne();//if there are not any neighbor cells to move,moves to empty column
			virtual bool isOne();//Adds a neighbor cell to a single cell of the computer
			virtual bool isOneVertical();//Adds a neighbor cell to a single cell of the computer vertically
			virtual bool isTwoVertical();//Adds a neighbor cell to two cells of the computer vertically
			virtual bool isThreeVertical();//Adds a neighbor cell to three cells of the computer vertically
			virtual bool defend3Vertical();//Defends itself from three neighbors cells
			virtual bool isTwo();//Adds a neighbor cell to two cells of the computer
			virtual bool isThree();//Adds a neighbor cell to three cells of the computer
			virtual bool Defend3();//Prevents the opponent from winning by preventing four same cells from coming together
			
			int checkSave(const string &col,string &fileName)const;//Checks whether the user's input is SAVE
			int checkLoad(const string &col,string &fileName)const;//Checks whether the user's input is LOAD
			virtual int saveBoard(const string &fileName)const;//Saves the current board,player,size and game type to file
			virtual int loadBoard(const string &fileName);//Read file and loads the saved game 
			void printBoard() const;// Print current game board
			void resizeBoard(); // Creates a board and fills the board with empty cells
			void gameMenu(char &gameChoice);//Ask user height and width,game type
			void continueGame();//Continues the game  after loading the board
	};
}

#endif
