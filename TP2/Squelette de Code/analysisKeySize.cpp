#include "analysisKeySize.hpp"
#include <iostream>


/****************************************************************/
/* Construct an object representing a keySize with its          */
/* substrings and values for a specific cipher                  */
/****************************************************************/
AnalysisKeySize::AnalysisKeySize(const int kSize, const std::string & cipher)
: encoded(cipher), keySize(kSize) , subSequences(kSize), keysAndDecoded(NB_BEST_KEYS_PER_KEYSIZE, {0.0, {DEFAULT_STRING, DEFAULT_STRING}}),
bestCharactersForKeys(kSize, std::vector<std::pair<char, double>>(NB_BEST_CHARS, {DEFAULT_LETTER, 0}))
{

    // Generate the substrings of the text
    // The number of substrings generated depend on the size of the key
    for (long unsigned int i = 0; i < cipher.size(); i++)
        subSequences[i % keySize].first += cipher[i];

    // Calculate the IC value of each substring
    for (int i = 0; i < kSize; i++)
    {
        subSequences[i].second = calculateIC(subSequences[i].first);
        averageIc += subSequences[i].second;
    }

    // returns the mean of all substrings IC
    averageIc /= (double)kSize;
}

/********************************************/
/* Method to encode text using the Caesar   */
/* cipher with a specified offset value.    */
/********************************************/
std::string AnalysisKeySize::encodeCaesar(const std::string &text, int caesarValue)
{

    std::string encoded = text;
    for (long unsigned int i = 0; i < encoded.size(); i++)
        encoded[i] = ((encoded[i] - 'A' + caesarValue) % 26) + 'A';

    return encoded;
}

/********************************************/
/* Method to decode text encoded with the   */
/* Caesar cipher using a specified offset   */
/* value.                                   */
/********************************************/
std::string AnalysisKeySize::decodeCaesar(const std::string &text, int caesarValue)
{

    std::string encoded = text;
    int tmp;

    for (long unsigned int i = 0; i < encoded.size(); i++)
    {
        tmp = (encoded[i] - 'A' - caesarValue) % 26;
        encoded[i] = (tmp < 0) ? 'Z' + tmp + 1 : tmp + 'A';
    }

    return encoded;
}

/****************************************************************/
/* Calculate the chiSquared value of a given string in a        */
/* specific language                                            */
/****************************************************************/
double AnalysisKeySize::chiSquaredResult(const std::string &text, const long unsigned int &textSize, const std::string &language)
{
    double letterApparition;
    double expectedApparition;
    double sum = 0;

    for (char letter = 'A'; letter <= 'Z'; letter++)
    {
        // For all letters of the alphabet we calculate its number of appearance in the string to analyse
        letterApparition = (double)getCount(text, letter);
        // Then we calculate the expected number of this letter in the string with its frequency in the language
        expectedApparition = (((languages.at(language)).first).at(letter) / 100) * textSize;
        // We apply the chiSquared formula
        sum += (pow((letterApparition - expectedApparition), 2)) / expectedApparition;
    }

    return sum;
}

/********************************************/
/* Calculate the most probable key used to  */
/* encrypt the original text with the       */
/* Vigenere algorithm                       */
/********************************************/
void AnalysisKeySize::getKeys(std::string language)
{

    double currentChiSquared;
    std::string caesarDecoded;
    long unsigned int subsequenceSize;

    // We calculate each character of the key one by one
    for (int i = 1; i <= keySize; i++)
    {
        subsequenceSize = subSequences[i - 1].first.size();

        // We calculate each of the 26 letters that could be used to encrypt the substring
        for (int caesar = 0; caesar < 26; caesar++)
        {

            // For this letter we decode the message with the reverse algorithm of caesar
            caesarDecoded = decodeCaesar(subSequences[i - 1].first, caesar);
            // With this decoded string we can now get its chiSquared value
            currentChiSquared = chiSquaredResult(caesarDecoded, subsequenceSize, language);

            for (int j = 0; j < NB_BEST_CHARS; j++)
            {
                // The more the chiSquared value is close to zero the closest it is to its original language statistically
                if ((bestCharactersForKeys[i - 1][j].first == DEFAULT_LETTER) || (currentChiSquared <= bestCharactersForKeys[i - 1][j].second))
                {
                    for (int k = NB_BEST_CHARS -1; k > j; k--)
                    {
                        bestCharactersForKeys[i - 1][k] = bestCharactersForKeys[i - 1][k - 1];
                    }

                    bestCharactersForKeys[i - 1][j] = {(char)(caesar + 'A'), currentChiSquared};
                    break;
                }
            }
        }
    }
    // After finding the best characters for each key position, calculate the keys and decodes
    calculateKeysAndDecodes();
}

/********************************************/
/* Method to count the occurrences of a     */
/* specific character in a given text.      */
/********************************************/
double AnalysisKeySize::getCount(std::string text, char c)
{
    double count = 0;
    for (auto letter : text)
        if (letter == c)
            count++;
    return count;
}


/********************************************/
/* Recursive method to generate all        */
/* possible combinations of characters     */
/* from a set of possibilities.            */
/********************************************/
void generateCombinations(
    const std::vector<std::vector<std::pair<char, double>>> &possibilities,
    std::string currentCombination,
    long unsigned int currentPosition,
    std::vector<std::string> &allCombinations)
{
    if (currentPosition == possibilities.size())
    {
        // We reached the end of the string we have to add the new combination
        allCombinations.push_back(currentCombination);
        return;
    }

    for (const std::pair<char, double> &option : possibilities[currentPosition])
    {
        // Add the character from this column to the current string
        std::string newCombination = currentCombination + option.first;

        // Recursively call for the next column
        generateCombinations(possibilities, newCombination, currentPosition + 1, allCombinations);
    }
}


/********************************************/
/* Method to decrypt a Vigenere cipher text */
/* using the provided key.                  */
/********************************************/
std::string decryptVigenere(const std::string &text, const std::string &key)
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
        d = d < 0 ? d + 26 : d;

        // Reconvert into ASCII base
        char decipher_letter = d + 'A';

        // Adding letter to the de decipher text
        out += decipher_letter;

        // Taking the next letter of the key
        (++indice_key) %= key.length();
    }

    return out;
}


/********************************************/
/* Method to calculate possible keys and    */
/* their corresponding decoded texts for a  */
/* given Vigenere key size, based on the    */
/* best characters for each key position.   */
/********************************************/
void AnalysisKeySize::calculateKeysAndDecodes()
{
    double ic = 0.0;
    std::string decoded = "";
    std::vector<std::string> allCombinations; // Vector to store all possible key combinations
    generateCombinations(bestCharactersForKeys, "", 0, allCombinations);

    // Display all possible combinations
    for (const std::string &possibleKey : allCombinations)
    {

        decoded = decryptVigenere(encoded, possibleKey);
        ic = calculateIC(decoded);

        // Compare the IC value with the current best IC values
        for (int i = 0; i < NB_BEST_KEYS_PER_KEYSIZE; i++)
        {
            // The more the chiSquared value is close to zero the closest it is to its original language statistically
            if ((keysAndDecoded[i].second.first == DEFAULT_STRING) || (ic <= keysAndDecoded[i].first))
            {
                // moove existing best key-decode pairs to make space for the new one
                for (int k = NB_BEST_KEYS_PER_KEYSIZE -1; k > i; k--)
                {
                    keysAndDecoded[k] = keysAndDecoded[k - 1];
                }

                keysAndDecoded[i] = {ic, {possibleKey, decoded}};
                break;
            }
        }
    }
}

/********************************************/
/* Method to calculate the Index of         */
/* Coincidence (IC) for a given text.       */
/********************************************/
double AnalysisKeySize::calculateIC(std::string text)
{
    double IC = 0.0;
    double frequencies[26];

    // We take the number of occurences for each letter of the alphabet and put it in an array
    for (auto letter = 'A'; letter <= 'Z'; letter++)
        frequencies[letter - 'A'] = getCount(text, letter);

    // Calculate the IC of the text
    for (double f : frequencies)
        IC += f * (f - 1) / (text.size() * (text.size() - 1));

    return IC;
}