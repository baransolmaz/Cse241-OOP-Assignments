#include <iostream>
#include "hex_header.h"
using namespace std;

void print_table(char table[][12] , int size){//prints the array 
	cout<< " ";
	for (int i = 0; i < size; ++i)
		cout<< " " << (char)('a' +i) ; 
	cout<< endl;
	for (int i = 0; i < size; ++i){
		cout<< i+1 ;
		if (i<9)
			cout<< " ";
		for (int k = 0; k < i; ++k){
			cout<< " " ;
		}
		for (int j = 0; j < size; ++j)
			cout<< " " << table[i][j];
		cout<< endl;
	}
}
void reset_table(char table[][12]){//makes all variables '.' in array
	for (int i = 0; i < 12; ++i)
		for (int j = 0; j < 12; ++j)
			table[i][j]='.' ;
}
void play_w_friend(char table[][12] , int size){//User1 versus User2
	char  player1='x',player2='o',x;
	int y;
	do{
		print_table(table,size);
		do{
			cout<< "Player 1's turn:"<<endl;
			cin>>x>>y;
		}while(check_input(size,y,x) == 0 || check_location(y,x,table)==0);
		table[y-1][int(x-'a')]=player1;
		if (find_initial(table,size,player1,0,0)==1){
			cout<<"Player-1 Wins"<<endl;
			break;
		}
		print_table(table,size);
		do{
			cout<< "Player 2's turn:"<<endl;
			cin>>x>>y;
		}while(check_input(size,y,x) == 0 || check_location(y,x,table)==0);
		table[y-1][int(x-'a')]=player2;
		if (find_initial(table,size,player2,0,0)==1){
			cout<<"Player-2 Wins"<<endl;
			break;
		}
	}while(check_table(table,size)==0);
	print_table(table,size);		
}
void play_w_computer(char table[][12] , int size){//User1 versus Computer
	char  player1='x',computer='o',x;
	int y;
	do{
		print_table(table,size);
		do{
			cout<< "Player 1's turn:"<<endl;
			cin>>x>>y;
		}while(check_input(size,y,x) == 0 || check_location(y,x,table)==0);
		table[y-1][int(x-'a')]=player1;
		if (find_initial(table,size,player1,0,0)==1){
			cout<<"Player-1 Wins"<<endl;
			break;
		}
		cout<< "Computer's turn:"<<endl;
		computers_turn(table,size,y,x);
		if (find_initial(table,size,computer,0,0)==1){
			cout<<"Computer Wins"<<endl;
			break;
		}
	}while(check_table(table,size)==0);
	print_table(table,size);		
}
int find_initial(char table[][12], int size,char player,int x,int y){//Finds the first character of players in rows and columns
	int check=0;
	if (player=='x'){
		for (int i = x; i <=size-1; ++i)
			if (table[i][y]==player){
				check=check_win(table,size,player,i-1,y+1);
				if (check==1)
					table[i][y]-=32;
			}
	}else if (player=='o')
		for (int i = y; i <=size-1; ++i)
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
	if (player=='x'){
		for (int i = x; table[i][y]=='x',i <x+2; ++i)//checks right and right-up
			if (table[i][y]==player){
				table[i][y]-=32;
				if (y==size-1)
					return 1;//x win
				check=check_win(table,size,player,i-1,y+1);
				if (check==0)
					table[i][y]+=32;
				return check;
			}
		for (int i = y-2;table[x+2][i]=='x' ,i <y; ++i)//checks left-down and down
			if (table[x+2][i]==player){
				table[x+2][i]-=32;
				check=check_win(table,size,player,x+1,i+1);
				if (check==0)
					table[x+2][i]+=32;
				return check;
			}
		for (int i = y-2 , j=x+1 ;table[j][i]=='x' ,i < y, j>x-1 ; ++i,--j)//checks left and up
			if (table[j][i]=='x'){
				table[j][i]-=32;
				check=check_win(table,size,player,j-1,i+1);
				if (check==0)
					table[j][i]+=32;
				return check;
			}
	}else if (player=='o'){
		for (int i = y; table[x][i]=='o',i <y+2; ++i)
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
		for (int i = x-2;table[i][y+2]=='o',i <x; ++i)
			if (table[i][y+2]==player){
				table[i][y+2]-=32;
				check=check_win(table,size,player,i+1,y+1);
				if (check==0){
					table[i][y+2]+=32;
				}else
					return 1;
			}
		for (int i = x-2 , j=y+1 ;table[i][j]=='o' ,i < x, j>y-1 ; ++i,--j)
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
	char new_x2= char((((int)x+(int)'a')/2)+1);//for smart moves -> average of inputed and zero(it's 'a' in alphabet) 
	if ((float)size/2>int(x-'a')){//a-b-c
		if (table[y-1][int(x-'a')-1]=='x')//if the left side is 'x'
		{
			if (check_location(y+1,new_x,table)==1 && check_input(size,y+1,new_x)==1)
			{
				table[y][int(new_x-'a')]='o';
			}else if (check_location(y-1,new_x,table)==1 && check_input(size,y-1,new_x)==1)
			{
				table[y-2][int(new_x-'a')]='o';
			}else if (check_location(y+1,char(new_x-1),table)==1 && check_input(size,y+1,char(new_x-1))==1)
			{
				table[y][int(new_x-'a')-1]='o';
			}else
				put_empty(table,size,y,x);
		}else{//if the left side is not 'x'
			if (check_location(y,new_x,table)==1 && check_input(size,y,new_x)==1)
			{
				table[y-1][int(new_x-'a')]='o';
			}else if (check_location(y+1,new_x,table)==1 && check_input(size,y+1,new_x)==1)
			{
				table[y][int(new_x-'a')]='o';
			}else
				put_empty(table,size,y,x);
		}
	}else{//d-e-f
		if (table[y-1][int(x-'a')+1]=='x')//if the right side is 'x'
		{
			if (check_location(y+1,new_x2,table)==1 && check_input(size,y+1,new_x2)==1)
			{
				table[y][int(new_x2-'a')]='o';
			}else if (check_location(y-1,new_x2,table)==1 && check_input(size,y+1,new_x2)==1)
			{
				table[y-2][int(new_x2-'a')]='o';
			}else if (check_location(y+1,char(new_x2-1),table)==1 && check_input(size,y+1,char(new_x2-1))==1)
			{
				table[y][int(new_x2-'a')-1]='o';
			}else
				put_empty(table,size,y,x);
		}else{//if the right side is not 'x'
			if (check_location(y,new_x2,table)==1 && check_input(size,y,new_x2)==1)
			{
				table[y-1][int(new_x2-'a')]='o';
			}else if (check_location(y,char(new_x2-1),table)==1 && check_input(size,y,char(new_x2-1))==1)
			{
				table[y-1][int(new_x2-'a')-1]='o';
			}else
				put_empty(table,size,y,x);
		}
	}
}
void put_empty(char table[][12], int size,int y,char x){//plays computer's moves
	if (check_location(y-1,char(x+1),table)==1 && check_input(size,y-1,char(x+1)) == 1 )//if the right-up side is empty
	{
		table[y-2][int(x-'a')+1]='o';
	}else if (check_location(y,char(x+1),table)==1 && check_input(size,y,char(x+1)) == 1 )//if the right side is empty
	{
		table[y-1][int(x-'a')+1]='o';
	}else if (check_location(y,char(x-1),table)==1 && check_input(size,y,char(x-1)) == 1 )//if the left side is empty
	{
		table[y-1][int(x-'a')-1]='o';
	}else if (check_location(y+1,char(x-1),table)==1 && check_input(size,y+1,char(x-1)) == 1 )//if the left-down side is empty
	{
		table[y][int(x-'a')-1]='o';
	}else if (check_location(y+1,x,table)==1 && check_input(size,y+1,x) == 1 )//if the down side is empty
	{
		table[y][int(x-'a')]='o';
	}else if (check_location(y-1,x,table)==1 && check_input(size,y-1,x) == 1 )//if the up side is empty
	{
		table[y-2][int(x-'a')]='o';
	}
}
int check_input(int size ,int y,char x){//controls the inputs if it is in the range or not
	if (1<=y && y<=size && 'a'<=x && x<='a'+size-1){
		return 1;
	}else
		return 0;
}
int check_location(int y,char x,char table[][12]){//checks the location if it is empty or not
	if (table[y-1][int(x-'a')]== '.'){
		return 1;
	}else
		return 0;
}
int check_table(char table[][12],int size){//checks all variables in array if there is any empty location to play
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			if (table[i][j]=='.')
				return 0;
	return 1;
}