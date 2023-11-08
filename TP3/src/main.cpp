#include "P16.hpp"
#include "block.hpp"
#include <iostream>

const int N = 1<<16;

P16 tab[N];
void buildInversor(P16 tab[]);
void shiftRow(P16 &);

int main() {
  
  buildInversor(tab);

  return 0;
}

void buildInversor(P16 tab[]) {
  P16 polynomeToFindInverse{1};
  for (int i = 0; i < N; i++) {

    P16 polynomeInverse{1};

    while ((polynomeInverse * polynomeToFindInverse).polynome != 1) {
      polynomeInverse.multiplyX();
    }

    tab[i] = polynomeInverse;
    polynomeToFindInverse.polynome++;
  }
}


void shiftRow(P16 &p, unsigned int i)
{
    short int lastBits = p.polynome >> (16-i);
    p.polynome <<= i;
    p.polynome += lastBits;
}