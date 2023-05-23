# Directories
SRC_DIR := src
HEADER_DIR := $(SRC_DIR)/headers
SOURCE_DIR := $(SRC_DIR)/impl
BUILD_DIR := builds

# Commands
GXX := g++ -g -Wall -Werror -pthread -std=c++2a -O3

LINKER_LIBS := -lglfw3 -lopengl32 -lgdi32 -lglew32

# Files
HEADER_FILES = $(HEADER_DIR)/*.hpp
SOURCE_FILES = $(SOURCE_DIR)/*.cpp
MAIN_FILE := $(SRC_DIR)/main.cpp

# Arguements
EXE_NAME := $(BUILD_DIR)/Main.exe

# Calls
all: $(MAIN_FILE) $(HEADER_FILES) $(SOURCE_FILES)
	$(GXX) -c $(MAIN_FILE) -o CompiledFile.o
	$(GXX) $(SOURCE_FILES) CompiledFile.o -o $(EXE_NAME) $(LINKER_LIBS) 
	rm CompiledFile.o

clean: $(EXE_NAME)
	rm $(Build)/$(EXE_NAME)