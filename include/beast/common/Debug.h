#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <cstdio>

class Debug
{
public:
    Debug(const char* prefix, const char* basepath, const char* filename );
    Debug(const char* prefix, const char* filename );
    Debug(const char* prefix );
    
    ~Debug();

    void print(const char* format, ...);

    FILE* getFile();

    Debug(const Debug&) = delete;
    Debug& operator=(const Debug&) = delete;

private:
    FILE* fdbg;
    char* prefix;
};

#endif // __DEBUG_H__