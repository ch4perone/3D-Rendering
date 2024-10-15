CXX = g++
CXXFLAGS = -std=c++17 -lglut -lGLU -lGL
SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
TARGET = app

all: $(TARGET)

$(TARGET): $(SRC_FILES)
	$(CXX) $(SRC_FILES) -o $(TARGET) $(CXXFLAGS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)
