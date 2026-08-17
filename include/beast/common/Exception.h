#ifndef BEAST_EXCEPTION_H
#define BEAST_EXCEPTION_H

#include <stdexcept>

class Exception : public std::runtime_error
{
public:
    explicit Exception(const char* arg);
    const char* msg;
};

#endif
