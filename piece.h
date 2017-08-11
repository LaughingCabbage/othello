/*************************
*******Kevin Gentile******
***EECE Ohio University***
*********12/01/15*********
*****Project 7: part 3***/


//piece.h
#ifndef PIECE_H
#define PIECE_H
#include"colors.h"
#include<iostream>
using namespace std;
namespace main_savitch_14 {
//class piece
	//PUBLIC:
		//void flip()
		//bool isBlack()
		//bool isWhite()
		//bool isEmpty()
	//PRIVATE:
		//char color
		
	class piece{
		public:
			//DEFAULT CONSTRUCTOR FOR PIECE CLASS
			piece(char c = 'x') : color(c){}
			piece(const piece& other){
				color = other.color;
			}
			void operator=(const piece& other){
				color = other.color;		
			}
			//FUNCTION TO HANDLE FLIPPING PIECES
			void flip()
				{
					if (color == 'b')color = 'w';
					else if (color=='w')color = 'b';
				}
			void setPiece(char c)
				{
					color = c;
				}
			void print(string background)const
				{
					//HANDLES BLACK BACKGROUND PIECES
					if(background=="B_BLACK"){
						if(isEmpty())
							cout<<B_BLACK<<" "<<RESET;
						else if(isWhite())
							cout<<B_BLACK<<WHITE<<"@"<<RESET;
						else
							cout<<B_BLACK<<BLUE<<"@"<<RESET;
					//HANDLES RED BACKGROUND PIECES
					}else if(background=="B_RED"){
						if(isEmpty())
							cout<<B_RED<<" "<<RESET;
						else if(isWhite())
							cout<<B_RED<<WHITE<<"@"<<RESET;
						else
							cout<<B_RED<<BLUE<<"@"<<RESET;
					}
				}
			
			//FUNCTION TO HANDLE BLACK COLORED PIECES
			bool isBlack()const
				{
					if(color == 'b')return true;
					else return false;
				}
				
			//FUNCTION TO HANDLE WHITE COLORED PIECES
			bool isWhite()const
				{
					if(color == 'w')return true;
					else return false;
				}
				
			//FUNCTION TO HANDLE EMPTY PIECES	
			bool isEmpty()const
				{
					if(color == 'x')return true;
					else return false;
				}
			
			//FUNCTION TO RETURN COLOR CHARACTER
			char getColor()const{
				return color;
			}
		private:
			char color;
	};
}
#endif
