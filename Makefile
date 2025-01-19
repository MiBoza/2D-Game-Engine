CC = g++
debug = -g -fsanitize=address
CFLAGS = -std=c++20 -w -fmax-errors=6 $(debug)
LFLAGS = -lSDL2_image -lSDL2
Include = -I include

all: Object Game Main Join

Join:
	$(CC) $(debug) out/Main.a out/Game.a out/Object.a out/Vector2.a $(LFLAGS) -o debug.obj
Main:
	$(CC) $(CFLAGS) $(Include) -c source/Main.cpp -o out/Main.a
Game:
	$(CC) $(CFLAGS) $(Include) -c source/Game.cpp -o out/Game.a
Object:
	$(CC) $(CFLAGS) $(Include) -c source/Object.cpp -o out/Object.a
Vector2:
	$(CC) $(CFLAGS) $(Include) -c source/Vector2.cpp -o out/Vector2.a
