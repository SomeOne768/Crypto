#pragma once

/**
 * @brief class that respresent
 *
 */
class P16
{
    short int polynome;

public:
    P16() = default;
    P16(short int x);
    ~P16() = default;

    void multiplyX();
    void multiply(const P16&);

    P16 operator+(const P16 &);
};