TASKNO=1

APP=tictactoe

OPTIONS=-std=c++2a -Iinc -W -Wall -pedantic

__start__: obj ./${APP}
	./${APP}

obj:
	mkdir obj

./${APP}: obj/main.o obj/Board.o obj/Game.o
	g++ ${OPTIONS} -o ./${APP} obj/main.o obj/Board.o obj/Game.o

obj/main.o: src/main.cpp inc/Board.hh inc/Game.hh
	g++ ${OPTIONS} -c -o obj/main.o src/main.cpp

obj/Board.o: src/Board.cpp inc/Board.hh
	g++ ${OPTIONS} -c -o obj/Board.o src/Board.cpp

obj/Game.o: src/Game.cpp inc/Game.hh inc/Board.hh
	g++ ${OPTIONS} -c -o obj/Game.o src/Game.cpp

clean:
	rm -f obj/* ./${APP} core.* core

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./tictactoe

help:
	@echo ""
	@echo " make          - tworzenie i uruchomienie aplikacji"
	@echo " make clean    - usuniecie produktow kompilacji i konsolidacji"
	@echo " make valgrind - debugowanie przy uzyciu valgrinda"
	@echo " make help     - wyswietla niniejsza informacje"
	@echo ""