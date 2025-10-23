# compiler
CC = gcc

# compiler flags
FLAGS = -Wall -Werror -pedantic -Iinc

# external libraries to link
LINK = -lpng -lm -fopenmp

FLINK = -fopenmp

# pattern specific flags for targets
bin/%_profile  : FLAGS += -pg 
bin/%_freevar  : FLAGS += -Wno-unused-variable -Wno-unused-but-set-variable
bin/%_memcheck : FLAGS += -fsanitize=address -g3
bin/%_fast     : FLAGS += -O3 -DNDEBUG -march=native -flto
bin/%_debug    : FLAGS += -g3

# generic make object
obj/%.o : src/%.c inc/%.h | obj
	$(CC) $(FLAGS) -c -o $@ $< $(FLINK)

# make object for files with no header
obj/%.o : src/%.c | obj
	$(CC) $(FLAGS) -c -o $@ $< $(FLINK)

# generic make binary
bin/test_png_writ% : obj/test_png_write.o obj/png_utils.o obj/color.o | bin
	$(CC) $(FLAGS) -o $@ $^ $(LINK)

bin/fracta% : obj/fractal.o obj/png_utils.o obj/color.o obj/mandelbrot.o | bin
	$(CC) $(FLAGS) -o $@ $^ $(LINK)

.PRECIOUS: bin/% obj/%.o
.PHONY: clean

obj : 
	mkdir -p obj

bin : 
	mkdir -p bin

clean : 
	rm -rf obj bin *.log
