#ifndef __LAZY_H__
#define __LAZY_H__

#include <functional>
#include <memory>

template<typename T>
class lazy
{

public:
    template<
        typename U,
        typename URet = decltype(std::declval<U>()()),
        typename CheckReturnType = typename std::enable_if<std::is_convertible<URet, T>::value>::type
    >
    lazy(U&& func) : func(std::forward<U>(func))
    {
    }
    
    lazy(lazy<T>&& other) = default;
    lazy(lazy<T>& other) = delete;
    
    lazy(T&& val) : value(new T(std::forward<T>(val)))
    {
    }

    const T& operator()()
    {
        if (!value) {
            value.reset(new T(std::forward<T>(func())));
        }
        return *value;
    }

private:
    std::function<T()> func;
    std::unique_ptr<T> value;
};

template<typename F>
auto make_lazy(F&& func) -> lazy<decltype(func())>
{
    return lazy<decltype(func())>(std::forward<F>(func));
}

#define LAZY_BLOCK(...) make_lazy([&]{ __VA_ARGS__; })
#define LAZY(...) LAZY_BLOCK(return __VA_ARGS__;)

#endif//__LAZY_H__
