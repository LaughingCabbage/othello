/*************************
*******Kevin Gentile******
***EECE Ohio University***
*********12/01/15*********
*****Project 7: part 3***/


//board.h
//This file inherets 
#ifndef BOARD_H
#define BOARD_H
#include<cstdlib>
#include"piece.h"
#include"game.h"

namespace main_savitch_14{
	class othello : public game {
		public:
			othello();
			othello(const othello& other);
			othello& operator=(const othello& other);
			~othello();
			void printBoard()const;
			othello* clone()const;	
			void compute_moves(std::queue<std::string>& moves)const;			
			void display_status()const;
			int evaluate()const;
			bool is_game_over()const;
			bool is_legal(const std::string&)const;
			void restart();
			void setInitialPieces();
			const std::string getMove();
			void make_move(const std::string& move);
			void print(int row, int column,std::string background);
			
			//game::who winning() const;
			
		private:
			piece* board[8][8];
			int whiteScore;
			int blackScore;
			int passes;
			bool quitGame;
	};
}
#endif
