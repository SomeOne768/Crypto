#include <iostream>
#include <string>
using namespace std;

class Vigenere
{
public:
  string key;
 
  Vigenere(string key)
  {
    // Modifying all characters other than uppercase : lowercase -> uppercase, other -> delete
    for(unsigned int i = 0; i < key.size(); ++i)
    {
      if(key[i] >= 'A' && key[i] <= 'Z')
        this->key += key[i];
      else if(key[i] >= 'a' && key[i] <= 'z')
        this->key += key[i] + 'A' - 'a';
    }
  }
 
  string encrypt(string text)
    {
      string out;
      int indexKey = 0;

      // Modifying all characters other than uppercase : lowercase -> uppercase, other -> delete
      for(unsigned int i = 0; i < text.length(); ++i)
      {
        if(text[i] >= 'A' && text[i] <= 'Z'){
          out += ((text[i] - 'A' + key[indexKey] - 'A') % 26) + 'A';
          indexKey = (indexKey + 1) % key.length();
        }
        else if(text[i] >= 'a' && text[i] <= 'z')
        {
          out += ((text[i] - 'a' + key[indexKey] - 'A') % 26) + 'A';
          indexKey = (indexKey + 1) % key.length();
        }
      }

      return out;
    }
 
  string decrypt(string text)
  {
    // Text is all uppercase
    string out;

    // To find the original letter we must:
    // Graphically
    // 1. Take a letter from the key
    // 2. Find the letter of the cipher to get the (real)text
    
    // Mathematically
    // Labels:
    // k: key
    // c: cipher
    // d: decipher
    // Calcul for each caractere: d = (c - k) [26] and if d<0 then take 'Z' + d

    int indice_key = 0;
    for(char cypher_letter : text)
    {
      // decypher letter and converting into base 26
      int d = (cypher_letter - key[indice_key]) % 26;
      // checking if d < 0
      d = d<0? d+26:d;    

      // Reconvert into ASCII base
      char decipher_letter = d + 'A';

      // Adding letter to the de decipher text
      out += decipher_letter;

      // Taking the next letter of the key
      indice_key++;
      indice_key%= key.length();
    } 

    return out;
  }
};

//////////////////////////////////////////////////////////////////
//                             MAIN                             //
//////////////////////////////////////////////////////////////////

int main()
{
  Vigenere cipher("ALGORITHM");
 
  string original_en  = "PYTHAGORE";
  string encrypted_en = cipher.encrypt(original_en);
  string decrypted_en = cipher.decrypt(encrypted_en);
  cout << original_en << endl;
  cout << "Encrypted: " << encrypted_en << endl;
  cout << "Decrypted: " << decrypted_en << endl;

  // string original_fr  = "Principe de Kerckhoffs - Toute la securite d'un systeme cryptographique doit reposer sur la clef et pas sur le systeme lui meme.";

  // string encrypted_fr = cipher.encrypt(original_fr);
  // string decrypted_fr = cipher.decrypt(encrypted_fr);
 
  // cout << original_fr << endl;
  // cout << "Encrypted: " << encrypted_fr << endl;
  // cout << "Decrypted: " << decrypted_fr << endl;

}

