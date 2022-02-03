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
	public: 
		class Cell
		{
			public:
				char getX()const;
				void setX(char _x_);
				int getY()const;
				void setY(char _y_);
				char getState()const;
				void setState(char _type_);
				Cell();
				Cell(char _x_,int _y_);
			private:
				int y;
				char x;
				char type;
		};
		
		static int totalMarked() {return marked;}
		Hex(int _size_,int _type_);
		explicit Hex();
		Hex(const std::string& filename);
		
		Hex(const Hex &hex2);
		~Hex();
		const Hex& operator = (const Hex& hex2);

		Hex operator--( int );
		Hex& operator--();
		bool operator==(Hex& hex2);
		friend ostream &operator<<(ostream &out,const Hex &game);
		friend ofstream &operator<<(ofstream &out,const Hex &game);
		friend ifstream &operator>>(ifstream &in,Hex &game);
		
		void setSize(int _size_);
		int getSize()const;
		void setType(int _type_);
		int getType()const;
		void loadGame(const std::string& filename);
		void saveGame(const std::string& filename);
		void playGame();
		const Cell play();
		void play(Cell cell);
		int marked_cells()const;
		bool compare_games(const Hex& hex2);
		const int isFinished();
		void startGame();
		const float userScore(char player);
	private:
		Cell **hexCells;
		int neighboorCells_x(int i ,int j,char player);
		int neighboorCells_o(int i ,int j,char player);
		void putTable(char player,int y,int x);
		char getTable(int y,int x)const;
		char last_char;
		int size,type,last_int;
		void create_table();
		int check_turn();
		int options(const std::string& input);
		int find_initial(char player,int x,int y);
		int check_win(char player,int x,int y);
		void make_upper(char winner);
		int make_atoi(const std::string& input);
		int check_input(int y,char x);
		Cell put_empty(int y,char x);
		Cell computers_turn(int y,char x);
		static int marked;
		Cell *moves;
		void putLast(Cell cell);
		Cell extractCell(int y,char x)const ;
		const int whoIstheWinner();
};	
#endif