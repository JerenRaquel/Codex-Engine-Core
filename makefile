# Directories
BUILD_DIR := build
TOOLS_DIR := tools
LIBRARIES_DIR := libs
ENGINE_DIR := engine
GENERATED_FILES_DIR := generatedFiles

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

# Libraries
LIB_INCLUDE_PATHS := -I$(FREE_TYPE) -I$(GLM) -I$(STB) -I$(UUID_V4) -I$(IMGUI)
INCLUDE_PATHS := $(LIB_INCLUDE_PATHS) -I$(ENGINE_HEADER_DIR) 
LINKER_LIBS := $(OPENGL)/libglfw3.a $(BUILD_DIR)/glew32.dll -lopengl32 -lgdi32 $(INCLUDE_PATHS) $(FREE_TYPE)/libfreetype.a

# Flags
GXX_WERROR_FLAGS := -Wall -Werror
GXX_FLAGS := -pthread -std=c++2a -O2 -mavx

# Commands
GXX := g++ $(GXX_WERROR_FLAGS) $(GXX_FLAGS)
GXX_DEBUG := g++ -g $(GXX_FLAGS)

#* =======================================================
#* 													Files
#* =======================================================
# Header Files
IMGUI_HEADER_FILES := $(wildcard $(IMGUI)/*.h)

ENGINE_HEADER_FILES := $(wildcard $(ENGINE_HEADER_DIR)/*.hpp)
ENGINE_HEADER_FILES += $(wildcard $(ENGINE_HEADER_DIR)/**/*.hpp)
ENGINE_HEADER_FILES += $(wildcard $(ENGINE_HEADER_DIR)/**/**/*.hpp)

# Source Files
IMGUI_SOURCE_FILES := $(wildcard $(IMGUI)/*.cpp)

ENGINE_SOURCE_FILES := $(wildcard $(ENGINE_SOURCE_DIR)/*.cpp)
ENGINE_SOURCE_FILES +=  $(wildcard $(ENGINE_SOURCE_DIR)/**/*.cpp)
ENGINE_SOURCE_FILES +=  $(wildcard $(ENGINE_SOURCE_DIR)/**/**/*.cpp)

# Object Files 
IMGUI_OBJECT_FILES := $(addprefix $(GENERATED_FILES_DIR)/imgui/,$(addsuffix .o,$(basename $(notdir $(IMGUI_SOURCE_FILES)))))
ENGINE_OBJECT_FILES := $(addprefix $(GENERATED_FILES_DIR)/engine/,$(addsuffix .o, $(basename $(notdir $(ENGINE_SOURCE_FILES)))))

# Static Libraries
STATIC_ENGINE := $(GENERATED_FILES_DIR)/engine.a
STATIC_IMGUI := $(GENERATED_FILES_DIR)/imgui.a
STATIC_LIBRARIES := $(STATIC_ENGINE) $(STATIC_IMGUI)

#* =======================================================
#* 										Commands
#* =======================================================
engine: $(STATIC_ENGINE)

imgui: $(STATIC_IMGUI)
	
#* =======================================================
#* 										Clean Commands
#* =======================================================
clean: cleanEngine cleanImGui

cleanEngine:
	rm -f $(ENGINE_OBJECT_FILES) $(STATIC_ENGINE)

cleanImGui:
	rm -f $(IMGUI_OBJECT_FILES) $(STATIC_IMGUI)

#* =======================================================
#* 										Library Creation
#* =======================================================
$(STATIC_ENGINE): $(ENGINE_OBJECT_FILES) $(ENGINE_HEADER_FILES)
	ar rcvs $@ $(ENGINE_OBJECT_FILES)

$(STATIC_IMGUI): $(IMGUI_OBJECT_FILES) $(IMGUI_HEADER_FILES)
	ar rcvs $@ $(IMGUI_OBJECT_FILES)

#* =======================================================
#* 										Object Files
#* =======================================================
# ImGui Object Files
$(GENERATED_FILES_DIR)/imgui/%.o: $(IMGUI_HEADER_FILES) $(IMGUI_SOURCE_FILES)
	$(GXX) $(addprefix $(IMGUI)/,$(addsuffix .cpp,$(basename $(notdir $@)))) -c -o $@ $(INCLUDE_PATHS)

# Engine Object Files
$(GENERATED_FILES_DIR)/engine/%.o: $(ENGINE_SOURCE_DIR)/%.cpp $(ENGINE_HEADER_DIR)/%.hpp
	$(GXX) $< -c -o $@ $(INCLUDE_PATHS)

$(GENERATED_FILES_DIR)/engine/%.o: $(ENGINE_SOURCE_DIR)/**/%.cpp $(ENGINE_HEADER_DIR)/**/%.hpp
	$(GXX) $< -c -o $@ $(INCLUDE_PATHS)

$(GENERATED_FILES_DIR)/engine/%.o: $(ENGINE_SOURCE_DIR)/**/**/%.cpp $(ENGINE_HEADER_DIR)/**/**/%.hpp
	$(GXX) $< -c -o $@ $(INCLUDE_PATHS)
