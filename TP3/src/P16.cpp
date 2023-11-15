#include "P16.hpp"

P16::P16(short int x) : polynome(x) {}

P16 P16::operator+(const P16 &p)
{
    short int res = p.polynome ^ polynome;
    return P16{res};
}

void P16::multiplyX()
{
    short int signe = polynome >> 15;
    polynome <<= 1;
    if (signe)
    {
        (*this) = (*this) + P16{45};
    }
}

void P16::multiply(const P16 &p)
{
    short int last = p.polynome;
    for (int i = 1; i < 15; i++)
    {
        last <<= 1;
        if (last % 2 == 1)
            for (int j = 0; j < i; j++)
                this->multiplyX();
    }
}


P16& P16::operator*(const P16 &p)
{
    this->multiply(p);
    return *this;
}

