/*************************
*******Kevin Gentile******
***EECE Ohio University***
*********12/01/15*********
*****Project 7: part 3***/

//board.cc
#include"board.h"
#include"colors.h"
#include"piece.h"
#include<iostream>
#include<cstdlib>

void printColor(std::string color);
//void printColorInverted(std::string color);
	
	//CONSTRUCTOR FOR CHILD: OTHELLO 
main_savitch_14::othello::othello(){
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			board[i][j] = new piece;
		}
	}
	whiteScore = 0;
	blackScore = 0;
	passes = 0;
	quitGame = false;
}

//COPY CONSTRUCTOR
main_savitch_14::othello::othello(const main_savitch_14::othello& other){
	piece* tmp;
	for(int i =0; i < 8; i++){
		for(int j=0; j < 8; j++){
			tmp = new piece(*other.board[i][j]);
			board[i][j] = tmp;
		}
	}
	whiteScore = other.whiteScore;
	blackScore = other.blackScore;
	passes = other.passes;
	quitGame = other.quitGame;
}

//ASSIGNMENT OPERATOR
main_savitch_14::othello& main_savitch_14::othello::operator=(const othello& other){
	if(this == &other)return *this;
	else{
		for(int i =0; i < 8; i++){
			for(int j=0; j < 8; j++){
				board[i][j] = other.board[i][j];
			}
		}
		whiteScore = other.whiteScore;
		blackScore = other.blackScore;
		passes = other.passes;
		quitGame = other.quitGame;
	}
}
//DESTRUCTOR
main_savitch_14::othello::~othello(){
	for(int i=0; i<8;i++){
		for(int j=0; j<8; j++){
			delete board[i][j];
		}
	}
}

void main_savitch_14::othello::printBoard()const{
	char m = 'A';
	//HANDLE FIRST ROW OF LETTER INDICIES
	cout << endl<<B_BLUE<<"  ";
	for(int i = 1; i<=8; i++,m++){
		cout<<B_BLUE<<"  "<<m<<"  ";
	}
	cout<<"  "<<RESET<<endl;
	//BEGIN PRINTING BOARD SPACES
		for(int i = 0; i < 8; i++){
			//HANDLE FIRST NUMBER COLUMN INDICIES
			cout<<B_BLUE<<" "<<i+1<<RESET;
		//HORIZONTAL: HANDLE ALTERNATING SPACE COLORS
			for(int j = 0; j < 8; j++){
				if(i%2 == 0){
					if(j%2==0){
						printColor("B_BLACK");
							board[i][j]->print("B_BLACK");
						printColor("B_BLACK");
					}else{
						printColor("B_RED");
							board[i][j]->print("B_RED");
						printColor("B_RED");
					}
				}else{
					if(j%2==0){
						printColor("B_RED");
							board[i][j]->print("B_RED");
						printColor("B_RED");
					}else{
						printColor("B_BLACK");
							board[i][j]->print("B_BLACK");
						printColor("B_BLACK");
					}
				}			
			}
			cout<<B_BLUE<<i+1<<" "<<RESET<<endl;
		}
		m = 'A'; //REINITALIZE LETTER INDEX FOR NEW PRINTING SEQUENCE
		
	//HANDLE FINAL ROW OF LETTER INDICIES
	cout<<B_BLUE<<"  ";
	for(int i = 1; i<=8; i++,m++){
		cout<<B_BLUE<<"  "<<m<<"  ";
	}
	cout<<"  "<<RESET<<endl;
}

main_savitch_14::othello* main_savitch_14::othello::clone()const{
	return new othello(*this);
}

void main_savitch_14::othello::compute_moves(std::queue<std::string>& moves)const{
	string str;
	for(int m = 0;m < 8;m++){
		for(int n = 0;n<8;n++){
			str= char(m+65);
			str+= char(n+49);
			if(is_legal(str)){
				moves.push(str);
			}
		}
	}
}

void main_savitch_14::othello::display_status()const{
	printBoard();
	cout<<"\t\t    Score\n"
		 <<"\t   Black: " <<blackScore<<"\t  White: "<<whiteScore<<endl;
	if(passes >= 1){
		cout<<"No moves. P	layer Passes.\n";
	}
	if(moves_completed() % 2 == 0)
		cout<<"White move.\n";
	else
		cout<<"Black move.\n"; 
}

int main_savitch_14::othello::evaluate()const{
	if(whiteScore==blackScore)return 0;
	if(whiteScore > blackScore)return -1;
	else return 1;
}

bool main_savitch_14::othello::is_game_over()const{
	if(whiteScore+blackScore == 64 || quitGame == true || passes == 2)
		return true;
	else
		return false;
}
	
bool main_savitch_14::othello::is_legal(const std::string& input)const{
	int column,row;
	bool u,ur,r,dr,d,dl,l,ul;
	int i,j;
	char move = 'x';
	u=ur=r=dr=d=dl=l=ul=false;
	column = -1;
	row = -1;
	if(moves_completed() % 2 == 0){
		move = 'w';
	}else{
		move = 'b';
	}
	//PARSE INPUT
	column = int(input[0])-65;
	row = int(input[1])-49;
	i = row;
	j = column;
	
	//CHECK FOR QUIT GAME. HANDLING QUIT IN MAKE MOVE
	if(input[0] == '0')return true;
	//CHECK TO 
	//SEE IF INPUT IS ON BOARD
	if(column > 7 || row > 7 || column < 0 || row < 0)return false;
	//CHECK TO SEE IF INPUT LOCATION IS ALREADY FILLED
	if(!board[row][column]->isEmpty())return false;
	//CLOCKWISE CHECK 8 DIRECTIONS FOR ANOTHER PIECE OF OPPOSITE COLOR
	
		//CHECK UP
	if(i - 1 >= 0 && !board[i-1][j]->isEmpty() && board[i-1][j]->getColor() != move){
		u=true;
	}
		//CHECK UP RIGHT
	if((i-1 >= 0 && j+1 < 8) && !board[i-1][j+1]->isEmpty() && board[i-1][j+1]->getColor() != move)
		ur=true;
		//CHECK RIGHT
	if(j + 1 < 8 && !board[i][j+1]->isEmpty() && board[i][j+1]->getColor() != move)
		r=true;
		//CHECK DOWN RIGHT
	if((i+1 < 8 && j+1 < 8) && !board[i+1][j+1]->isEmpty() && board[i+1][j+1]->getColor() != move)
		dr=true;
		//CHECK DOWN
	if(i+1 < 8 && !board[i+1][j]->isEmpty() && board[i+1][j]->getColor() != move)
		d=true;
		//CHECK DOWN LEFT
	if((i+1 < 8 && j-1 >=0) && !board[i+1][j-1]->isEmpty() && board[i+1][j-1]->getColor() != move)
		dl=true;
		//CHECK LEFT
	if(j-1 >=0 && !board[i][j-1]->isEmpty() && board[i][j-1]->getColor() != move)
		l=true;
		//CHECK UP LEFT
	if((j-1 >=0 && i-1 >= 0) && !board[i-1][j-1]->isEmpty() && board[i-1][j-1]->getColor() != move)
		ul=true;
	//IF ALL CASES ARE FALSE, THE MOVE IS NOT LEGAL
	if(u==false&&ur==false&&r==false&&dr==false&&d==false&&dl==false&&l==false&&ul==false)
	return false;
	
	//NEED TO CHECK FOR FLANKING PIECE

	bool flanks = false;		
			//CHECK FOR SUPERIOR FLANKING PIECE
	if(u){
		i = row;
		j = column;
		for(;i-1 >=0 && !board[i-1][j]->isEmpty();i--){
			if(board[i-1][j]->getColor() == move)flanks = true;
		}
	}
	if(ur){
		i = row;
		j = column;
			//CHECK FOR SUPERIOR RIGHT FLANKING PIECE
		for(;(i-1 >= 0 && j+1 < 8) && !board[i-1][j+1]->isEmpty();i--,j++){
			if(board[i-1][j+1]->getColor() == move)flanks = true;
		}
	}
	if(r){
			//CHECK RIGHT
		i = row;
		j = column;
			//CHECK FOR RIGHT FLANKING PIECE
		for(;j + 1 < 8 && !board[i][j+1]->isEmpty();j++){
			if(board[i][j+1]->getColor() == move)flanks = true;
		}
	}
	if(dr){
			//CHECK DOWN RIGHT
		i = row;
		j = column;
			//CHECK FOR INFERIOR RIGHT FLANKING PIECE
		for(;(i+1 < 8 && j+1 < 8) && !board[i+1][j+1]->isEmpty();i++,j++){
			if(board[i+1][j+1]->getColor() == move)flanks = true;
		}
	}
	if(d){
			//CHECK DOWN
		i = row;
		j = column;
			//CHECK FOR INFERIOR FLANKING PIECE
		for(;i+1 < 8 && !board[i+1][j]->isEmpty();i++){
			if(board[i+1][j]->getColor() == move)flanks = true;
		}
	}
	if(dl){
			//CHECK DOWN LEFT
		i = row;
		j = column;
			//CHECK FOR INFERIOR LEFT FLANKING PIECE
		for(;(i+1 < 8 && j-1 >=0) && !board[i+1][j-1]->isEmpty();i++,j--){
			if(board[i+1][j-1]->getColor() == move)flanks = true;
		}
	}
	if(l){
			//CHECK LEFT
		i = row;
		j = column;
		//CHECK FOR LEFT FLANKING PIECE
		for(;j-1 >=0 && !board[i][j-1]->isEmpty();j--){
			if(board[i][j-1]->getColor() == move)flanks = true;
		}
	}
	if(ul){
			//CHECK UP LEFT
		i = row;
		j = column;
			//CHECK FOR SUPERIOR LEFT FLANKING PIECE
		for(;(i-1 >=0 && j-1 >= 0) && !board[i-1][j-1]->isEmpty();i--,j--){
			if(board[i-1][j-1]->getColor() == move)flanks = true;
		}
	}
	if(flanks)return true;
	else return false;
}

void main_savitch_14::othello::restart(){
	for(int i =0; i < 8; i++){
		for(int j=0; j<8;j++){
			board[i][j]->setPiece('x');
		}
	}
	game::restart();
	setInitialPieces();
}
	
void main_savitch_14::othello::setInitialPieces(){
	board[3][3]->setPiece('w');
	board[4][4]->setPiece('w');
	board[3][4]->setPiece('b');
	board[4][3]->setPiece('b');
	
}

const std::string main_savitch_14::othello::getMove(){
	return get_user_move();
}

void main_savitch_14::othello::make_move(const std::string& input){
	int column,row;
	char move = 'x';
	//HANDLING QUIT GAME
	if(input[0] == '0'){
		quitGame = true;
		return;
	}
	
	//PARSE INPUT
	column = int(input[0])-65;
	row = int(input[1])-49;

	if(moves_completed() % 2 == 0){
		board[row][column]->setPiece('w');
		move = 'w';
	}else{
		board[row][column]->setPiece('b');
		move = 'b';
	}
	
	int i,j; //INDEXING VALUES
	bool validCheck = false; //DETERMINES IF FLANKING PIECE EXISTS

	//CHECK FOR PEICES TO FLIP WORKING CLOCKWISE
	
			//CHECK UP
	i = row;
	j = column;
			//CHECK FOR SUPERIOR FLANKING PIECE
	for(;i-1 >=0 && !board[i-1][j]->isEmpty();i--){
		if(board[i-1][j]->getColor() == move)validCheck = true;
	}
	i = row;
	j = column;
	for(;validCheck &&
		  i - 1 >= 0 && 
		 !board[i-1][j]->isEmpty() && 
		  board[i-1][j]->getColor() != move
		 	;i--){

		board[i-1][j]->flip();
	}
	
			//CHECK UP RIGHT
	i = row;
	j = column;
	validCheck = false;
			//CHECK FOR SUPERIOR RIGHT FLANKING PIECE
	for(;(i-1 >= 0 && j+1 < 8) && !board[i-1][j+1]->isEmpty();i--,j++){
		if(board[i-1][j+1]->getColor() == move)validCheck = true;
	}
	i = row;
	j = column;
	for(;validCheck &&
		 (i-1 >= 0 && j+1 < 8) && 
		  !board[i-1][j+1]->isEmpty() &&
		  board[i-1][j+1]->getColor() != move
		  ;i--,j++){
		board[i-1][j+1]->flip();	
	}
	
		//CHECK RIGHT
	i = row;
	j = column;
	validCheck = false;
		//CHECK FOR RIGHT FLANKING PIECE
	for(;j + 1 < 8 && !board[i][j+1]->isEmpty();j++){
		if(board[i][j+1]->getColor() == move)validCheck = true;
	}
	i = row;
	j = column;
	for(;validCheck &&
		  j + 1 < 8 && 
		 !board[i][j+1]->isEmpty() &&
		  board[i][j+1]->getColor() != move
		 ;j++){
		board[i][j+1]->flip();
	}	
	
		//CHECK DOWN RIGHT
	i = row;
	j = column;
	validCheck = false;
		//CHECK FOR INFERIOR RIGHT FLANKING PIECE
	for(;(i+1 < 8 && j+1 < 8) && !board[i+1][j+1]->isEmpty();i++,j++){
		if(board[i+1][j+1]->getColor() == move)validCheck = true;
	}
	i = row;
	j = column;
	for(;validCheck &&
		 (i+1 < 8 && j+1 < 8) &&
		 !board[i+1][j+1]->isEmpty() &&
		  board[i+1][j+1]->getColor() != move
		 ;i++,j++){
		board[i+1][j+1]->flip();
	}
	
		//CHECK DOWN
	i = row;
	j = column;
	validCheck = false;
		//CHECK FOR INFERIOR FLANKING PIECE
	for(;i+1 < 8 && !board[i+1][j]->isEmpty();i++){
		if(board[i+1][j]->getColor() == move)validCheck = true;
	}
	i = row;
	j = column;
	for(;validCheck &&
		  i+1 < 8 &&
		 !board[i+1][j]->isEmpty() &&
		 board[i+1][j]->getColor() != move
		 ;i++){
		board[i+1][j]->flip();
	}
		//CHECK DOWN LEFT
	i = row;
	j = column;
	validCheck = false;
		//CHECK FOR INFERIOR LEFT FLANKING PIECE
	for(;(i+1 < 8 && j-1 >=0) && !board[i+1][j-1]->isEmpty();i++,j--){
		if(board[i+1][j-1]->getColor() == move)validCheck = true;
	}
	i = row;
	j = column;
	for(;validCheck &&
		 (i+1 < 8 && j-1 >=0) && 
		 !board[i+1][j-1]->isEmpty() &&
		 board[i+1][j-1]->getColor() != move
		 ;i++,j--){
		board[i+1][j-1]->flip();
	}
	
		//CHECK LEFT
	i = row;
	j = column;
	validCheck = false;
	//CHECK FOR LEFT FLANKING PIECE
	for(;j-1 >=0 && !board[i][j-1]->isEmpty();j--){
		if(board[i][j-1]->getColor() == move)validCheck = true;
	}
	i = row;
	j = column;
	for(;validCheck &&
		  j-1 >=0 && 
		 !board[i][j-1]->isEmpty() &&
		  board[i][j-1]->getColor() != move
		 ;j--){
		board[i][j-1]->flip(); 
	}
		
		//CHECK UP LEFT
	i = row;
	j = column;
	validCheck = false;
		//CHECK FOR SUPERIOR LEFT FLANKING PIECE
	for(;(i-1 >=0 && j-1 >= 0) && !board[i-1][j-1]->isEmpty();i--,j--){
		if(board[i-1][j-1]->getColor() == move)validCheck = true;
	}
	i = row;
	j = column;
	for(;validCheck &&
		 (i-1 >=0 && j-1 >= 0) && 
		 !board[i-1][j-1]->isEmpty() &&
		  board[i-1][j-1]->getColor() != move
		 ;i--,j--){
		board[i-1][j-1]->flip();
	}
	
	//UPDATE SCORING
	whiteScore = 0;
	blackScore = 0;
	for(i = 0; i < 8; i++){
		for(j = 0; j < 8; j++){
			if(board[i][j]->isWhite())
				whiteScore++;
			else if(board[i][j]->isBlack())
				blackScore++;
		}
	}
	//NEED TO CHECK FOR AT LEAST ONE VALID MOVE AFTER MOVE IS MADE
	bool valid = false;
	string str;
	row = 0;
	column  = 0;
	for(int m = 0;m < 8;m++){
		for(int n = 0;n<8;n++){
			str= char(m+65);
			str+= char(n+49);
			if(is_legal(str)){
				valid = true;
			}
		}
	}
	if(valid == false){
		passes++;
		game::make_move(input);
		return;
	}
	passes = 0;
	game::make_move(input);	
}
	
void printColor(std::string color){
	if(color == "B_BLACK"){
		for(int i =0; i < 2;i++){
			cout<<B_BLACK<<" ";
		}
		cout<<RESET;
	}else if(color == "B_RED"){
		for(int i = 0; i <2;i++){
			cout<<B_RED<<" ";
		}
		cout<<RESET;
	}
	else cout<<"Improper use of printColor\n\n";
}












