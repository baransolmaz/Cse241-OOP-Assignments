#ifndef hex_header
#define hex_header

void print_table(char table[][12] , int size);//prints the array 
void reset_table(char table[][12]);//makes all variables '.' in array
void play_w_friend(char table[][12] , int size);//User1 versus User2
void play_w_computer(char table[][12] , int size);//User1 versus Computer
int find_initial(char table[][12], int size,char player,int x,int y);//Finds the first character of players in rows and columns
int check_input(int size ,int y,char x);//controls the inputs if it is in the range or not
int check_location(int y,char x,char table[][12]);//checks the location if it is empty or not
int check_table(char table[][12],int size);//checks all variables in array if there is any empty location to play
int check_win(char table[][12], int size,char player,int x,int y);//checks the paths for players 
void computers_turn(char table[][12], int size,int y,char x);//plays computer's moves
void put_empty(char table[][12], int size,int y,char x);
#endif