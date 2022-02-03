#ifndef hex_header
#define hex_header 

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;
enum Cell_type
{
	empty='.',player1='x',player2='o',computer='o'
};
class Hex {       
	private:
		class Cell
		{
			public:
				int y;
				char x;
				char type=empty;
		};
		vector<vector< Cell > > hexCells;
		void putTable(char player,int y,int x);
		char getTable(int y,int x);
		char last_char;
		int size,type,last_int;
		void reset_table();
		int check_turn();
		int options(const std::string& input);
		int find_initial(char player,int x,int y);
		int check_win(char player,int x,int y);
		void make_upper(char winner);
		int make_atoi(const std::string& input);
		int check_input(int y,char x);
		void put_empty(int y,char x);
		void computers_turn(int y,char x);
		static int marked;
	public: 
		static int totalMarked() {return marked;}
		Hex(int _size_,int _type_);
		Hex();
		Hex(const std::string& filename);
		void loadGame(const std::string& filename);
		void saveGame(const std::string& filename);
		void playGame();
		void play();
		void play(char x,int y);
		int marked_cells();
		bool compare_games(Hex hex2);	
		void print_table();
		void setSize(int _size_);
		int getSize()const;
		void setType(int _type_);
		int getType()const;
		int isFinished();
		void startGame();
};	
#endif