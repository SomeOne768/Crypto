#include "analysisKeySize.hpp"
#include <iostream>


// Construct an object representing a keySize and its substrings and values for a specific cipher
AnalysisKeySize::AnalysisKeySize(const int kSize, const std::string & cipher):keySize(kSize),subSequences(kSize)
{

    // Generate the substrings of the text, the number of substrings generated is the size of the key
    for (long unsigned int i = 0; i < cipher.size(); i++) subSequences[i % keySize].first += cipher[i];

    // Calculate the IC value of each substring
    for (int i = 0; i < kSize; i++){
        subSequences[i].second = calculateIC(subSequences[i].first);
        averageIc += subSequences[i].second;
    }

    averageIc /= (double) kSize;
}

// Encode a string with the caesar algorithm
std::string AnalysisKeySize::encodeCaesar(const std::string & text, int caesarValue){

    std::string encoded = text;
    for (long unsigned int i = 0; i < encoded.size(); i++)
        encoded[i] = ((encoded[i] - 'A' + caesarValue) % 26) + 'A';

    return encoded;
}

// Decode a given string with the caesar algorithm
std::string AnalysisKeySize::decodeCaesar(const std::string & text, int caesarValue){

    std::string encoded = text;
    int tmp;

    for (long unsigned int i = 0; i < encoded.size(); i++){
        tmp = (encoded[i] - 'A' - caesarValue) % 26;
        encoded[i] = (tmp < 0) ? 'Z' + tmp + 1 : tmp + 'A';
    }

    return encoded;
}

// Calculate the chiSquared value of a given string in a specific language
double AnalysisKeySize::chiSquaredResult(const std::string & text, const long unsigned int & textSize, const std::string & language)
{
    double letterApparition; 
    double expectedApparition;
    double sum = 0;
     
    for (char letter = 'A'; letter <= 'Z'; letter++)
    {
        // For all letters of the alphabet we calculate its number of appearance in the string to analyse
        letterApparition	= (double) getCount(text, letter);
        // Then we calculate the expected number of this letter in the string with its frequency in the language
        expectedApparition	= (((languages.at(language)).first).at(letter) / 100) * textSize;
        // We apply the chiSquared formula 
        sum += (pow((letterApparition - expectedApparition), 2)) / expectedApparition;
    }

    return sum;
}


// Calculate the most probable key used to encrypt with the Vigenere algorithm the original text
const std::string AnalysisKeySize::getKey(std::string language)
{   

    double chiSquared;
    double minChiSquared;
    std::string key = "";
    char minChiSquaredLetter;
    std::string caesarDecoded;
    long unsigned int subsequenceSize;

    // We calculate each character of the key one by one
    for (int i = 1; i <= keySize; i++)
    {	
        subsequenceSize = subSequences[i-1].first.size();

        // We set a default minimum value of the chi squared and letter used to encrypt this substring
        minChiSquared = 10000.0;
        minChiSquaredLetter = 'A';

        // We calculate each of the 26 letters that could be used to encrypt the substring
        for (int caesar = 0; caesar < 26; caesar++){

            // For this letter we decode the message with the reverse algorithm of caesar
            caesarDecoded = decodeCaesar(subSequences[i-1].first, caesar);
            // With this decoded string we can now get its chiSquared value
            chiSquared = chiSquaredResult(caesarDecoded, subsequenceSize, language);

            // The more the chiSquared value is close to zero the closest it is to its original language statistically
            if (chiSquared < minChiSquared)
            {
                minChiSquared 		= chiSquared;
                minChiSquaredLetter	= 'A' + caesar;
            }
        }

        // After all the calculation of this specific character of the key
        // We add the one with the minimum chiSquared value of all the 26 letters
        key += minChiSquaredLetter;
    }

    return key;
}

// Returns the number of occurences of a character in a string
double AnalysisKeySize::getCount(std::string text, char c)
{
    double count = 0;
    for (auto letter : text) if (letter == c) count++;
    return count;
}


// Calculate the IC value of a string 
double AnalysisKeySize::calculateIC(std::string text)
{
    double IC = 0.0;
    double frequencies[NUMBER_OF_LETTER];

    // We take the number of occurences for each letter of the alphabet and put it in an array
    for (auto letter = 'A'; letter <= 'Z'; letter++) frequencies[letter - 'A'] = getCount(text, letter);
     
    // Calculate the IC of the text
    for (double f : frequencies) IC += f * (f - 1) / (text.size() * (text.size() - 1));

    return IC;
}