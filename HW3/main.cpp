#include <iostream>
#include <fstream>

#include "TL.h"
#include "TLMethods.h"
#include "Reader.h"

using TL = TypeList<int, double, double>;

int main() {
    std::string filename = "input.txt"; //in cmake-build-debug

    Reader<TL>* reader = new Reader<TL>(filename);
    void* mem = reader->readNextLine();

    int a = *(int*)mem;
    mem = (void*)((int*)mem + sizeof(int));
    std::cout << a << " " << mem << std::endl;
    double b = *(double*)mem;
    mem = (void*)((int *)mem + sizeof(double));
    std::cout << b << " " << mem << std::endl;
    double c = *(double*)mem;
    mem = (void*)((int*)mem + sizeof(double));
    std::cout << c << " " << mem << std::endl << std:: endl;



    mem = reader->readNextLine();

    a = *(int*)mem;
    mem = (void*)((int*)mem + sizeof(int));
    std::cout << a << " " << mem << std::endl;
    b = *(double*)mem;
    mem = (void*)((int*)mem + sizeof(double));
    std::cout << b << " " << mem << std::endl;
    c = *(double*)mem;
    mem = (void*)((int*)mem + sizeof(double));
    std::cout << c << " " << mem << std::endl;

    return 0;
}