#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Cell.h"
#include "Abstract.h"
#include "Adapter.h"

using namespace std;
using namespace BrnSlmz;
template<template<typename...> class Temp>
HexAdapter<Temp>::HexAdapter(){//Constructor
	setSize(5);
	setType(1);
	reset();
}
template<template<typename...> class Temp>
void HexAdapter<Temp> ::reset(){//Resets game and board
	moves.clear();
	hexCells.resize(getSize());
	for (auto i = 0; i < getSize(); ++i){
		hexCells[i].resize(getSize());
		for (auto j = 0; j < getSize(); ++j)
			putTable(empty,i,j);
	}
}
template<template<typename...> class Temp>
void HexAdapter<Temp>::putTable(char player,int y,int x){//Puts in Cell
	hexCells[y][x].setX(x+'a');
	hexCells[y][x].setY(y);
	hexCells[y][x].setState(player);
}
template<template<typename...> class Temp>
void HexAdapter<Temp> ::readFromFile(const std::string& filename){//Loads from file 
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
template<template<typename...> class Temp>
void HexAdapter<Temp> ::print(){//Prints the board on screen
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
template<template<typename...> class Temp>
char HexAdapter<Temp>::getTable(int y,int x)const{//Returns state of cell
	if (0<=x && 0<=y && x<size&& y<size){
		return hexCells[y][x].getState();
	}else
		return empty;
}
template<template<typename...> class Temp>
const bool HexAdapter<Temp>::isEnd(){//Controls the table if it is finished or not
	for (int i = 0; i < getSize(); ++i)
		for (int j = 0; j < getSize(); ++j)
			if (getTable(i,j)==player1-32 || getTable(i,j)==player2-32)
				return true;
	return false;
}
template<template<typename...> class Temp>
int HexAdapter<Temp>::numberOfMoves()const{//Returns the number of moves in game
	int number=0;
	for (int i = 0; i < getSize(); ++i){
		for (int j = 0; j < getSize(); ++j)
			if (getTable(i,j)!= empty)
				number++;
	}
	return number;
}
template<template<typename...> class Temp>
void HexAdapter<Temp> ::writeToFile(const std::string& filename){//Saves the game to file 
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
template<template<typename...> class Temp>
const Cell HexAdapter<Temp> ::operator()(int i,int j)const{//Returns the cell or throws false if there isn't any cell
	if(i<getSize() && j<getSize() )
		return hexCells[i][j];
	else
		throw false;
}
template<template<typename...> class Temp>
void HexAdapter<Temp>::putLast(Cell cell){//Puts the Cell into the container as a last member
	moves.push_back(cell);
}
template<template<typename...> class Temp>
Cell HexAdapter<Temp>::lastMove(){//Returns the last move or throws false if there isn't any move
	if (numberOfMoves()-1>=0)
		return moves[numberOfMoves()-1];
	else
		throw false ;
}
template<template<typename...> class Temp>
const Cell HexAdapter<Temp>::getMove(int i)const{//Returns the move that played before
	return moves[i];
}