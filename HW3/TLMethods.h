//
// Created by kravets on 12.12.18.
// TypeList from HW2
//

#pragma once

#include <type_traits>

#include "TL.h"

#ifndef HW3_TLMETHODS_H
#define HW3_TLMETHODS_H


//Check empty
template<typename TList>
struct IsEmpty :
        std::true_type {};

template<>
struct IsEmpty<EmptyTypeList> :
        std::true_type {};


template<typename ...Args>
struct IsEmpty<TypeList<Args...>> :
        std::integral_constant<bool,
                std::is_same<typename TypeList<Args...>::Head, Void>::value &&
                IsEmpty<typename TypeList<Args...>::Tail>::value>{};



//Length
template<typename TList>
struct Length :
        std::integral_constant<unsigned int, 0> {};

template<typename ...Args>
struct Length<TypeList<Args...>> :
        std::integral_constant<unsigned int , IsEmpty<TypeList<Args...>>::value != 0
                                              ? 1 + Length<typename TypeList<Args...>::Tail>::value
                                              : 0> {};


//Индексированый доступ
template<typename TList, unsigned int i>
struct TypeAt {
    typedef Void type;
};

template<typename ...Args>
struct TypeAt<TypeList<Args...>, 0> {
    typedef typename TypeList<Args...>::Head type;
};

template<typename ...Args, unsigned int i>
struct TypeAt<TypeList<Args...>, i> {
    typedef typename TypeAt<typename TypeList<Args...>::Tail, i - 1>::type type;
};



//Добавление элемента в начало
template<typename T, typename TList> struct Append;

template<typename T, typename ...Args>
struct Append<T, TypeList<Args...>> {
    typedef TypeList<T, Args...> NewTypeList;
};



//Получение первых N
template<typename TList, unsigned int N> struct GetFirstN;

template<typename ...Args>
struct GetFirstN<TypeList<Args...>, 0> {
    typedef EmptyTypeList headN;
};

template<unsigned int N>
struct GetFirstN<EmptyTypeList, N> {
    typedef EmptyTypeList headN;
};

template<typename ...Args, unsigned int N>
struct GetFirstN<TypeList<Args...>, N> {
    typedef typename Append<typename TypeList<Args...>::Head,
            typename GetFirstN<typename TypeList<Args...>::Tail, N - 1>::headN>::NewTypeList headN;
};


//Удаления первых N
template<typename TList, unsigned int N> struct DeleteFirstN;

template<typename ...Args>
struct DeleteFirstN<TypeList<Args...>, 0> {
    typedef TypeList<Args...> TLWithoutFirstN;
};

template<unsigned int N>
struct DeleteFirstN<EmptyTypeList, N> {
    typedef EmptyTypeList TLWithoutFirstN;
};

template<typename ...Args, unsigned int N>
struct DeleteFirstN<TypeList<Args...>, N> {
    typedef typename DeleteFirstN<typename TypeList<Args...>::Tail, N - 1>::TLWithoutFirstN TLWithoutFirstN;
};


//Подсчет размера
template<typename TList>
struct SumSize : std::integral_constant<unsigned int, 0> {};

template<typename ...Args>
struct SumSize<TypeList<Args...>> : std::integral_constant<unsigned int, IsEmpty<TypeList<Args...>>::value ?
        0 : sizeof(typename TypeList<Args...>::Head) /**/+ SumSize<typename TypeList<Args...>::Tail>::value
>
{
};

#endif //HW3_TLMETHODS_H
