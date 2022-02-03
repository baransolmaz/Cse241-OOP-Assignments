#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Cell.h"
#include "Vector.h"
#include "Abstract.h"
using namespace std;
using namespace BrnSlmz;
void HexVector::putTable(char player,int y,int x){//Puts in Cell
	hexCells[y][x].setX(x+'a');
	hexCells[y][x].setY(y);
	hexCells[y][x].setState(player);
}
HexVector::HexVector(){//Constructor
	setSize(5);
	setType(1);
	reset();
}
void HexVector ::readFromFile(const std::string& filename){//Loads from file
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
		Cell cell;
		for (int i = 0; i <mark; ++i){
			in_file>>_x_>>_y_>>state;
			cell.setX(_x_);
			cell.setY(_y_);
			cell.setState(state);
			moves.push_back(cell);
		}
	}
	in_file.close();
}
void HexVector ::reset(){//Resets game and board
	moves.clear();
	hexCells.resize(getSize());
	for (auto i = 0; i < getSize(); ++i){
		hexCells[i].resize(getSize());
		for (auto j = 0; j < getSize(); ++j)
			putTable(empty,i,j);
	}
}
void HexVector ::print(){//Prints the board on screen
	cout<< " ";
	for (int i = 0; i < getSize(); i++)
		cout<< " " << (char)('a' +i) ; 
	cout<< endl;
		for (int i = 0; i < getSize(); i++){
		cout<< i+1 ;
		if (i<9)	cout<< " ";
		for (int k = 0; k < i; k++)		cout<< " " ;
		for (int j = 0; j < getSize(); j++){
			cout<< " " << getTable(i,j);
		}
		cout<< endl;
	}
}
char HexVector::getTable(int y,int x)const{//Returns state of cell
	if (0<=x && 0<=y && x<size&& y<size){
		return hexCells[y][x].getState();
	}else
		return empty;
}
const bool HexVector::isEnd(){//Controls the table if it is finished or not
	for (int i = 0; i < getSize(); ++i)
		for (int j = 0; j < getSize(); ++j)
			if (getTable(i,j)==player1-32 || getTable(i,j)==player2-32)
				return true;
	return false;
}
int HexVector::numberOfMoves()const{//Returns the number of marked cells in game
	int number=0;
	for (int i = 0; i < getSize(); ++i){
		for (int j = 0; j < getSize(); ++j)
			if (getTable(i,j)!= empty)
				number++;
	}
	return number;
}
void HexVector::writeToFile(const std::string& filename){//Saves the game to file
	ofstream out_file;
	out_file.open(filename,ios::out | ios::trunc );
	out_file<<getSize()<<endl;
	out_file<<getType()<<endl;
	for (int i = 0; i <getSize(); ++i){
		for (int j = 0; j < getSize(); ++j)
			out_file<<getTable(i,j);
		out_file <<endl;
	}
	out_file<< numberOfMoves() <<endl;
	for (int i = 0; i < numberOfMoves(); ++i)
			out_file<<moves[i].getX()<<moves[i].getY()<<moves[i].getState()<<endl;
	out_file.close();
}
const Cell HexVector::operator()(int i,int j)const{//Returns the cell or throws false if there isn't any cell
	if(i<=getSize() && j<=getSize() )
		return hexCells[i][j];
	else
		throw false;
}
void HexVector::putLast(Cell cell){//Puts the Cell into the vector as a last member
	moves.push_back(cell);
}
Cell HexVector::lastMove(){//Returns the last move or throws false if there isn't any move
	if (numberOfMoves()-1>=0)
		return moves[numberOfMoves()-1];
	else
		throw false ;
}
const Cell HexVector::getMove(int i)const{//Returns the move that played before
	return moves[i];
}