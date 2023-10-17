#include "vigenereCryptanalysis.hpp"
#include <algorithm>
#include <iostream>
#include <cctype>

/**************************************************************************/
/* Constructor build an object that make the complete analysis            */
/* It try to find the different possible keys and decipher the text       */
/**************************************************************************/
VigenereCryptanalysis::VigenereCryptanalysis(const string &cipher, const string &language, const int &maximumKeySize)
    : maxKeySize(maximumKeySize), encodedCipher(cipher)
{
    // Convert the entire encodedCipher to uppercase for uniformity
    for (long unsigned int i = 0; i < encodedCipher.size(); i++)
        encodedCipher[i] = toupper(encodedCipher[i]);

     // Initialize a vector to store the best key sizes based on the average Index of Coincidence (IC)
    std::vector<std::pair<int, double>> bestKeySizes(NB_BEST_KEYSIZES, {-1, 0.0});

    // We calculate all the substrings and their values for each keySize from 1 to the maximum size passed in argument
    for (int i = 0; i < maxKeySize; i++)
    {

        analysisKeys.push_back(AnalysisKeySize(i + 1, cipher));

        for (int j = 0; j < NB_BEST_KEYSIZES; j++)
        {

            // The more the chiSquared value is close to zero the closest it is to its original language statistically
            if ((bestKeySizes[j].first == -1) || (analysisKeys[i].averageIc > bestKeySizes[j].second))
            {
                for (int k = NB_BEST_KEYSIZES - 1; k > j; k--)
                {
                    bestKeySizes[k] = bestKeySizes[k - 1];
                }

                bestKeySizes[j] = {i + 1, analysisKeys[i].averageIc};
                break;
            }
        }
    }

    // Iterate through the best key sizes and analyze them to find the keys and their decoded versions
    for (int j = 0; j < NB_BEST_KEYSIZES; j++)
    {
        if (bestKeySizes[j].first != -1)
        {
            analysisKeys[bestKeySizes[j].first - 1].getKeys(language);
            for (std::pair<double, std::pair<std::string, std::string>> keyAndDecoded : analysisKeys[bestKeySizes[j].first - 1].keysAndDecoded)
            {
                if (keyAndDecoded.second.first != DEFAULT_STRING)
                {
                    std::cout << "\nKey " << j << " : " << keyAndDecoded.second.first << "\nDecoded :   " << keyAndDecoded.second.second << std::endl;
                }
            }
        }
    }
}

/********************************************/
/* Method that returns the encoded cipher   */
/* stored in the VigenereCryptanalysis class*/
/********************************************/
const string VigenereCryptanalysis::getEncodedCipher() const
{
    return encodedCipher;
}

/********************************************/
/* Method that returns the language used in */
/* the VigenereCryptanalysis class.         */
/********************************************/
const string VigenereCryptanalysis::getLanguage() const
{
    return language;
}
