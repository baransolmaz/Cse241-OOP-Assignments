#include <iostream>
#include <string>
#include <fstream>
#include "hex_header.h"
using namespace std;
enum Cell_states
{
	empty='.',player1='x',player2='o',computer='o'
};
void print_table(char table[][12],int size){//prints the array 
	cout<< " ";
	for (int i = 0; i < size; ++i)
		cout<< " " << (char)('a' +i) ; 
	cout<< endl;
	for (int i = 0; i < size; ++i){
		cout<< i+1 ;
		if (i<9)	cout<< " ";
		for (int k = 0; k < i; ++k)		cout<< " " ;
		for (int j = 0; j < size; ++j){
			if (table[i][j] != player1 && table[i][j] != player2)
				table[i][j]=empty;
			cout<< " " << table[i][j];
		}
		cout<< endl;
	}
}
void reset_table(char table[][12]){//makes all variables '.' in array
	for (auto i = 0; i < 12; ++i)
		for (auto j = 0; j < 12; ++j)
			table[i][j]=empty ;
}
void play_w_computer(char table[][12] , int size){//User1 versus Computer
	string filename ,input;
	int y;
	char winner;
	do{
		print_table(table,size);
		do{
			cout<< "Player 1's turn:"<<endl;
			cin>>input;
			if (options(table,size,2,input)!=1)
				return;
			y=check_atoi(input);
		}while(check_input(size,y,input[0]) == 0 || check_location(y,input[0],table)==0);
		table[y-1][int(input[0]-'a')]=player1;
		if (find_initial(table,size,player1,0,0)==1){
			cout<<"Player-1 Wins"<<endl;
			winner=player1;
			break;
		}
		cout<< "Computer's turn:"<<endl;
		computers_turn(table,size,y,input[0]);
		if (find_initial(table,size,computer,0,0)==1){
			cout<<"Computer Wins"<<endl;
			winner=computer;
			break;
		}
	}while(check_table(table,size)==0);
	make_upper(table,size,winner);
	print_table(table,size);		
}
int find_initial(char table[][12], int size,char player,int x,int y){//Finds the first character of players in rows and columns
	int check=0;
	if (player==player1){
		for (decltype(size) i = x; i <=size-1; ++i)
			if (table[i][y]==player){
				check=check_win(table,size,player,i-1,y+1);
				if (check==1)
					table[i][y]-=32;
			}
	}else if (player==player2)
		for (decltype(size) i = y; i <=size-1; ++i)
			if (table[x][i]==player){
				table[x][i]-=32;
				check=check_win(table,size,player,x+1,i-1);
				if (check==0)
					table[x][i]+=32;
			}
	return check;
}
int check_win(char table[][12], int size,char player,int x,int y){//checks the paths for players 
	int check=0,j;
	if (player==player1){
		for (int i = x; table[i][y]==player1,i <x+2; ++i)//checks right and right-up
			if (table[i][y]==player){
				table[i][y]-=32;
				if (y==size-1)
					return 1;//x win
				check=check_win(table,size,player,i-1,y+1);
				if (check==0)
					table[i][y]+=32;
				return check;
			}
		for (int i = y-2;table[x+2][i]==player1 ,i <y; ++i)//checks left-down and down
			if (table[x+2][i]==player){
				table[x+2][i]-=32;
				check=check_win(table,size,player,x+1,i+1);
				if (check==0)
					table[x+2][i]+=32;
				return check;
			}
		for (int i = y-2 , j=x+1 ;table[j][i]==player1 ,i < y, j>x-1 ; ++i,--j)//checks left and up
			if (table[j][i]==player){
				table[j][i]-=32;
				check=check_win(table,size,player,j-1,i+1);
				if (check==0)
					table[j][i]+=32;
				return check;
			}
	}else if (player==player2){
		for (int i = y; table[x][i]==player2,i <y+2; ++i)
			if (table[x][i]==player){
				table[x][i]-=32;
				if (x==size-1)
					return 1;//y win
				check=check_win(table,size,player,x+1,i-1);
				if (check==0){
					table[x][i]+=32;
				}else
					return 1;
			}
		for (int i = x-2;table[i][y+2]==player2,i <x; ++i)
			if (table[i][y+2]==player){
				table[i][y+2]-=32;
				check=check_win(table,size,player,i+1,y+1);
				if (check==0){
					table[i][y+2]+=32;
				}else
					return 1;
			}
		for (int i = x-2 , j=y+1 ;table[i][j]==player2 ,i < x, j>y-1 ; ++i,--j)
			if (table[i][j]==player){
				table[i][j]-=32;
				check=check_win(table,size,player,i+1,j-1);
				if (check==0){
					table[i][j]+=32;
				}else
					return 1;
			}
			return check;
	}
	return 0;
}
void computers_turn(char table[][12], int size,int y,char x){//plays computer's moves
	char new_x= char(((int)x+(int)(size+'a'))/2);//for smart moves ->average of inputed and size
	char new_x2= char((((int)x+(int)'a')/2)+1);//for smart moves -> average of inputed and zero('a' in alphabet) 
	if ((float)size/2>int(x-'a')){//left half of the table 
		if (table[y-1][int(x-'a')-1]==player1)//if the left side is 'x'
		{
			if (check_location(y+1,new_x,table)==1 && check_input(size,y+1,new_x)==1)
			{
				table[y][int(new_x-'a')]=computer;
			}else if (check_location(y-1,new_x,table)==1 && check_input(size,y-1,new_x)==1)
			{
				table[y-2][int(new_x-'a')]=computer;
			}else if (check_location(y+1,char(new_x-1),table)==1 && check_input(size,y+1,char(new_x-1))==1)
			{
				table[y][int(new_x-'a')-1]=computer;
			}else
				put_empty(table,size,y,x);
		}else{//if the left side is not 'x'
			if (check_location(y,new_x,table)==1 && check_input(size,y,new_x)==1)
			{
				table[y-1][int(new_x-'a')]=computer;
			}else if (check_location(y+1,new_x,table)==1 && check_input(size,y+1,new_x)==1)
			{
				table[y][int(new_x-'a')]=computer;
			}else
				put_empty(table,size,y,x);
		}
	}else{//right half of the table
		if (table[y-1][int(x-'a')+1]==player1)//if the right side is 'x'
		{
			if (check_location(y+1,new_x2,table)==1 && check_input(size,y+1,new_x2)==1)
			{
				table[y][int(new_x2-'a')]=computer;
			}else if (check_location(y-1,new_x2,table)==1 && check_input(size,y+1,new_x2)==1)
			{
				table[y-2][int(new_x2-'a')]=computer;
			}else if (check_location(y+1,char(new_x2-1),table)==1 && check_input(size,y+1,char(new_x2-1))==1)
			{
				table[y][int(new_x2-'a')-1]=computer;
			}else
				put_empty(table,size,y,x);
		}else{//if the right side is not 'x'
			if (check_location(y,new_x2,table)==1 && check_input(size,y,new_x2)==1)
			{
				table[y-1][int(new_x2-'a')]=computer;
			}else if (check_location(y,char(new_x2-1),table)==1 && check_input(size,y,char(new_x2-1))==1)
			{
				table[y-1][int(new_x2-'a')-1]=computer;
			}else
				put_empty(table,size,y,x);
		}
	}
}
void put_empty(char table[][12], int size,int y,char x){//plays computer's moves
	if (check_location(y-1,char(x+1),table)==1 && check_input(size,y-1,char(x+1)) == 1 )//if the right-up side is empty
	{
		table[y-2][int(x-'a')+1]=computer;
	}else if (check_location(y,char(x+1),table)==1 && check_input(size,y,char(x+1)) == 1 )//if the right side is empty
	{
		table[y-1][int(x-'a')+1]=computer;
	}else if (check_location(y,char(x-1),table)==1 && check_input(size,y,char(x-1)) == 1 )//if the left side is empty
	{
		table[y-1][int(x-'a')-1]=computer;
	}else if (check_location(y+1,char(x-1),table)==1 && check_input(size,y+1,char(x-1)) == 1 )//if the left-down side is empty
	{
		table[y][int(x-'a')-1]=computer;
	}else if (check_location(y+1,x,table)==1 && check_input(size,y+1,x) == 1 )//if the down side is empty
	{
		table[y][int(x-'a')]=computer;
	}else if (check_location(y-1,x,table)==1 && check_input(size,y-1,x) == 1 )//if the up side is empty
	{
		table[y-2][int(x-'a')]=computer;
	}
}
int check_input(int size ,int y,char x){//controls the inputs if it is in the range or not
	if (1<=y && y<=size && 'a'<=x && x<='a'+size-1){
		return 1;
	}else
		return 0;
}
int check_atoi(const std::string& input){//if user enters two-digit character as a number,converts to integer 
	int i=1,y=0;
	while(0<= (int)input[i]-'0' && (int)input[i]-'0'<=9){
		y=(10*y)+(int)input[i]-'0';
		i++;
	}
	return y;
}
int check_location(int y,char x,char table[][12]){//checks the location if it is empty or not
	if (table[y-1][int(x-'a')]== empty){
		return 1;
	}else
		return 0;
}
int check_table(char table[][12],int size){//checks all variables in array if there is any empty location to play
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			if (table[i][j]== empty)
				return 0;
	return 1;
}
void play_w_friend(char table[][12],int size){//User1 versus User2
	int out=0,y;
	string input,filename;
	char winner;
	do{
		switch(check_turn(table,size))
			{
				case 1: print_table(table,size);
						do{
							cout<< "Player 1's turn:"<<endl;
							cin>>input;
							if (options(table,size,1,input)!=1)
								return;
							y=check_atoi(input);
						}while(check_input(size,y,input[0]) == 0 || check_location(y,input[0],table)==0);
						table[y-1][int(input[0]-'a')]=player1;
						if (find_initial(table,size,player1,0,0)==1){
							cout<<"Player-1 Wins"<<endl;
							winner=player1;				
							out=1;
							break;
						}
				case 2: print_table(table,size);
						do{
							cout<< "Player 2's turn:"<<endl;
							cin>>input;
							if (options(table,size,1,input)!=1)
									return;
							y=check_atoi(input);
						}while(check_input(size,y,input[0]) == 0 || check_location(y,input[0],table)==0);
						table[y-1][int(input[0]-'a')]=player2;
						if (find_initial(table,size,player2,0,0)==1){
							cout<<"Player-2 Wins"<<endl;
							winner=player2;
							out=1;
							break;
						}
			}
	}while(check_table(table,size)==0 || out!=1);
	make_upper(table,size,winner);
	print_table(table,size);		
}
int check_turn(char table[][12],int size){////Checks the table for to find whose turn is next
	auto counter= 0;
	for (auto i = 0; i < size; ++i)
		for (auto j = 0; j < size; ++j)
			if (table[i][j] != empty)
				counter+=1;
	if (counter%2==0)
		return 1;
	else
		return 2;
}
void new_game(){//Starts new game
	char table[12][12];
	int size = 0,type;
	do{
		cout<<endl<<"Enter width of board:(6->12)"<<endl;
		cin>> size; 
	}while(size> 12 || size<6);
	reset_table(table);
	do{
		cout<<endl<< "1-Play with friend"<< endl<<"2-Play with computer"<< endl<<"Please select:" << endl<<"----You can save your game while playing----"<< endl<<"(Save/save filename.txt)"<<endl;
		cin>> type;
		load_game(table,size,type);
	}while( 1> type || type > 2 );
}
void load_game(char table[][12],int size,int type) {//Loads the table
	switch(type){
		case 1: cout<<endl<<"Player vs. Player"<<endl;
				play_w_friend(table,size);
			break;
		case 2: cout<<endl<<"Player vs. Computer"<<endl;
				play_w_computer(table,size);
			break;
		default:cerr<<"Wrong input."<<endl;
	}
}
void save_table_to_file(char table[][12],int size,int type,const std::string& filename){//Saves the table to file
	ofstream out_file;
	out_file.open(filename,ios::out | ios::trunc );
	out_file<<size<<endl;
	out_file<<type<<endl;
	for (int i = 0; i < 12; ++i)
		out_file<<table[i]<<endl;
	out_file.close();
}
void read_file_to_fill_table(char table[][12],int &size,int &type,const std::string& filename){//Fills the table from file
	ifstream in_file;
	in_file.open(filename,ios::in);
	if (in_file.is_open()==0){
		cerr<<"Couldn't open/find the file"<<endl;
	}else{
		in_file >> size;
		in_file >> type;
		for (int i = 0; i < 12; ++i)
			in_file>>table[i];
	}
	in_file.close();
}
int options(char table[][12],int size,int type,const std::string& input){//Checks commands for saving/loading 
	string filename,save;
	if (input=="Save" || input=="save" ||input=="SAVE" ){
		cin>>filename;
		save_table_to_file(table,size,type,filename);
		cout<<endl<<"Your progress has been saved"<<endl<<endl;
	}else if (input=="Exit" || input=="exit" || input=="EXIT"  ){
		cout<<"Exit without saving?(y/n) -> if no ,enter a filename too"<<endl;
		cin>>save;
		switch(save[0])
			{
				case 'y': cout<<endl<< "You lost the unsaved data"<<endl<<endl;
						  return 0;
				case 'n': cin>>filename;
						  save_table_to_file(table,size,type,filename);
						  cout<<endl<< "Your progress has been saved"<<endl<<endl;
						  return 0;
				default : cout<<endl<< "Closing without saving"<<endl<<endl;
						  return 0;
			}
	}
	return 1;
}
void make_upper(char table[][12],int size,char winner){// makes upper those connected to path
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			if (table[i][j]==winner)
				if (table[i][j+1]==winner-32 || table[i+1][j]==winner-32 || table[i][j-1]==winner-32 ||table[i-1][j+1]==winner-32 || table[i-1][j]==winner-32 ||table[i+1][j-1]==winner-32 )
				{
					table[i][j]-=32;
					make_upper(table,size,winner);
				}
}