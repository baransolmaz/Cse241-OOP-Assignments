#ifndef hex_header
#define hex_header 

void print_table(char table[][12],int size=6);//prints the array 
void reset_table(char table[][12]);//makes all variables '.' in array
void play_w_friend(char table[][12],int size);//User1 versus User2
void play_w_computer(char table[][12],int size);//User1 versus Computer
int find_initial(char table[][12],int size,char player,int x,int y);//Finds the first character of players in rows and columns
int check_input(int size,int y,char x);//controls the inputs if it is in the range or not
int check_location(int y,char x,char table[][12]);//checks the location if it is empty or not
int check_table(char table[][12],int size);//checks all variables in array if there is any empty location to play
int check_win(char table[][12], int size,char player,int x,int y);//checks the paths for players 
void computers_turn(char table[][12], int size,int y,char x);//plays computer's moves
void put_empty(char table[][12], int size,int y,char x);
int check_turn(char table[][12],int size);//Checks the table for to find whose turn is next
void new_game();//Starts a new game
void read_file_to_fill_table(char table[][12],int &size,int &type,const std::string& filename);//Fills the table from file
void load_game(char table[][12],int size,int type);//Loads the table
void save_table_to_file(char table[][12],int size,int type,const std::string& filename);//Saves the table to file
int options(char table[][12],int size,int type,const std::string& input); //Checks commands for saving/loading 
int check_atoi(const std::string&  input);//if user enters two-digit character as a number,converts to integer 
void make_upper(char table[][12],int size,char winner);// makes upper those connected to path
#endif