#ifndef adapt
#define adapt

#include "Cell.h"
#include "Abstract.h"
using namespace std;

namespace BrnSlmz{
	template<template<typename...> class Temp>
	class HexAdapter : public AbstractHex {
		public: 
			HexAdapter();
			void readFromFile(const std::string& filename)override;
			void writeToFile(const std::string& filename)override;
			const bool isEnd()override;
			void reset() override;
			int numberOfMoves()const override;
			void print()override;
			Cell lastMove()override;
			const Cell operator()(int i,int j)const override;
			const Cell getMove(int i)const override;
		private:
			Temp<Temp<Cell>> hexCells;
			Temp<Cell> moves;
			void putTable(char player,int y,int x)override;
			char getTable(int y,int x)const override ;
			void putLast(Cell cell)override;
	};
}
#endif