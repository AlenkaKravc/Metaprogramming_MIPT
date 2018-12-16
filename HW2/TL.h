//
// Created by kravets on 12.12.18.
//

#ifndef HW2_TL_H
#define HW2_TL_H

struct Void {};

template <typename ...Args>
struct TypeList {
    typedef Void Head;
    typedef Void Tail;
};


template <typename H, typename ...T>
struct TypeList<H, T...> {
    typedef H Head;
    typedef TypeList<T...> Tail;
};

typedef TypeList<> EmptyTypeList;

#endif //HW2_TL_H
