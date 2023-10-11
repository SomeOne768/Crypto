#include <algorithm>
#include <array>
#include <cctype>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

typedef array<pair<char, double>, 26> FreqArray;
const int NUMBER_OF_LETTER = 26;

class VigenereCryptanalysis {
private:
  array<double, 26> targets;
  array<double, 26> sortedTargets;

  // TO COMPLETE

public:
  VigenereCryptanalysis(const array<double, 26> &targetFreqs) {
    targets = targetFreqs;
    sortedTargets = targets;
    sort(sortedTargets.begin(), sortedTargets.end());
  }

  pair<string, string> analyze(string input) {
    string key = "ISIMA PERHAPS";
    string result = "I CAN NOT DECRYPT THIS TEXT FOR NOW :-)" + input;

    return make_pair(result, key);
  }

  map<int, string> static getSubSequences(string cipher, int keySize) {
    // Building subsequences for each letter of the key
    // To iterate we need to categorify each cypher's letter such as
    // cypher_letter_number % keySize Letter 1 will have all the 0 Letter 2 will
    // have all the 1
    // ..

    map<int, string>
        sequences; // Map: <0, subsequence 1> ; <1, subsequence 2> ...

    int i = 0;
    for (auto letter : cipher) {
      sequences[i % keySize] += letter;
      i++;
    }

    return sequences;
  }

  double static getFrequencies(string text, char c) {
    // Return the frequence of a letter
    // Ex: 'aieie" f(a) = 1/5: f(i)=f(e)=2/5
    double count = 0;
    for (auto letter : text) {
      if (letter == c)
        count++;
    }

    return (double) count / text.size();
  }

  double static calculateThePeriod(string text) {

    // We take the frequencies for each letter
    double frequencies[NUMBER_OF_LETTER];
    for (auto letter = 'A'; letter<= 'Z' ; letter++) {
      frequencies[letter - 'A'] = getFrequencies(text, letter);
    }

    // Calculate de IC
    double IC = 0;
    for (double f : frequencies) {
      IC += f * (f - 1) / (text.size() * (text.size() - 1));
    }

    return IC;
  }

  static std::vector<std::pair<int, double>> top3ICs(std::map<int, double> averageICValues) {
    // Convert the map to a vector of pairs (result vector)
    std::vector<std::pair<int, double>> resultVec(averageICValues.begin(), averageICValues.end());

    // Sort the vector in descending order based on values
    std::sort(resultVec.begin(), resultVec.end(), [](const auto &a, const auto &b) {
        return a.second > b.second;
    });

    int i = 0;
    std::vector<std::pair<int, double>> result;

    // Collect the top 3 elements 
    for (const auto& element : resultVec) {
      if (i++ > 2) break;
      result.push_back({element.first, element.second});
    }

    return result;
  }

};

double Approx(double v, int n)
{
  v = v * pow(10, n);

  return round(v) / pow(10, n);
}

std::string toUpperCase(const std::string& str) {
    std::string result = str;
    for (char& c : result) {
        c = std::toupper(c);
    }
    return result;
}


int main() {
  string input = "YOU HAVE TO COPY THE CIPHERTEXT FROM THE ATTACHED FILES OR "
                 "FROM YOUR CIPHER ALGORITHM";

  array<double, 26> english = {
      0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015,
      0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749,
      0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758,
      0.00978, 0.02360, 0.00150, 0.01974, 0.00074};

  array<double, 26> french = {
      0.0811, 0.0081, 0.0338, 0.0428, 0.1769, 0.0113, 0.0119, 0.0074, 0.0724,
      0.0018, 0.0002, 0.0599, 0.0229, 0.0768, 0.0520, 0.0292, 0.0083, 0.0643,
      0.0887, 0.0744, 0.0523, 0.0128, 0.0006, 0.0053, 0.0026, 0.0012};

  // TEST
  string test_cypher = "12121212", test_key = "HM";
  auto res = VigenereCryptanalysis::getSubSequences(test_cypher, 2);

  // Recupérer les séquences en fonction de la taille de la clé
  std::cout << "Test subsequences\n";
  std::cout << res[0] << "==1111 ? \n"
            << (res[0] == "1111" ? "Passed" : "Failed") << "\n";
  std::cout << res[1] << "==2222 ? \n"
            << (res[1] == "2222" ? "Passed" : "Failed") << "\n";

  // Calculer la periode pour chaque sequences + moyenne
  string cypher_exo2 =
      "vptnvffuntshtarptymjwzirappljmhhqvsubwlzzygvtyitarptyiougxiuydtgzhhvvmumshwkzgstfmekvmpkswdgbilvjljmglmjfqwioiivknulvvfemioiemojtywdsajtwmtcgluysdsumfbieugmvalvxkjduetukatymvkqzhvqvgvptytjwwldyeevquhlulwpkt";
  
  cypher_exo2 = toUpperCase(cypher_exo2);
  

  std::cout << "\nTest Period calcul\n";
  res = VigenereCryptanalysis::getSubSequences(cypher_exo2, 2);
  double mean_IC_2 = VigenereCryptanalysis::calculateThePeriod(res[1]) * VigenereCryptanalysis::calculateThePeriod(res[0]) / 2.0;
  std::cout << VigenereCryptanalysis::calculateThePeriod(res[0]) << "\n";
  std::cout << VigenereCryptanalysis::calculateThePeriod(res[1]) << "\n";
  std::cout << mean_IC_2 << "\n";


  // Test for the sort algorithm
  map<int, double> elt{{1, 2.2}, {2, 2.3}, {3, 2.5}, {5, 1.1}};

  auto data = VigenereCryptanalysis::top3ICs(elt);

  for (const auto& element : data) {
    std::cout << element.first << " : " << element.second << std::endl;
  }

  // VigenereCryptanalysis vc_en(english);
  // pair<string, string> output_en = vc_en.analyze(input);

  // cout << "Key: " << output_en.second << endl;
  // cout << "Text: " << output_en.first << endl;

  // VigenereCryptanalysis vc_fr(french);
  // pair<string, string> output_fr = vc_fr.analyze(input);

  // cout << "Key: " << output_fr.second << endl;
  // cout << "Text: " << output_fr.first << endl;
}
