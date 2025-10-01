CC := g++
LFLAGS := -lSDL2_image -lSDL2_ttf -lSDL2
Include := -I ../../Include

release_CFLAGS := -std=c++20 -w -fmax-errors=6 -s -O3
debug_CFLAGS := -std=c++20 -w -fmax-errors=6 -g -fsanitize=address

source_objects := Main.o
debug_objects := $(addprefix debug/,$(source_objects))
release_objects := $(addprefix release/,$(source_objects))

clear:
	clear
clean:
	rm -f $(debug_objects) $(release_objects) debug.obj release.obj
$(debug_objects): debug/%.o: %.cpp
	$(CC) $(debug_CFLAGS) $(Include) -c $^ -o $@
debug.obj: $(debug_objects) ../../Silly_Debug.a
	$(CC) $(debug_CFLAGS) $^ $(LFLAGS) -o $@
run_debug: debug.obj
	./debug.obj

$(release_objects): release/%.o: %.cpp
	$(CC) $(release_CFLAGS) $(Include) -c $^ -o $@
release.obj: $(release_objects) ../../Silly_Release.a
	$(CC) $^ $(LFLAGS) -o $@
run_release: release.obj
	./release.obj
