#pragma once
#include <stdexcept>

class container_empty : public std::runtime_error {
    public:
        container_empty() : std::runtime_error("cannot remove from an empty container") {}
};

class element_not_found : public std::runtime_error {
    public:
        element_not_found() : std::runtime_error("element not found") {}
};