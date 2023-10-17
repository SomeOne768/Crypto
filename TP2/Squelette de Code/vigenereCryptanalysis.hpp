#ifndef VIGENERECRYPTANALYSIS_HPP
#define VIGENERECRYPTANALYSIS_HPP

using namespace std;

#include <string>
#include <array>
#include <vector>
#include <map>
#include "analysisKeySize.hpp"
#include "vigenere.hpp"

class VigenereCryptanalysis
{
	private:

		int maxKeySize;
                string language;
                string encodedCipher;
                vector<AnalysisKeySize> analysisKeys;

	public:

                VigenereCryptanalysis(const string &, const string &, const int &);
                const string getLanguage() const;
                const string getEncodedCipher() const;
        
};

#endif