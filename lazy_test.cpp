#include <iostream>

#include "lazy.h"


int getx() {
    std::cout << "[Calculating x]";
    return 1;
}

void f(lazy<int> x)
{
    // Move constructor should fail
    // auto y = x;
    std::cout << "1. x = " << x() << std::endl;
    std::cout << "2. x = " << x() << std::endl;
}

int main()
{
    int x = 0;
    std::cout << "Direct construction" << std::endl;
    f(lazy<int>([&]{ return x++; }));
    std::cout << "make_lazy" << std::endl;
    f(make_lazy([&]{ return x++; }));
    std::cout << "LAZY macro" << std::endl;
    f(LAZY( x++ ));
    std::cout << "Implicit lambda conversion" << std::endl;
    f([&]{return x++;});
    //std::cout << "Implicit lambda conversion with wrong type (should fail to compile)" << std::endl;
    //f([&]{return "x++";});
    std::cout << "Non-lazy call" << std::endl;
    f(getx());
    std::cout << "Lazy call (above wrapped with LAZY macro)" << std::endl;
    f(LAZY(getx()));
}
