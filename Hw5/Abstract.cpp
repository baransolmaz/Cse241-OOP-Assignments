#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <deque>
#include "Abstract.h"
#include "Cell.h"
using namespace std;
using namespace BrnSlmz;

void AbstractHex::setSize(int _size_){ size=_size_; reset();}//Sets size
int AbstractHex::getSize()const{ return size; }//Returns size
void AbstractHex::setType(int _type_){ type=_type_;}//Sets type
int AbstractHex::getType()const{ return type; }//Returns type
int AbstractHex::getLastint(){return lastint;}//for computers move
char AbstractHex::getLastchar(){return lastchar;}//for computers move
void AbstractHex::putLastint(int x){ lastint=x; }//for computers move
void AbstractHex::putLastchar(char x){ lastchar=x; }//for computers move
void AbstractHex::make_upper(char winner){//Makes upper those connected to path
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			if (getTable(i,j)==winner)
				if (getTable(i,j+1)==winner-32 || getTable(i+1,j)==winner-32 || getTable(i,j-1)==winner-32 ||getTable(i-1,j+1)==winner-32 || getTable(i-1,j)==winner-32 ||getTable(i+1,j-1)==winner-32 ){
					putTable(winner-32,i,j);
					make_upper(winner);
				}
}
void AbstractHex::playGame(){//Starts new game
	int _size_,_type_;
	do{
		cout<<endl<<"\tEnter width of board:(5->30)"<<endl;
		cin>>_size_;
	}while(_size_> 30 || _size_<5);
	setSize(_size_);
	reset();
	do{
		cout<<endl<< "\t1-Play with friend"<< endl<<"\t2-Play with computer"<< endl<<"Please select:" << endl;
		cin>>_type_;
	}while( 1> _type_ || _type_ > 2 );
	setType(_type_);
	startGame();
}
int AbstractHex::make_atoi(const std::string& input){//If user enters two-digit character as a number,converts to integer 
	int i=1,y=0;
	while(0<= (int)input[i]-'0' && (int)input[i]-'0'<=9){
		y=(10*y)+(int)input[i]-'0';
		i++;
	}
	return y;
}
int AbstractHex::options(const std::string& input){//Checks commands for saving/loading 
	string filename,save;
	if (input=="Save" || input=="save" ||input=="SAVE"){
		cin>>filename;
		writeToFile(filename);
		cout<<endl<<"Your progress has been saved."<<endl<<endl;
	}else if (input == "Load" || input == "load" || input == "LOAD"){
		cin>> filename;
		readFromFile(filename);
		startGame();
		return 0;
	}
	return 1;
}
void AbstractHex::play(Cell cell){//Plays the players's move
	switch(check_turn())
		{
			case 1:	putTable(player1,cell.getY(),cell.getX()-'a');
					putLastint(cell.getY());
					putLastchar(cell.getX()); 
					cell.setState(player1);
					break;
			case 2: putTable(player2,cell.getY(),cell.getX()-'a');
					cell.setState(player2);
					break;
		}
	putLast(cell);
	if (find_initial(player1,0,0)==1 || find_initial(player2,0,0)==1 ){
		cout<<"Player-"<<check_turn()%2 +1<<" Wins"<<endl;
		if (check_turn()==1){
			make_upper(player2);
		}else
			make_upper(player1);		
	}
}
const Cell AbstractHex::play(){//Plays the computer's move
	Cell played;
	played= computers_turn(getLastint(),getLastchar());
	if (find_initial(computer,0,0)==1 ){
		cout<<"Computer Wins"<<endl;
		make_upper(computer);
	}
	putLast(played);
	return played;
}
int AbstractHex::check_turn(){//Checks the table for to find whose turn is next
	auto counter= 0;
	for (auto i = 0; i < getSize(); i++)
		for (auto j = 0; j < getSize(); j++)
			if (getTable(i,j) != empty){
				counter+=1;
			}
	if (counter%2==0)
		return 1;
	else
		return 2;
}
int AbstractHex::check_input(int y,char x){//Controls the inputs if it is in the range or not
	if (1<=y && y<=size && 'a'<=x && x<='a'+size)
		if (getTable(y-1,x-'a') == empty){
			return 1;
		}else
			return 0;
	return 0;
}
void AbstractHex::startGame(){//Starts the game
	string input;
	int y;
	switch(type){
		case 1:	do{
					print();
					do{
						cout<< "Player "<< check_turn()<<"'s turn:"<<endl;
						cin>>input;
						if (options(input)!=1)
							return;
						y=make_atoi(input);					
					}while(check_input(y,input[0]) == 0);
					play(operator()(y-1,input[0]-'a') );
					cout <<"SCORE 1.player::::: "<< userScore(player1)<<endl<<"SCORE 2.player::::: "<< userScore(player2)<<endl;
					}while(isEnd()!=true);
			break;
		case 2: do{
					print();
					do{
						cout<< "Player 1's turn:"<<endl;
						cin>>input;
						if (options(input)!=1)
							return;
						y=make_atoi(input);
					}while(check_input(y,input[0]) == 0);
					play(operator()(y-1,input[0]-'a'));
					if(isEnd()!=true){ cout<< "Computer's turn:"<<endl; play();}
					cout <<"SCORE 1.player::::: "<< userScore(player1)<<endl<<"SCORE 2.player::::: "<< userScore(player2)<<endl;
				}while(isEnd()!=true);
			break;
		default:cerr<<"Wrong input."<<endl;
	}
	print();
}
int AbstractHex::find_initial(char player,int x,int y){//Finds the first character of players in rows and columns
	int check=0;
	if (player==player1){
		for (int i = x; i <=getSize()-1; ++i)
			if (getTable(i,y)==player1){
				check=check_win(player1,i-1,y+1);
				if (check==1)
					putTable(player1-32,i,y);
			}
	}else if (player==player2)
		for (int i = y; i <=getSize()-1; ++i)
			if (getTable(x,i)==player2){
				check=check_win(player2,x+1,i-1);
				if (check==1)
					putTable(player2-32,x,i);
			}
	return check;
}
int AbstractHex::check_win(char player,int x,int y){//Checks the paths for players 
	int check=0,j;
	if (player==player1){
		for (int i = x;  i<x+2; ++i)//checks right and right-up
			if (getTable(i,y) ==player){			
				putTable(getTable(i,y)-32,i,y);
				if (y==size-1)
					return 1;//x win
				check=check_win(player,i-1,y+1);
				if (check==0)
					putTable(getTable(i,y)+32,i,y);
				return check;
			}
		for (int i = y-2; i <y; i++)//checks left-down and down
			if (getTable(x+2,i)==player1){
				putTable(getTable(x+2,i)-32,x+2,i);
				check=check_win(player,x+1,i+1);
				if (check==0)
					putTable(getTable(x+2,i)+32,x+2,i);
				return check;
			}
		for (int i = y-2 , j=x+1 ; i < y && j>x-1 ; ++i, --j)//checks left and up
			if (getTable(j,i)==player){
				putTable(getTable(j,i)-32,j,i);
				check=check_win(player,j-1,i+1);
				if (check==0)
					putTable(getTable(j,i)+32,j,i);
				return check;
			}
	}else if (player==player2){
		for (int i = y; i<y+2 ; ++i)
			if (getTable(x,i)==player){
				putTable(getTable(x,i)-32,x,i);
				if (x==getSize()-1)
					return 1;//O win
				check=check_win(player,x+1,i-1);
				if (check==0){
					putTable(getTable(x,i)+32,x,i);
				}else
					return 1;
			}
		for (int i = x-2;  i <x; ++i)
			if (getTable(i,y+2)==player){
				putTable(getTable(i,y+2)-32,i,y+2);
				check=check_win(player,i+1,y+1);
				if (check==0){
					putTable(getTable(i,y+2)+32,i,y+2);
				}else
					return 1;
			}
		for (int i = x-2 , j=y+1 ; i < x && j>y-1 ; ++i,--j)
			if (getTable(i,j)==player){
				putTable(getTable(i,j)-32,i,j);
				check=check_win(player,i+1,j-1);
				if (check==0){
					putTable(getTable(i,j)+32,i,j);
				}else
					return 1;
			}
			return check;
	}
	return 0;
}
Cell AbstractHex::computers_turn(int y,char x){//Plays computer's moves
	char new_x= char(((int)x+(int)(getSize()+'a'))/2);//for smart moves ->average of inputed and size
	char new_x2= char((((int)x+(int)'a')/2)+1);//for smart moves -> average of inputed and zero('a' in alphabet) 
	if ((float)getSize()/2>int(x-'a')){//left half of the table 
		if (getTable(y-1,int(x-'a')-1)==player1)//if the left side is 'x'
		{
			if (check_input(y+1,new_x)==1)	{	
				putTable(computer,y,int(new_x-'a'));
				return operator()(y,new_x-'a');
			}else if (check_input(y-1,new_x)==1){
				putTable(computer,y-2,int(new_x-'a'));
				return operator()(y-2,new_x-'a');
			}else if (check_input(y+1,char(new_x-1))==1){
				putTable(computer,y,int(new_x-'a')-1);
				return operator()(y,new_x-1-'a');
			}else
				return put_empty(y,x);
		}else{//if the left side is not 'x'
			if (check_input(y,new_x)==1){
				putTable(computer,y-1,int(new_x-'a'));
				return operator()(y-1,new_x-'a');
			}else if (check_input(y+1,new_x)==1){
				putTable(computer,y,int(new_x-'a'));
				return operator()(y,new_x-'a');
			}else
				 return put_empty(y,x);
		}
	}else{//right half of the table
		if (getTable(y-1,int(x-'a')+1)==player1)//if the right side is 'x'
		{
			if (check_input(y+1,new_x2)==1){
				putTable(computer,y,int(new_x2-'a'));
				return operator()(y,new_x2-'a');
			}else if (check_input(y+1,new_x2)==1)
			{
				putTable(computer,y-2,int(new_x2-'a'));
				return operator()(y-2,new_x2-'a');
			}else if (check_input(y+1,char(new_x2-1))==1)
			{
				putTable(computer,y,int(new_x2-'a')-1);
				return operator()(y,new_x2-1-'a');
			}else
				return put_empty(y,x);
		}else{//if the right side is not 'x'
			if (check_input(y,new_x2)==1)
			{
				putTable(computer,y-1,int(new_x2-'a'));
				return operator()(y-1,new_x2-'a');
			}else if (check_input(y,char(new_x2-1))==1)
			{
				putTable(computer,y-1,int(new_x2-'a')-1);
				return operator()(y-1,new_x2-1-'a');
			}else
				 return put_empty(y,x);
		}
	}
}
Cell AbstractHex::put_empty(int y,char x){//Plays computer's moves
	if (check_input(y-1,char(x+1)) == 1 ){//if the right-up side is empty
		putTable(computer,y-2,int(x-'a')+1);
		return operator()(y-2,x+1-'a');
	}else if (check_input(y,char(x+1)) == 1 ){//if the right side is empty
		putTable(computer,y-1,int(x-'a')+1);
		return operator()(y-1,x+1-'a');
	}else if (check_input(y,char(x-1)) == 1 ){//if the left side is empty
		putTable(computer,y-1,int(x-'a')-1);
		return operator()(y-2,x-1-'a');
	}else if (check_input(y+1,char(x-1)) == 1 ){//if the left-down side is empty
		putTable(computer,y,int(x-'a')-1);
		return operator()(y,x-1-'a');
	}else if (check_input(y+1,x) == 1 ){//if the down side is empty
		putTable(computer,y,int(x-'a'));
		return operator()(y,x-'a');
	}else if (check_input(y-1,x) == 1 ){//if the up side is empty
		putTable(computer,y-2,int(x-'a'));
		return operator()(y-2,x-'a');
	}else{
		int i,j;
		for (i = 0; i < getSize()-1; i++){
			for (j = 0; j < getSize()-1; j++)
				if (getTable(i,j)==empty)
					break;
			if (getTable(i,j)==empty)
					break;
		}
		putTable(computer,i,j);
		return operator()(i,j);
	}
}
const float AbstractHex::userScore(char player){//Calculates the Score
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
int AbstractHex::neighboorCells_x(int i,int j,char player){//Helper function for score
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
int AbstractHex::neighboorCells_o(int i,int j,char player){//Helper function for score
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
bool AbstractHex::operator==(const AbstractHex& game) const{//Compares two games 
    if (this->getSize()== game.getSize()){
    	for (int i = 0; i < game.getSize(); i++)
        	for (int j = 0; j < getSize(); j++)
           		if(this->getTable(i,j)!= game.getTable(i,j))
                	return false;
    }else
    	return false;
    return true; 
}