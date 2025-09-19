#include "bigint.hpp"
#include <iostream>

int main() {
    const bigint a(42);
    bigint b(21), c, d(1337), e(d);

    std::cout << "a = " << a << std::endl;      // muestra: a = 42
    std::cout << "b = " << b << std::endl;      // muestra: b = 21
    std::cout << "c = " << c << std::endl;      // muestra: c = 0
    std::cout << "d = " << d << std::endl;      // muestra: d = 1337
    std::cout << "e = " << e << std::endl;      // muestra: e = 1337

    std::cout << "a + b = " << a + b << std::endl;          // muestra: a + b = 63
    std::cout << "(c += a) = " << (c += a) << std::endl;    // muestra: (c += a) = 42

    std::cout << "b = " << b << std::endl;          // muestra: b = 21
    std::cout << "++b = " << ++b << std::endl;      // muestra: ++b = 22
    std::cout << "b++ = " << b++ << std::endl;      // muestra: b++ = 22

    std::cout << "(b << 10) + 42 = " << ((b << 10) + 42) << std::endl;      // muestra: (b << 10) + 42 = 230000000042
    std::cout << "(d <<= 4) = " << (d <<= 4) << std::endl;                  // muestra: (d <<= 4) = 13370000
    std::cout << "(d >>= 2) = " << (d >>= (const bigint)2) << std::endl;    // muestra: (d >>= 2) = 133700

    std::cout << "a = " << a << std::endl;       // muestra: a = 42
    std::cout << "d = " << d << std::endl;       // muestra: d = 133700

    std::cout << "(d < a) = " << (d < a) << std::endl;      // muestra: 0
    std::cout << "(d <= a) = " << (d <= a) << std::endl;    // muestra: 0 
    std::cout << "(d > a) = " << (d > a) << std::endl;      // muestra: 1 
    std::cout << "(d >= a) = " << (d >= a) << std::endl;    // muestra: 1 
    std::cout << "(d == a) = " << (d == a) << std::endl;    // muestra: 0 
    std::cout << "(d != a) = " << (d != a) << std::endl;    // muestra: 1 
}

