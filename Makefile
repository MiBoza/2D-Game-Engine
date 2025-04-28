CC := g++
purpose := "release"
LFLAGS := -lSDL2_image -lSDL2
Include := -I include

ifeq ($(purpose), "release")
	CFLAGS := -std=c++20 -w -fmax-errors=6 -s -O3
	build := release
else
	CFLAGS := -std=c++20 -w -fmax-errors=6 -g -fsanitize=address
	build := debug
endif

auxiliaries := $(build)/Aggregate.a $(build)/Timing.a $(build)/TextureManager.a $(build)/RigidBody.a $(build)/Object.a $(build)/Vector2.a

all: Vector2 Object RigidBody TextureManager Aggregate Timing Main Join
run:
	./$(build).obj
clean:
	rm -f $(wildcard *.obj) $(wildcard $(build)/*)
Join:
	$(CC) $(CFLAGS) $(build)/Main.a $(auxiliaries) $(LFLAGS) -o $(build).obj
HotFix:
	$(CC) $(CFLAGS) $(Include) source/Hot_Fix.cpp $(build)/Vector2.a -o Hot_Fix.obj
Main:
	$(CC) $(CFLAGS) $(Include) -c source/Main.cpp -o $(build)/Main.a
Aggregate:
	$(CC) $(CFLAGS) $(Include) -c source/Aggregate.cpp -o $(build)/Aggregate.a
Timing:
	$(CC) $(CFLAGS) $(Include) -c source/Timing.cpp -o $(build)/Timing.a
TextureManager:
	$(CC) $(CFLAGS) $(Include) -c source/TextureManager.cpp -o $(build)/TextureManager.a
RigidBody:
	$(CC) $(CFLAGS) $(Include) -c source/RigidBody.cpp -o $(build)/RigidBody.a
Object:
	$(CC) $(CFLAGS) $(Include) -c source/Object.cpp -o $(build)/Object.a
Vector2:
	$(CC) $(CFLAGS) $(Include) -c source/Vector2.cpp -o $(build)/Vector2.a
