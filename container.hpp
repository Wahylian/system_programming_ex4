#pragma once
#include <vector>
#include <stdexcept>
#include <iostream>
#include <string>
#include <algorithm>

#include "orderingTypes.hpp"
#include "customExceptions.hpp"

#include "Functors/ascending.hpp"
#include "Functors/descending.hpp"


using namespace std;

template <typename T>
class myContainer {
    private :
        // a vector to hold the elements of the container
        vector<T>* data;
    public :
        // constructor
        myContainer<T>();

        // cop from array
        myContainer<T>(const T* begin, const T* end);

        // copy constructor
        myContainer<T>(const myContainer<T>& other);

        // destructor
        ~myContainer<T>();

        // assignment operator
        myContainer<T>& operator=(const myContainer<T>& other);

        // adds an element to the container
        void addElement(const T& element);

        // removes all instances of element from the container
        // Throws:
        // - element_not_found exception if the element is not in the container
        void removeElement(const T& element);

        // returns the size of the container
        int size() const;
    
        // returns true if the container is empty, false otherwise
        bool isEmpty() const;

        // returns true if the container contains the element, false otherwise
        bool contains(const T& element) const;

        // outputs the elements of the container in order of insertion
        friend ostream& operator<<(ostream& os, const myContainer<T>& container){
            // goes over the elements of the container in order of insertion
            const vector<T> *vector = container.data;
            os << "{";
            for(int i = 0; i < vector->size(); ++i) {
                // adds the element to the output stream
                os << (*vector)[i];
                // if not the last element, add a comma and space
                if (i < vector->size() - 1) {
                    os << ", ";
                }
            }
            // go down a line after adding all the elements
            os << "}"<< endl;
            // return the output stream
            return os;
        }

    private:
        // creates a vector of pointers to the elements in the container
        // this is used to create the iterators for the container
        vector<T*> createDataPointers();

    public:
        // a class of the iterator for the container
        class Iterator{
            // allows the container to build the iterator
            friend class myContainer<T>;

            private:
                const myContainer<T>* cAddress; // save the address of the container for equality checks
                int index;
                // a vector with pointers to the elements in the container
                vector<T*> copyData;

                // the constructor is private to ensure it can only be created by the container
                // constructor
                Iterator(const myContainer<T> *address, const vector<T*>& data, orderingTypes &type, int startIndex = 0);
            
            public:
                // going to the next element prefix increment
                Iterator& operator++();

                // going to the next element postfix increment
                Iterator operator++(int);
                
                // check if the two iterators are equal, returns true if they are
                bool operator==(const Iterator& other) const;

                // check if the two iterators are equal, returns true if they are not
                bool operator!=(const Iterator& other) const;

                // returns the reference to the current element
                T& operator*();
        };

    #pragma region begin&end

        // returns an iterator to the beginning of the container in ascending order
        Iterator begin_ascending_order();

        // returns an iterator to the end of the container in ascending order
        Iterator end_ascending_order();

        // returns an iterator to the beginning of the container in descending order
        Iterator begin_descending_order();

        // returns an iterator to the end of the container in descending order
        Iterator end_descending_order();

        // returns an iterator to the beginning of the container in sidecross order
        Iterator begin_side_cross_order();

        // returns an iterator to the end of the container in sidecross order
        Iterator end_side_cross_order();

        // returns an iterator to the beginning of the container in reverse order
        Iterator begin_reverse_order();

        // returns an iterator to the end of the container in reverse order
        Iterator end_reverse_order();

        // returns an iterator to the beginning of the container in regular order
        Iterator begin_order();

        // returns an iterator to the end of the container in regular order
        Iterator end_order();

        // returns an iterator to the begining of the container in middle out order
        Iterator begin_middle_out_order();

        // returns an iterator to the end of the container in middle out order
        Iterator end_middle_out_order();

    #pragma endregion
};

#pragma region implementation

template <typename T>
myContainer<T>::myContainer() : data(new vector<T>()) {
    // nothing to do here
}

template <typename T>
myContainer<T>::myContainer(const T* begin, const T* end) : data(new vector<T>()) {
    // copies over the elements from the array to the vector
    for (const T* it = begin; it != end; ++it) {
        data->push_back(*it);
    }
}

template <typename T>
myContainer<T>::myContainer(const myContainer<T>& other) : data(new vector<T>(*other.data)) {
    // nothing to do here, as the vector copy constructor handles the copying
}

template <typename T>
myContainer<T>::~myContainer() {
    delete data; // delete the vector to free memory
}

template <typename T>
myContainer<T>& myContainer<T>::operator=(const myContainer<T>& other) {
    if (this != &other) { // check for self-assignment
        *data = *other.data; // copy the vector
    }
    return *this;
}

template <typename T>
void myContainer<T>::addElement(const T& element) {
    data->push_back(element); // adds the element to the end of the vector
}

template <typename T>
void myContainer<T>::removeElement(const T& element){
    if(this->isEmpty())
        throw container_empty(); // throw an exception if the container is empty

    bool found = false;
    for(auto it = data->begin(); it != data->end(); ++it) {
        // check if the current element is equal to the element to be removed
        if (*it == element) {
            // if it is remove it from the vector
            it = data->erase(it); // removes the element and returns the next iterator
            // set found to true, as an instance of the element was found and removed
            found = true;
            --it; // adjust iterator after erase, to avoid skipping the next element
        }
    }
    if (!found) {
        throw element_not_found(); // throw an exception if the element was not found
    }
}

template <typename T>
int myContainer<T>::size() const {
    return data->size(); // returns the size of the vector
}

template <typename T>
bool myContainer<T>::isEmpty() const {
    return data->empty(); // returns true if the vector is empty, false otherwise
}

template <typename T>
bool myContainer<T>::contains(const T& element) const {
    // checks if the element is in the vector
    return std::find(data->begin(), data->end(), element) != data->end();
}

template <typename T>
vector<T*> myContainer<T>::createDataPointers(){
    // create a vector the size of the data vector
    vector<T*> pointers(data->size());

    // fill the vector with pointers to the elements in the data vector
    for (size_t i = 0; i < data->size(); ++i) {
        pointers[i] = &(*data)[i]; // get the address of the element in the vector
    }

    // return the vector of pointers
    return pointers;
}

#pragma region Iter_Imp
template <typename T>
myContainer<T>::Iterator::Iterator(const myContainer<T> *address, const vector<T*>& data, orderingTypes &type, int startIndex) : 
    cAddress{address}, index(startIndex), copyData{} {
    // create a temp vector to hold the pointers to the elements in the data vector
    vector<T*> tempData = {};
    for (T* pointer : data) {
        tempData.push_back(pointer); // adds the pointer to the tempData vector
    }
    
    switch (type){
        case AscendingOrder: {
            // sort the tempData in ascending order
            sort(tempData.begin(), tempData.end(), Ascending<T>());
            // copy the sorted data to the copyData vector
            copyData = tempData;
            break;
        }
        case DescendingOrder: {
            // sort the tempData in descending order
            sort(tempData.begin(), tempData.end(), Descending<T>());
            // copy the sorted data to the copyData vector
            copyData = tempData;
            break;
        }
        case SideCrossOrder: {
            // sort the temp data in ascending order
            sort(tempData.begin(), tempData.end(), Ascending<T>());
            
            // saves the size of the data vector
            int size = data.size();

            // while there are elements left to copy
            for(int i=0; i<size; i++) {
                
                if (i % 2 == 0) {
                    // if the index is even, add the smallest element not already copied
                    // from the start of the tempData
                    copyData.push_back(tempData[i / 2]);
                } 
                else { 
                    // if the index is odd, add the largest element not already copied 
                    // from the end of tempData
                    copyData.push_back(tempData[size - 1 - (i / 2)]);
                }
            }
            break;
        }
        case ReverseOrder: {
            // if the vector is empty, break
            if (tempData.empty()) {
                break;
            }
            // add the values from the tempData to the copyData in reverse order
            for(auto it = tempData.end() - 1; it >= tempData.begin(); --it) {
                copyData.push_back(*it);
            }
            break;
        }
        case Order: {
            // copies the tempData to the copyData vector as is
            copyData = tempData;
            break;
        }
        case MiddleOutOrder: {
            // get the middle index of the tempData vector
            int middleIndex = tempData.size() / 2;

            // while there are elements left to copy
            for(int i=0; i<tempData.size(); i++) {
                if (i % 2 == 0) {
                    // if the index is even, add the element at middleIndex + i/2
                    copyData.push_back(tempData[middleIndex + (i / 2)]);
                } 
                else { 
                    // if the index is odd, add the element at middleIndex - (i/2 + 1)
                    copyData.push_back(tempData[middleIndex - (i / 2  + 1)]);
                }
            }
            break;
        }
        default: {
            throw std::invalid_argument("Invalid ordering type");
        }
    }
}

template <typename T>
myContainer<T>::Iterator& myContainer<T>::Iterator::operator++() {
    // increment the index to point to the next element
    ++index;
    return *this;
}

template <typename T>
myContainer<T>::Iterator myContainer<T>::Iterator::operator++(int) {
    // create a copy of the current iterator
    Iterator temp = *this;
    // increment the index to point to the next element
    ++index;
    return temp; // return the copy
}

template <typename T>
bool myContainer<T>::Iterator::operator==(const Iterator& other) const {
    // make sure the other iterator is talking about the same container
    if (this->cAddress != other.cAddress) {
        // if the addresses of the containers are not the same, the iterators cannot be equal
        return false; 
    }

    // check if the index and copyData are the same
    return index == other.index && copyData == other.copyData;
}

template <typename T>
bool myContainer<T>::Iterator::operator!=(const Iterator& other) const {
    // check if the iterators are not equal
    return !(*this == other);
}

template <typename T>
T& myContainer<T>::Iterator::operator*() {
    // checks the iterator is within the bounds of the copyData vector
    if (index < 0 || index >= copyData.size()) {
        throw std::out_of_range("Iterator out of range");
    }
    // returns the reference to the current element
    return *copyData[index];
}

#pragma endregion

#pragma region begin&end_Imp
template <typename T>
myContainer<T>::Iterator myContainer<T>::begin_ascending_order() {
    // creates an iterator to the beginning of the container in ascending order
    orderingTypes type = AscendingOrder;
    return Iterator(this, this->createDataPointers(), type, 0);
}

template <typename T>
myContainer<T>::Iterator myContainer<T>::end_ascending_order() {
    // creates an iterator to the end of the container in ascending order
    orderingTypes type = AscendingOrder;
    return Iterator(this, this->createDataPointers(), type, data->size());
}

template <typename T>
myContainer<T>::Iterator myContainer<T>::begin_descending_order() {
    // creates an iterator to the beginning of the container in descending order
    orderingTypes type = DescendingOrder;
    return Iterator(this, this->createDataPointers(), type, 0);
}

template <typename T>
myContainer<T>::Iterator myContainer<T>::end_descending_order() {
    // creates an iterator to the end of the container in descending order
    orderingTypes type = DescendingOrder;
    return Iterator(this, this->createDataPointers(), type, data->size());
}

template <typename T>
myContainer<T>::Iterator myContainer<T>::begin_side_cross_order() {
    // creates an iterator to the beginning of the container in sidecross order
    orderingTypes type = SideCrossOrder;
    return Iterator(this, this->createDataPointers(), type, 0);
}

template <typename T>
myContainer<T>::Iterator myContainer<T>::end_side_cross_order() {
    // creates an iterator to the end of the container in sidecross order
    orderingTypes type = SideCrossOrder;
    return Iterator(this, this->createDataPointers(), type, data->size());
}

template <typename T>
myContainer<T>::Iterator myContainer<T>::begin_reverse_order() {
    // creates an iterator to the beginning of the container in reverse order
    orderingTypes type = ReverseOrder;
    return Iterator(this, this->createDataPointers(), type, 0);
}

template <typename T>
myContainer<T>::Iterator myContainer<T>::end_reverse_order() {
    // creates an iterator to the end of the container in reverse order
    orderingTypes type = ReverseOrder;
    return Iterator(this, this->createDataPointers(), type, data->size());
}

template <typename T>
myContainer<T>::Iterator myContainer<T>::begin_order() {
    // creates an iterator to the beginning of the container in regular order
    orderingTypes type = Order;
    return Iterator(this, this->createDataPointers(), type, 0);
}

template <typename T>
myContainer<T>::Iterator myContainer<T>::end_order() {
    // creates an iterator to the end of the container in regular order
    orderingTypes type = Order;
    return Iterator(this, this->createDataPointers(), type, data->size());
}
template <typename T>
myContainer<T>::Iterator myContainer<T>::begin_middle_out_order() {
    // creates an iterator to the beginning of the container in middle out order
    orderingTypes type = MiddleOutOrder;
    return Iterator(this, this->createDataPointers(), type, 0);
}

template <typename T>
myContainer<T>::Iterator myContainer<T>::end_middle_out_order() {
    // creates an iterator to the end of the container in middle out order
    orderingTypes type = MiddleOutOrder;
    return Iterator(this, this->createDataPointers(), type, data->size());
}
#pragma endregion