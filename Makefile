CXX      := g++
CXXFLAGS := -Wall
LDFLAGS  := -lglut -lGLU -lGL
BUILD    := ./Build
OBJ_DIR  := $(BUILD)/Objects
APP_DIR  := $(BUILD)/Apps
INC_DIR  := ./Include
TARGET   := marchingCube
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
	@mkdir -p $(OBJ_DIR)
	@find . -name "*.h" | xargs 

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*
	-@rm -fv ./$(TARGET)
	