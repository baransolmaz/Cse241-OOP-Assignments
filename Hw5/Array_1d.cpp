#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include "Cell.h"
#include "Abstract.h"
#include "Array_1d.h"

using namespace std;
using namespace BrnSlmz;
HexArray1D::HexArray1D(){//Constructor
	setSize(5);
	setType(1);
	reset();
}
HexArray1D::~HexArray1D(){//Destructor
	free(hexCells);
	free(moves);
}
HexArray1D::HexArray1D(const HexArray1D &hex2){//Copy constructor
	setSize(hex2.getSize());
	setType(hex2.getType());
	reset();
	for (int i = 0; i < getSize(); ++i)
		for (int j = 0; j < getSize(); ++j)
			putTable(hex2.getTable(i,j),i,j);
	moves = (Cell*) malloc(hex2.numberOfMoves()*sizeof(Cell));
		for (int i = 0; i <hex2.numberOfMoves(); ++i){
			moves[i].setX(hex2.moves[i].getX());
			moves[i].setY(hex2.moves[i].getY());
		}
}
const HexArray1D& HexArray1D::operator=(const HexArray1D &hex2){//Copy assigment overload
	if (hexCells!=nullptr){
		free(hexCells);
	}
	setSize(hex2.getSize());
	setType(hex2.getType());
	reset();
	for (int i = 0; i < getSize(); ++i)
		for (int j = 0; j < getSize(); ++j)
			putTable(hex2.getTable(i,j),i,j);
	moves = (Cell*) malloc(hex2.numberOfMoves()*sizeof(Cell));
		for (int i = 0; i <hex2.numberOfMoves(); ++i){
			moves[i].setX(hex2.moves[i].getX());
			moves[i].setY(hex2.moves[i].getY());
		}
	return *this;
}
void HexArray1D ::reset(){//Resets game and board
	hexCells = (Cell*) malloc(getSize()*getSize()* sizeof(Cell));
	moves = (Cell*) malloc(sizeof(Cell));
	if(hexCells == NULL)                     
    {
        cerr<<"Error! memory not allocated."<<endl;
    }else
    	for (int i = 0; i < getSize()*getSize(); ++i)
    		putTable(empty,(i-i%getSize())/getSize(),i%getSize());
}
void HexArray1D::putTable(char player,int y,int x){//Puts in Cell
	hexCells[(y*getSize())+x].setX(x+'a');
	hexCells[(y*getSize())+x].setY(y);
	hexCells[(y*getSize())+x].setState(player);
}
void HexArray1D ::readFromFile(const std::string& filename){//Loads from file
	ifstream in_file;
	int _size_,_type_,mark,_y_;
	char state,_x_;
	in_file.open(filename,ios::in);
	if (in_file.is_open()==0){
		cerr<<"Couldn't open/find the file"<<endl;
	}else{
		in_file >> _size_; setSize(_size_);
		in_file >>_type_; setType(_type_ );
		reset();
		for (int i = 0; i < getSize(); ++i)
			for (int j = 0; j < getSize(); ++j){
				in_file>>state;
				putTable(state,i,j);
			}
		in_file>>mark;
		moves = (Cell*) malloc(mark* sizeof(Cell));
		Cell cell;
		for (int i = 0; i <mark; ++i){
			in_file>>_x_>>_y_>>state;
			cell.setX(_x_);
			cell.setY(_y_);
			cell.setState(state);
			moves[i]=cell;
		}
	}
	in_file.close();  
}
void HexArray1D ::print(){//Prints the board on screen
	cout<< " ";
	for (int i = 0; i < getSize(); i++)
		cout<< " " << (char)('a' +i) ; 
	for (int i = 0; i < getSize()*getSize(); i++){
		if (i%getSize()==0)
		{
			cout<< endl<< (i-i%getSize())/getSize()+1 ;
			if ((i-i%getSize())/getSize()<9)	cout<< " ";
			for (int k = 0; k < (i-i%getSize())/getSize(); k++)
				cout<< " " ;
		}
		cout<< " " << getTable((i-i%getSize())/getSize(),i%getSize());
	}
	cout<< endl;
}
char HexArray1D::getTable(int y,int x)const{//Returns state of cell
	if (0<= y*getSize()+x  && y*getSize()+x <getSize()*getSize()){
		return hexCells[y*getSize()+x].getState();
	}else
		return empty;
}
const bool HexArray1D::isEnd(){//Controls the table if it is finished or not
	for (int i = 0; i < getSize()*getSize(); ++i)
		if (getTable((i-i%getSize())/getSize(),i%getSize())==player1-32 || getTable((i-i%getSize())/getSize(),i%getSize())==player2-32)
			return true;
	return false;
}
int HexArray1D::numberOfMoves()const{//Returns the number of moves in game
	int number=0;
	for (int i = 0; i < getSize()*getSize(); ++i)
		if (getTable((i-i%getSize())/getSize(),i%getSize())!= empty)
			number++;
	
	return number;
}
void HexArray1D::writeToFile(const std::string& filename){//Saves the game to file
	ofstream out_file;
	out_file.open(filename,ios::out | ios::trunc );
	out_file<<getSize()<<endl;
	out_file<<getType()<<endl;
	for (int i = 0; i <getSize()*getSize(); ++i){
		out_file<<getTable((i-i%getSize())/getSize(),i%getSize());
		if (i%getSize()==getSize()-1)
			out_file <<endl;
	}
	out_file<< numberOfMoves() <<endl;
	for (int i = 0; i < numberOfMoves(); ++i)
			out_file<<moves[i].getX()<<moves[i].getY()<<moves[i].getState()<<endl;
	out_file.close();
}
const Cell HexArray1D::operator()(int i,int j)const{//Returns the cell or throws false if there isn't any cell
	if(i<=getSize() && j<=getSize() )
		return hexCells[i*getSize()+j] ;
	else
		throw false;
}
void HexArray1D::putLast(Cell cell){//Puts the Cell into the dynamic array as a last member
	Cell *new_moves;
	new_moves = (Cell*) malloc(numberOfMoves()* sizeof(Cell));
	for (int i = 0; i < numberOfMoves()-1; ++i)
		new_moves[i]=moves[i];
	moves = (Cell*) malloc(numberOfMoves()* sizeof(Cell));
	for (int i = 0; i < numberOfMoves()-1; ++i)
		moves[i]=new_moves[i];

	moves[numberOfMoves()-1]= cell;
}
Cell HexArray1D::lastMove(){//Returns the last move or throws false if there isn't any move
	if (numberOfMoves()-1>=0)
		return moves[numberOfMoves()-1];
	else
		throw false ;
}
const Cell HexArray1D::getMove(int i)const{//Returns the move that played before 
	return moves[i];
}