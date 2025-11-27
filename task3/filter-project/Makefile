CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -Wpedantic

TARGET := filter
SOURCES := main.cpp image.cpp filters.cpp similarity.cpp
HEADERS := image.h filters.h similarity.h

GEN_TARGET := generate_test_image
GEN_SOURCES := generate_test_image.cpp image.cpp

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

$(GEN_TARGET): $(GEN_SOURCES) image.h
	$(CXX) $(CXXFLAGS) $(GEN_SOURCES) -o $(GEN_TARGET)

all: $(TARGET) $(GEN_TARGET)

clean:
	rm -f $(TARGET) $(GEN_TARGET) *.exe

