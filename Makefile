# Required libraries: glut, glew, GL, glm, glfw3
# libglm-dev, libglfw3-dev libglew-dev

OSFLAG :=
ifeq ($(OS),Windows_NT)
	OSFLAG += -D WIN32
	ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
		OSFLAG += -D AMD64
	endif
	ifeq ($(PROCESSOR_ARCHITECTURE),x86)
		OSFLAG += -D IA32
	endif
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		OSFLAG  += -D LINUX
		LDFLAGS := -lglut -lGLU -lGL -lGLEW -lglfw
	endif
	ifeq ($(UNAME_S),Darwin)
		OSFLAG  += -D OSX
		LDFLAGS := /System/Library/Frameworks/GLUT.framework/GLUT /System/Library/Frameworks/OpenGL.framework/OpenGL -lGLEW -lglfw
	endif

	UNAME_P := $(shell uname -p)
	ifeq ($(UNAME_P),x86_64)
		OSFLAG += -D AMD64
	endif
		ifneq ($(filter %86,$(UNAME_P)),)
	OSFLAG += -D IA32
		endif
	ifneq ($(filter arm%,$(UNAME_P)),)
		OSFLAG += -D ARM
	endif
endif

CXX      := g++
CXXFLAGS := -Wall -std=c++11
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
	
