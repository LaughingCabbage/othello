///@author Brock Ferrell
// CS2401
// November 23, 2015
// Project7

/**\file main.cc
*\breif
*contains the main file for the othello game
**/
#include "game.h"
#include "othello.h"
using namespace main_savitch_14;


int main()
{
	Othello theGame;
	theGame.restart();
	theGame.play();
}
