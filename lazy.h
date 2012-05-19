#ifndef __LAZY_H__
#define __LAZY_H__

#include <functional>

template<typename T>
class lazy
{

public:
    lazy(std::function<T()> func) : func(func), evaluated(false)
    {
    }

    const T& operator()()
    {
        if (!evaluated) {
            value = func();
            evaluated = true;
        }
        return value;
    }

private:
    std::function<T()> func;
    T value;
    bool evaluated;
};

template<typename F>
auto make_lazy(F func) -> lazy<decltype(func())>
{
    return lazy<decltype(func())>(func);
}

#define LAZY(EXPR) make_lazy([&]{ return EXPR; })

#endif//__LAZY_H__
