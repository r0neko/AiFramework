CXX = $(CROSS_COMPILE)g++

COMPILE_FLAGS = -Os -I../AiFramework/include -L../AiFramework/build -D_LINUX
CXX_FLAGS = -std=c++2a $(COMPILE_FLAGS)

.PHONY: all
all: AiFrameworkTestApp

AiFrameworkTestApp:
	@mkdir -p build
	$(CXX) $(CXX_FLAGS) -o build/$@ app.cpp -laifw
	@cp ../AiFramework/build/libaifw.so build/

run: AiFrameworkTestApp
	LD_LIBRARY_PATH=./build ./build/AiFrameworkTestApp

clean:
	rm -rf build
