CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lraylib

SRC = main.c fcanvas.c fractals.c
BUILD_DIR = build/
OBJ = $(patsubst %.c,$(BUILD_DIR)%.o,$(SRC))
TARGET = bin/denpng

all: $(TARGET)

$(TARGET): $(OBJ) | bin
	$(CC) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

bin:
	mkdir -p bin

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)
