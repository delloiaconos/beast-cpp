#include <beast/common/Debug.h>

#include <cassert>
#include <cstdio>
#include <cstring>

static void readFile(
    const char* filename,
    char* buffer,
    std::size_t bufferSize)
{
    FILE* file = std::fopen(filename, "r");

    assert(file != nullptr);

    const std::size_t n =
        std::fread(
            buffer,
            1,
            bufferSize - 1,
            file
        );

    buffer[n] = '\0';

    std::fclose(file);
}


static void test_print_with_prefix()
{
    const char* filename = "test_debug.log";

    {
        Debug dbg( "[TEST] ", filename );

        dbg.print(
            "Value = %d\n",
            42
        );
    }

    char buffer[256];

    readFile(
        filename,
        buffer,
        sizeof(buffer)
    );

    assert(
        std::strcmp(
            buffer,
            "[TEST] Value = 42\n"
        ) == 0
    );

    std::remove(filename);
}


static void test_multiple_prints()
{
    const char* filename = "test_debug.log";

    {
        Debug dbg( "[DBG] ", filename );

        dbg.print("First\n");
        dbg.print("Second\n");
        dbg.print("Value = %.2f\n", 3.14);
    }

    char buffer[256];

    readFile(
        filename,
        buffer,
        sizeof(buffer)
    );

    assert(
        std::strcmp(
            buffer,
            "[DBG] First\n"
            "[DBG] Second\n"
            "[DBG] Value = 3.14\n"
        ) == 0
    );

    std::remove(filename);
}


static void test_without_prefix()
{
    const char* filename = "test_debug.log";

    {
        Debug dbg( nullptr, filename );

        dbg.print("No prefix\n");
    }

    char buffer[256];

    readFile(
        filename,
        buffer,
        sizeof(buffer)
    );

    assert(
        std::strcmp(
            buffer,
            "No prefix\n"
        ) == 0
    );

    std::remove(filename);
}


static void test_basepath_constructor()
{
    const char* basepath = ".";
    const char* filename = "test_debug.log";

    {
        Debug dbg("[PATH] ", basepath, filename );

        dbg.print("Hello\n");
    }

    char buffer[256];

    readFile(
        filename,
        buffer,
        sizeof(buffer)
    );

    assert(
        std::strcmp(
            buffer,
            "[PATH] Hello\n"
        ) == 0
    );

    std::remove(filename);
}


int main()
{
    test_print_with_prefix();
    test_multiple_prints();
    test_without_prefix();
    test_basepath_constructor();

    std::printf("All Debug tests passed.\n");

    return 0;
}
