#include <exception>

struct NotEnoughCoins : public std::exception
{
    const char* what() const throw ()
    {
        return "Player does not have enough coins";
    }
};

#pragma once
