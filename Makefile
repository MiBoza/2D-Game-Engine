CC := g++
purpose := "debug"
LFLAGS := -lSDL2_image -lSDL2
Include := -I include

ifeq ($(purpose), "release")
	CFLAGS := -std=c++20 -w -fmax-errors=6 -s -O3
	target := release.obj
else
	CFLAGS := -std=c++20 -w -fmax-errors=6 -g -fsanitize=address
	target := debug.obj
endif

auxiliaries := out/Timing.a out/Aggregate.a out/RigidBody.a out/Object.a out/TextureManager.a out/Vector2.a

all: Vector2 TextureManager Object RigidBody Aggregate Timing Main Join

clean:
	rm -f $(wildcard *.obj) $(wildcard out/*)
Join:
	$(CC) $(CFLAGS) out/Main.a out/Aggregate.a out/Timing.a out/RigidBody.a out/Object.a out/TextureManager.a out/Vector2.a $(LFLAGS) -o debug.obj
HotFix:
	$(CC) $(CFLAGS) $(Include) source/Hot_Fix.cpp -o Hot_Fix.obj
Main:
	$(CC) $(CFLAGS) $(Include) -c source/Main.cpp -o out/Main.a
Aggregate:
	$(CC) $(CFLAGS) $(Include) -c source/Aggregate.cpp -o out/Aggregate.a
Timing:
	$(CC) $(CFLAGS) $(Include) -c source/Timing.cpp -o out/Timing.a
RigidBody:
	$(CC) $(CFLAGS) $(Include) -c source/RigidBody.cpp -o out/RigidBody.a
Object:
	$(CC) $(CFLAGS) $(Include) -c source/Object.cpp -o out/Object.a
TextureManager:
	$(CC) $(CFLAGS) $(Include) -c source/TextureManager.cpp -o out/TextureManager.a
Vector2:
	$(CC) $(CFLAGS) $(Include) -c source/Vector2.cpp -o out/Vector2.a


#Tests

Open_Window:
	$(CC) $(CFLAGS) $(Include) -c Tests/Open_Window.cpp -o out/Open_Window.a
	$(CC) $(CFLAGS) out/Open_Window.a $(auxiliaries) $(LFLAGS) -o Open_Window.obj
Objects_Swirl:
	$(CC) $(CFLAGS) $(Include) -c Tests/Objects_Swirl.cpp -o out/Objects_Swirl.a
	$(CC) $(CFLAGS) out/Objects_Swirl.a $(auxiliaries) $(LFLAGS) -o Objects_Swirl.obj
