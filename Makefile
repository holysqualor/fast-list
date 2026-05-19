CXX = g++

SRC = examples/demo.cpp
INCLUDE = include/fast_list.h
TARGET = build/build

$(TARGET): $(SRC) $(INCLUDE)
	@mkdir -p build
	@$(CXX) $(SRC) -Iinclude -o $(TARGET)