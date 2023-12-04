#ifndef MYLIBRARY_H
#define MYLIBRARY_H

#include <iostream>

namespace MyLibrary {
    inline void PrintMessage() {
        std::cout << "Hello from MyLibrary!" << std::endl;
    }
}

#endif // MYLIBRARY_H