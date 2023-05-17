#ifndef _TYPE_TRAITS_
#define _TYPE_TRAITS_

template<typename T>
struct TypeTrait{
    static const bool isPointer = false;
};
template<typename T>
struct TypeTrait<T*>{
    static const bool isPointer = true;
};

#endif