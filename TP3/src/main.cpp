#include "P16.hpp"
#include "block.hpp"
#include <iostream>

void buildInversor(P16 tab[]);

int main() {
  P16 tab[16];
  buildInversor(tab);

  return 0;
}

void buildInversor(P16 tab[]) {
  P16 polynomeToFindInverse{1};
  for (int i = 0; i < 16; i++) {

    P16 polynomeInverse{1};

    while ((polynomeInverse * polynomeToFindInverse).polynome != 1) {
      polynomeInverse.multiplyX();
    }
    
    tab[i] = polynomeInverse;
    polynomeToFindInverse.polynome <<= 1;
  }
}