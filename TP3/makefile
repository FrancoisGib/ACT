CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Wpedantic \
          -Wformat=2 -Wno-unused-parameter -Wshadow -Wno-discarded-qualifiers \
          -Wwrite-strings -Wstrict-prototypes -Wold-style-definition \
          -Wredundant-decls -Wnested-externs -Wmissing-include-dirs \
			 -Wjump-misses-init -Wlogical-op -g -O3 -D_XOPEN_SOURCE=700

LFLAGS = -lm
INCLUDE = # -I./include

SOURCES = lib \
		  linked_list \
		  tree \
		  http_tree \
		  parsing \
		  logger \
		  http

OBJECTS = $(addsuffix .o, $(SOURCES))

SRC_DIR = src
BUILD_DIR = build
MAIN_OUTPUT = main

dir:
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

$(BUILD_DIR)/%-no-ssl.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

main: dir $(OBJECTS_DIR)
	$(CC) $(CFLAGS) -o $(MAIN_OUTPUT) $(SRC_DIR)/main.c $(OBJECTS_DIR) $(INCLUDE) $(LFLAGS)

clean:
	rm -rf logs $(MAIN_OUTPUT) $(BUILD_DIR)