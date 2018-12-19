//
// Created by kravets on 12.12.18.
// TypeList from HW2
//


#pragma once

#ifndef HW3_TL_H
#define HW3_TL_H


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

#endif //HW3_TL_H
