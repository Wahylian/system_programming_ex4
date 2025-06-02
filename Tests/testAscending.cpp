#include "testAscending.hpp"


TEST_CASE("Test Correct Ascending Order Integer") {
    vector<int *> data = {new int(1), new int(3), new int(2)};

    Ascending<int> ascendingFunctor;
    CHECK(ascendingFunctor(data[0], data[1]) == true); // 1 < 3
    CHECK(ascendingFunctor(data[1], data[2]) == false); // 3 < 2
    CHECK(ascendingFunctor(data[0], data[2]) == true); // 1 < 2

    // sort the data using the functor
    sort(data.begin(), data.end(), ascendingFunctor);

    // check that the data is sorted in ascending order
    CHECK(*data[0] == 1);
    CHECK(*data[1] == 2);
    CHECK(*data[2] == 3);

    // clean up
    for (auto ptr : data) {
        delete ptr; // free the allocated memory
    }
}

TEST_CASE("Test Correct Ascending Order String") {
    vector<string *> data = {new string("apple"), new string("banana"), new string("cherry")};

    Ascending<string> ascendingFunctor;
    CHECK(ascendingFunctor(data[0], data[1]) == true); // "apple" < "banana"
    CHECK(ascendingFunctor(data[1], data[2]) == true); // "banana" < "cherry"
    CHECK(ascendingFunctor(data[0], data[2]) == true); // "apple" < "cherry"

    // sort the data using the functor
    sort(data.begin(), data.end(), ascendingFunctor);

    // check that the data is sorted in ascending order
    CHECK(*data[0] == "apple");
    CHECK(*data[1] == "banana");
    CHECK(*data[2] == "cherry");

    // clean up
    for (auto ptr : data) {
        delete ptr; // free the allocated memory
    }
}

TEST_CASE("Test Correct Ascending Order Double") {
    vector<double *> data = {new double(3.14), new double(2.71), new double(1.41)};

    Ascending<double> ascendingFunctor;
    CHECK(ascendingFunctor(data[0], data[1]) == false); // 3.14 < 2.71
    CHECK(ascendingFunctor(data[1], data[2]) == false); // 2.71 < 1.41
    CHECK(ascendingFunctor(data[0], data[2]) == false); // 3.14 < 1.41

    // sort the data using the functor
    sort(data.begin(), data.end(), ascendingFunctor);

    // check that the data is sorted in ascending order
    CHECK(*data[0] == 1.41);
    CHECK(*data[1] == 2.71);
    CHECK(*data[2] == 3.14);

    // clean up
    for (auto ptr : data) {
        delete ptr; // free the allocated memory
    }
}

TEST_CASE("Test Ascending Order with Empty Vector") {
    vector<int *> data; // empty vector

    Ascending<int> ascendingFunctor;

    // sort the empty vector
    sort(data.begin(), data.end(), ascendingFunctor);

    // check that the vector is still empty
    CHECK(data.empty());
}

TEST_CASE("Test Ascending Order with Single Element") {
    vector<int *> data = {new int(42)}; // single element vector

    Ascending<int> ascendingFunctor;

    // sort the single element vector
    sort(data.begin(), data.end(), ascendingFunctor);

    // check that the single element is still there
    CHECK(*data[0] == 42);

    // clean up
    delete data[0]; // free the allocated memory
}

TEST_CASE("Test Ascending Order with Complex Numbers") {
    vector<complex *> data = {new complex(1, 2), new complex(3, 4), new complex(2, 3), new complex(3, 5)};

    Ascending<complex> ascendingFunctor;

    // sort the data using the functor
    sort(data.begin(), data.end(), ascendingFunctor);

    // check that the data is sorted in ascending order based on real part
    CHECK(*data[0] == complex(1, 2));
    CHECK(*data[1] == complex(2, 3));
    CHECK(*data[2] == complex(3, 4));
    CHECK(*data[3] == complex(3, 5));

    // clean up
    for (auto ptr : data) {
        delete ptr; // free the allocated memory
    }
}