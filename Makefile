CC := g++
LFLAGS := -lSDL2_image -lSDL2_ttf -lSDL2
Include := -I Project -I include

debug_CFLAGS := -std=c++20 -w -fmax-errors=6 -g -fsanitize=address
release_CFLAGS := -std=c++20 -w -fmax-errors=6 -s -O3


source_objects := Aggregate.a Aggregate2.a TextureManager.a RigidBody.a Object.a Vector2.a
project_objects := Input_Handler.a Main.a

debug_project := $(addprefix debug/,$(project_objects))
release_project := $(addprefix release/,$(project_objects))
debug_source := $(addprefix debug/,$(source_objects))
release_source := $(addprefix release/,$(source_objects))

Hot_Fix.obj: source/Hot_Fix.cpp
	$(CC) $(debug_CFLAGS) $^ $(LFLAGS) -o $@
clear:
	clear
clean:
	rm -f debug/Main.a debug/Input_Handler.a debug.obj
	rm -f release/Main.a release/Input_Handler.a release.obj

debug.obj: $(debug_project) $(debug_source)
	$(CC) $(debug_CFLAGS) $^ $(LFLAGS) -o $@
run_debug:
	./debug.obj
Project/Input_Handler.cpp:
	ln -s `realpath include/Default_Input.hpp` Project/Input_Handler.hpp
	ln -s `realpath source/Default_Input.cpp` Project/Input_Handler.cpp
$(debug_project): debug/%.a: Project/%.cpp
	$(CC) $(debug_CFLAGS) $(Include) -c $^ -o $@
$(debug_source): debug/%.a: source/%.cpp
	$(CC) $(debug_CFLAGS) $(Include) -c $^ -o $@

release.obj: $(release_project) $(release_source)
	$(CC) $(release_CFLAGS) $^ $(LFLAGS) -o $@
run_release:
	./release.obj
$(release_project): release/%.a: Project/%.cpp
	$(CC) $(release_CFLAGS) $(Include) -c $^ -o $@
$(release_source): release/%.a: source/%.cpp
	$(CC) $(release_CFLAGS) $(Include) -c $^ -o $@
