#ifndef VIGENERE_HPP
#define VIGENERE_HPP

#include <string>

class Vigenere
{
	public:

		std::string key;
		Vigenere(const std::string &);
		std::string encrypt(const std::string &);
	    std::string decrypt(const std::string &);
};

#endif