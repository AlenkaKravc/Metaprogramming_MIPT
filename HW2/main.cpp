#include <iostream>

#include "Hierarchy.h"

template<typename T>
struct Holder : T {
};

template<typename T , typename base>
struct HolderS : base {

};


class first {};

class second {};

class third {};

class Root : public GenScatterHierarchy<TypeList<first , second , third> , Holder , HolderS> {
};


int main() {
    Root root;

    std::cout << sizeof(root) << std::endl;
    return 0;
}