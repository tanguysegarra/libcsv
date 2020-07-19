#pragma once

#include <iostream>
#include <exception>

class InvalidArgumentException : public std::exception
{
public:
    InvalidArgumentException(const std::string& msg)
    {
        msg_ = msg;
        std::cerr << msg << "\n";
    }

    virtual const char* what() const noexcept
    {
        return msg_.c_str();
    }

private:
    std::string msg_;
};
