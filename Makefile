# Compiler and flags
CC = gcc
CFLAGS = -Wall -I./include
LDFLAGS = -L./lib -lSDL2

# Source files and target
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
TARGET = my_sdl_app

# Build rules
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
