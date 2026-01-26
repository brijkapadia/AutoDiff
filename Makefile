CC := gcc
CFLAGS_DEBUG := -g -Wall -Wextra -Werror -Iinclude -fanalyzer -fsanitize=address 
CFLAGS_RELEASE := -O3 -Wall -Wextra -Werror -Iinclude

SRC := $(wildcard src/*.c)
MAIN := src/main.c
BIN_DEBUG := bin/debug
BIN_RELEASE := bin/release

all: $(BIN_DEBUG)

$(BIN_DEBUG): $(SRC)
	$(CC) $(CFLAGS_DEBUG) $(MAIN) -o $(BIN_DEBUG)

$(BIN_RELEASE): $(SRC)
	$(CC) $(CFLAGS_RELEASE) $(MAIN) -o $(BIN_RELEASE)

run: $(BIN_DEBUG)
	./$(BIN_DEBUG)

run-release: $(BIN_RELEASE)
	./$(BIN_RELEASE)

clean:
	rm -f $(BIN_DEBUG) $(BIN_RELEASE)
