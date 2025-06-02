#include "testDescending.hpp"


TEST_CASE("Test Correct Descending Order Integer") {
    vector<int *> data = {new int(1), new int(3), new int(2)};

    Descending<int> descendingFunctor;
    CHECK(descendingFunctor(data[0], data[1]) == false); // 1 < 3
    CHECK(descendingFunctor(data[1], data[2]) == true); // 3 < 2
    CHECK(descendingFunctor(data[0], data[2]) == false); // 1 < 2

    // sort the data using the functor
    sort(data.begin(), data.end(), descendingFunctor);

    // check that the data is sorted in descending order
    CHECK(*data[0] == 3);
    CHECK(*data[1] == 2);
    CHECK(*data[2] == 1);

    // clean up
    for (auto ptr : data) {
        delete ptr; // free the allocated memory
    }
}

TEST_CASE("Test Correct Descending Order String") {
    vector<string *> data = {new string("apple"), new string("cherry"), new string("banana")};

    Descending<string> descendingFunctor;
    CHECK(descendingFunctor(data[0], data[1]) == false); // "apple" < "cherry"
    CHECK(descendingFunctor(data[1], data[2]) == true); // "cherry" > "banana"  
    CHECK(descendingFunctor(data[0], data[2]) == false); // "apple" < "banana"

    // sort the data using the functor
    sort(data.begin(), data.end(), descendingFunctor);

    // check that the data is sorted in descending order
    CHECK(*data[0] == "cherry");
    CHECK(*data[1] == "banana");
    CHECK(*data[2] == "apple");

    // clean up
    for (auto ptr : data) {
        delete ptr; // free the allocated memory
    }
}

TEST_CASE("Test Correct Descending Order Double") {
    vector<double *> data = {new double(2.71), new double(3.14), new double(1.41)};

    Descending<double> descendingFunctor;
    CHECK(descendingFunctor(data[0], data[1]) == false); // 2.71 < 3.14
    CHECK(descendingFunctor(data[1], data[2]) == true); // 3.14 > 1.41
    CHECK(descendingFunctor(data[0], data[2]) == true); // 2.71 > 1.41

    // sort the data using the functor
    sort(data.begin(), data.end(), descendingFunctor);

    // check that the data is sorted in descending order
    CHECK(*data[0] == 3.14);
    CHECK(*data[1] == 2.71);
    CHECK(*data[2] == 1.41);

    // clean up
    for (auto ptr : data) {
        delete ptr; // free the allocated memory
    }
}

TEST_CASE("Test Descending Order with Empty Vector") {
    vector<int *> data; // empty vector

    Descending<int> descendingFunctor;

    // sort the empty vector
    sort(data.begin(), data.end(), descendingFunctor);

    // check that the vector is still empty
    CHECK(data.empty());
}

TEST_CASE("Test Descending Order with Single Element") {
    vector<int *> data = {new int(42)}; // single element vector

    Descending<int> descendingFunctor;

    // sort the single element vector
    sort(data.begin(), data.end(), descendingFunctor);

    // check that the single element is still there
    CHECK(*data[0] == 42);

    // clean up
    delete data[0]; // free the allocated memory
}

TEST_CASE("Test Descending Order with Complex Numbers") {
    vector<complex *> data = {new complex(1, 2), new complex(3, 4), new complex(2, 3), new complex(3, 5)};

    Descending<complex> descendingFunctor;

    // sort the data using the functor
    sort(data.begin(), data.end(), descendingFunctor);

    // check that the data is sorted in descending order based on real part
    CHECK(*data[0] == complex(3, 5));
    CHECK(*data[1] == complex(3, 4));
    CHECK(*data[2] == complex(2, 3));
    CHECK(*data[3] == complex(1, 2));

    // clean up
    for (auto ptr : data) {
        delete ptr; // free the allocated memory
    }
}