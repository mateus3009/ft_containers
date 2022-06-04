#ifndef DUMMY_HPP
#define DUMMY_HPP

#include <iostream>

namespace foo
{

    struct cat
    {
        void meow() { std::cout << "meow foo" << std::endl; }
    };

}

namespace bar
{

    struct cat
    {
        void meow() { std::cout << "meow bar" << std::endl; }
    };

}

#endif
