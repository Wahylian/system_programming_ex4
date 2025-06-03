#include "testContainer.hpp"

TEST_CASE("Test Container Default Constructor"){
    // create an instance of the container
    myContainer<int> container;

    // check if the container is empty
    CHECK(container.isEmpty() == true);

    // check if the size is 0
    CHECK(container.size() == 0);
}

TEST_CASE("Test Container Copy Constructor"){
    // create an instance of the container
    myContainer<int> c1;

    // check if the container is empty
    CHECK(c1.isEmpty() == true);

    // create a copy of the container
    myContainer<int> c2(c1);

    // check if the copy is empty
    CHECK(c2.isEmpty() == true);

    // check if the size of the copy is 0
    CHECK(c2.size() == 0);

    // add an element to the original container
    c1.addElement(5);

    // check that the original container is not empty
    CHECK(c1.isEmpty() == false);

    // check if the copy is still empty
    CHECK(c2.isEmpty() == true);

    // check that the addresses of the original and copy are different
    CHECK(&c1 != &c2);
}

TEST_CASE("Test Container Array Constructor"){
    SUBCASE("Empty Array"){
        // create an empty array
        int arr[] = {};

        // create a container from the empty array
        myContainer<int> container(arr, arr + 0);

        // check if the container is empty
        CHECK(container.isEmpty() == true);

        // check if the size is 0
        CHECK(container.size() == 0);
    }
    SUBCASE("Array with Elements"){
        // create an array with elements
        int arr[] = {1, 2, 3, 4, 5};

        // create a container from the array
        myContainer<int> container(arr, arr + 5);

        // check if the container is not empty
        CHECK(container.isEmpty() == false);

        // check if the size is 5
        CHECK(container.size() == 5);

        // check if the elements are added correctly
        CHECK(container.contains(1) == true);
        CHECK(container.contains(2) == true);
        CHECK(container.contains(3) == true);
        CHECK(container.contains(4) == true);
        CHECK(container.contains(5) == true);
    }
    SUBCASE("Array of Complex Objects"){
        // create an array of complex numbers
        complex arr[] = {complex(1, 2), complex(3, 4), complex(5, 6)};

        // create a container from the array
        myContainer<complex> container(arr, arr + 3);

        // check if the container is not empty
        CHECK(container.isEmpty() == false);

        // check if the size is 3
        CHECK(container.size() == 3);

        // check if the elements are added correctly
        CHECK(container.contains(complex(1, 2)) == true);
        CHECK(container.contains(complex(3, 4)) == true);
        CHECK(container.contains(complex(5, 6)) == true);
    }
}

TEST_CASE("Test Container Assignment Operator"){
    SUBCASE("Self Assignment"){
        // create an instance of the container
        myContainer<int> container;

        // add an element to the container
        container.addElement(10);

        // save the address of the original container
        myContainer<int> *originalAddress = &container;

        #pragma clang diagnostic push
        #pragma clang diagnostic ignored "-Wself-assign-overloaded"
        container = container;
        #pragma clang diagnostic pop

        // check that the container is not empty
        CHECK(container.isEmpty() == false);

        // check that the size is 1
        CHECK(container.size() == 1);

        // check that the element is still there
        CHECK(container.contains(10) == true);

        // check that the address of the container hasn't changed
        CHECK(originalAddress == &container);
    }
    SUBCASE("Different Containers"){
        // create a new container
        myContainer<int> c1;
        
        // add an element to the original container
        c1.addElement(20);

        // check that the container is not empty
        CHECK(c1.isEmpty() == false);

        // check that the size is 1
        CHECK(c1.size() == 1);

        // check that the container has 20
        CHECK(c1.contains(20) == true);

        // save the address of the original container
        myContainer<int> *originalAddress = &c1;

        // create a new container
        myContainer<int> c2;

        // save the address of the new container
        myContainer<int> *newAddress = &c2;

        // assign the original to it
        c2 = c1;

        // check that the new container is not empty
        CHECK(c2.isEmpty() == false);

        // check that the size is 1
        CHECK(c2.size() == 1);

        // check that the new container has the same element as the original
        CHECK(c2.contains(20) == true);

        // check that the addresses of the original and new containers are different 
        CHECK(&c1 != &c2);

        // check that the address of the original container hasn't changed
        CHECK(originalAddress == &c1);

        // check that the address of the new container hasn't changed
        CHECK(newAddress == &c2);
    }
}

TEST_CASE("Test Container Destructor"){
    SUBCASE("Default Constructor"){
        // create an instance of the container
        myContainer<int> *container = new myContainer<int>();

        // check if the container is empty
        CHECK(container->isEmpty() == true);

        // check if the size is 0
        CHECK(container->size() == 0);

        // add an element to the container
        container->addElement(10);

        // check if the container is not empty
        CHECK(container->isEmpty() == false);

        // delete the container
        delete container;
    }
    SUBCASE("Copy Constructor"){
        myContainer<int> *c1 = new myContainer<int>();

        // check if the container is empty
        CHECK(c1->isEmpty() == true);

        // add an element to the original container
        c1->addElement(20);

        // check that the container has 20
        CHECK(c1->contains(20) == true);
        
        // copy the container
        myContainer<int> *c2 = new myContainer<int>(*c1);

        // check if the copy is not empty
        CHECK(c2->isEmpty() == false);

        // check that it has the same size as the original
        CHECK(c2->size() == c1->size());

        // check that the elements are the same
        CHECK(c2->contains(20) == true);

        // add an element to the copy
        c2->addElement(30);

        // check that the copy has 30
        CHECK(c2->contains(30) == true);

        // check that the original does not have 30
        CHECK(c1->contains(30) == false);

        // check that their sizes are different
        CHECK(c1->size() != c2->size());

        // check that their addresses are different
        CHECK(c1 != c2);

        // delete the containers
        delete c1;
        delete c2;
    }
    SUBCASE("Array Constructor"){
        // create a new array with elements
        int *arr = new int[5]{1, 2, 3, 4, 5};

        // create a container from the array
        myContainer<int> *container = new myContainer<int>(arr, arr + 5);

        // check if the container is not empty
        CHECK(container->isEmpty() == false);

        // check if the size is 5
        CHECK(container->size() == 5);

        // check that the addresses of the container and the values in the array are different
        int i = 0;
        auto endIt = container->end_order();
        for(auto it = container->begin_order(); it != endIt; ++it, ++i) {
            // check that the address of the element in the container is not the same as the address in the array
            CHECK(&(*it) != &arr[i]);
            // check that they are equal
            CHECK(*it == arr[i]);
        }

        // delete the array
        delete[] arr;

        // delete the container
        delete container;
    }
    SUBCASE("Assignment Operator"){
        // create a new container
        myContainer<int> *c1 = new myContainer<int>();

        // add an element to the original container
        c1->addElement(10);

        // check that the container is not empty
        CHECK(c1->isEmpty() == false);

        // check that the size is 1
        CHECK(c1->size() == 1);

        // save the address of the original container
        myContainer<int> *originalAddress = c1;

        // create a new container
        myContainer<int> *c2 = new myContainer<int>();

        // save the address of the new container
        myContainer<int> *newAddress = c2;

        // assign the original to it
        *c2 = *c1;

        // check that the new container is not empty
        CHECK(c2->isEmpty() == false);

        // check that the size is 1
        CHECK(c2->size() == 1);

        // check that the new container has the same element as the original
        CHECK(c2->contains(10) == true);

        // check that the addresses of the original and new containers are different
        CHECK(c1 != c2);

        // check that the address of the original container hasn't changed
        CHECK(originalAddress == c1);

        // check that the address of the new container hasn't changed
        CHECK(newAddress == c2);

        // delete the containers
        delete c1;
        delete c2;
    }
}

TEST_CASE("Test Add Element"){
    SUBCASE("Add Element to Empty Container"){
        // create an instance of the container
        myContainer<int> container;

        // check if the container is empty
        CHECK(container.isEmpty() == true);

        // check that 42 is not in the container
        CHECK(container.contains(42) == false);

        // add an element to the container
        container.addElement(42);

        // check if the container is not empty
        CHECK(container.isEmpty() == false);

        // check if the size is 1
        CHECK(container.size() == 1);

        // check that the element is added correctly
        CHECK(container.contains(42) == true);
    }
    SUBCASE("Add Element to Non-Empty Container"){
        // create an instance of a container from an array
        int arr[] = {1, 2, 3};
        myContainer<int> container(arr, arr + 3);

        // check if the container is not empty
        CHECK(container.isEmpty() == false);
        
        // add an element to the container
        container.addElement(4);

        // check that the container has 4 elements
        CHECK(container.size() == 4);

        // check that the element is added correctly
        CHECK(container.contains(4) == true);

        // check that the other elements are still there
        for(int i = 1; i <= 3; ++i) {
            CHECK(container.contains(i) == true);
        }
    }
    SUBCASE("Add Duplicate Element"){
        // create an instance of the container
        myContainer<int> container;

        // add an element to the container
        container.addElement(5);

        // check if the container is not empty
        CHECK(container.isEmpty() == false);

        // check if the size is 1
        CHECK(container.size() == 1);

        // add the same element again
        container.addElement(5);

        // check if the size is still 1 (assuming duplicates are allowed)
        CHECK(container.size() == 2);

        // check that the element is still there
        CHECK(container.contains(5) == true);
    }
}

TEST_CASE("Test Remove Element"){
    SUBCASE("Element Exists"){
        // create an instance of a container
        myContainer<int> container;

        // add some elements to the container
        container.addElement(1);
        container.addElement(2);
        container.addElement(3);

        // check if the container is not empty
        CHECK(container.isEmpty() == false);

        // check if the size is 3
        CHECK(container.size() == 3);

        // check that the element 2 exists in the container
        CHECK(container.contains(2) == true);

        // remove an element that exists
        container.removeElement(2);

        // check if the size is now 2
        CHECK(container.size() == 2);

        // check that the removed element is no longer in the container
        CHECK(container.contains(2) == false);

        // check that the other elements are still there
        CHECK(container.contains(1) == true);
        CHECK(container.contains(3) == true);
    }
    SUBCASE("Element Does Not Exist"){
        // create an instance of a container
        myContainer<int> container;

        // add some elements to the container
        container.addElement(1);
        container.addElement(2);
        container.addElement(3);

        // check if the container is not empty
        CHECK(container.isEmpty() == false);

        // check if the size is 3
        CHECK(container.size() == 3);

        // check that the element 4 does not exist in the container
        CHECK(container.contains(4) == false);

        // try to remove an element that does not exist
        CHECK_THROWS_AS(container.removeElement(4), element_not_found);
    }
    SUBCASE("Muliple Instances of Element"){
        // create an array with multiple instances of an element
        int arr[] = {1, 2, 2, 3, 2};

        // create an instance of a container
        myContainer<int> container(arr, arr + 5);

        // check if the container is not empty
        CHECK(container.isEmpty() == false);

        // check if the size is 5
        CHECK(container.size() == 5);

        // check that the element 2 exists in the container
        CHECK(container.contains(2) == true);

        // remove the element 2
        container.removeElement(2);

        // check that the size is now 2
        CHECK(container.size() == 2);

        // check that the removed element is no longer in the container
        CHECK(container.contains(2) == false);

        // check that the other elements are still there
        CHECK(container.contains(1) == true);
        CHECK(container.contains(3) == true);
    }
    SUBCASE("Remove First Element"){
        // create an array with elements
        int arr[] = {1, 2, 3, 4, 5};

        // create an instance of a container
        myContainer<int> container(arr, arr + 5);

        // get the order iterator
        auto it = container.begin_order();

        // check if the first element is 1
        CHECK(*it == 1);

        // remove the first element
        container.removeElement(1);

        // check that the size is now 4
        CHECK(container.size() == 4);

        // check that the first element is now 2
        it = container.begin_order();
        CHECK(*it == 2);
    }
    SUBCASE("Remove Last Element"){
        // create an array with elements
        int arr[] = {1, 2, 3, 4, 5};
        
        // create an instance of a container
        myContainer<int> container(arr, arr + 5);

        // get the reverse order iterator
        auto it = container.begin_reverse_order();

        // check that the element at the end is 5
        CHECK(*it == 5);

        // remove the last element
        container.removeElement(5);

        // check that the size is now 4
        CHECK(container.size() == 4);

        // check that the last element is now 4
        it = container.begin_reverse_order();
        CHECK(*it == 4);
    }
    SUBCASE("Remove Element from Empty Container"){
        // create an instance of a container
        myContainer<int> container;

        // check if the container is empty
        CHECK(container.isEmpty() == true);

        // try to remove an element from the empty container
        CHECK_THROWS_AS(container.removeElement(1), container_empty);
    }
}

TEST_CASE("Test Add Elements After Removal"){
    SUBCASE("Add After Removing All Elements"){
        // create an array with elements
        int arr[] = {1, 2, 3, 4, 5};

        // create an instance of a container
        myContainer<int> container(arr, arr + 5);

        // remove all elements one by one
        for(int i = 1; i <= 5; ++i) {
            // check that the element exists before removing it
            CHECK(container.contains(i) == true);

            // remove the element
            container.removeElement(i);

            // check that the element no longer exists
            CHECK(container.contains(i) == false);

            // check that the size is reduced by 1
            CHECK(container.size() == 5 - i);
        }

        // check that the container is empty after removing all elements
        CHECK(container.isEmpty() == true);

        // check that the size is 0
        CHECK(container.size() == 0);

        // try to remove an element from the empty container
        CHECK_THROWS_AS(container.removeElement(1), container_empty);

        // try to add an element to the empty container
        container.addElement(10);

        // check that the container is not empty after adding an element
        CHECK(container.isEmpty() == false);

        // check that the size is 1 after adding an element
        CHECK(container.size() == 1);

        // check that the element is added correctly
        CHECK(container.contains(10) == true);
    }
    SUBCASE("Add After Removing Some Elements"){
        // create an array with elements
        int arr[] = {1, 2, 3, 4, 5};

        // create an instance of a container
        myContainer<int> container(arr, arr + 5);

        // remove some of the elements
        container.removeElement(3);
        container.removeElement(4);

        // check that the size is now 3
        CHECK(container.size() == 3);

        // check that the elements 1, 2, and 5 are still there
        CHECK(container.contains(1) == true);
        CHECK(container.contains(2) == true);
        CHECK(container.contains(5) == true);
        
        // check that the element 3 is no longer in the container
        CHECK(container.contains(3) == false);
        // check that the element 4 is no longer in the container
        CHECK(container.contains(4) == false);

        // add a new element to the container
        container.addElement(6);

        // check that the size is now 4
        CHECK(container.size() == 4);
        // check that the new element is added correctly
        CHECK(container.contains(6) == true);
    }
}

TEST_CASE("Test Size Method"){
    SUBCASE("Empty Container"){
        // create an instance of a container
        myContainer<int> container;

        // check if the size is 0
        CHECK(container.size() == 0);
    }
    SUBCASE("Test After Adding Elements"){
        // create an instance of a container
        myContainer<int> container;

        // add some elements to the container
        container.addElement(1);
        container.addElement(2);
        container.addElement(3);

        // check if the size is 3
        CHECK(container.size() == 3);
    }
    SUBCASE("Test After Removing Elements"){
        // create an instance of a container
        myContainer<int> container;

        // add some elements to the container
        container.addElement(1);
        container.addElement(2);
        container.addElement(3);

        // check if the size is 3
        CHECK(container.size() == 3);

        // remove an element from the container
        container.removeElement(2);

        // check if the size is now 2
        CHECK(container.size() == 2);

        // remove another element from the container
        container.removeElement(1);

        // check if the size is now 1
        CHECK(container.size() == 1);

        // remove the last element from the container
        container.removeElement(3);

        // check if the size is now 0
        CHECK(container.size() == 0);
    }
}

TEST_CASE("Test IsEmpty Method"){
    SUBCASE("Empty Container"){
        // create an instance of a container
        myContainer<int> container;

        // check if the container is empty
        CHECK(container.isEmpty() == true);
    }
    SUBCASE("Non-Empty Container"){
        // create an array with elements
        int arr[] = {1, 2, 3, 4, 5};

        // create an instance of a container
        myContainer<int> container(arr, arr + 5);

        // check that the container is not empty
        CHECK(container.isEmpty() == false);
    }
    SUBCASE("Emptied Container (After Removal of All Elements)"){
        // create an array with elements
        int arr[] = {1, 2, 3, 4, 5};

        // create an instance of a container
        myContainer<int> container(arr, arr + 5);

        // remove all elements one by one
        for(int i = 1; i <= 5; ++i) {
            container.removeElement(i);
        }

        // check that the container is empty after removing all elements
        CHECK(container.isEmpty() == true);
    }
}

TEST_CASE("Test Contains Method"){
    SUBCASE("Existing Element"){
        // create an instance of a container
        myContainer<int> container;

        // add some elements to the container
        container.addElement(1);
        container.addElement(2);
        container.addElement(3);

        // check if the container contains the elements
        CHECK(container.contains(1) == true);
        CHECK(container.contains(2) == true);
        CHECK(container.contains(3) == true);
    }
    SUBCASE("Non-Existing Element"){
        // create an instance of a container
        myContainer<int> container;

        // add some elements to the container
        container.addElement(1);
        container.addElement(2);
        container.addElement(3);

        // check if the container does not contain a non-existing element
        CHECK(container.contains(4) == false);
    }
    SUBCASE("Removed Element"){
        // create an instance of a container
        myContainer<int> container;

        // add some elements to the container
        container.addElement(1);
        container.addElement(2);
        container.addElement(3);

        // check if the container contains the elements
        CHECK(container.contains(1) == true);
        CHECK(container.contains(2) == true);
        CHECK(container.contains(3) == true);

        // remove an element from the container
        container.removeElement(2);

        // check if the removed element is no longer in the container
        CHECK(container.contains(2) == false);
    }
}

TEST_CASE("Test Output Stream Operator"){
    SUBCASE("Empty Container"){
        // create an instance of a container
        myContainer<int> container;

        // create an output stream
        cout<< "Testing output stream operator for empty container" << endl;
        
        // print the output to a string stream
        cout<<container;
    }
    SUBCASE("Container with Elements"){
        // create an array with elements
        int arr[] = {1, 2, 3, 4, 5};

        // create an instance of a container
        myContainer<int> container(arr, arr + 5);

        // create an output stream
        cout<< "Testing output stream operator for non-empty container" << endl;

        // print the output to a string stream
        cout<<container;
    }
}