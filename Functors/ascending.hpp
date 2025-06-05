// rido1607@gmail.com
#pragma once

template <typename T>
struct Ascending{
    public:
        // this function compares two pointers to the same type and 
        // checks if the second object is bigger than the first, return true if it is
        bool operator() (const T* p1, const T* p2) const {
            return *p1 < *p2;
        }
};