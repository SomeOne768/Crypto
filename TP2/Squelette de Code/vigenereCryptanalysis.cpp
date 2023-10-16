#include "vigenereCryptanalysis.hpp"
#include <algorithm>
#include <iostream>

// Constructor of a vigenereCryptanalysis object to decrypt an encoded string and find the key used to encode it 
// with the vigenere algorithm
VigenereCryptanalysis::VigenereCryptanalysis(const string & cipher, const string & languageInit, const int & maximumKeySize)
: maxKeySize(maximumKeySize), language(languageInit), encodedCipher(cipher) 
{

    int bestKeySize 	= 1;
    double closestValue = 0.0;
    double languageValue= languages.at(language).second;

    // We calculate all the substrings and their values for each keySize from 1 to the maximum size passed in argument
    for (int i = 1; i <= maxKeySize; i++){

        analysisKeys.push_back(AnalysisKeySize(i, cipher));

        // We choose to keep the keySize with the substrings that have the closest average IC value to 
        // the language average IC

        /*
        if (abs((analysisKeys[i-1].averageIc) - languageValue) < abs(closestValue - languageValue))
        {
            closestValue = analysisKeys[i-1].averageIc;
            bestKeySize = i;
        }
        */
        

        // We choose to keep the biggest value of IC of the substrings generated for a given keySize
        if ((analysisKeys[i-1].averageIc) > closestValue){
            closestValue = analysisKeys[i-1].averageIc;
            bestKeySize = i;
        }
    }

    // After we have the keySize with the best statistical values for this language we calculate the original key
    keyFound = analysisKeys[bestKeySize-1].getKey(language);
    // Then we decrypt the text with the key we found to get back to the original text before encryption
    decodedCipher = Vigenere(keyFound).decrypt(cipher);
}

const string VigenereCryptanalysis::getKeyFound() const 
{
    return keyFound;
}

const string VigenereCryptanalysis::getLanguage() const 
{
    return language;
}

const string VigenereCryptanalysis::getEncodedCipher() const 
{
    return encodedCipher;
}

const string VigenereCryptanalysis::getDecodedCipher() const 
{
    return decodedCipher;
}





























/************************************************************************************/
/* 																					*/
/************************************************************************************/

// vector<std::string> VigenereCryptanalysis::getSubSequences(std::string & cipher, int & keySize)
// {
//     // Building subsequences for each letter of the key
//     // To iterate we need to categorify each cypher's letter such as
//     // cypher_letter_number % keySize Letter 1 will have all the 0 Letter 2 will
//     // have all the 1
//     // ..

//     // Vector of subsquences


//     vector<std::string> subSequences(keySize);

//     for (long unsigned int i = 0; i < cipher.size(); i++)
//     {
//         subSequences[i % keySize] += cipher[i];
//     }

//     return subSequences;
// }

/************************************************************************************/
/* 																					*/
/************************************************************************************/

// double VigenereCryptanalysis::getFrequencies(string text, char c)
// {
//     // Return the frequence of a letter
//     // Ex: 'aieie" f(a) = 1/5: f(i)=f(e)=2/5
//     double count = 0;
//     for (auto letter : text)
//     {
//         if (letter == c)
//             count++;
//     }

//     return count;
// }

/************************************************************************************/
/* 																					*/
/************************************************************************************/

// double VigenereCryptanalysis::calculateThePeriod(string text)
// {

//     // We take the frequencies for each letter
//     double frequencies[NUMBER_OF_LETTER];
//     for (auto letter = 'A'; letter <= 'Z'; letter++)
//     {
//         frequencies[letter - 'A'] = getFrequencies(text, letter);
//     }

//     // Calculate de IC
//     double IC = 0;
//     for (double f : frequencies)
//     {
//         IC += f * (f - 1) / (text.size() * (text.size() - 1));
//     }

//     return IC;
// }

/************************************************************************************/
/* 																					*/
/************************************************************************************/

// map<double, string> VigenereCryptanalysis::getEachPeriod(vector<string> &subSequences)
// {

//     map<double, string> subSequencesValues;

//     for (string subSequence : subSequences)
//     {
//         subSequencesValues.insert({calculateThePeriod(subSequence), subSequence});
//     }

//     return subSequencesValues;
// }

/************************************************************************************/
/* 																					*/
/************************************************************************************/

// double VigenereCryptanalysis::averageOfPeriods(const map<double, string> &subSequencesPeriods)
// {
//     double average = 0.0;

//     for (auto const &pair : subSequencesPeriods)
//     {
//         // We add to the average each IC value of the subsequences
//         average += (pair.first);
//     }

//     // We divide the sum of IC values by the number of subsequences
//     average /= (double)subSequencesPeriods.size();
//     return average;
// }

/************************************************************************************/
/* 																					*/
/************************************************************************************/

// vector<double> VigenereCryptanalysis::getAverages(string & cipher, int & maxKeySize)
// {
    
//     vector<double> allAverages;
//     vector<string> subSequences;
//     map<double, string> subSequencesPeriods;
//     double averageOfPeriod; 

//     for (int i = 1; i < maxKeySize; i++)
//     {
//         subSequences        = getSubSequences(cipher, i);
//         subSequencesPeriods = getEachPeriod(subSequences);
//         averageOfPeriod     = averageOfPeriods(subSequencesPeriods);
//         allAverages.push_back(averageOfPeriod);
//     }

//     return allAverages;
// }

// string static decrypt(string & cipher, int & maxKeySize);