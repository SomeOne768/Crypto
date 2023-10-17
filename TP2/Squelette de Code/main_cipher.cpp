#include <iostream>
#include <string>
#include "vigenere.hpp"
using namespace std;

//////////////////////////////////////////////////////////////////
//                             MAIN                             //
//////////////////////////////////////////////////////////////////

int main()
{
  Vigenere cipher("ALGORITHM");

  string original_en = "PYTHAGORE";
  string encrypted_en = cipher.encrypt(original_en);
  string decrypted_en = cipher.decrypt(encrypted_en);
  cout << original_en << endl;
  cout << "Encrypted: " << encrypted_en << endl;
  cout << "Decrypted: " << decrypted_en << endl;

  string original_fr  = "Principe de Kerckhoffs - Toute la securite d'un systeme cryptographique doit reposer sur la clef et pas sur le systeme lui meme.";

  string encrypted_fr = cipher.encrypt(original_fr);
  string decrypted_fr = cipher.decrypt(encrypted_fr);

  cout << original_fr << endl;
  cout << "Encrypted: " << encrypted_fr << endl;
  cout << "Decrypted: " << decrypted_fr << endl;
}
