#include<iostream>
#include<fstream>
#include<string>
#include"Cell.h"

using namespace std;

namespace SORMAN{
	Cell::Cell(){//Creates a default cell
		position = 'A';
		row = 0;
		type = '*';
	}
	Cell::Cell(char newType){//Take single paramater for construct type of Cell class
		type = newType;
	}

	Cell::Cell(int newRow,int newPos,char newType){ //Take single paramater for construct Cell class
		row = newRow;
		position = newPos;
		type = newType;
	}

	ostream &operator<<(ostream &out,const Cell &cell){//Shows the coordinates and types of cell
		out<<"Height:"<<cell.row<<endl;
		out<<"Width:"<<cell.position<<endl;
		out<<"Type of cell:"<<cell.type<<endl;

		return out;
	}

	istream &operator>>(istream &in,Cell &cell){//Takes the coordinates and types for cell

		in>>cell.row;
		in>>cell.position;
		in>>cell.type;

		return in;

	}

	bool Cell::operator == (const Cell &cell)const{//Checks whether two cells are same or not
		return(row == cell.row &&
			   position == cell.position &&
			   type == cell.type); 
	}
}