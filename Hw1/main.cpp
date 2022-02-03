#include <iostream>
#include "hex_header.h"
using namespace std;

int main() {
	char table[12][12],x;
	int size = 0,option,y;
	do{
		cout<< "Enter width of board:(6->12)" << endl;
		cin>> size; 
	}while(size> 12 || size<6);
	reset_table(table);
	do{
		cout<< "1-Play with friend"<< endl<<"2-Play with computer"<< endl<<"Please select:"<<endl;
		cin>> option;
		switch(option)
		{
			case 1:play_w_friend(table,size);
				break;
			case 2:play_w_computer(table,size);
				break;
			default:cout<<"Wrong input."<<endl;
		}
	}while( 1> option || option > 2 );
	
   return 0;
}