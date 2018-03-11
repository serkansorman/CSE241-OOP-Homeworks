#ifndef CONNECTFOURDIAG_H
#define CONNECTFOURDIAG_H

#include "ConnectFourAbstract.h"

using namespace std;

namespace SORMAN{

	class ConnectFourDiag:public ConnectFourAbstract{
		public:
			ConnectFourDiag();
			ConnectFourDiag(int newRow,int newCol);
			ConnectFourDiag(const ConnectFourDiag &game);//Copy constructor
		private:
			const ConnectFourDiag &operator = (const ConnectFourDiag &game);
			
			//Functions are redefined  for checking end of game  diagonally
			virtual bool checkAll();//Checks diagonally for the game ends
			
			//Functions are redefined  for playing computer diagonally
			virtual bool isTwo();//Adds a neighbor cell diagonally to two cells of the computer
			virtual bool isThree();//Adds a neighbor cell diagonally to three cells of the computer
			virtual bool Defend3();//Defend three diagonal neighbour cells
			virtual bool play();//Plays the computer according to diagonal game type
	};
}


#endif