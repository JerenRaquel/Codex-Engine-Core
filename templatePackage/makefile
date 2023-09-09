#* ------------------------------------------------------------------
#*														GXX and Flags
#* ------------------------------------------------------------------
# Flags
GXX_WERROR_FLAGS := -Wall -Werror
GXX_FLAGS := -pthread -std=c++2a -O2 -mavx

# Commands
GXX := g++ $(GXX_WERROR_FLAGS) $(GXX_FLAGS)
GXX_DEBUG := g++ -g $(GXX_FLAGS)

#* ------------------------------------------------------------------
#*														Directories
#* ------------------------------------------------------------------
BUILD_DIR := build
CODEX := Codex-Engine-Core
ENGINE_DIR := $(CODEX)/engine
GENERATED_FILES_DIR := $(CODEX)/generatedFiles
LIBRARY_DIR := $(CODEX)/libs
SRC_DIR := src
# Subdirectories
FREE_TYPE := $(LIBRARY_DIR)/freetype
GLM := $(LIBRARY_DIR)/glm
IMGUI := $(LIBRARY_DIR)/imgui
OPENGL := $(LIBRARY_DIR)/opengl
STB := $(LIBRARY_DIR)/stb
UUID_V4 := $(LIBRARY_DIR)/uuid_v4

#* ------------------------------------------------------------------
#*													Linker Libraries
#* ------------------------------------------------------------------
LIB_INCLUDE_PATHS := -I$(FREE_TYPE) -I$(GLM) -I$(STB) -I$(UUID_V4) -I$(IMGUI)
INCLUDE_PATHS := $(LIB_INCLUDE_PATHS) -I$(ENGINE_DIR) 
LINKER_LIBS := $(OPENGL)/libglfw3.a $(BUILD_DIR)/glew32.dll -lopengl32 -lgdi32 $(INCLUDE_PATHS) $(FREE_TYPE)/libfreetype.a


#* ------------------------------------------------------------------
#*														FILES
#* ------------------------------------------------------------------
# Source Files
MAIN_SOURCE_FILE := $(SRC_DIR)/main.cpp
SOURCE_FILES := $(wildcard $(SRC_DIR)/impl/*.cpp)
SOURCE_FILES += $(wildcard $(SRC_DIR)/impl/**/*.cpp)

# Static Libraries
ENGINE := $(GENERATED_FILES_DIR)/engine.a
IMGUI := $(GENERATED_FILES_DIR)/imgui.a
STATIC_LIBRARIES := $(ENGINE) $(IMGUI)

# Object Files
MAIN_OBJECT_FILE := $(GENERATED_FILES_DIR)/main.o
SOURCE_OBJECT_FILES := $(addprefix $(GENERATED_FILES_DIR)/src/,$(addsuffix .o, $(basename $(notdir $(SOURCE_FILES)))))

# Build Files
REQUIRED_BUILD_FILES := $(MAIN_OBJECT_FILE)
REQUIRED_BUILD_FILES += $(SOURCE_OBJECT_FILES)
REQUIRED_BUILD_FILES += $(STATIC_LIBRARIES)

# Executable
EXE_NAME := $(BUILD_DIR)/main.exe

#* =======================================================
#* 										Commands
#* =======================================================
all: $(REQUIRED_BUILD_FILES)
	rm -f $(BUILD_DIR)/imgui.ini
	$(GXX) $(MAIN_OBJECT_FILE) $(SOURCE_OBJECT_FILES) -o $(EXE_NAME) $(STATIC_LIBRARIES) $(LINKER_LIBS) 

clean:
	rm -f $(REQUIRED_BUILD_FILES)
	rm -f $(EXE_NAME)
	rm -f $(BUILD_DIR)/imgui.ini

#* =======================================================
#* 										Object Files
#* =======================================================
# Main Object File
$(MAIN_OBJECT_FILE): $(MAIN_SOURCE_FILE)
	$(GXX) $< -c -o $@ $(INCLUDE_PATHS)
	
# Engine Object Files
$(ENGINE): 
	$(MAKE) -C $(CODEX) engine

$(IMGUI): 
	$(MAKE) -C $(CODEX) imgui

# Source Object Files
$(GENERATED_FILES_DIR)/src/%.o: $(SRC_DIR)/impl/%.cpp $(SRC_DIR)/headers/%.hpp
	$(GXX) $< -c -o $@ $(INCLUDE_PATHS)

$(GENERATED_FILES_DIR)/src/%.o: $(SRC_DIR)/impl/**/%.cpp $(SRC_DIR)/headers/**/%.hpp
	$(GXX) $< -c -o $@ $(INCLUDE_PATHS)