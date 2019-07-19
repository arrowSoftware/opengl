# Required libraries: glut, glew, GL, glm, glfw3
# libglm-dev, libglfw3-dev libglew-dev

#OLD_SHELL := $(SHELL)
#SHELL = $(warning Building $@$(if $<, (from $<))$(if $?, ($? newer)))$(OLD_SHELL) -x

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
BLD_DIR  := ./Build
OBJ_DIR  := $(BLD_DIR)/Objects/$(BUILD)
APP_DIR  := $(BLD_DIR)/Apps/$(BUILD)
INC_DIR  := ./Include
TARGET   := opengl

INCLUDE  := -IInclude/ \
            -I./Source/ \
			-I./Source/Core/ \
			-I./Source/Core/Object/ \
			-I./Source/Core/Input/ \
			-I./Source/Core/Application/ \
			-I./Source/Core/Event/ \
			-I./Source/Core/Commands/ \
			-I./Source/Core/Shaders/ \
			-I./Source/Core/utils/ \
			-I./Source/Core/Camera/

SRC      := $(wildcard Source/Core/*.cpp) \
			$(wildcard Source/Core/Object/*.cpp) \
			$(wildcard Source/Core/Camera/*.cpp) \
			$(wildcard Source/Core/Input/*.cpp) \
			$(wildcard Source/Core/Application/*.cpp) \
			$(wildcard Source/Core/Event/*.cpp) \
			$(wildcard Source/Core/Commands/*.cpp) \
			$(wildcard Source/Core/Shaders/*.cpp) \
            $(wildcard Source/*.cpp)

OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)

#.PHONY: all build clean debug release

debug: CXXFLAGS += -DDEBUG
debug: all

release: CXXFLAGS += -O2
release: all

build:
	@mkdir -p $(APP_DIR)
	@cp ./Source/Shaders/* $(APP_DIR)
	@mkdir -p $(OBJ_DIR)
	@find . -name "*.h" | xargs

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $(APP_DIR)/$(TARGET) $(OBJECTS) $(LDFLAGS)
	@cp -v ./Source/Core/Shaders/* $(APP_DIR)/.
	#ln -s $(APP_DIR)/$(TARGET) ./$(TARGET)

clean:
	@rm -rvf $(OBJ_DIR)/*
	@rm -rvf $(APP_DIR)/*
	@rm -fv ./$(TARGET)
	@rm -fv $(INC_DIR)/*
