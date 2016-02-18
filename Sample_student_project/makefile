all: build archive


build: game.o main.o othello.o
	g++ game.o main.o othello.o -o game
	rm *.o

archive: build
	tar -cvzf game.tar.gz makefile game.cc main.cc othello.cc\
				colors.h game.h piece.h othello.h

game.o: game.cc game.h
	g++ -c game.cc

main.o: main.cc game.h othello.h
	g++ -c main.cc

othello.o: othello.cc othello.h game.h piece.h piece.h
	g++ -c othello.cc

clean:
	rm *.o *~ game game.tar.gz
