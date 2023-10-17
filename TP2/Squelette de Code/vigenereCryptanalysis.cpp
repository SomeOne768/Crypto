#include "vigenereCryptanalysis.hpp"
#include <algorithm>
#include <iostream>
#include <cctype>
sssssssssssssssssssssssssssssssssssssss
/**************************************************************************/
/* Constructor build an object that make the complete analysis            */
/* It try to find the different possible keys and decipher the text       */
/**************************************************************************/
VigenereCryptanalysis::VigenereCryptanalysis(const string & cipher, const string & language,const int & maximumKeySize)
: maxKeySize(maximumKeySize), encodedCipher(cipher) 
{
    // transform each letter to uppercase
    for (long unsigned int i = 0; i < encodedCipher.size(); i++)
        encodedCipher[i] = toupper(encodedCipher[i]);

    for (long unsigned int i = 0; i < encodedCipher.size(); i++) encodedCipher[i] = toupper(encodedCipher[i]);

    std::vector<std::pair<int, double>> bestKeySizes(NB_BEST_KEYSIZES, {-1, 0.0});

    // We calculate all the substrings and their values for each keySize from 1 to the maximum size passed in argument
    for (int i = 0; i < maxKeySize; i++){

    // Make analysis for the different keysize
    for (int i = 0; i < maxKeySize; i++)
    {
        // Get the mean IC for the specifik keysize
        analysisKeys.push_back(AnalysisKeySize(i + 1, cipher));

        for (int j = 0; j < NB_BEST_KEYSIZES; j++)
        {   

            // The more the chiSquared value is close to zero the closest it is to its original language statistically
            if ((bestKeySizes[j].first == -1) || (analysisKeys[i].averageIc > bestKeySizes[j].second))
            {
                for (int k = NB_BEST_KEYSIZES -1; k > j; k--)
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
    for (int j = 0; j < NB_BEST_KEYSIZES; j++)
    {   

        if (bestKeySizes[j].first != -1)
        {
            analysisKeys[bestKeySizes[j].first - 1].getKeys(language);
            for (std::pair<double, std::pair<std::string, std::string>> keyAndDecoded : analysisKeys[bestKeySizes[j].first - 1].keysAndDecoded)
            {
                if (keyAndDecoded.second.first != DEFAULT_STRING)
                {
                    std::cout << "\nKey " << j << " : " << keyAndDecoded.second.first << "\nDecoded :   " <<  keyAndDecoded.second.second << std::endl;
                }
            }
        }
    }
}


const string VigenereCryptanalysis::getEncodedCipher() const 
{
    return encodedCipher;
}

const string VigenereCryptanalysis::getLanguage() const 
{
    return language;
}
