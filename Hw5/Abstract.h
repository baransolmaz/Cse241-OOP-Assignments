#ifndef abs
#define abs 
#include "Cell.h"
using namespace std;
enum Cell_type
{
	empty='.',player1='x',player2='o',computer='o'
};
namespace BrnSlmz{
	class AbstractHex {       
		public: 
			virtual ~AbstractHex(){};
			int getSize()const;
			void setType(int _type_);
			int getType()const;
			void playGame();
			void setSize(int _size_);
			virtual void readFromFile(const std::string& filename)=0;
			virtual void writeToFile(const std::string& filename)=0;
			virtual const bool isEnd()=0;
			virtual void reset()=0;
			virtual int numberOfMoves()const=0;
			virtual void print()=0;
			virtual Cell lastMove()=0;
			virtual const Cell operator()(int i,int j)const =0;
			virtual const Cell getMove(int i)const =0;
			bool operator==(const AbstractHex& game)const;
			const Cell play();
			void play(Cell cell);
			const float userScore(char player);
		protected:
			int size,type,marked;
			int lastint;
			char lastchar;
			int neighboorCells_x(int i ,int j,char player);
			int neighboorCells_o(int i ,int j,char player);
			int getLastint();
			char getLastchar();
			void putLastint(int x);
			void putLastchar(char x);
			int make_atoi(const std::string& input);
			virtual char getTable(int y,int x)const=0 ;
			virtual void putTable(char player,int y,int x)=0;
			void startGame();
			int options(const std::string& input);
			int check_turn();
			int check_input(int y,char x);
			void make_upper(char winner);
			int find_initial(char player,int x,int y);
			int check_win(char player,int x,int y);
			Cell put_empty(int y,char x);
			Cell computers_turn(int y,char x);
			virtual void putLast(Cell cell)=0;
		
	};
}
#endif