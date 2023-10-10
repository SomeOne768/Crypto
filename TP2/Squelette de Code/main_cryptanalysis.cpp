#include <algorithm>
#include <array>
#include <iostream>
#include <map>
#include <string>
#include <vector>

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
    int count = 0;
    for (auto letter : text) {
      if (letter == c)
        count++;
    }

    return count / text.size();
  }

  // @Jalil
  double static calculateThePeriod(string text) {
    
    // We take the frequencies for each letter
    double frequencies[NUMBER_OF_LETTER];
    for (int i = 0; i < NUMBER_OF_LETTER; i++)
    {
      frequencies[i] = getFrequencies(text, 'A'+i);
    }

    // Calculate de IC
    double IC = 0;
    for(double f : frequencies)
    {
      IC += f *(f-1) / (NUMBER_OF_LETTER * (NUMBER_OF_LETTER - 1) );
    }

    return IC;
  }

  // @Souleymane
  // double static calculateThePeriod(string text) {
  //   double indice = 0;
  //   int n = text.length(), ni = 0;
  //   for (char i = 'A'; i <= 'Z'; i++) {
  //     if (text.find(i) != std::string::npos) {
  //       ni = count(text.begin(), text.end(), i);
  //       indice += (ni * (ni - 1)) / static_cast<double>(n * (n - 1));
  //     }
  //   }
  //   return indice;
  // }
};

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
  std::cout << "Test Period calcul\n";
  std::cout << VigenereCryptanalysis::calculateThePeriod(res[0]) << "==0 ? \n"
            << (VigenereCryptanalysis::calculateThePeriod(res[0]) == 0 ? "Passed" : "Failed") << "\n";
  std::cout <<  VigenereCryptanalysis::calculateThePeriod(res[1]) << "==0 ? \n"
            << (VigenereCryptanalysis::calculateThePeriod(res[1]) == 0 ? "Passed" : "Failed") << "\n";
            std::cout <<  VigenereCryptanalysis::calculateThePeriod(res[1]) << "==0 ? \n"
            << (VigenereCryptanalysis::calculateThePeriod(res[1]) == 0 ? "Passed" : "Failed") << "\n";

  VigenereCryptanalysis vc_en(english);
  pair<string, string> output_en = vc_en.analyze(input);

  cout << "Key: " << output_en.second << endl;
  cout << "Text: " << output_en.first << endl;

  VigenereCryptanalysis vc_fr(french);
  pair<string, string> output_fr = vc_fr.analyze(input);

  cout << "Key: " << output_fr.second << endl;
  cout << "Text: " << output_fr.first << endl;
}
