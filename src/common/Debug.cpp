#include <beast/common/Debug.h>

#include <cstdarg>
#include <cstdlib>
#include <cstring>

Debug::Debug(const char* prefix_, const char* basepath, const char* filename )
    : fdbg(nullptr), prefix(nullptr)
{
    /*
     * Store prefix.
     */
    if (prefix_ != nullptr)
    {
        prefix = static_cast<char*>( std::malloc(std::strlen(prefix_) + 1) );

        if (prefix != nullptr)
        {
            std::strcpy(prefix, prefix_);
        }
    }

    if (basepath == nullptr || filename == nullptr)
        return;

    /*
     * Allocate:
     *
     * basepath + "/" + filename + '\0'
     */
    const size_t path_length =
        std::strlen(basepath) +
        std::strlen(filename) +
        2;

    char* filepath =
        static_cast<char*>(std::malloc(path_length));

    if (filepath == nullptr) {
        return;
    }

    /*
     * Add the directory separator only if necessary.
     */
    const size_t base_length = std::strlen(basepath);

    if (base_length > 0 &&
        basepath[base_length - 1] != '/' &&
        basepath[base_length - 1] != '\\') {
        std::snprintf( filepath, path_length, "%s/%s", basepath, filename );
    } else {
        std::snprintf( filepath, path_length, "%s%s", basepath, filename );
    }

    fdbg = std::fopen(filepath, "w");

    std::free(filepath);
}


Debug::Debug(const char* prefix_, const char* filename )
    : fdbg(nullptr),
      prefix(nullptr)
{
    /*
     * Store prefix.
     */
    if (prefix_ != nullptr) {
        prefix = static_cast<char*>(
            std::malloc(std::strlen(prefix_) + 1)
        );

        if (prefix != nullptr) {
            std::strcpy(prefix, prefix_);
        }
    }

    if (filename != nullptr) {
        fdbg = std::fopen(filename, "w");
    }
}


Debug::~Debug()
{
    if (fdbg != nullptr) {
        std::fclose(fdbg);
        fdbg = nullptr;
    }

    if (prefix != nullptr) {
        std::free(prefix);
        prefix = nullptr;
    }
}


void Debug::print(const char* format, ...)
{
    if (fdbg == nullptr || format == nullptr) {
        return;
    }
    
    if (prefix != nullptr) {
        std::fprintf(fdbg, "%s", prefix);
    }

    va_list args;

    va_start(args, format);
    std::vfprintf(fdbg, format, args);
    va_end(args);

    std::fflush(fdbg);
}

FILE* Debug::getFile( void ) 
{
    return fdbg;
}