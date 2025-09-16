CC := g++
LFLAGS := -lSDL2_image -lSDL2_ttf -lSDL2
Include := -I Include

Game := Blocks
Silly_Debug := ../../Silly_Debug.a
Silly_Release := ../../Silly_Release.a
debug_CFLAGS := -std=c++20 -w -fmax-errors=6 -g -fsanitize=address
release_CFLAGS := -std=c++20 -w -fmax-errors=6 -s -O3

source_objects := Main.o Blocks.o
debug_objects := $(addprefix debug/,$(source_objects))
release_objects := $(addprefix release/,$(source_objects))

clear:
	clear
clean:
	rm -f $(debug_objects) $(release_objects) debug.obj release.obj
debug.obj: $(debug_objects) $(Silly_Debug)
	$(CC) $(debug_CFLAGS) $^ $(LFLAGS) -o $@
release.obj: $(release_objects) $(Silly_Release)
	$(CC) $(release_CFLAGS) $^ $(LFLAGS) -o $@
run_debug: debug.obj
	./debug.obj
run_release: release.obj
	./release.obj
$(debug_objects): debug/%.o: %.cpp
	$(CC) $(debug_CFLAGS) $(Include) -c $^ -o $@
$(release_objects): release/%.o: %.cpp
	$(CC) $(release_CFLAGS) $(Include) -c $^ -o $@
