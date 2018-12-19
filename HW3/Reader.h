//
// Created by kravets on 17.12.18.
//

#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include "TL.h"
#include "TLMethods.h"


#ifndef HW3_READER_H
#define HW3_READER_H


template<typename TL>
class Reader;

template<typename TL>
class Helper;

template<typename ...Args>
class Helper<TypeList<Args...>> {

    using head = typename TypeList<Args...>::Head;
    using tail = typename TypeList<Args...>::Tail;

public:

    Helper(void *mem , std::ifstream &file) {
        head a;
        file >> a;
        *((head *) mem) = a;
        mem = (void *) ((int *) mem + sizeof(head));
        Helper<tail> h(mem , file);
    }
};

template<>
class Helper<EmptyTypeList> {
public:
    Helper(void *mem , std::ifstream &file) {}
};


template<typename ...Args>

class Reader<TypeList<Args...>> {
public:

    explicit Reader(std::string filename) {
        this->file.open(filename.c_str());
        size = SumSize<TypeList<Args...>>::value;
    }

    ~Reader() {
        this->file.close();
    }

    void *readNextLine() {
        void *mem = malloc(size);
        Helper<TypeList<Args...>> h(mem , file);
        return mem;
    }

private:
    std::ifstream file;
    size_t size;
};


#endif //HW3_READER_H
