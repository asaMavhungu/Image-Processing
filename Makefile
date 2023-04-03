CC = g++
CFLAGS = -Wall -Wextra -std=c++20 # Enable all compiler warnings, Use C++20

SOURCES = imageProcessor.cpp connectedComponent.cpp
DRIVER = $(if $(filter test,$(MAKECMDGOALS)),driver_test.cpp,driver.cpp)
EXECUTABLE = $(if $(filter driver_test.cpp,$(DRIVER)),test.out,findcomp.out)
OBJECTS = $(SOURCES:.cpp=.o) $(DRIVER:.cpp=.o)

# Compile executable file
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE)

# Compile object files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Compile test executable
test: DRIVER = driver_test.cpp
test: clean $(EXECUTABLE)

# Remove executable and object files
clean:
	rm -f *.o *.out