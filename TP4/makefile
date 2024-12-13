CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Wpedantic \
          -Wformat=2 -Wno-unused-parameter -Wshadow -Wno-discarded-qualifiers \
          -Wwrite-strings -Wstrict-prototypes -Wold-style-definition \
          -Wredundant-decls -Wnested-externs -Wmissing-include-dirs \
			 -Wjump-misses-init -Wlogical-op -g -O3 -D_XOPEN_SOURCE=700

LFLAGS = # -lm
INCLUDE = -I./include

SOURCES = quicksort \
			 swap_functions \
			 process \
			 lib  \
			 linked_list

OBJECTS = $(addsuffix .o, $(SOURCES))

SRC_DIR = src
BUILD_DIR = build
MAIN_OUTPUT = main
EXPERIMENTS_OUTPUT = experiments_main

OBJECTS_DIR = $(addprefix $(BUILD_DIR)/, $(OBJECTS))

all: main

dir:
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

main: dir $(OBJECTS_DIR)
	$(CC) $(CFLAGS) -o $(MAIN_OUTPUT) $(SRC_DIR)/main.c $(OBJECTS_DIR) $(INCLUDE) $(LFLAGS)

experiments: dir $(OBJECTS_DIR)
	$(CC) $(CFLAGS) -o $(EXPERIMENTS_OUTPUT) $(SRC_DIR)/experiments.c $(OBJECTS_DIR) $(INCLUDE) $(LFLAGS)
	@echo
	./experiments_main
	gnuplot experiments/delay.gnu
	gnuplot experiments/ratio.gnu
	gnuplot experiments/constructive_heuristic.gnu
	gnuplot experiments/hill_climbing.gnu
	gnuplot experiments/ils.gnu

clean:
	rm -rf $(MAIN_OUTPUT) $(EXPERIMENTS_OUTPUT) $(BUILD_DIR) **/*.dat