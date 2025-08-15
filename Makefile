CC := g++
LFLAGS := -lSDL2_image -lSDL2_ttf -lSDL2
Include := -I Project -I include

debug_CFLAGS := -std=c++20 -w -fmax-errors=6 -g -fsanitize=address
release_CFLAGS := -std=c++20 -w -fmax-errors=6 -s -O3


source_objects := Aggregate.o Aggregate2.o TextureManager.o RigidBody.o Object.o Vector2.o
project_objects := Input_Handler.o Main.o

debug_project := $(addprefix debug/,$(project_objects))
release_project := $(addprefix release/,$(project_objects))
debug_source := $(addprefix debug/,$(source_objects))
release_source := $(addprefix release/,$(source_objects))

Hot_Fix.obj: source/Hot_Fix.cpp
	$(CC) $(debug_CFLAGS) $^ $(LFLAGS) -o $@
clear:
	clear
clean:
	rm -f debug/Main.o debug/Input_Handler.o debug.obj
	rm -f release/Main.o release/Input_Handler.o release.obj

debug.obj: $(debug_project) $(debug_source)
	$(CC) $(debug_CFLAGS) $^ $(LFLAGS) -o $@
run_debug:
	./debug.obj
Project/Input_Handler.cpp:
	ln -s `realpath include/Default_Input.hpp` Project/Input_Handler.hpp
	ln -s `realpath source/Default_Input.cpp` Project/Input_Handler.cpp
$(debug_project): debug/%.o: Project/%.cpp
	$(CC) $(debug_CFLAGS) $(Include) -c $^ -o $@
$(debug_source): debug/%.o: source/%.cpp
	$(CC) $(debug_CFLAGS) $(Include) -c $^ -o $@


release.obj: $(release_project) release/Silly_Game.a
	$(CC) $(release_CFLAGS) $^ $(LFLAGS) -o $@
release/Silly_Game.a: $(release_source)
	ar -rcs release/Silly_Game.a $^
run_release:
	./release.obj
$(release_project): release/%.o: Project/%.cpp
	$(CC) $(release_CFLAGS) $(Include) -c $^ -o $@
$(release_source): release/%.o: source/%.cpp
	$(CC) $(release_CFLAGS) $(Include) -c $^ -o $@
