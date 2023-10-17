#include "vigenereCryptanalysis.hpp"
#include <algorithm>
#include <iostream>
#include <cctype>

/**************************************************************************/
/* Constructor build an object that make the complete analysis            */
/* It try to find the different possible keys and decipher the text       */
/**************************************************************************/
VigenereCryptanalysis::VigenereCryptanalysis(const string &cipher,
                                             const string &languageInit, const int &maximumKeySize)
    : maxKeySize(maximumKeySize), language(languageInit), encodedCipher(cipher)
{
    // transform each letter to uppercase
    for (long unsigned int i = 0; i < encodedCipher.size(); i++)
        encodedCipher[i] = toupper(encodedCipher[i]);

    // Build a vector that will contains keys with their respectives
    // size and IC sorted from best to worst
    std::vector<std::pair<int, double>> bestKeySizes(NUMBER_OF_KEYSIZES, {-1, 0.0});

    // Make analysis for the different keysize
    for (int i = 0; i < maxKeySize; i++)
    {
        // Get the mean IC for the specifik keysize
        analysisKeys.push_back(AnalysisKeySize(i + 1, cipher));

        /************************ TO MOOVE LATER ************************/
        // Find the best key
        for (int j = 0; j < NUMBER_OF_KEYSIZES; j++)
        {
            
            // The more the chiSquared value is close to zero the closest it is to its original language statistically
            if ((bestKeySizes[j].first == -1) || (analysisKeys[i].averageIc > bestKeySizes[j].second))
            {
                for (int k = NUMBER_OF_KEYSIZES - 1; k > j; k--)
                {
                    bestKeySizes[k] = bestKeySizes[k - 1];
                }

                bestKeySizes[j] = {i + 1, analysisKeys[i].averageIc};
                break;
            }
        }
        /************************ TO MOOVE LATER ************************/
    }


    // Display results of the best key with its decoded text
    for (int j = 0; j < NUMBER_OF_KEYSIZES; j++)
    {
        if (bestKeySizes[j].first != -1)
        {
            analysisKeys[bestKeySizes[j].first - 1].getKeys(languageInit);
            for (std::pair<double, std::pair<std::string, std::string>> keyAndDecoded : analysisKeys[bestKeySizes[j].first - 1].keysAndDecoded)
            {
                std::cout << "\n Key : " << keyAndDecoded.second.first << "\n Decoded :   " << keyAndDecoded.second.second << std::endl;
            }
        }
    }
}

const string VigenereCryptanalysis::getLanguage() const
{
    return language;
}

const string VigenereCryptanalysis::getEncodedCipher() const
{
    return encodedCipher;
}