all: othello

othello: main.o game.o board.o
	g++ main.o game.o board.o -o othello

main.o: main.cc
	g++ -c main.cc

game.o: game.cc
	g++ -c game.cc

board.o: board.cc
	g++ -c board.cc

clean:
	rm  -f *.o *~
