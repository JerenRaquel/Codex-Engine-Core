# Directories
SRC_DIR := src
BUILD_DIR := builds
TOOLS_DIR := tools
LIBRARIES_DIR := $(SRC_DIR)/libs
ENGINE_DIR := $(SRC_DIR)/engine
SIMULATION_DIR := $(SRC_DIR)/simulation

# Header Directories
FREE_TYPE := $(LIBRARIES_DIR)/freetype
GLM := $(LIBRARIES_DIR)/glm

# Subdirectories
ENGINE_HEADER_DIR := $(ENGINE_DIR)/headers
ENGINE_SOURCE_DIR := $(ENGINE_DIR)/impl
SIMULATION_HEADER_DIR := $(SIMULATION_DIR)/headers
SIMULATION_SOURCE_DIR := $(SIMULATION_DIR)/impl
TRACY_DIR := $(TOOLS_DIR)/tracy

# Libraries
INCLUDE_PATHS := -I$(FREE_TYPE) -I$(GLM) -I$(ENGINE_HEADER_DIR) -I$(SIMULATION_HEADER_DIR)
LINKER_LIBS := -lglfw3 -lopengl32 -lgdi32 -lglew32 $(INCLUDE_PATHS) $(FREE_TYPE)/libfreetype.a
TRACY_LIBS := -L$(TRACY_DIR)/tracy -lws2_32 -lwinmm -ldbghelp

# Flags
GXX_WERROR_FLAGS := -Wall -Werror
GXX_FLAGS := -pthread -std=c++2a -O3
TRACY_FLAGS := -D_WIN32_WINNT=0x0602 -DWINVER=0x0602 -DTRACY_ENABLE

# Commands
GXX := g++ $(GXX_WERROR_FLAGS) $(GXX_FLAGS)
GXX_DEBUG := g++ -g $(GXX_FLAGS)

# Files
MAIN_FILE := $(SRC_DIR)/main.cpp
HEADER_FILES = $(ENGINE_HEADER_DIR)/*.hpp $(SIMULATION_HEADER_DIR)/*.hpp
SOURCE_FILES = $(ENGINE_SOURCE_DIR)/*.cpp $(SIMULATION_SOURCE_DIR)/*.cpp

# Arguements
EXE_NAME := $(BUILD_DIR)/Main.exe

# Calls
all: $(MAIN_FILE) $(HEADER_FILES) $(SOURCE_FILES)
	$(GXX) -c $(MAIN_FILE) -o CompiledFile.o $(INCLUDE_PATHS) 
	$(GXX) $(SOURCE_FILES) CompiledFile.o -o $(EXE_NAME) $(LINKER_LIBS) 
	rm CompiledFile.o

debug: $(MAIN_FILE) $(HEADER_FILES) $(SOURCE_FILES) $(TRACY_DIR)/tracy/Tracy.hpp $(TRACY_DIR)/TracyClient.cpp
	$(GXX_DEBUG) $(TRACY_FLAGS) -c $(MAIN_FILE) -o CompiledFile.o
	$(GXX_DEBUG) $(TRACY_FLAGS) $(SOURCE_FILES) CompiledFile.o $(TRACY_DIR)/TracyClient.cpp -o $(EXE_NAME) $(LINKER_LIBS) $(TRACY_LIBS)
	rm CompiledFile.o


clean: $(EXE_NAME)
	rm $(Build)/$(EXE_NAME)