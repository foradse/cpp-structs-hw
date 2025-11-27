CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -Wpedantic

TARGET := inheritarr
SOURCES := main.cpp dynarr.cpp arrtxt.cpp arrcsv.cpp
HEADERS := dynarr.h arrtxt.h arrcsv.h

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET).exe

clean:
	rm -f $(TARGET) *.exe *.txt *.csv

.PHONY: clean
