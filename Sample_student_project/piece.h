// Brock Ferrell
// CS2401
// November 23, 2015
// Project7

/**
	\file piece.h
	\breif contains instructions for board pieces
**/
#ifndef PIECE_H
#define PIECE_H
/*****************************\enum color
*contains enumerations for colors.
****************************************/
/**\var black
black piece
**/
/**\var white
white piece
**/
/**\var blank
blank piece
**/
enum color {black, white, blank};
///	\class piece
class piece {
public:
	piece() {theColor = blank;}

	void flip()
	{
		if (theColor == white) {
			theColor = black;
		}
		else if (theColor == black) {
			theColor = white;
		}
	}

	bool is_blank()const {return theColor == blank;}
	bool is_black()const {return theColor == black;}
	bool is_white()const {return theColor == white;}
	void set_white() {theColor = white;}
	void set_black() {theColor = black;}

private:
	color theColor;

};

#endif

