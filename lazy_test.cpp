#include <iostream>

#include "lazy.h"

void f(lazy<int> x)
{
    std::cout << "1. x = " << x() << std::endl;
    std::cout << "2. x = " << x() << std::endl;
}

int main()
{
    int x = 0;
    f(lazy<int>([&]{ return x++; }));
    f(make_lazy([&]{ return x++; }));
    f(LAZY( x++ ));
}
