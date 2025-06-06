// rido1607@gmail.com
#include "testDescendingOrderIter.hpp"

TEST_CASE("Test Begin and End"){
    SUBCASE("Test Begin and End on an Empty Container"){
        // create an empty container
        MyContainer<int> emptyContainer;

        // check that the size of the container is 0
        CHECK(emptyContainer.size() == 0);

        // get the iterator to the beginning
        auto itBegin = emptyContainer.begin_descending_order();

        // get the iterator to the end
        auto itEnd = emptyContainer.end_descending_order();

        // check if the iterator is equal to the end iterator
        CHECK(itBegin == itEnd);
    }
    SUBCASE("Test Begin and End on a Non-Empty Container"){
        SUBCASE("With One Element"){
            // create a container with one element
            MyContainer<int> container;
            container.addElement(42);

            // check that the size of the container is 1
            CHECK(container.size() == 1);

            // get the iterator to the beginning
            auto itBegin = container.begin_descending_order();

            // get the iterator to the end
            auto itEnd = container.end_descending_order();

            // check if the iterator is not equal to the end iterator
            CHECK(itBegin != itEnd);

            // check if dereferencing the iterator gives the correct value
            CHECK(*itBegin == 42);

            // check if incrementing the iterator moves it to the end
            ++itBegin;
            CHECK(itBegin == itEnd);
        }
        SUBCASE("With Multiple Elements"){
            // create a container with multiple elements
            MyContainer<int> container;
            container.addElement(1);
            container.addElement(2);
            container.addElement(3);

            // check that the size of the container is 3
            CHECK(container.size() == 3);

            // get the iterator to the beginning
            auto itBegin = container.begin_descending_order();

            // get the iterator to the end
            auto itEnd = container.end_descending_order();

            // check if the iterator is not equal to the end iterator
            CHECK(itBegin != itEnd);

            // advance the iterator 3 times and check that it reaches the end
            itBegin++;
            itBegin++;
            itBegin++;

            // check if the iterator is now equal to the end iterator
            CHECK(itBegin == itEnd);
        }
    }
}

TEST_CASE("Test Iterator from a New Container"){
    MyContainer<int> *container = new MyContainer<int>();
    container->addElement(1);
    container->addElement(2);
    container->addElement(3);

    // create an iterator to the beginning of the container
    MyContainer<int>::Iterator it = container->begin_descending_order();

    // check that the iterator is not equal to the end iterator
    CHECK(it != container->end_descending_order());

    // advance the iterator 3 times and make sure it reaches the end
    it++;
    it++;
    it++;

    // check if the iterator is now equal to the end iterator
    CHECK(it == container->end_descending_order());

    // clean up
    delete container;
}

TEST_CASE("Test Correct Advancing (Prefix)"){
    SUBCASE("Test Advancing Until the End of the Container"){
        // create a container with multiple elements
        int arr[] = {1, 2, 3, 4, 5};
        MyContainer<int> container(arr, arr + 5);

        // get the iterator to the beginning
        auto it = container.begin_descending_order();
        
        // create a counter to make sure the iterator advances correctly
        int counter = 0;
        while(it != container.end_descending_order()) {
            // advance the iterator and save the result of the increment
            auto copy = ++it;

            // advance the counter
            counter++;

            // check that the copy is equal to the iterator
            CHECK(copy == it);

            // check that the copy and the it are not the same object
            CHECK(&copy != &it);
        }

        // check that the counter matches the size of the container
        CHECK(counter == container.size());
    }
    SUBCASE("Test Advancing Beyond the End of the Container"){
        // create a container with multiple elements
        int arr[] = {1, 2, 3, 4, 5};
        MyContainer<int> container(arr, arr + 5);

        // get the iterator to the beginning
        auto it = container.begin_descending_order();
        
        // create a counter to make sure the iterator advances correctly
        int counter = 0;
        while(it != container.end_descending_order()) {
            // advance the iterator
            ++it;

            // advance the counter
            counter++;
        }

        // check that the counter matches the size of the container
        CHECK(counter == container.size());

        // check that advancing the iterator again does not throw an error
        CHECK_NOTHROW(++it);
    }
}

TEST_CASE("Test Correct Advancing (Postfix)"){
    SUBCASE("Test Advancing Until the End of the Container"){
        // create a container with multiple elements
        int arr[] = {1, 2, 3, 4, 5};
        MyContainer<int> container(arr, arr + 5);

        // get the iterator to the beginning
        auto it = container.begin_descending_order();
        
        // create a counter to make sure the iterator advances correctly
        int counter = 0;
        while(it != container.end_descending_order()) {
            // advance the iterator and save the result of the increment
            auto copy = it++;

            // advance the counter
            counter++;

            // check that the copy is not equal to the iterator
            CHECK(copy != it);

            // check that advancing the copy by one gives it
            CHECK(++copy == it);

            // check that the copy and the it are not the same object
            CHECK(&copy != &it);
        }

        // check that the counter matches the size of the container
        CHECK(counter == container.size());
    }
    SUBCASE("Test Advancing Beyond the End of the Container"){
        // create a container with multiple elements
        int arr[] = {1, 2, 3, 4, 5};
        MyContainer<int> container(arr, arr + 5);

        // get the iterator to the beginning
        auto it = container.begin_descending_order();
        
        // create a counter to make sure the iterator advances correctly
        int counter = 0;
        while(it != container.end_descending_order()) {
            // advance the iterator
            it++;

            // advance the counter
            counter++;
        }

        // check that the counter matches the size of the container
        CHECK(counter == container.size());

        // check that advancing the iterator again does not throw an error
        CHECK_NOTHROW(it++);
    }
}

TEST_CASE("Test Operator=="){
    SUBCASE("Test Comparing Two Iterators of the Same Container"){
        SUBCASE("Test Comparing Two Iterators of an Empty Container"){
            // create an empty container
            MyContainer<int> container;

            // get the iterators to the beginning of the container
            auto it1 = container.begin_descending_order();
            auto it2 = container.begin_descending_order();

            // check that the iterators are equal
            CHECK(it1 == it2);
        }
        SUBCASE("Test at the Same Position"){
            // create a container with one element
            MyContainer<int> container;
            container.addElement(42);

            // get the iterator to the beginning of the container
            auto it1 = container.begin_descending_order();
            auto it2 = container.begin_descending_order();

            // check if the iterators are equal
            CHECK(it1 == it2);
        }
        SUBCASE("Test at Different Positions"){
            // create a container with multiple elements
            MyContainer<int> container;
            container.addElement(1);
            container.addElement(2);
            container.addElement(3);

            // get the iterator to the beginning of the container
            auto it1 = container.begin_descending_order();
            auto it2 = container.begin_descending_order();

            // advance the first iterator
            ++it1;

            // check if the iterators are not equal
            CHECK(!(it1 == it2));
        }
    }
    SUBCASE("Test Comparing Two Iterators of Different Containers"){
        SUBCASE("Test Comparing Two Iterators of Empty Containers"){
            // create two empty containers
            MyContainer<int> container1;
            MyContainer<int> container2;

            // get the iterators to the beginning of the containers
            auto it1 = container1.begin_descending_order();
            auto it2 = container2.begin_descending_order();

            // check that the iterators are not equal
            CHECK(!(it1 == it2));
        }
        SUBCASE("Containers with the Same Variables"){
            // create two containers with the same elements
            int arr[] = {1, 2, 3};
            MyContainer<int> container1(arr, arr + 3);
            MyContainer<int> container2(arr, arr + 3);

            // get the iterators to the beginning of the containers
            auto it1 = container1.begin_descending_order();
            auto it2 = container2.begin_descending_order();

            while(it1 != container1.end_descending_order() && it2 != container2.end_descending_order()) {
                // check that the iterators are not equal
                CHECK(!(it1 == it2));

                // advance both iterators
                ++it1;
                ++it2;
            }
        }
        SUBCASE("Containers with Different Variables"){
            // create two containers with the same elements
            int arr1[] = {1, 2, 3};
            int arr2[] = {4, 5, 6};
            MyContainer<int> container1(arr1, arr1 + 3);
            MyContainer<int> container2(arr2, arr2 + 3);

            // get the iterators to the beginning of the containers
            auto it1 = container1.begin_descending_order();
            auto it2 = container2.begin_descending_order();

            while(it1 != container1.end_descending_order() && it2 != container2.end_descending_order()) {
                // check that the iterators are not equal
                CHECK(!(it1 == it2));

                // advance both iterators
                ++it1;
                ++it2;
            }
        }
    }
}

TEST_CASE("Test Operator!="){
    SUBCASE("Test Comparing Two Iterators of the Same Container"){
        SUBCASE("Test Comparing Two Iterators of an Empty Container"){
            // create an empty container
            MyContainer<int> container;

            // get the iterators to the beginning of the container
            auto it1 = container.begin_descending_order();
            auto it2 = container.begin_descending_order();

            // check that the iterators are equal
            CHECK(!(it1 != it2));
        }
        SUBCASE("Test at the Same Position"){
            // create a container with one element
            MyContainer<int> container;
            container.addElement(42);

            // get the iterator to the beginning of the container
            auto it1 = container.begin_descending_order();
            auto it2 = container.begin_descending_order();

            // check if the iterators are equal
            CHECK(!(it1 != it2));
        }
        SUBCASE("Test at Different Positions"){
            // create a container with multiple elements
            MyContainer<int> container;
            container.addElement(1);
            container.addElement(2);
            container.addElement(3);

            // get the iterator to the beginning of the container
            auto it1 = container.begin_descending_order();
            auto it2 = container.begin_descending_order();

            // advance the first iterator
            ++it1;

            // check if the iterators are not equal
            CHECK(it1 != it2);
        }
    }
    SUBCASE("Test Comparing Two Iterators of Different Containers"){
        SUBCASE("Test Comparing Two Iterators of Empty Containers"){
            // create two empty containers
            MyContainer<int> container1;
            MyContainer<int> container2;

            // get the iterators to the beginning of the containers
            auto it1 = container1.begin_descending_order();
            auto it2 = container2.begin_descending_order();

            // check that the iterators are not equal
            CHECK(it1 != it2);
        }
        SUBCASE("Containers with the Same Variables"){
            // create two containers with the same elements
            int arr[] = {1, 2, 3};
            MyContainer<int> container1(arr, arr + 3);
            MyContainer<int> container2(arr, arr + 3);

            // get the iterators to the beginning of the containers
            auto it1 = container1.begin_descending_order();
            auto it2 = container2.begin_descending_order();

            while(it1 != container1.end_descending_order() && it2 != container2.end_descending_order()) {
                // check that the iterators are not equal
                CHECK((it1 != it2));

                // advance both iterators
                ++it1;
                ++it2;
            }
        }
        SUBCASE("Containers with Different Variables"){
            // create two containers with the same elements
            int arr1[] = {1, 2, 3};
            int arr2[] = {4, 5, 6};
            MyContainer<int> container1(arr1, arr1 + 3);
            MyContainer<int> container2(arr2, arr2 + 3);

            // get the iterators to the beginning of the containers
            auto it1 = container1.begin_descending_order();
            auto it2 = container2.begin_descending_order();

            while(it1 != container1.end_descending_order() && it2 != container2.end_descending_order()) {
                // check that the iterators are not equal
                CHECK(it1 != it2);

                // advance both iterators
                ++it1;
                ++it2;
            }
        }
    }
}

TEST_CASE("Test Accessing Elements"){
    SUBCASE("Test Accessing Elements Outside of the Range"){
        // create a container with mutiple elements
        int arr[] = {1, 2, 3, 4, 5};
        MyContainer<int> container(arr, arr + 5);

        // get the iterator to the ending of the container
        auto it = container.end_descending_order();

        // advance the iterator one more time
        ++it;

        // check that attempting to access the element throws an out_of_range exception
        CHECK_THROWS_AS(*it, std::out_of_range); 
    }
    SUBCASE("Test Accessing Elements of an Empty Container"){
        // create an empty container
        MyContainer<int> emptyContainer;

        // get the iterator to the beginning of the container
        auto it = emptyContainer.begin_descending_order();

        // check that attempting to access the element throws an out_of_range exception
        CHECK_THROWS_AS(*it, std::out_of_range);
    }
    SUBCASE("Test Accessing Elements of a Container with One Element"){
        // create a container with one element
        MyContainer<int> container;
        container.addElement(42);

        // get the iterator to the beginning of the container
        auto it = container.begin_descending_order();

        // check that the value of the element is correct
        CHECK(*it == 42);
    }
    SUBCASE("Test Accessing Elements of a Container with Multiple Elements"){
        // create a container with multiple elements
        int arr[] = {1, 2, 3, 4, 5};
        MyContainer<int> container(arr, arr + 5);

        // get the iterator to the beginning of the container
        auto it = container.begin_descending_order();

        // check that the values of the elements are correct
        for(int i = 0; i < container.size(); ++i) {
            CHECK(*it == arr[4 -i]); // since the iterator is descending
            ++it;
        }
    }
    SUBCASE("Test Accessing at End"){
        // create a container with multiple elements
        int arr[] = {1, 2, 3, 4, 5};
        MyContainer<int> container(arr, arr + 5);

        // get the iterator to the end of the container
        auto it = container.end_descending_order();

        // check that attempting to access the element throws an out_of_range exception
        CHECK_THROWS_AS(*it, std::out_of_range);
    }
    SUBCASE("Test Accessing a Container of Complex Numbers"){
        // create a container with complex numbers
        complex arr[] = {complex(1, 2), complex(3, 4), complex(5, 6)};
        MyContainer<complex> complexContainer(arr, arr + 3);

        // get the iterator to the beginning of the container
        auto it = complexContainer.begin_descending_order();

        // check that the values of the elements are correct
        CHECK(*it == complex(5, 6)); 
        ++it;
        CHECK(*it == complex(3, 4));
        ++it;
        CHECK(*it == complex(1, 2));
    }
}

TEST_CASE("Test Changing Elements"){
    SUBCASE("Test Changing Elements Outside of Range"){
        // create a container with multiple elements
        int arr[] = {1, 2, 3, 4, 5};
        MyContainer<int> container(arr, arr + 5);

        // get the iterator to the ending of the container
        auto it = container.end_descending_order();

        // check that attempting to change the element throws an out_of_range exception
        CHECK_THROWS_AS(*it = 10, std::out_of_range);
    }
    SUBCASE("Test Changing Elements of an Empty Container"){
        // create an empty container
        MyContainer<int> emptyContainer;

        // get the iterator to the beginning of the container
        auto it = emptyContainer.begin_descending_order();

        // check that attempting to change the element throws an out_of_range exception
        CHECK_THROWS_AS(*it = 10, std::out_of_range);
    }
    SUBCASE("Test Changing Elements of a Container with One Element"){
        // create a container with one element
        MyContainer<int> container;
        container.addElement(42);

        // get the iterator to the beginning of the container
        auto it = container.begin_descending_order();

        // change the value of the element
        *it = 100;

        // check that the value of the element is correct
        CHECK(*it == 100);

        // create a new iterator to the beginning of the container
        auto it2 = container.begin_descending_order();

        // check that the value of the element is still correct
        CHECK(*it2 == 100);
    }
    SUBCASE("Test Changing Element and Accessing It from a Second Iterator"){
        // create a container with multiple elements
        int arr[] = {1, 2, 3, 4, 5};
        MyContainer<int> container(arr, arr + 5);

        // create 2 iterators to the beginning of the container
        auto it1 = container.begin_descending_order();
        auto it2 = container.begin_descending_order();

        // advance both iterators to the third element
        ++it1;
        ++it1;
        ++it2;
        ++it2;

        // check that the value of both iterators is the same
        CHECK(*it1 == 3);
        CHECK(*it2 == 3);
        CHECK(it1 == it2);

        // change the value of the third element using the first iterator
        *it1 = 100;

        // check that the value of the first iterator is correct
        CHECK(*it1 == 100);
        // check that the value of the second iterator was changed as well
        CHECK(*it2 == 100);

        // check that the two iterators are still equal
        CHECK(it1 == it2);
    }

    SUBCASE("Tests Affected by the Iterator Order"){
        SUBCASE("Test Changing Elements of a Container with Multiple Elements"){
            // create a container with multiple elements
            int arr[] = {1, 2, 3, 4, 5};
            MyContainer<int> container(arr, arr + 5);

            // get the iterator to the beginning of the container
            auto it = container.begin_descending_order();

            // change the value of the third element
            ++it;
            ++it;
            *it = 100;

            // check that the value of the third element is correct
            CHECK(*it == 100);

            // since the iterator is descending, the first element in a new iterator should be 100
            auto it2 = container.begin_descending_order();
            CHECK(*it2 == 100);
            
            // check that the size of the container is still the same
            CHECK(container.size() == 5);

            // check that the rest of the elements are still in the correct order
            ++it2;
            CHECK(*it2 == 5);
            ++it2;
            CHECK(*it2 == 4);
            ++it2;
            CHECK(*it2 == 2);
            ++it2;
            CHECK(*it2 == 1);

        }
        SUBCASE("Test Changing Last Element"){
            // create a container with multiple elements
            int arr[] = {1, 2, 3, 4, 5};
            MyContainer<int> container(arr, arr + 5);

            // get the iterator to the beginning of the container
            auto it = container.begin_descending_order();

            // go to the last element
            for(int i = 0; i < container.size() - 1; ++i) {
                ++it;
            }

            // change its value
            *it = 10;

            // check that the value of the last element is correct
            CHECK(*it == 10);

            // since the iterator is descending, the first element in a new iterator should be 10
            auto it2 = container.begin_descending_order();
            CHECK(*it2 == 10);

            // check that the size of the container is still the same
            CHECK(container.size() == 5);

            // check that the rest of the elements are still in the correct order
            ++it2;
            CHECK(*it2 == 5);
            ++it2;
            CHECK(*it2 == 4);
            ++it2;
            CHECK(*it2 == 3);
            ++it2;
            CHECK(*it2 == 2);

            // check that in the actual internal order of the container the first element is 10
            auto it3 = container.begin_order();
            CHECK(*it3 == 10);
            ++it3;
            CHECK(*it3 == 2);
            ++it3;
            CHECK(*it3 == 3);
            ++it3;
            CHECK(*it3 == 4);
            ++it3;
            CHECK(*it3 == 5);
        }
        SUBCASE("Test Changing First Element"){
            // create a container with multiple elements
            int arr[] = {1, 2, 3, 4, 5};
            MyContainer<int> container(arr, arr + 5);

            // get the iterator to the beginning of the container
            auto it = container.begin_descending_order();

            // change the value of the first element
            *it = -5;

            // check that the value of the first element is correct
            CHECK(*it == -5);

            // check that the size of the container is still the same
            CHECK(container.size() == 5);

            // since the iterator is descending, the last element in a new iterator should be -5
            auto it2 = container.begin_descending_order();
            
            // check that the rest of the elements are still in the correct order
            CHECK(*it2 == 4);
            ++it2;
            CHECK(*it2 == 3);
            ++it2;
            CHECK(*it2 == 2);
            ++it2;
            CHECK(*it2 == 1);
            ++it2;

            // check that the last element is -5
            CHECK(*it2 == -5);

            // check that in the actual internal order of the container the last element is -5
            auto it3 = container.begin_order();
            CHECK(*it3 == 1);
            ++it3;
            CHECK(*it3 == 2);
            ++it3;
            CHECK(*it3 == 3);
            ++it3;
            CHECK(*it3 == 4);
            ++it3;
            CHECK(*it3 == -5);
        }
    }
}

TEST_CASE("Test Correct Order"){
    SUBCASE("Test for Integers"){
        // create an array of 10 integers between -100 and 99 
        int arr[10]= {0};

        for(int i = 0; i < 10; ++i) {
            arr[i] = rand() % 200 - 100; // random integers between -100 and 99
        }

        // create a container with the array
        MyContainer<int> container(arr, arr + 10);

        // sort the array in descending order
        // to do so turn the array into its compliment
        for(int i = 0; i < 10; ++i) {
            arr[i] = -arr[i];
        }
        // sort the array in ascending order
        std::sort(arr, arr + 10);
        // turn the array back to its original values
        for(int i = 0; i < 10; ++i) {
            arr[i] = -arr[i];
        }

        // create an iterator to the beginning of the container
        auto it = container.begin_descending_order();
        int i = 0;

        // check that the values of the elements are correct
        for(; it != container.end_descending_order(); ++it, ++i) {
            CHECK(*it == arr[i]);
        }
    }
    SUBCASE("Test for Complex Numbers"){
        // create an array of 10 complex numbers
        complex arr[10] = {0};

        for(int i = 0; i < 10; ++i) {
            arr[i] = complex(rand() % 200 - 100, rand() % 200 - 100); // random complex numbers
        }

        // create a container with the array
        MyContainer<complex> container(arr, arr + 10);

        // sort the array in descending 
        // turn the array into its compliment
        for(int i = 0; i < 10; ++i) {
            arr[i] = -arr[i];
        }
        // sort the array in ascending order
        std::sort(arr, arr + 10);
        // turn the array back to its original values
        for(int i = 0; i < 10; ++i) {
            arr[i] = -arr[i];
        }

        // create an iterator to the beginning of the container
        auto it = container.begin_descending_order();
        int i = 0;

        // check that the values of the elements are correct
        for(; it != container.end_descending_order(); ++it, ++i) {
            CHECK(*it == arr[i]);
        }
    }
}