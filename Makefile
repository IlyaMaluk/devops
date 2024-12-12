CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
SOURCES = lab2/lab2/main.cpp lab2/lab2/TrigonometryClass.cpp lab2/lab2/factorial.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = my_program

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)
