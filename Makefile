CC = g++
CFLAGS = -Wall -Wextra -std=c++20 # Enable all compiler warnings, Use C++20
EXECUTABLE = a.out # Name of executable, *.out for unix executile
SOURCES = imageProcessor.cpp asa.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Compile executable file
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE)

# Compile object files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Reamove executable and object files
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)