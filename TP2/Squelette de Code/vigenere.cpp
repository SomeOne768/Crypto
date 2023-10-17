#include "vigenere.hpp"

/********************************************/
/* Constructor that take a key and check it */
/* Contains only valide characters          */
/********************************************/
Vigenere::Vigenere(const std::string & initKey)
{
    // Modifying all characters other than uppercase : lowercase -> uppercase, other -> delete
    for (unsigned int i = 0; i < initKey.size(); ++i)
    {
        if (initKey[i] >= 'A' && initKey[i] <= 'Z')
            this->key += initKey[i];
        else if (initKey[i] >= 'a' && initKey[i] <= 'z')
            this->key += initKey[i] + 'A' - 'a';
    }
}


/********************************************/
/* Method that take in input a plain text   */
/* and cipher it with the class key         */
/* It also check (and remove if necessary)  */
/* all the characters and keep, transform   */
/* letter to uppercase                      */
/********************************************/
std::string Vigenere::encrypt(const std::string & text)
{
    std::string out;
    int indexKey = 0;

    // Modifying all characters other than uppercase : lowercase -> uppercase, other -> delete
    for (unsigned int i = 0; i < text.length(); ++i)
    {
        if (text[i] >= 'A' && text[i] <= 'Z')
        {
            out += ((text[i] - 'A' + key[indexKey] - 'A') % 26) + 'A';
            indexKey = (indexKey + 1) % key.length();
        }
        else if (text[i] >= 'a' && text[i] <= 'z')
        {
            out += ((text[i] - 'a' + key[indexKey] - 'A') % 26) + 'A';
            indexKey = (indexKey + 1) % key.length();
        }
    }

    return out;
}


/********************************************/
/* Method that take as input a cipher text  */
/* which must contains only uppercase letter*/
/* and decipher it with the class key.      */
/********************************************/
std::string Vigenere::decrypt(const std::string & text)
{
    // Text is all uppercase
    std::string out;

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
    for (char cypher_letter : text)
    {
        // decypher letter and converting into base 26
        int d = (cypher_letter - key[indice_key]) % 26;
        // checking if d < 0
        d = (d < 0) ? d + 26 : d;

        // Reconvert into ASCII base
        char decipher_letter = d + 'A';

        // Adding letter to the de decipher text
        out += decipher_letter;

        // Taking the next letter of the key
        (++indice_key)%=key.length();
    }

    return out;
}