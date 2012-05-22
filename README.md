Lazyargs
========

This class allows one to use lazy arguments (call-by-need) in C++11. Lazy arguments are evaluated at most once, on first use,
using lambdas to store their evaluating function.

Functions taking lazy arguments need to use the lazy wrapping class and the () operator, so

    void f(int x) {
    ...
        g(x);
    ...
    }

becomes

    void f(lazy<int> x) {
    ...
        g( x() );
    ...
    }
    
Then, anyone who calls a lazy function has to either pass a lambda into make_lazy:

    f(make_lazy([&] { return expensive_make_x(); }));
    
or use the LAZY helper macro (equivalent to the above):

    f(LAZY(expensive_make_x()));