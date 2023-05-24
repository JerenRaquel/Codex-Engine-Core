# Directories
SRC_DIR := src
BUILD_DIR := builds
ENGINE_DIR := $(SRC_DIR)/engine
SIMULATION_DIR := $(SRC_DIR)/simulation

# Subdirectories
ENGINE_HEADER_DIR := $(ENGINE_DIR)/headers
ENGINE_SOURCE_DIR := $(ENGINE_DIR)/impl
SIMULATION_HEADER_DIR := $(SIMULATION_DIR)/headers
SIMULATION_SOURCE_DIR := $(SIMULATION_DIR)/impl

# Commands
GXX := g++ -g -Wall -Werror -pthread -std=c++2a -O3

LINKER_LIBS := -lglfw3 -lopengl32 -lgdi32 -lglew32

# Files
MAIN_FILE := $(SRC_DIR)/main.cpp
HEADER_FILES = $(ENGINE_HEADER_DIR)/*.hpp $(SIMULATION_HEADER_DIR)/*.hpp
SOURCE_FILES = $(ENGINE_SOURCE_DIR)/*.cpp $(SIMULATION_SOURCE_DIR)/*.cpp

# Arguements
EXE_NAME := $(BUILD_DIR)/Main.exe

# Calls
all: $(MAIN_FILE) $(HEADER_FILES) $(SOURCE_FILES)
	$(GXX) -c $(MAIN_FILE) -o CompiledFile.o
	$(GXX) $(SOURCE_FILES) CompiledFile.o -o $(EXE_NAME) $(LINKER_LIBS) 
	rm CompiledFile.o

clean: $(EXE_NAME)
	rm $(Build)/$(EXE_NAME)