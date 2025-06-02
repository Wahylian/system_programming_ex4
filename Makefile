# rido1607@gmail.com
CXX=clang++
CXXFLAGS=-Wall -Werror -std=c++2a 

# object files for the functors 
FUNC_OBJ = Functors/ascending.o Functors/descending.o

# object files for the container
CONTAINER_OBJ = container.o $(FUNC_OBJ)

# object files for custom classes to be used in the tests
CUSTOM_OBJ = CustomStructs/complex.o

# object files for the test files
TEST_OBJ = Tests/testFile.o $(CUSTOM_OBJ) Tests/testAscending.o Tests/testDescending.o

# valgrind flags, taken from course site, folder 02-classes-constructors-destructors: the makefile in the valgrind folder
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all --error-exitcode=99 

# turns the specified cpp file into an object file with the same name
%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# creates the main executable (gui)
Main: $(CONTAINER_OBJ)
	$(CXX) $(CXXFLAGS) -o Main $(CONTAINER_OBJ)

valgrind: Main
	valgrind $(VALGRIND_FLAGS) ./Main

# creates a test executable for the test files
test: $(TEST_OBJ) $(CONTAINER_OBJ)
	$(CXX) $(CXXFLAGS) -o test $(TEST_OBJ) $(CONTAINER_OBJ) 

# checks for memory leaks during the tests
valgrind-test: test
	valgrind $(VALGRIND_FLAGS) ./test

clean:
	rm -f *.o CustomStructs/*.o Functors/*.o Tests/*.o Main test 

.PHONY: clean 