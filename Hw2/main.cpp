#include <iostream>
#include <string>
#include <fstream>

#include "hex_header.h"
using namespace std;

int main(void) {
	string input,filename;
	char table[12][12];
	int size = 0,option;
	do{
		cout<<"New/new"<<endl<<"Load/load filename.txt"<< endl<<"Exit/exit"<<endl<<"Enter an option:" << endl;
		cin>> input;
		if (input == "New" || input == "new"||input == "NEW"){
			new_game();
			input = "Exit";
		}else if (input == "Load" || input == "load" || input == "LOAD"){
			cin>> filename;
			read_file_to_fill_table(table,size,option,filename);
			load_game(table,size,option);
			input = "Exit";
		}else if (input == "Exit" || input == "exit"|| input == "EXIT"){
			cout<< "See u later"<<endl;
		}else
			cerr << "Invalid Option"<<endl<<endl;
	}while(input != "Exit" && input != "exit" && input != "EXIT");
   return 0;
}