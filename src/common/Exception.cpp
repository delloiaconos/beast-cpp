#include <beast/common/Exception.h>

Exception::Exception(const char* arg)
    : std::runtime_error(arg), msg(arg)
{
}
