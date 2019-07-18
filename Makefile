# Required libraries: glut, glew, GL, glm, glfw3
# libglm-dev, libglfw3-dev libglew-dev

CXX      := g++
CXXFLAGS := -Wall
LDFLAGS  := -lglut -lGLU -lGL -lGLEW -lglfw
BUILD    := ./Build
OBJ_DIR  := $(BUILD)/Objects
APP_DIR  := $(BUILD)/Apps
INC_DIR  := ./Include
TARGET   := opengl

INCLUDE  := -IInclude/ \
            -I./Source/Core/

SRC      := $(wildcard Source/Core/*.cpp) \
            $(wildcard Source/*.cpp)

OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $(APP_DIR)/$(TARGET) $(OBJECTS) $(LDFLAGS)
	#ln -s $(APP_DIR)/$(TARGET) ./$(TARGET) 

.PHONY: all build clean debug release

build:
	@mkdir -p $(APP_DIR)
	@cp ./Source/Shaders/* $(APP_DIR)
	@mkdir -p $(OBJ_DIR)
	@find . -name "*.h" | xargs 

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

clean:
	@rm -rvf $(OBJ_DIR)/*
	@rm -rvf $(APP_DIR)/*
	@rm -fv ./$(TARGET)
	@rm -fv $(INC_DIR)/*
	
