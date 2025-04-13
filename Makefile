CC = g++
debug = -g -fsanitize=address
release = -s -O3
purpose = $(debug)
CFLAGS = -std=c++20 -w -fmax-errors=6 $(purpose)
LFLAGS = -lSDL2_image -lSDL2
Include = -I include

all: Vector2 TextureManager Object RigidBody Game Timing Main Join

Join:
	$(CC) $(purpose) out/Main.a out/Game_Timing.a out/Game.a out/RigidBody.a out/Object.a out/TextureManager.a out/Vector2.a $(LFLAGS) -o debug.obj
HotFix:
	$(CC) $(CFLAGS) $(Include) source/Hot_Fix.cpp out/Vector2.a -o Hot_Fix.obj
Main:
	$(CC) $(CFLAGS) $(Include) -c source/Main.cpp -o out/Main.a
Timing:
	$(CC) $(CFLAGS) $(Include) -c source/Game_Timing.cpp -o out/Game_Timing.a
Game:
	$(CC) $(CFLAGS) $(Include) -c source/Game.cpp -o out/Game.a
RigidBody:
	$(CC) $(CFLAGS) $(Include) -c source/RigidBody.cpp -o out/RigidBody.a
Object:
	$(CC) $(CFLAGS) $(Include) -c source/Object.cpp -o out/Object.a
TextureManager:
	$(CC) $(CFLAGS) $(Include) -c source/TextureManager.cpp -o out/TextureManager.a
Vector2:
	$(CC) $(CFLAGS) $(Include) -c source/Vector2.cpp -o out/Vector2.a
