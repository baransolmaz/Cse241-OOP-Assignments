#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "hex_header.h"
using namespace std;

int Hex::marked{ 0 };
inline void Hex::setSize(int _size_){ size=_size_;}//Sets size
inline int Hex::getSize()const{ return size; }//Returns size
inline void Hex::setType(int _type_){ type=_type_;}//Sets type
inline int Hex::getType()const{ return type; }//Returns type
inline void Hex::putTable(char player,int y,int x){	hexCells[y][x].x=x+'a';	hexCells[y][x].y=y;	hexCells[y][x].type = player;}//Puts in 2D vector

Hex::Hex(int _size_ ,int _type_){ setSize(_size_);setType(_type_); reset_table();}//Sets
Hex::Hex(){ setSize(5) ;setType(1);reset_table();}//puts default 
Hex::Hex(const std::string& filename){ loadGame(filename);}

char Hex::getTable(int y,int x){//Returns state of cell
	if (0<=x && 0<=y && x<size&& y<size){
		return hexCells[y][x].type;
	}else
		return empty;
}
void Hex::playGame(){//Starts new game
	int _size_,_type_;
	do{
		cout<<endl<<"\tEnter width of board:(5->30)"<<endl;
		cin>>_size_;
	}while(_size_> 30 || _size_<5);
	setSize(_size_);
	reset_table();
	do{
		cout<<endl<< "\t1-Play with friend"<< endl<<"\t2-Play with computer"<< endl<<"Please select:" << endl;
		cin>>_type_;
	}while( 1> _type_ || _type_ > 2 );
	setType(_type_);
	startGame();
}
void Hex::make_upper(char winner){//Makes upper those connected to path
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			if (getTable(i,j)==winner)
				if (getTable(i,j+1)==winner-32 || getTable(i+1,j)==winner-32 || getTable(i,j-1)==winner-32 ||getTable(i-1,j+1)==winner-32 || getTable(i-1,j)==winner-32 ||getTable(i+1,j-1)==winner-32 ){
					putTable(winner-32,i,j);
					make_upper(winner);
				}
}
void Hex::play(){//Plays the computer's move
	computers_turn(last_int,last_char);
	if (find_initial(computer,0,0)==1 ){
		cout<<"Computer Wins"<<endl;
		make_upper(computer);
	}
}
void Hex::play(char x,int y){//Plays the players's move
	switch(check_turn())
		{
			case 1:	putTable(player1,y-1,x-'a');
					marked++;
					last_int=y;
					last_char=x; 
					break;
			case 2: putTable(player2,y-1,x-'a');
					marked++;
					break;
		}
	if (find_initial(player1,0,0)==1 || find_initial(player2,0,0)==1 ){
		cout<<"Player-"<<check_turn()%2 +1<<" Wins"<<endl;
		if (check_turn()==1){
			make_upper(player2);
		}else
			make_upper(player1);		
	}
}
void Hex::print_table(){//Prints the vector 
	cout<< " ";
	for (int i = 0; i < getSize(); ++i)
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
void Hex::reset_table(){//Makes all variables '.' in vector
	hexCells.resize(size);
	for (auto i = 0; i < size; ++i){
		hexCells[i].resize(size);
		for (auto j = 0; j < size; ++j)
			putTable(empty,i,j);
	}
}
int Hex::find_initial(char player,int x,int y){//Finds the first character of players in rows and columns
	int check=0;
	if (player==player1){
		for (decltype(size) i = x; i <=size-1; ++i)
			if (getTable(i,y)==player1){
				check=check_win(player1,i-1,y+1);
				if (check==1)
					putTable(player1-32,i,y);
			}
	}else if (player==player2)
		for (decltype(size) i = y; i <=size-1; ++i)
			if (getTable(x,i)==player2){
				check=check_win(player2,x+1,i-1);
				if (check==1)
					putTable(player2-32,x,i);
			}
	return check;
}
int Hex::check_win(char player,int x,int y){//Checks the paths for players 
	int check=0,j;
	if (player==player1){
		for (int i = x;  i<x+2; ++i)//checks right and right-up
			if (getTable(i,y) ==player){			
				hexCells[i][y].type -=32;
				if (y==size-1)
					return 1;//x win
				check=check_win(player,i-1,y+1);
				if (check==0)
					hexCells[i][y].type +=32;
				return check;
			}
		for (int i = y-2; i <y; i++)//checks left-down and down
			if (getTable(x+2,i)==player1){
				hexCells[x+2][i].type-=32;
				check=check_win(player,x+1,i+1);
				if (check==0)
					hexCells[x+2][i].type+=32;
				return check;
			}
		for (int i = y-2 , j=x+1 ; i < y && j>x-1 ; ++i, --j)//checks left and up
			if (getTable(j,i)==player){
				hexCells[j][i].type-=32;
				check=check_win(player,j-1,i+1);
				if (check==0)
					hexCells[j][i].type+=32;
				return check;
			}
	}else if (player==player2){
		for (int i = y; i<y+2 ; ++i)
			if (getTable(x,i)==player){
				hexCells[x][i].type-=32;
				if (x==size-1)
					return 1;//O win
				check=check_win(player,x+1,i-1);
				if (check==0){
					hexCells[x][i].type+=32;
				}else
					return 1;
			}
		for (int i = x-2;  i <x; ++i)
			if (getTable(i,y+2)==player){
				hexCells[i][y+2].type-=32;
				check=check_win(player,i+1,y+1);
				if (check==0){
					hexCells[i][y+2].type+=32;
				}else
					return 1;
			}
		for (int i = x-2 , j=y+1 ; i < x && j>y-1 ; ++i,--j)
			if (getTable(i,j)==player){
				hexCells[i][j].type-=32;
				check=check_win(player,i+1,j-1);
				if (check==0){
					hexCells[i][j].type+=32;
				}else
					return 1;
			}
			return check;
	}
	return 0;
}
void Hex::computers_turn(int y,char x){//Plays computer's moves
	char new_x= char(((int)x+(int)(getSize()+'a'))/2);//for smart moves ->average of inputed and size
	char new_x2= char((((int)x+(int)'a')/2)+1);//for smart moves -> average of inputed and zero('a' in alphabet) 
	if ((float)getSize()/2>int(x-'a')){//left half of the table 
		if (getTable(y-1,int(x-'a')-1)==player1)//if the left side is 'x'
		{
			if (check_input(y+1,new_x)==1)
			{
				hexCells[y][int(new_x-'a')].type=computer;
			}else if (check_input(y-1,new_x)==1)
			{
				hexCells[y-2][int(new_x-'a')].type=computer;
			}else if (check_input(y+1,char(new_x-1))==1)
			{
				hexCells[y][int(new_x-'a')-1].type=computer;
			}else
				put_empty(y,x);
		}else{//if the left side is not 'x'
			if (check_input(y,new_x)==1)
			{
				hexCells[y-1][int(new_x-'a')].type=computer;
			}else if (check_input(y+1,new_x)==1)
			{
				hexCells[y][int(new_x-'a')].type=computer;
			}else
				put_empty(y,x);
		}
	}else{//right half of the table
		if (getTable(y-1,int(x-'a')+1)==player1)//if the right side is 'x'
		{
			if (check_input(y+1,new_x2)==1)
			{
				hexCells[y][int(new_x2-'a')].type=computer;
			}else if (check_input(y+1,new_x2)==1)
			{
				hexCells[y-2][int(new_x2-'a')].type=computer;
			}else if (check_input(y+1,char(new_x2-1))==1)
			{
				hexCells[y][int(new_x2-'a')-1].type=computer;
			}else
				put_empty(y,x);
		}else{//if the right side is not 'x'
			if (check_input(y,new_x2)==1)
			{
				hexCells[y-1][int(new_x2-'a')].type=computer;
			}else if (check_input(y,char(new_x2-1))==1)
			{
				hexCells[y-1][int(new_x2-'a')-1].type=computer;
			}else
				put_empty(y,x);
		}
	}
}
void Hex::put_empty(int y,char x){//Plays computer's moves
	if (check_input(y-1,char(x+1)) == 1 )//if the right-up side is empty
	{
		hexCells[y-2][int(x-'a')+1].type=computer;
	}else if (check_input(y,char(x+1)) == 1 )//if the right side is empty
	{
		hexCells[y-1][int(x-'a')+1].type=computer;
	}else if (check_input(y,char(x-1)) == 1 )//if the left side is empty
	{
		hexCells[y-1][int(x-'a')-1].type=computer;
	}else if (check_input(y+1,char(x-1)) == 1 )//if the left-down side is empty
	{
		hexCells[y][int(x-'a')-1].type=computer;
	}else if (check_input(y+1,x) == 1 )//if the down side is empty
	{
		hexCells[y][int(x-'a')].type=computer;
	}else if (check_input(y-1,x) == 1 )//if the up side is empty
	{
		hexCells[y-2][int(x-'a')].type=computer;
	}
}
int Hex::check_input(int y,char x){//Controls the inputs if it is in the range or not
	if (1<=y && y<=size && 'a'<=x && x<='a'+size)
		if (hexCells[y-1][int(x-'a')].type== empty){
			return 1;
		}else
			return 0;
	return 0;
}
int Hex::make_atoi(const std::string& input){//If user enters two-digit character as a number,converts to integer 
	int i=1,y=0;
	while(0<= (int)input[i]-'0' && (int)input[i]-'0'<=9){
		y=(10*y)+(int)input[i]-'0';
		i++;
	}
	return y;
}
int Hex::check_turn(){//Checks the table for to find whose turn is next
	auto counter= 0;
	for (auto i = 0; i < size; i++)
		for (auto j = 0; j < size; j++)
			if (getTable(i,j) != empty){
				counter+=1;
			}
	if (counter%2==0)
		return 1;
	else
		return 2;
}
void Hex::startGame(){//Starts the game
	string input;
	int y;
	switch(type){
		case 1:	do{
					print_table();
					do{
						cout<< "Player "<< check_turn()<<"'s turn:"<<endl;
						cin>>input;
						if (options(input)!=1)
							return;
						y=make_atoi(input);					
					}while(check_input(y,input[0]) == 0);
					play(input[0],y);
				}while(isFinished()!=1);
			break;
		case 2: do{
					print_table();
					do{
						cout<< "Player 1's turn:"<<endl;
						cin>>input;
						if (options(input)!=1)
							return;
						y=make_atoi(input);
					}while(check_input(y,input[0]) == 0);
					play(input[0],y);
					if(isFinished()!=1){ cout<< "Computer's turn:"<<endl; play(); marked++;}
				}while(isFinished()!=1);
			break;
		default:cerr<<"Wrong input."<<endl;
	}
	print_table();
}
int Hex::isFinished(){//Controls the table if it is finished or not
	for (int i = 0; i < getSize(); ++i)
		for (int j = 0; j < getSize(); ++j)
			if (getTable(i,j)==player1-32 || getTable(i,j)==player2-32)
				return 1;
	return 0;
}
void Hex::saveGame(const std::string& filename){//Saves the table to file
	ofstream out_file;
	out_file.open(filename,ios::out | ios::trunc );
	out_file<<getSize()<<endl;
	out_file<<getType()<<endl;
	for (int i = 0; i < getSize(); ++i){
		for (int j = 0; j < getSize(); ++j)
			out_file<<getTable(i,j);
		out_file <<endl;
	}
	out_file.close();
}
void Hex::loadGame(const std::string& filename){//Fills the table from file
	ifstream in_file;
	in_file.open(filename,ios::in);
	int _size_,_type_;
	char state;
	if (in_file.is_open()==0){
		cerr<<"Couldn't open/find the file"<<endl;
	}else{
		in_file >> _size_; setSize(_size_);
		in_file >>_type_; setType(_type_ );
		reset_table();
		for (int i = 0; i < getSize(); ++i)
			for (int j = 0; j < getSize(); ++j){
				in_file>>state;
				putTable(state,i,j);
			}
	}
	in_file.close();
	marked+=marked_cells();
}
int Hex::options(const std::string& input){//Checks commands for saving/loading 
	string filename,save;
	if (input=="Save" || input=="save" ||input=="SAVE" ){
		cin>>filename;
		saveGame(filename);
		cout<<endl<<"Your progress has been saved."<<endl<<endl;
	}else if (input == "Load" || input == "load" || input == "LOAD"){
		cin>> filename;
		loadGame(filename);
		startGame();
		return 0;
	}
	return 1;
}
int Hex::marked_cells(){//Returns the number of marked cells in game
	int number=0;
	for (int i = 0; i < getSize(); ++i){
		for (int j = 0; j < getSize(); ++j)
			if (getTable(i,j)!= empty)
				number++;
	}
	return number;
}
bool Hex::compare_games(Hex hex2){//Compares two games
	if (marked_cells()>hex2.marked_cells())
  	{
  		return true;
  	}else
  		return false;
}