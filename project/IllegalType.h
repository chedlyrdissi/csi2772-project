#include <exception>

struct IllegalType : public std::exception
{
    const char* what() const throw ()
    {
        return "Card Type does not match";
    }
};

#pragma once
