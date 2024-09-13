# Compiler
CC = clang

# Compiler flags
CFLAGS = -Wall -Werror

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = examples
INC_DIR = include

# Header directory for TinyDeep
INC_TINYDEEP_DIR = include/TinyDeep

# Source files and corresponding object files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Main source file and corresponding object file
MAIN_SRC = $(BIN_DIR)/hello_world_nn.c
MAIN_OBJ = $(OBJ_DIR)/hello_world_nn.o

# Executable name (extension changes based on OS)
TARGET = $(BIN_DIR)/hello_world_nn$(EXE)

# Platform-specific settings
ifeq ($(OS),Windows_NT)
    RM = -del
    RMDIR = rmdir /S /Q
    MKDIR = if not exist $(subst /,\\,$(1)) mkdir $(subst /,\\,$(1))
    EXE = .exe
else
    RM = rm -f
    RMDIR = rm -rf
    MKDIR = mkdir -p $(1)
    EXE = 
endif

# Default target
all: $(TARGET)

# Create the executable
$(TARGET): $(OBJ_FILES) $(MAIN_OBJ)
	$(call MKDIR,$(BIN_DIR))
	$(CC) $(CFLAGS) -I$(INC_TINYDEEP_DIR) -I$(INC_DIR) -o $@ $(OBJ_FILES) $(MAIN_OBJ)

# Compile each .c file into a .o file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(call MKDIR,$(OBJ_DIR))
	$(CC) $(CFLAGS) -I$(INC_TINYDEEP_DIR) -I$(INC_DIR) -c $< -o $@

# Compile the main source file into an object file
$(MAIN_OBJ): $(MAIN_SRC)
	$(call MKDIR,$(OBJ_DIR))
	$(CC) $(CFLAGS) -I$(INC_TINYDEEP_DIR) -I$(INC_DIR) -c $< -o $@

# Clean up object files and executable
clean:
	$(foreach file, $(OBJ_FILES) $(MAIN_OBJ), $(RM) $(subst /,\,$(file)) ;)
	$(RMDIR) $(OBJ_DIR)
	$(RM) $(subst /,\,$(TARGET))

# Phony targets
.PHONY: all clean
