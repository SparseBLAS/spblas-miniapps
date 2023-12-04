#include <iostream>
#include "rbki.hh"
#include "rsvd.hh"

int main() {
    std::cout << "Hello from MyProject!" << std::endl;

    // Functionality from mylibrary1.h
    rsvd::PrintMessage1();

    // Functionality from mylibrary2.h
    rbki::PrintMessage2();

    return 0;
}