#ifndef CONNECTFOURPLUS_H
#define CONNECTFOURPLUS_H
#include "ConnectFourAbstract.h"

using namespace std;

namespace SORMAN{
	class ConnectFourPlus:public ConnectFourAbstract{
		public:
			ConnectFourPlus();
			ConnectFourPlus(int newRow,int newCol);
			ConnectFourPlus(const ConnectFourPlus &game);//Copy constructor
		protected:
			const ConnectFourPlus &operator = (const ConnectFourPlus &game);//Assignment operator
			virtual bool checkAll();//Checks board Horizontally and Vertically
	};
}

#endif