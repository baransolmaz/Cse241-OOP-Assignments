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
inline void Hex::putTable(char player,int y,int x){	hexCells[y][x].setX(x+'a');	hexCells[y][x].setY(y);	hexCells[y][x].setState(player);}//Puts in Cell
//Cell Constructors
/*Hex::Cell::Cell(){	Hex::Cell::setY(1);	Hex::Cell::setX('a'); Hex::Cell::setState(empty); }
Hex::Cell::Cell(char _x_,int _y_){ Hex::Cell::setY(_y_);Hex::Cell::setX(_x_);}*/

/*//Getters & Setters for Cell Class
inline char Hex::Cell::getX()const{return x;}
inline void Hex::Cell::setX(char _x_){x=_x_;}
inline int Hex::Cell::getY()const{return y;}
inline void Hex::Cell::setY(char _y_){y=_y_;}
inline char Hex::Cell::getState()const{return type;}
inline void Hex::Cell::setState(char _type_){type=_type_;}*/
//Hex Constructors
Hex::Hex(int _size_ ,int _type_){ setSize(_size_);setType(_type_); create_table();}//Sets
Hex::Hex(){ setSize(5); setType(1); create_table();}//puts default 
Hex::Hex(const std::string& filename){ loadGame(filename);}
Hex::~Hex(){//Destructor
	for (int i = 0; i < getSize(); ++i)
		delete[] this->hexCells[i];
	delete[] this->hexCells;
	delete[] this->moves;
}
Hex::Hex(const Hex &hex2){//Copy constructor
	setSize(hex2.getSize());
	setType(hex2.getType());
	create_table();
	for (int i = 0; i < getSize(); ++i)
		for (int j = 0; j < getSize(); ++j)
			putTable(hex2.getTable(i,j),i,j);
	moves = new Hex::Cell[hex2.marked_cells()];
		for (int i = 0; i <hex2.marked_cells(); ++i){
			moves[i].setX(hex2.moves[i].getX());
			moves[i].setY(hex2.moves[i].getY());
		}
}
const Hex& Hex::operator=(const Hex &hex2){//Copy assigment overload
	if (hexCells!=nullptr){
		for (int i = 0; i < getSize(); ++i)
			delete[] hexCells[i];
		delete[] hexCells;
	}
	setSize(hex2.getSize());
	setType(hex2.getType());

	create_table();
	for (int i = 0; i < getSize(); ++i)
		for (int j = 0; j < getSize(); ++j)
			putTable(hex2.getTable(i,j),i,j);
	moves = new Hex::Cell[hex2.marked_cells()];
		for (int i = 0; i <hex2.marked_cells(); ++i){
			moves[i].setX(hex2.moves[i].getX());
			moves[i].setY(hex2.moves[i].getY());
		}
	return *this;
}
Hex Hex::operator--( int ){//Prefix decrement overload 
	Hex temp= *this;
	if (moves!=nullptr && marked_cells()!=0)
		for (int i = 0; i < getType(); ++i){
			int y=moves[marked_cells()-1].getY();
			int x = moves[marked_cells()-1].getX();
			putTable(empty,y,x-'a');
		}
	return  temp; 
}
Hex& Hex::operator--(){//Postfix decrement overload
	if (moves!=nullptr && marked_cells()!=0)
		for (int i = 0; i < getType(); ++i){
			int y=moves[marked_cells()-1].getY();
			int x = moves[marked_cells()-1].getX();
			putTable(empty,y,x-'a');
		}
	return *this;
}
bool Hex::operator==(Hex& hex2){// == overload
	if (this->marked_cells()>hex2.marked_cells()){
  		return 1;
  	}else
  		return 0;
}
ostream &operator<<( ostream &out,const Hex &game ){//For screen print
	out<< " ";
	for (int i = 0; i < game.getSize(); ++i)
		out<< " " << (char)('a' +i) ; 
	out<< endl;
	for (int i = 0; i < game.getSize(); i++){
		out<< i+1 ;
		if (i<9)	out<< " ";
		for (int k = 0; k < i; k++)		out<< " " ;
		for (int j = 0; j < game.getSize(); j++){
			out<< " " << game.getTable(i,j);
		}
		out<< endl;
	}
	return out;            
}
ofstream &operator<<( ofstream &out,const Hex &game ){//For game save

	out<<game.getSize()<<endl;
	out<<game.getType()<<endl;
	for (int i = 0; i <game.getSize(); ++i){
		for (int j = 0; j < game.getSize(); ++j)
			out<<game.getTable(i,j);
		out <<endl;
	}
	out<< game.marked_cells() <<endl;
	for (int i = 0; i < game.marked_cells(); ++i)
			out<<game.moves[i].getX()<<game.moves[i].getY()<<endl;
	return out;            
}
ifstream &operator>>( ifstream  &in,Hex &game ){//For game load 
	int _size_,_type_,mark,_y_;
	char state,_x_;
	if (in.is_open()==0){
		cerr<<"Couldn't open/find the file"<<endl;
	}else{
		in >> _size_; game.setSize(_size_);
		in >>_type_; game.setType(_type_ );
		game.create_table();
		for (int i = 0; i < game.getSize(); ++i)
			for (int j = 0; j < game.getSize(); ++j){
				in>>state;
				game.putTable(state,i,j);
			}
		in>>mark;
		game.moves = new Hex::Cell[mark];
		for (int i = 0; i <mark; ++i){
			in>>_x_>>_y_;
			game.moves[i].setX(_x_);
			game.moves[i].setY(_y_);
		}
	}
	return in;            
}
char Hex::getTable(int y,int x)const{//Returns state of cell
	if (0<=x && 0<=y && x<size&& y<size){
		return this->hexCells[y][x].getState();
	}else
		return empty;
}
void Hex::putLast(Hex::Cell cell){//Puts the Cell into the dynamic array as a last member
	Cell *new_moves;
	new_moves = new Cell[marked_cells()];
	for (int i = 0; i < marked_cells()-1; ++i)
		new_moves[i]=moves[i];

	moves = new Cell[marked_cells()];
	for (int i = 0; i < marked_cells()-1; ++i)
		moves[i]=new_moves[i];

	moves[marked_cells()-1]= cell;
}
void Hex::playGame(){//Starts new game
	int _size_,_type_;
	do{
		cout<<endl<<"\tEnter width of board:(5->30)"<<endl;
		cin>>_size_;
	}while(_size_> 30 || _size_<5);
	setSize(_size_);
	create_table();
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
const Hex::Cell Hex::play(){//Plays the computer's move
	Cell played;
	played= computers_turn(last_int,last_char);
	if (find_initial(computer,0,0)==1 ){
		cout<<"Computer Wins"<<endl;
		make_upper(computer);
	}
	marked++;
	putLast(played);
	return played;
}
void Hex::play(Hex::Cell cell){//Plays the players's move
	switch(check_turn())
		{
			case 1:	putTable(player1,cell.getY(),cell.getX()-'a');
					marked++;
					last_int=cell.getY();
					last_char=cell.getX(); 
					break;
			case 2: putTable(player2,cell.getY(),cell.getX()-'a');
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
void Hex::create_table(){//Makes all variables '.' in vector
	hexCells = new Cell*[size];
	if (hexCells == nullptr){
	   	cerr << "Something happened while memory allocation";
	}else
		for (auto i = 0; i < size; ++i){
			hexCells[i]= new Cell[size];
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
				hexCells[i][y].setState(hexCells[i][y].getState()-32);
				if (y==size-1)
					return 1;//x win
				check=check_win(player,i-1,y+1);
				if (check==0)
					hexCells[i][y].setState(hexCells[i][y].getState()+32);
				return check;
			}
		for (int i = y-2; i <y; i++)//checks left-down and down
			if (getTable(x+2,i)==player1){
				hexCells[x+2][i].setState(hexCells[x+2][i].getState()-32);
				check=check_win(player,x+1,i+1);
				if (check==0)
					hexCells[x+2][i].setState(hexCells[x+2][i].getState()+32);
				return check;
			}
		for (int i = y-2 , j=x+1 ; i < y && j>x-1 ; ++i, --j)//checks left and up
			if (getTable(j,i)==player){
				hexCells[j][i].setState(hexCells[j][i].getState()-32);
				check=check_win(player,j-1,i+1);
				if (check==0)
					hexCells[j][i].setState(hexCells[j][i].getState()+32);
				return check;
			}
	}else if (player==player2){
		for (int i = y; i<y+2 ; ++i)
			if (getTable(x,i)==player){
				hexCells[x][i].setState(hexCells[x][i].getState()-32);
				if (x==size-1)
					return 1;//O win
				check=check_win(player,x+1,i-1);
				if (check==0){
					hexCells[x][i].setState(hexCells[x][i].getState()+32);
				}else
					return 1;
			}
		for (int i = x-2;  i <x; ++i)
			if (getTable(i,y+2)==player){
				hexCells[i][y+2].setState(hexCells[i][y+2].getState()-32);
				check=check_win(player,i+1,y+1);
				if (check==0){
					hexCells[i][y+2].setState(hexCells[i][y+2].getState()+32);
				}else
					return 1;
			}
		for (int i = x-2 , j=y+1 ; i < x && j>y-1 ; ++i,--j)
			if (getTable(i,j)==player){
				hexCells[i][j].setState(hexCells[i][j].getState()-32);
				check=check_win(player,i+1,j-1);
				if (check==0){
					hexCells[i][j].setState(hexCells[i][j].getState()+32);
				}else
					return 1;
			}
			return check;
	}
	return 0;
}
Hex::Cell Hex::computers_turn(int y,char x){//Plays computer's moves
	char new_x= char(((int)x+(int)(getSize()+'a'))/2);//for smart moves ->average of inputed and size
	char new_x2= char((((int)x+(int)'a')/2)+1);//for smart moves -> average of inputed and zero('a' in alphabet) 
	if ((float)getSize()/2>int(x-'a')){//left half of the table 
		if (getTable(y-1,int(x-'a')-1)==player1)//if the left side is 'x'
		{
			if (check_input(y+1,new_x)==1)	{	
				hexCells[y][int(new_x-'a')].setState(computer);
				return extractCell(y,new_x);
			}else if (check_input(y-1,new_x)==1){
				hexCells[y-2][int(new_x-'a')].setState(computer);
				return extractCell(y-2,new_x);
			}else if (check_input(y+1,char(new_x-1))==1){
				hexCells[y][int(new_x-'a')-1].setState(computer);
				return extractCell(y,new_x-1);
			}else
				return put_empty(y,x);
		}else{//if the left side is not 'x'
			if (check_input(y,new_x)==1){
				hexCells[y-1][int(new_x-'a')].setState(computer);
				return extractCell(y-1,new_x);
			}else if (check_input(y+1,new_x)==1){
				hexCells[y][int(new_x-'a')].setState(computer);
				return extractCell(y,new_x);
			}else
				 return put_empty(y,x);
		}
	}else{//right half of the table
		if (getTable(y-1,int(x-'a')+1)==player1)//if the right side is 'x'
		{
			if (check_input(y+1,new_x2)==1){
				hexCells[y][int(new_x2-'a')].setState(computer);
				return extractCell(y,new_x2);
			}else if (check_input(y+1,new_x2)==1)
			{
				hexCells[y-2][int(new_x2-'a')].setState(computer);
				return extractCell(y-2,new_x2);
			}else if (check_input(y+1,char(new_x2-1))==1)
			{
				hexCells[y][int(new_x2-'a')-1].setState(computer);
				return extractCell(y,new_x2-1);
			}else
				return put_empty(y,x);
		}else{//if the right side is not 'x'
			if (check_input(y,new_x2)==1)
			{
				hexCells[y-1][int(new_x2-'a')].setState(computer);
				return extractCell(y-1,new_x2);
			}else if (check_input(y,char(new_x2-1))==1)
			{
				hexCells[y-1][int(new_x2-'a')-1].setState(computer);
				return extractCell(y-1,new_x2-1);
			}else
				 return put_empty(y,x);
		}
	}
}
Hex::Cell Hex::put_empty(int y,char x){//Plays computer's moves
	if (check_input(y-1,char(x+1)) == 1 ){//if the right-up side is empty
		hexCells[y-2][int(x-'a')+1].setState(computer);
		 return extractCell(y-2,x+1);
	}else if (check_input(y,char(x+1)) == 1 ){//if the right side is empty
		hexCells[y-1][int(x-'a')+1].setState(computer);
		return extractCell(y-1,x+1);
	}else if (check_input(y,char(x-1)) == 1 ){//if the left side is empty
		hexCells[y-1][int(x-'a')-1].setState(computer);
		return extractCell(y-2,x-1);
	}else if (check_input(y+1,char(x-1)) == 1 ){//if the left-down side is empty
		hexCells[y][int(x-'a')-1].setState(computer);
		return extractCell(y,x-1);
	}else if (check_input(y+1,x) == 1 ){//if the down side is empty
		hexCells[y][int(x-'a')].setState(computer);
		return extractCell(y,x);
	}else if (check_input(y-1,x) == 1 ){//if the up side is empty
		hexCells[y-2][int(x-'a')].setState(computer);
		return extractCell(y-2,x);
	}else{
		int i,j;
		for (i = 0; i < getSize()-1; i++){
			for (j = 0; j < getSize()-1; j++)
				if (getTable(i,j)==empty)
					break;
			if (getTable(i,j)==empty)
					break;
		}
		hexCells[i][j].setState(computer);
		return extractCell(i,char(j+'a'));
	}
}
int Hex::check_input(int y,char x){//Controls the inputs if it is in the range or not
	if (1<=y && y<=size && 'a'<=x && x<='a'+size)
		if (hexCells[y-1][int(x-'a')].getState() == empty){
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
					cout<<*this;
					do{
						cout<< "Player "<< check_turn()<<"'s turn:"<<endl;
						cin>>input;
						if (options(input)!=1)
							return;
						y=make_atoi(input);					
					}while(check_input(y,input[0]) == 0);
					play(extractCell(y-1,input[0]));
					putLast(extractCell(y-1,input[0]));
					cout <<"SCORE 1.player::::: "<< userScore(player1)<<endl<<"SCORE 2.player::::: "<< userScore(player2)<<endl;
					}while(isFinished()!=1);
			break;
		case 2: do{
					cout<<*this;
					do{
						cout<< "Player 1's turn:"<<endl;
						cin>>input;
						if (options(input)!=1)
							return;
						y=make_atoi(input);
					}while(check_input(y,input[0]) == 0);
					play(extractCell(y-1,input[0]));
					putLast(extractCell(y-1,input[0]));
					if(isFinished()!=1){ cout<< "Computer's turn:"<<endl; play();}
					cout <<"SCORE 1.player::::: "<< userScore(player1)<<endl<<"SCORE 2.player::::: "<< userScore(player2)<<endl;
				}while(isFinished()!=1);
			break;
		default:cerr<<"Wrong input."<<endl;
	}
	cout<<*this;
}
const int Hex::isFinished(){//Controls the table if it is finished or not
	for (int i = 0; i < getSize(); ++i)
		for (int j = 0; j < getSize(); ++j)
			if (getTable(i,j)==player1-32 || getTable(i,j)==player2-32)
				return 1;
	return 0;
}
void Hex::saveGame(const std::string& filename){//Saves the table to file
	ofstream out_file;
	out_file.open(filename,ios::out | ios::trunc );
	out_file<<*this;
	out_file.close();
}
void Hex::loadGame(const std::string& filename){//Fills the table from file
	ifstream in_file;
	in_file.open(filename,ios::in);
	if (in_file.is_open()==0){
		cerr<<"Couldn't open/find the file"<<endl;
	}else
		in_file >> *this; 
	
	in_file.close();
	marked+=marked_cells();
}
int Hex::options(const std::string& input){//Checks commands for saving/loading 
	string filename,save;
	if (input=="Save" || input=="save" ||input=="SAVE"){
		cin>>filename;
		saveGame(filename);
		cout<<endl<<"Your progress has been saved."<<endl<<endl;
	}else if (input == "Load" || input == "load" || input == "LOAD"){
		cin>> filename;
		loadGame(filename);
		startGame();
		return 0;
	}else if(input=="Undo" || input=="undo" ||input=="UNDO"){
		(*this)--;
		cout<<*this;
	}
	return 1;
}
int Hex::marked_cells()const{//Returns the number of marked cells in game
	int number=0;
	for (int i = 0; i < getSize(); ++i){
		for (int j = 0; j < getSize(); ++j)
			if (getTable(i,j)!= empty)
				number++;
	}
	return number;
}
bool Hex::compare_games(const Hex& hex2){//Compares two games
	Hex cp;
	cp = hex2;
	if (*this == cp){
  		return true;
  	}else
  		return false;
}
Hex::Cell Hex::extractCell(int y,char x)const{ return hexCells[y][x-'a'] ; }//Returns cell location
const float Hex::userScore(char player){//Calculates the Score
	float score=0.0,score_perConnect=100.0/(getSize()*getSize());
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			if (getTable(i,j)==player || getTable(i,j)==player-32)
				if (player==player1){
					score+=score_perConnect*neighboorCells_x(i,j,player)*(j+1)*(i+1);
				}else
					score+=score_perConnect*neighboorCells_o(i,j,player)*(j+1)*(i+1);				
	return score;
}
int Hex::neighboorCells_x(int i,int j,char player){//Helper function for score
	int n_Cells=0;
	if (getTable(i,j+1)==player || getTable(i,j+1)==player-32)
		n_Cells++;
	if (getTable(i,j-1)==player ||getTable(i,j-1)==player-32 )
		n_Cells++;
	if (getTable(i-1,j+1)==player||getTable(i-1,j+1)==player-32)
		n_Cells++;
	if (getTable(i+1,j-1)==player || getTable(i+1,j-1)==player-32)
		n_Cells++;
	return n_Cells +1;
}
int Hex::neighboorCells_o(int i,int j,char player){//Helper function for score
	int n_Cells=0;
	if (getTable(i+1,j)==player||getTable(i+1,j)==player-32)
		n_Cells++;
	if (getTable(i-1,j+1)==player||getTable(i-1,j+1)==player-32)
		n_Cells++;
	if (getTable(i-1,j)==player||getTable(i-1,j)==player-32)
		n_Cells++;
	if (getTable(i+1,j-1)==player||getTable(i+1,j-1)==player-32)
		n_Cells++;
	return n_Cells +1;
}
const int Hex::whoIstheWinner(){//Returns winner player
	for (int i = 0; i < getSize(); ++i)
		for (int j = 0; j < getSize(); ++j)
			if (getTable(i,j)== player1-32){
				return 1 ;
			}else if (getTable(i,j)== player2-32 ){
				return 2 ;}
	return 0;
}