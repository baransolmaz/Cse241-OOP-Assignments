#ifndef Array_1d
#define Array_1d
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Cell.h"
#include "Abstract.h"
using namespace std;

namespace BrnSlmz{
	class HexArray1D : public AbstractHex {       
		public: 
			HexArray1D();
			
			~HexArray1D();
			HexArray1D(const HexArray1D &hex2);
			const HexArray1D& operator=(const HexArray1D &hex2);
			
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
			Cell *hexCells;
			Cell *moves;
			void putTable(char player,int y,int x)override;
			char getTable(int y,int x)const override ;
			void putLast(Cell cell)override;
	};
}
#endif