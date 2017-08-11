all: doc build archive


build: game.o main.o board.o
	g++ game.o main.o board.o -o Othello
	rm *.o

archive: build
	tar -cvzf Othello.tar.gz makefile game.cc main.cc board.cc\
				colors.h game.h piece.h board.h LISCENSE.txt
doc: Doxyfile
	doxygen Doxyfile

game.o: game.cc game.h
	g++ -c game.cc

main.o: main.cc game.h board.h
	g++ -c main.cc

board.o: board.cc board.h game.h piece.h colors.h
	g++ -c board.cc

clean:
	rm -f *.o *~ Othello Othello.tar.gz
	rm -rf html latex
