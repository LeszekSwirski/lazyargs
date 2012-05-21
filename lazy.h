#ifndef __LAZY_H__
#define __LAZY_H__

#include <functional>

template<typename T>
class lazy
{

public:
    lazy(std::function<T()> func) : func(func)
    {
    }

    const T& operator()()
    {
        if (func) {
            value = func();
            func = nullptr;
        }
        return value;
    }

private:
    std::function<T()> func;
    T value;
};

template<typename F>
auto make_lazy(F func) -> lazy<decltype(func())>
{
    return lazy<decltype(func())>(func);
}

#define LAZY(EXPR) make_lazy([&]{ return EXPR; })

#endif//__LAZY_H__
