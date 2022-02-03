#include <iostream>
#include <vector>
#include <deque>
#include "Cell.h"
#include "Abstract.h"
#include "Vector.h"
#include "Array_1d.h"
#include "Adapter.h"
#include "Adapter.cpp"
using namespace std;
using namespace BrnSlmz;	

bool check(AbstractHex** games,int numberOfGames);

int main( ) {
	cout<<endl<<"Game1 -> HexVector to AbstractHex"<<endl<<endl;
		HexVector vec1;
		AbstractHex *abs1=&vec1;
			abs1->playGame();
			cout<<"lastMove(): "<< abs1->lastMove().getX()<<abs1->lastMove().getY()+1<<endl;
			cout<<"isEnd(): "<< abs1->isEnd()<<endl;
			cout<<"numberOfMoves(): "<<abs1->numberOfMoves()<<endl;
	
	cout<<endl<<"Game2 -> HexVector to AbstractHex"<<endl<<endl;
		HexVector vec2;
		AbstractHex *abs2=&vec2;
		Cell cell;
		cell.setX('e'); cell.setY(5);
			abs2->readFromFile("save1.txt");
			abs2->play(cell);
			abs2->play();
			abs2->print();
			abs2->writeToFile("save1_new.txt");
			cout<<"lastMove(): "<< abs2->lastMove().getX()<<abs2->lastMove().getY()<<endl;
			cout<<"isEnd(): "<< abs2->isEnd()<<endl;
			cout<<"numberOfMoves(): "<<abs2->numberOfMoves()<<endl;
	
	cout<<endl<<"Game3 -> HexAdapter<deque> to AbstractHex"<<endl<<endl;
		HexAdapter<deque> adapter1;
		AbstractHex *abs3=&adapter1;
		Cell loc_cell; 
			abs3->readFromFile("save2.txt");
			abs3->print();
			cout<<endl<<"operator("<<abs3->getSize()+1<<","<<abs3->getSize()+1<<"): ";
			try{
				loc_cell=abs3->operator()(abs3->getSize()+1,abs3->getSize()+1);
				cout<<"Location: "<<loc_cell.getX()<<loc_cell.getY()+1<<" Type: "<<loc_cell.getState()<<endl;
			}catch(bool)
			{
				cerr<<"No Cell"<<endl;
			}
			cout<<"lastMove(): "<< abs3->lastMove().getX()<<abs3->lastMove().getY()+1<<endl;
			cout<<"isEnd(): "<< abs3->isEnd()<<endl;
			cout<<"numberOfMoves(): "<<abs3->numberOfMoves()<<endl;

	cout<<endl<<"Game4 -> HexArray1D to AbstractHex"<<endl<<endl;
		HexArray1D array1;
		AbstractHex *abs4=&array1;
		Cell last_cell;
			cout<<"operator==(Game3) : "<<abs4->operator==(*abs3)<<endl;
			cout<<"lastMove(): ";
			try{
				last_cell=abs4->lastMove();
				cout<< last_cell.getX()<<last_cell.getY()<<endl;
			}catch(bool)
			{
				cerr<<"No moves"<<endl;
			}
			cout<<"isEnd(): "<< abs4->isEnd()<<endl;
			cout<<"numberOfMoves(): "<<abs4->numberOfMoves()<<endl;
	
	cout<<endl<<"Global Function With An Array Of Valid Games Except -Game4-( No Move )"<<endl;
	AbstractHex* games[4]= {&vec1,&vec2,&adapter1,&array1};
	cout<<endl<<check(games,4)<<endl;
	
	cout<<endl<<"Global Function With An Array Of Same Games Except -Game2- (Invalid Move) "<<endl;
	abs2->play();//With this move, Computer plays twice in a row
	cout<<endl<<check(games,4)<<endl;

	cout<<endl<<"Global Function With An Array Of Same Games Without -Game2- but Different Order "<<endl;
	AbstractHex* games2[3]= {&array1,&adapter1,&vec1};
	cout<<endl<<check(games2,3)<<endl;
////Using Different Games
	HexVector vec3;
	AbstractHex *abs5=&vec3;
	abs5->readFromFile("save3.txt"); 
	
	HexAdapter<vector> adapter2;
	AbstractHex *abs6=&adapter2;
	abs6->readFromFile("save4.txt"); 

	HexArray1D array2;
	AbstractHex *abs7=&array2;
	abs7->readFromFile("save5.txt");

	cout<<endl<<"Global Function With An Array Of Different Valid Games "<<endl;
	AbstractHex* games3[3]= {&array2,&adapter2,&vec3};
	cout<<endl<<check(games3,3)<<endl;

	cout<<endl<<"Global Function With An Array Of All Games "<<endl;
	AbstractHex* games4[7]= {&adapter1,&adapter2,&array1,&array2,&vec1,&vec2,&vec3};
	cout<<endl<<check(games4,7)<<endl;
	return 0;
}
bool check(AbstractHex** games,int numberOfGames){//Global function that checks validity of moves
	cout<<"Number Of Games That Submitted: "<<numberOfGames<<endl;
	for (int i = 0; i < numberOfGames; ++i){
		cout<<"Is Game"<<i+1<<" valid ? : ";
		if (games[i]->numberOfMoves()==0){
			cout<< "-There is no move- "; 	
			return false;
		}else
			for (int j = 0; j < games[i]->numberOfMoves()-1; ++j)
				if (games[i]->getMove(j).getState()==games[i]->getMove(j+1).getState())
					return false;
		cout<<true<<endl;
	}
	cout<<"All Games Are Valid : ";
	return true;
}