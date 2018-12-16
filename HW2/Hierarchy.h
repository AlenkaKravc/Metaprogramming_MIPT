//
// Created by kravets on 12.12.18.
//

#pragma once

#include "TL.h"
#include "TLMethods.h"

#ifndef HW2_HIERARCHY_H
#define HW2_HIERARCHY_H


struct EmptyType {};

template<class TList , template<class AtomicType , class base> class Unit , class Root = EmptyType>
class GenLinearHierarchy;


template<typename TList , template<class> class UnitScatter ,
        template<class , class> class UnitLinear , unsigned int prevFib = 0 , unsigned int currFibb = 1>
class GenScatterHierarchy;


template<typename ...T , template<class> class UnitScatter ,
        template<class , class> class UnitLinear , unsigned int prevFib , unsigned int currFibb>
class GenScatterHierarchy<TypeList<T...> , UnitScatter , UnitLinear , prevFib , currFibb> :
public GenLinearHierarchy<typename GetFirstN<TypeList<T...> , currFibb + 1>::headN , UnitLinear , EmptyType> ,
public GenScatterHierarchy<DeleteFirstN<TypeList<T...> , currFibb + 1> , UnitScatter , UnitLinear , currFibb ,
prevFib + currFibb> {
};


template<typename AtomicType , template<class> class UnitScatter ,
        template<class , class> class UnitLinear , unsigned int prevFib , unsigned int currFibb>
class GenScatterHierarchy : public UnitScatter<AtomicType> {
};

template<template<class> class UnitScatter ,
        template<class , class> class UnitLinear>
class GenScatterHierarchy<EmptyTypeList , UnitScatter , UnitLinear> {
};


template<typename T1 , typename ...T2 , template<class , class> class Unit , class Root>
class GenLinearHierarchy<TypeList<T1 , T2...> , Unit , Root> :
public Unit<T1 , GenLinearHierarchy<TypeList<T2...> , Unit , Root>> {
};


template<typename T , template<class , class> class Unit , class Root>
class GenLinearHierarchy : public Unit<T , Root> {
};
#endif //HW2_HIERARCHY_H
