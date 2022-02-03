#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "hex_header.h"
using namespace std;
	
int main( ) {
	Hex::Cell c1('b',5),c2('d',5),c3('a',6),c4('a',3);
	cout<<"Game-1 :"<<endl;
	Hex game1;
	game1.playGame();
	cout <<"SCORE 1.player::::: "<< game1.userScore(player1)<<endl<<"SCORE 2.player::::: "<< game1.userScore(player2)<<endl;
	
	cout<<endl<<"Game-2 :"<<endl;
	Hex game2(6,2);//Size: 6 <----> Type : Player vs. Computer
	game2.startGame();// Starts the Game 2
	cout <<"SCORE 1.player::::: "<< game2.userScore(player1)<<endl<<"SCORE 2.player::::: "<< game2.userScore(player2)<<endl;

	cout<<endl<<"Game-3 :"<<endl;
	Hex game3("save1.txt");//Loads from file
	game3.play(c1);
	game3.play(c2);
	cout<<game3;
	cout <<"SCORE 1.player::::: "<< game3.userScore(player1)<<endl<<"SCORE 2.player::::: "<< game3.userScore(player2)<<endl;

	cout<<endl<<"Game-4 :"<<endl;
	Hex game4("save2.txt");
	game4.play(c3);
	game4.play();
	cout<<game4;
	cout <<"SCORE 1.player::::: "<< game4.userScore(player1)<<endl<<"SCORE 2.player::::: "<< game4.userScore(player2)<<endl;

	cout<<endl<<"Game-5 :"<<endl;
	Hex game5("save3.txt");
	game5.play(c4);
	cout<<game5;
	cout <<"SCORE 1.player::::: "<< game5.userScore(player1)<<endl<<"SCORE 2.player::::: "<< game5.userScore(player2)<<endl;

	cout<<endl<<"Is Game-1 Finished ?: "<<game1.isFinished()<<endl;
 	cout<<"Is Game-2 Finished ?: "<<game2.isFinished()<<endl;
 	cout<<"Is Game-3 Finished ?: "<<game3.isFinished()<<endl;
 	cout<<"Is Game-4 Finished ?: "<<game4.isFinished()<<endl;
 	cout<<"Is Game-5 Finished ?: "<<game5.isFinished()<<endl;

 	cout<<endl <<"Game1 > Game2 ? : "<<game1.compare_games(game2)<<endl;
 	cout <<"Game2 > Game3 ? : "<<game2.compare_games(game3)<<endl;
 	cout <<"Game3 > Game4 ? : "<<game3.compare_games(game4)<<endl;
 	cout <<"Game4 > Game5 ? : "<<game4.compare_games(game5)<<endl<<endl;

 	cout<<"Game-1 Marked Cells: "<<game1.marked_cells()<<endl;
 	cout<<"Game-2 Marked Cells: "<<game2.marked_cells()<<endl;
 	cout<<"Game-3 Marked Cells: "<<game3.marked_cells()<<endl;
 	cout<<"Game-4 Marked Cells: "<<game4.marked_cells()<<endl;
 	cout<<"Game-5 Marked Cells: "<<game5.marked_cells()<<endl;

	cout <<"Total Marked Cells : "<<Hex::totalMarked()<<endl;

	return 0;
}