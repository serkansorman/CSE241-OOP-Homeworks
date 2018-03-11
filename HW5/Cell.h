#ifndef CELL_H
#define CELL_H

using namespace std;

namespace SORMAN{
	class Cell{//Includes information of every cells in board
		public:
			Cell();
			Cell(char newType);
			Cell(int newRow,int newPos,char newType);
		
			inline void setType(char token){type = token;}//Set the cell's type
			inline char getType()const {return type;}//Access the cell's type

			bool operator == (const Cell &cell)const;//Compare two cells
			friend ostream &operator<<(ostream &out,const Cell &cell);//Overloads the insertion operator for Cell's member
			friend istream &operator>>(istream &in,Cell &cell);//Overloads the extraction operator for Cell's member
		private:
			char position;
			int row;
			char type;//Includes information of cells:Empty,User1,User2(or computer)
	};
}

#endif