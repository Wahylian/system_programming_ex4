# Assignment 4 - System Programming
### Name: Ido Ron
### ID: 215312729
---
## Project Features:
1.  **[Main](main.cpp)**- a main file to showcase the [MyContainer](container.cpp) Class.<br/>
This uses the Demo file provided with the assignment.
2.  **[Tests](Tests)**- a folder of test cases used to test the MyContainerincluding tests for:
    * General Tests for the container.
    * Each of the 6 iterators required for the container.
    * Tests for Functor Classes used for the Iterators.
3.  **[MyContainer Class](container.hpp)**- an implementation of MyContainer according to the requirements of the assignment.
4.  **[Complex Numbers](complex.cpp)**- an implementation of Complex numbers to use in the different tests.
5.  **[MAKEFILE](Makefile)**- a make file allowing the following commands:
    * **make Main**- a command to create the Main exe, which runs the [main](main.cpp) file.
    * **make valgrind**- a command to run the Main exe through valgrind, to check for *Memory Leaks*.
    * **make test**- a command to create the test exe, which runs the [Tests](Tests) files.
    * **make valgrind-test**- a command to run the test exe through valgrind, to check for *Memory Leaks*.
    * **make clean**- a command to remove all object and exe files from the project.

    