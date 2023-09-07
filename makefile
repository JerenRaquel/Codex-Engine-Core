# Directories
SRC_DIR := src
BUILD_DIR := build
TOOLS_DIR := tools
LIBRARIES_DIR := $(SRC_DIR)/libs
ENGINE_DIR := $(SRC_DIR)/engine
SIMULATION_DIR := $(SRC_DIR)/simulation
OBJECT_DIR := $(SRC_DIR)/objFiles

# Library Directories
FREE_TYPE := $(LIBRARIES_DIR)/freetype
GLM := $(LIBRARIES_DIR)/glm
IMGUI := $(LIBRARIES_DIR)/imgui
OPENGL := $(LIBRARIES_DIR)/opengl
STB := $(LIBRARIES_DIR)/stb
UUID_V4 := $(LIBRARIES_DIR)/uuid_v4

# Subdirectories
ENGINE_HEADER_DIR := $(ENGINE_DIR)/headers
ENGINE_SOURCE_DIR := $(ENGINE_DIR)/impl
SIMULATION_HEADER_DIR := $(SIMULATION_DIR)/headers
SIMULATION_SOURCE_DIR := $(SIMULATION_DIR)/impl
TRACY_DIR := $(TOOLS_DIR)/tracy

# Libraries
LIB_INCLUDE_PATHS := -I$(FREE_TYPE) -I$(GLM) -I$(STB) -I$(UUID_V4) -I$(IMGUI)
INCLUDE_PATHS := $(LIB_INCLUDE_PATHS) -I$(ENGINE_HEADER_DIR) -I$(SIMULATION_HEADER_DIR) -I$(TRACY_DIR)/tracy 
LINKER_LIBS := $(OPENGL)/libglfw3.a $(BUILD_DIR)/glew32.dll -lopengl32 -lgdi32 $(INCLUDE_PATHS) $(FREE_TYPE)/libfreetype.a
TRACY_LIBS := -L$(TRACY_DIR)/tracy -lws2_32 -lwinmm -ldbghelp

# Flags
GXX_WERROR_FLAGS := -Wall -Werror
GXX_FLAGS := -pthread -std=c++2a -O2 -mavx
TRACY_FLAGS := -D_WIN32_WINNT=0x0602 -DWINVER=0x0602 -DTRACY_ENABLE

# Commands
GXX := g++ $(GXX_WERROR_FLAGS) $(GXX_FLAGS)
GXX_DEBUG := g++ -g $(GXX_FLAGS)

#* Files
MAIN_FILE := $(SRC_DIR)/main.cpp

# Header Files
IMGUI_HEADER_FILES := $(wildcard $(IMGUI)/*.h)

ENGINE_HEADER_FILES := $(wildcard $(ENGINE_HEADER_DIR)/*.hpp)
ENGINE_HEADER_FILES += $(wildcard $(ENGINE_HEADER_DIR)/**/*.hpp)
ENGINE_HEADER_FILES += $(wildcard $(ENGINE_HEADER_DIR)/**/**/*.hpp)

SIMULATION_HEADER_FILES := $(wildcard $(SIMULATION_HEADER_DIR)/*.hpp) 
SIMULATION_HEADER_FILES += $(wildcard $(SIMULATION_HEADER_DIR)/**/*.hpp)
SIMULATION_HEADER_FILES += $(wildcard $(SIMULATION_HEADER_DIR)/**/**/*.hpp)

HEADER_FILES = $(ENGINE_HEADER_FILES) $(SIMULATION_HEADER_FILES)

# Source Files
IMGUI_SOURCE_FILES := $(wildcard $(IMGUI)/*.cpp)

ENGINE_SOURCE_FILES := $(wildcard $(ENGINE_SOURCE_DIR)/*.cpp)
ENGINE_SOURCE_FILES +=  $(wildcard $(ENGINE_SOURCE_DIR)/**/*.cpp)
ENGINE_SOURCE_FILES +=  $(wildcard $(ENGINE_SOURCE_DIR)/**/**/*.cpp)

SIMULATION_SOURCE_FILES := $(wildcard $(SIMULATION_SOURCE_DIR)/*.cpp)
SIMULATION_SOURCE_FILES += $(wildcard $(SIMULATION_SOURCE_DIR)/**/*.cpp)
SIMULATION_SOURCE_FILES += $(wildcard $(SIMULATION_SOURCE_DIR)/**/**/*.cpp)

SOURCE_FILES = $(ENGINE_SOURCE_FILES) $(SIMULATION_SOURCE_FILES)

# Object Files 
IMGUI_OBJECT_FILES := $(addprefix $(OBJECT_DIR)/imgui/,$(addsuffix .o,$(basename $(notdir $(IMGUI_SOURCE_FILES)))))
OBJECT_FILES := $(IMGUI_OBJECT_FILES) $(addprefix $(OBJECT_DIR)/,$(addsuffix .o, $(basename $(notdir $(SOURCE_FILES)))))

# Executable Name
EXE_NAME := $(BUILD_DIR)/Main.exe

#* =======================================================
#* 										Commands
#* =======================================================
all: $(OBJECT_FILES) $(OBJECT_DIR)/main.o $(IMGUI_SOURCE_FILES) $(IMGUI_HEADER_FILES)
	rm -f $(BUILD_DIR)/imgui.ini
	$(GXX) $(OBJECT_FILES) $(OBJECT_DIR)/main.o -o $(EXE_NAME) $(LINKER_LIBS)
	
#TODO: Make it faster
debug: $(MAIN_FILE) $(HEADER_FILES) $(SOURCE_FILES) $(TRACY_DIR)/tracy/Tracy.hpp $(TRACY_DIR)/TracyClient.cpp
	$(GXX_DEBUG) $(TRACY_FLAGS) -c $(MAIN_FILE) -o debugMain.o $(INCLUDE_PATHS) 
	$(GXX_DEBUG) $(TRACY_FLAGS) -c $(TRACY_DIR)/TracyClient.cpp -o tracy.o $(INCLUDE_PATHS) $(TRACY_LIBS)
	$(GXX_DEBUG) $(TRACY_FLAGS) $(SOURCE_FILES) tracy.o debugMain.o -o $(EXE_NAME) $(INCLUDE_PATHS) $(LINKER_LIBS) $(TRACY_LIBS)
	rm tracy.o debugMain.o

clean:
	rm -f $(EXE_NAME) $(OBJECT_FILES) $(OBJECT_DIR)/main.o

#* =======================================================
#* 										Object Files
#* =======================================================
# Target Object File
$(OBJECT_DIR)/main.o: $(MAIN_FILE)
	$(GXX) -c $(MAIN_FILE) -o $@ $(INCLUDE_PATHS) 

# ImGui Object Files
$(OBJECT_DIR)/imgui/%.o: $(IMGUI_HEADER_FILES) $(IMGUI_SOURCE_FILES)
	$(GXX) $(addprefix $(IMGUI)/,$(addsuffix .cpp,$(basename $(notdir $@)))) -c -o $@ $(INCLUDE_PATHS)

# Engine Object Files
$(OBJECT_DIR)/%.o: $(ENGINE_SOURCE_DIR)/%.cpp $(ENGINE_HEADER_DIR)/%.hpp
	$(GXX) $< -c -o $@ $(INCLUDE_PATHS)

$(OBJECT_DIR)/%.o: $(ENGINE_SOURCE_DIR)/**/%.cpp $(ENGINE_HEADER_DIR)/**/%.hpp
	$(GXX) $< -c -o $@ $(INCLUDE_PATHS)

$(OBJECT_DIR)/%.o: $(ENGINE_SOURCE_DIR)/**/**/%.cpp $(ENGINE_HEADER_DIR)/**/**/%.hpp
	$(GXX) $< -c -o $@ $(INCLUDE_PATHS)

# Simulation Object Files
$(OBJECT_DIR)/%.o: $(SIMULATION_SOURCE_DIR)/%.cpp $(SIMULATION_HEADER_DIR)/%.hpp
	$(GXX) $< -c -o $@ $(INCLUDE_PATHS)

$(OBJECT_DIR)/%.o: $(SIMULATION_SOURCE_DIR)/**/%.cpp $(SIMULATION_HEADER_DIR)/**/%.hpp
	$(GXX) $< -c -o $@ $(INCLUDE_PATHS)

$(OBJECT_DIR)/%.o: $(SIMULATION_SOURCE_DIR)/**/**/%.cpp $(SIMULATION_HEADER_DIR)/**/**/%.hpp
	$(GXX) $< -c -o $@ $(INCLUDE_PATHS)

