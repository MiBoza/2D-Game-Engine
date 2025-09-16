CC := g++
# CC := x86_64-w64-mingw32-g++
LFLAGS := -lSDL2_image -lSDL2_ttf -lSDL2
Include := -I Project -I Include

debug_CFLAGS := -std=c++20 -w -fmax-errors=6 -g -fsanitize=address
release_CFLAGS := -std=c++20 -w -fmax-errors=6 -s -O3

source1 := Window_Data.o Others.o Silly_Core.o Silly_Core2.o
source2 := TextureManager.o RigidBody.o Object.o Vector2.o
source_objects := $(source1) $(source2)
project_objects := Main.o Counter.o Swirl.o

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
Silly_Debug.a: $(debug_source)
	ar -rcs $@ $^
run_debug: debug.obj
	./debug.obj
$(debug_project): debug/%.o: Project/%.cpp
	$(CC) $(debug_CFLAGS) $(Include) -c $^ -o $@
$(debug_source): debug/%.o: source/%.cpp
	$(CC) $(debug_CFLAGS) $(Include) -c $^ -o $@


release.obj: $(release_project) Silly_Release.a
	$(CC) $(release_CFLAGS) $^ $(LFLAGS) -o $@
Silly_Release.a: $(release_source)
	ar -rcs $@ $^
run_release: release.obj
	./release.obj
$(release_project): release/%.o: Project/%.cpp
	$(CC) $(release_CFLAGS) $(Include) -c $^ -o $@
$(release_source): release/%.o: source/%.cpp
	$(CC) $(release_CFLAGS) $(Include) -c $^ -o $@
