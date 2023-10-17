#ifndef ANALYSISKEYSIZE_HPP
#define ANALYSISKEYSIZE_HPP

#include <string>
#include <cmath>
#include <vector>
#include <map>

// Frequences in % of a list of characters for a specific language
const std::map<std::string, std::pair<std::map<char, double>, double>> languages = 
{
	{"eng", {
		{
			{'A', 8.55}, {'B', 1.60}, {'C', 3.16}, {'D', 3.87}, {'E', 12.10}, 
			{'F', 2.18}, {'G', 2.09}, {'H', 4.96}, {'I', 7.33}, {'J', 0.22},
			{'K', 0.81}, {'L', 4.21}, {'M', 2.53}, {'N', 7.17}, {'O', 7.47},
			{'P', 2.07}, {'Q', 0.10}, {'R', 6.33}, {'S', 6.73}, {'T', 8.94},
			{'U', 2.68}, {'V', 1.06}, {'W', 1.83}, {'X', 0.19}, {'Y', 1.72}, {'Z', 0.11}
		}, 0.0667}
	},

	{"fra", {
		{
			{'A', 8.08 }, {'B', 0.96 }, {'C', 3.39}, {'D', 4.08}, {'E', 17.45}, 
			{'F', 1.12}, {'G', 1.18}, {'H', 0.93}, {'I', 7.26}, {'J', 0.30},
			{'K', 0.16}, {'L', 5.86}, {'M', 2.78}, {'N', 7.32}, {'O', 5.44},
			{'P', 2.98}, {'Q', 0.85}, {'R', 6.86}, {'S', 7.98}, {'T', 7.11},
			{'U', 5.59}, {'V', 1.29}, {'W', 0.08}, {'X', 0.43}, {'Y', 0.34}, {'Z', 0.10}
		}, 0.0778}
	}, 
	
	{"ger", {
		{
			{'A', 6.88}, {'B', 2.21}, {'C', 2.71}, {'D', 4.92 }, {'E', 15.99}, 
			{'F', 1.80}, {'G', 3.02}, {'H', 4.11}, {'I', 7.60}, {'J', 0.27},
			{'K', 1.50}, {'L', 3.72}, {'M', 2.75}, {'N', 9.59}, {'O', 2.99},
			{'P', 1.06}, {'Q', 0.04}, {'R', 7.71}, {'S', 6.41}, {'T', 6.43},
			{'U', 4.39}, {'V', 0.94}, {'W', 1.40}, {'X', 0.07}, {'Y', 0.13}, {'Z', 1.22}
		}, 1.000}
	},

	{"spa", {
		{
			{'A', 12.50}, {'B', 1.27}, {'C', 4.43}, {'D', 5.14}, {'E', 13.24}, 
			{'F', 0.79}, {'G', 1.17}, {'H', 0.81}, {'I', 6.91}, {'J', 0.45},
			{'K', 0.08}, {'L', 5.84}, {'M', 2.61}, {'N', 7.31}, {'O', 8.98},
			{'P', 2.75}, {'Q', 0.83}, {'R', 6.62}, {'S', 7.44}, {'T', 4.42},
			{'U', 4.00}, {'V', 0.98}, {'W', 0.03}, {'X', 0.19}, {'Y', 0.79}, {'Z', 0.42}
		}, 1.000}
	}, 

};

const int NB_BEST_KEYS_PER_KEYSIZE	= 5;
const int NB_BEST_CHARS		= 1;
const int NB_BEST_KEYSIZES	= 3;
const double MAX_CHISQUARED	= 9999999.9;

const char DEFAULT_LETTER		= '%';
const std::string DEFAULT_STRING= "%";

class AnalysisKeySize {

	public :

		std::string encoded;
		int keySize;
		double averageIc; // Average IC of all the IC values of the substrings

		// Each susbstring is represented by a pair of string and double
    	// Where the string is the substring itself and the double is its IC value
		std::vector<std::pair<std::string, double>> subSequences;

		std::vector<std::pair<double, std::pair<std::string, std::string>>> keysAndDecoded;

		std::vector<std::vector<std::pair<char, double>>> bestCharactersForKeys;

		AnalysisKeySize(const int, const std::string &);
		double calculateIC(std::string);
		double getCount(std::string, char);
		std::string encodeCaesar(const std::string &, int);
        std::string decodeCaesar(const std::string &, int);
		double chiSquaredResult(const std::string &, const long unsigned int &, const std::string &);
		void getKeys(std::string);
		void calculateKeysAndDecodes();
		
};

#endif