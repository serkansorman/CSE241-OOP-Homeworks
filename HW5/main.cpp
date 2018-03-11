#include<iostream>
#include<fstream>
#include<string>
#include "Cell.h"
#include "ConnectFourAbstract.h"
#include "ConnectFourPlus.h"
#include "ConnectFourDiag.h"
#include "ConnectFourPlusUndo.h"


using namespace std;


int main(){

	using namespace SORMAN;

	char modeChoice;

	while(modeChoice != 'P' && modeChoice != 'D' && modeChoice != 'U'){//Takes input until the choice is P or D or U
		cout<<"Choose the game mode 'P'(PLUS) ,'D'(DİAG) or U(UNDO):"<<endl;
		cin>>modeChoice;
	}

	if(modeChoice == 'P'){//if choice is P,plays Plus game
		ConnectFourPlus game;
		game.playGame();

	}
	else if(modeChoice == 'D'){//if choice is D,plays Diagonal game
		ConnectFourDiag game;
		game.playGame();

	}
	else if(modeChoice == 'U'){//if choice is P,plays Undo game
		ConnectFourPlusUndo game;
		game.playGame();

	}
	
	return 0;
}