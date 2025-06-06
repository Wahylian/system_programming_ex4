# rido1607@gmail.com
CXX=clang++
CXXFLAGS=-Wall -Werror -std=c++2a -I.

# object files for the functors 
FUNC_OBJ = Functors/ascending.o Functors/descending.o

# object files for the container
CONTAINER_OBJ = container.o customExceptions.o $(FUNC_OBJ)

# object files for custom classes to be used in the tests
CUSTOM_OBJ = CustomStructs/complex.o

# object files for the main exe
MAIN_OBJ = main.o $(CONTAINER_OBJ)

# obkect files for the iterator tests
ITER = Tests/IteratorTests/
ITER_TEST_OBJ = $(ITER)testAscendingOrderIter.o $(ITER)testDescendingOrderIter.o \
		$(ITER)testMiddleOutOrderIter.o $(ITER)testOrderIter.o $(ITER)testReverseOrderIter.o \
		$(ITER)testSideCrossOrderIter.o

# object files for the test files
TEST_OBJ = Tests/testFile.o $(CUSTOM_OBJ) Tests/testAscending.o Tests/testDescending.o \
		Tests/testContainer.o $(ITER_TEST_OBJ)

# valgrind flags, taken from course site, folder 02-classes-constructors-destructors: the makefile in the valgrind folder
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all --error-exitcode=99 

# turns the specified cpp file into an object file with the same name
%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# creates the main executable 
Main: $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) -o Main $(MAIN_OBJ)

valgrind: Main
	valgrind $(VALGRIND_FLAGS) ./Main

# creates a test executable for the test files
test: $(TEST_OBJ) $(CONTAINER_OBJ)
	$(CXX) $(CXXFLAGS) -o test $(TEST_OBJ) $(CONTAINER_OBJ) 

# checks for memory leaks during the tests
valgrind-test: test
	valgrind $(VALGRIND_FLAGS) ./test

clean:
	rm -f *.o CustomStructs/*.o Functors/*.o Tests/*.o Main test $(ITER)*.o

.PHONY: clean 