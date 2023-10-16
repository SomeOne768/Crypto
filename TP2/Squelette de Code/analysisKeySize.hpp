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
	}
};

const int NUMBER_OF_LETTER = 26;

class AnalysisKeySize {

	public :

		int keySize;
		double averageIc; // Average IC of all the IC values of the substrings

		// Each susbstring is represented by a pair of string and double
    	// Where the string is the substring itself and the double is its IC value
		std::vector<std::pair<std::string, double>> subSequences;

		AnalysisKeySize(const int, const std::string &);
		double calculateIC(std::string);
		double getCount(std::string, char);
		std::string encodeCaesar(const std::string &, int);
        std::string decodeCaesar(const std::string &, int);
		double chiSquaredResult(const std::string &, const long unsigned int &, const std::string &);
		const std::string getKey(std::string);
		
};

#endif