/*************************
*******Kevin Gentile******
***EECE Ohio University***
*********12/01/15*********
*****Project 7: part 3***/

//main.cc
#include<iostream>
#include<cstdlib>
#include"colors.h"
#include"game.h"
#include"piece.h"
#include"board.h"
	using namespace main_savitch_14;

int main(){
	othello board;
	othello::who winner;
	winner = board.play();
	switch(winner){
		case othello::HUMAN: 	cout << "White wins" <<endl; break;
		case othello::COMPUTER: cout << "Black wins" 	<<endl; break;
		case othello::NEUTRAL:	cout << "A draw"	<<endl; break;
	}
		
	return 0;
}


