# Compiler and linker
CC = gcc
LD = gcc

# Paths
PATH_INCLUDE = include
PATH_LIB = lib
PATH_BIN = bin
PATH_DEBUG = debug

# Source and output paths
SRC = $(shell find src -name "*.c")
OBJ = $(SRC:%.c=$(PATH_DEBUG)/%.o)
DEP = $(SRC:%.c=$(PATH_DEBUG)/%.d)

# Output binary
OUT = $(PATH_BIN)/my_sdl_app

# Include and library flags
INCFLAGS = -I$(PATH_INCLUDE) -I$(PATH_INCLUDE)/SDL2
LDFLAGS = -L$(PATH_LIB) -lSDL2 -lSDL2_ttf -lSDL2_mixer -lm

# Compiler flags
CCFLAGS  = -std=c2x
CCFLAGS += -O2
CCFLAGS += -g
CCFLAGS += -Wall
CCFLAGS += -Wextra
CCFLAGS += -Wpedantic
CCFLAGS += -Wfloat-equal
CCFLAGS += -Wstrict-aliasing
CCFLAGS += -Wswitch-default
CCFLAGS += -Wformat=2
CCFLAGS += -Wno-unused-parameter

# Detect OS and set specific flags
UNAME := $(shell uname -s)
ifeq ($(UNAME),Darwin)
    CCFLAGS += -DAPPLE
else ifeq ($(UNAME),Linux)
    LDFLAGS += -lSDL2_image
endif

# Include dependency files
-include $(DEP)

# Default target
all: dirs $(OUT)

# Create required directories
dirs:
	mkdir -p $(PATH_BIN) $(PATH_DEBUG)

# Link the binary
$(OUT): $(OBJ)
	$(LD) -o $@ $^ $(LDFLAGS)

# Compile source files into object files
$(PATH_DEBUG)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) -o $@ -MMD -c $(CCFLAGS) $(INCFLAGS) $<

# Clean build files
clean:
	rm -rf $(PATH_BIN) $(PATH_DEBUG)

# Print variables (for debugging)
print-%:
	@echo $($*)
