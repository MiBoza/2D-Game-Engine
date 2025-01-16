CC = g++
CFLAGS = -std=c++20 -w -fmax-errors=6
LFLAGS = -lSDL2 -lSDL2_image
Include = -I include

all: Game Main Join

Join:
	$(CC) out/Main.o out/Game.o  $(LFLAGS) -o debug.obj
Main:
	$(CC) $(CFLAGS) $(Include) -c source/Main.cpp -o out/Main.o
Game:
	$(CC) $(CFLAGS) $(Include) -c source/Game.cpp -o out/Game.o
