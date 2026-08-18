#include <beast/numerics/Matrix.h>
#include <cassert>

int main()
{
    Matrix a(2, 3);
    a(1, 1) = 1.0;
    a(1, 2) = 2.0;
    a(2, 3) = 6.0;

    Matrix b(1, 1);
    b = a;
    assert(b.GetRows() == 2);
    assert(b.GetCols() == 3);
    assert(b(1, 2) == 2.0);
    assert(b(2, 3) == 6.0);

    b = b; // self-assignment
    assert(b(1, 1) == 1.0);

    b.Transpose();
    assert(b.GetRows() == 3);
    assert(b.GetCols() == 2);
    assert(b(2, 1) == 2.0);
    assert(b(3, 2) == 6.0);
    return 0;
}
