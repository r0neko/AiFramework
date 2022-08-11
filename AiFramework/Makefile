CXX = $(CROSS_COMPILE)g++
CC = $(CROSS_COMPILE)gcc
AR = $(CROSS_COMPILE)ar
OBJ_COPY = $(CROSS_COMPILE)objcopy

OBJ_DIR = build/.temp

SRC_FILES = $(shell find src -type f -name '*.c*')
OBJ_FILES = $(patsubst src/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))
OBJ_FILES_NOTDIR = $(patsubst src/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

COMPILE_FLAGS = -Os -Wall -I./include -I./vendor/glad/include -D_LINUX -D_X11 -D_BUILD_AI_FRAMEWORK
CXX_FLAGS = -std=c++2a $(COMPILE_FLAGS)

%.o: %.c
	mkdir build -p
	mkdir $(OBJ_DIR) -p
	$(CC) $(COMPILE_FLAGS) -g -O -c $< -fPIC -o $(OBJ_DIR)/$(notdir $@)

$(OBJ_DIR)/%.o: src/%.cpp
	mkdir build -p
	mkdir $(OBJ_DIR) -p
	$(CXX) $(CXX_FLAGS) -g -O -c $< -fPIC -o $(OBJ_DIR)/$(notdir $@)

.PHONY: all
all: libaifw.so

glad: vendor/glad/src/glad.o

libaifw.so: glad $(OBJ_FILES)
	$(CXX) -shared $(CXX_FLAGS) -o build/$@ $(shell find $(OBJ_DIR) -type f -name '*.o*') -ldl -lX11 -lGL -lGLU

clean:
	rm -rf build