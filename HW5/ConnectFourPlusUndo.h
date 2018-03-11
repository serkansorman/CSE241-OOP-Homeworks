#ifndef CONNECTFOURPLUSUNDO_H
#define CONNECTFOURPLUSUNDO_H
#include "ConnectFourPlus.h"

using namespace std;
namespace SORMAN{
	class ConnectFourPlusUndo:public ConnectFourPlus{
		public:
			ConnectFourPlusUndo();
			ConnectFourPlusUndo(int newRow,int newCol);
			ConnectFourPlusUndo(const ConnectFourPlusUndo &game);//Copy constructor
		private:
			string oldMoves;//Includes all moves in the game

			const ConnectFourPlusUndo &operator = (const ConnectFourPlusUndo &game);
			void undoLetter();//Undo the last move
			int checkUndo(const string &col)const;//Checks whether input is load or not

			//Function is redefined for taking UNDO key word
			virtual int inputCol(char column);

			//Computer's move functions are redefined for recording each move to oldMoves string
			
			//Computer's horizantal moves
			virtual bool defaultOne();//if there are not any neighbor cells to move,moves to empty column
			virtual bool isOne();//Adds a neighbor cell to a single cell of the computer
			virtual bool isTwo();//Adds a neighbor cell to two cells of the computer
			virtual bool isThree();//Adds a neighbor cell to three  cells of the computer
			virtual bool Defend3();//Defends itself from three neighbors cells

			//Computer's vertical moves
			virtual bool isOneVertical();//Adds a neighbor cell to a single cell of the computer vertically
			virtual bool isTwoVertical();//Adds a neighbor cell to two cells of the computer vertically
			virtual bool isThreeVertical();//Adds a neighbor cell to three cells of the computer vertically
			virtual bool defend3Vertical();//Defends itself from three neighbors cells
			
			//Functions are redefined for write  all moves to file and read from file
			virtual int saveBoard(const string &fileName)const;//Saves the current board,player,size and game type to file
			virtual int loadBoard(const string &fileName);//Read file and loads the saved game 
	};
}

#endif