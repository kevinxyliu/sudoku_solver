evidence: board.h board.c solve.h solve.c evidence.c
	clang -Wall -g -O0 -o evidence board.c solve.c evidence.c

main: board.h board.c solve.h solve.c main.c
	clang -Wall -g -O0 -o main board.c solve.c main.c

board: board.h board.c evidence.c
	clang -Wall -g -O0 -o board board.c evidence.c
