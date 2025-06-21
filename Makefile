CC := g++
LFLAGS := -lSDL2_image -lSDL2
Include := -I Project -I include

debug_CFLAGS := -std=c++20 -w -fmax-errors=6 -g -fsanitize=address
release_CFLAGS := -std=c++20 -w -fmax-errors=6 -s -O3
Objects = $(target)/Input_Handler.a $(target)/Aggregate.a $(target)/Timing.a $(target)/TextureManager.a $(target)/RigidBody.a $(target)/Object.a $(target)/Vector2.a


HotFix:
	$(CC) $(CFLAGS) $(Include) source/Hot_Fix.cpp debug/Vector2.a -o Hot_Fix.obj

# target := debug
# debug.obj: debug/Main.a $(Objects)
# 	$(CC) $(debug_CFLAGS) debug/Main.a $(Objects) $(LFLAGS) -o debug.obj
# run_debug:
# 	./debug.obj
# clean_debug:
# 	rm -f release/Main.a release.obj
# debug/Main.a: Project/Main.cpp
# 	$(CC) $(debug_CFLAGS) $(Include) -c Project/Main.cpp -o debug/Main.a
# $(Objects): debug/%.a: source/%.cpp
# 	$(CC) $(debug_CFLAGS) $(Include) -c $^ -o $@

target := release
release.obj: release/Main.a $(Objects)
	$(CC) $(release_CFLAGS) release/Main.a $(Objects) $(LFLAGS) -o release.obj
run_release:
	./release.obj
clean_release:
	rm -f release/Main.a release.obj
release/Main.a: Project/Main.cpp
	$(CC) $(release_CFLAGS) $(Include) -c Project/Main.cpp -o release/Main.a
$(Objects): release/%.a: source/%.cpp
	$(CC) $(release_CFLAGS) $(Include) -c $^ -o $@
