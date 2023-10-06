#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <array>

using namespace std;
 
typedef array<pair<char, double>, 26> FreqArray;

int maxKeySize = 20;
int alphabet_number = 26;

// Define the English letter frequencies
struct LetterFrequency {
    char letter;
    double frequency;
};

LetterFrequency englishFrequencies[] = {
    {'E', 11.53},
    {'T', 9.75},
    {'A', 8.46},
    {'O', 7.60},
    {'I', 7.26},
    {'N', 7.09},
    {'S', 6.54},
    {'H', 6.09},
    {'R', 5.99},
    {'D', 4.25},
    {'L', 4.03},
    {'C', 2.78},
    {'U', 2.76},
    {'M', 2.41},
    {'W', 2.36},
    {'F', 2.23},
    {'G', 2.02},
    {'Y', 1.97},
    {'P', 1.93},
    {'B', 1.49},
    {'V', 0.98},
    {'K', 0.77},
    {'J', 0.15},
    {'X', 0.15},
    {'Q', 0.10},
    {'Z', 0.07}
};

map<int, string> getSubSequences(string cipher, int seq_number)
{
  map<int, string> sequences;
  int size = cipher.length(), j=0;
  for (int i=0; i<size; i++)
  {
    sequences[j%seq_number] += cipher[i];
    j++;
  }
  return sequences;
}

double calculateThePeriod(string text)  
{
  double indice = 0;
  int n = text.length(), ni=0;
  for (char i='A'; i<='Z'; i++)
  {
    if (text.find(i) != std::string::npos) 
    {       
      ni = count(text.begin(), text.end(), i);
      indice += (ni*(ni-1))/static_cast<double>(n*(n-1));
    }
  }
  return indice;
}

std::string toUpperCase(const std::string& str) {
    std::string result = str;
    for (char& c : result) {
        c = std::toupper(c);
    }
    return result;
}

map<int, double> findPeriodForSingleSequence(map<int, string> sequences)
{
  map<int, double> result;
  for (int i; i<sequences.size(); i++)
  {
    result[i] = calculateThePeriod(sequences[i]);
  }
  return result;
}

double averageIC(map<int, double> ics)
{
  double average = 0;
  for (int i=0; i<ics.size(); i++)
  {
    average += ics[i];
  }
  average /= (ics.size()-1);
  return average;
}

// The final key may be one of the highest average values 
// SO here we will the 5 highest values

vector<pair<int, pair<double, map<int, string>>>> getKeySizes(string cipher, int possibleKeys) 
{
  map<int, pair<double, map<int, string>>> result;
  for (int keySize = 2; keySize < maxKeySize; keySize++)
  {
    // Here we divide the sequence (cipher) in keySize-1 subSequences
    map<int, string> sequences = getSubSequences(cipher, keySize);

    // Here we collect the IC value for each single sequence 
    map<int, double> periods = findPeriodForSingleSequence(sequences);

    // And then here we collect the average value of the sequence (cipher)
    double average = averageIC(periods);

    // We associate each keySize to its average IC value for the cipher
    result[keySize] = pair<double, map<int, string>>(average, sequences);
  }

  // Create a vector to store pairs of keys and values
  vector<pair<int, pair<double, map<int, string>>>> pairs(result.begin(), result.end());

  // Sort the vector in descending order based on values
  sort(pairs.begin(), pairs.end(), [](const auto &a, const auto &b) {
      return a.second.first > b.second.first;
  });

  // Collect the 5 highest values
  int count = 0;
  vector<pair<int, pair<double, map<int, string>>>> top5Pairs;
  for (const auto &pair : pairs) {
      if (count >= 5) {
          break;
      }
      top5Pairs.push_back(pair);
      count++;
  }

  return top5Pairs;
}

// Then we should seek the key value

double chi_square(string cipher) 
{
  double chiSquare = 0;
  int size = sizeof(englishFrequencies) / sizeof(englishFrequencies[0]);
  for (char i = 'A'; i < '['; i++) {
    // Find the corresponding English letter frequency
    double Eq = 0; // Initialize Eq to zero

    // Search for the English letter 'i' in the array and get its frequency
    for (int j = 0; j < size; j++) {
      if (englishFrequencies[j].letter == i) {
        Eq = englishFrequencies[j].frequency;
        break; // Stop searching once found
      }
    }

    // Calculate the observed frequency (Cq) in the cipher
    int Cq = std::count(cipher.begin(), cipher.end(), i);

    // Calculate the chi-square value for this letter
    chiSquare += ((Cq - Eq) * (Cq - Eq)) / Eq;
  }

  return chiSquare;
}

string caesarEncrypt(string cipher, int step)
{
  string output;
  unsigned int size = cipher.length(); 
  for (unsigned int i=0; i<size; i++) 
  {
    output +=  static_cast<char>((cipher[i] - 'A' + step) % 26 + 'A');
  }
  return output;
}

// <keySize, pair<averageIc, map<keySize, subCipher>>> In input we take this

void findTheKey(vector<pair<int, pair<double, map<int, string>>>> sequenceData)
{
  const int alphabet_number = 26; 

  for (const auto& value : sequenceData)
  {
    int key = value.first;
    map<int, string> password;
    double average = value.second.first;

    for (const auto& result : value.second.second)
    {
      map<int, double> key_chisquare;

      for (int i = 0; i < alphabet_number; i++)
      {
        string ceasar = caesarEncrypt(result.second, i);
        double chiSquare = chi_square(ceasar);
        key_chisquare[i] = chiSquare;
      }

      // Sort the chi-square values to find the lowest ones
      vector<pair<int, double>> sorted_chisquare(key_chisquare.begin(), key_chisquare.end());
      sort(sorted_chisquare.begin(), sorted_chisquare.end(), [](const auto &a, const auto &b) {
        return a.second < b.second;
      });

      int i = 0;

      for (const auto& [cle, valeur] : sorted_chisquare)
      {
        password[i] += static_cast<char>('A' + cle);
        if (i >= 2) break; // Collect the 3 lowest chi-square keys
        i++;
      }
    }

    cout << "The possible password for keylength " << key << " with average " << average << ":\n";

    for (int i = 0; i < 3; i++) // Print the top 3 passwords
    {
      cout << "Password " << i + 1 << ": " << password[i] << endl;
    }
  }
}
 
class VigenereCryptanalysis
{
private:
  array<double, 26> targets;
  array<double, 26> sortedTargets;

  // TO COMPLETE
 
public:
  VigenereCryptanalysis(const array<double, 26>& targetFreqs) 
  {
    targets = targetFreqs;
    sortedTargets = targets;
    sort(sortedTargets.begin(), sortedTargets.end());
  }
 
  pair<string, string> analyze(string input) 
  {
    string key = "ISIMA PERHAPS";
    string result = "I CAN NOT DECRYPT THIS TEXT FOR NOW :-)" + input;
 
    return make_pair(result, key);
  }
};
 
int main() 
{
  string input = "YOU HAVE TO COPY THE CIPHERTEXT FROM THE ATTACHED FILES OR FROM YOUR CIPHER ALGORITHM";
 
  array<double, 26> english = {
    0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228,
    0.02015, 0.06094, 0.06966, 0.00153, 0.00772, 0.04025,
    0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987,
    0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150,
    0.01974, 0.00074};

  array<double, 26> french = {
    0.0811,  0.0081,  0.0338,  0.0428,  0.1769,  0.0113,
    0.0119,  0.0074,  0.0724,  0.0018,  0.0002,  0.0599, 
    0.0229,  0.0768,  0.0520,  0.0292,  0.0083,  0.0643,
    0.0887,  0.0744,  0.0523,  0.0128,  0.0006,  0.0053,
    0.0026,  0.0012};	

  string cipher = """gmyxzoocxziancxktanmyolupjrztgxwshctzluibuicyzwxyqtvqxzukibkotuxkagbknmimmzzyajvjzampqyzloinoiqknaumbknknvkaiakgwtnilvvzvqydmvjcximrvzkilxzqtomrgqmdjrzyazvzmmyjgkoaknkuiaivknvvy""";
  string cipher_U = toUpperCase(cipher);
  int possibleKeys = 15;
  vector<pair<int, pair<double, map<int, string>>>> data = getKeySizes(cipher_U, possibleKeys);

  findTheKey(data);

  // for (const auto& lines : data) {
  //     std::cout << "First: " << lines.first << std::endl;
  //     const auto& nestedPair = lines.second;

  //     std::cout << "Second (double): " << nestedPair.first << std::endl;

  //     const auto& innerMap = nestedPair.second;

  //     for (const auto& entry : innerMap) {
  //         std::cout << "Key: " << entry.first << ", Value: " << entry.second << std::endl;
  //     }
  // }
  // map<int, string> sequences = getSubSequences(cipher_U, 15);
  // for (const auto& data : sequences) {
  //   cout << data.first << " : " << data.second << endl;
  // }
  // map<int, double> periods = findPeriodForSingleSequence(sequences);

  // for (const auto& data : periods) {
  //   cout << data.first << " : " << data.second << endl;
  // }
  // double average = averageIC(periods);
  
  // cout << average << endl;

  // VigenereCryptanalysis vc_en(english);
  // pair<string, string> output_en = vc_en.analyze(input);
 
  // cout << "Key: "  << output_en.second << endl;
  // cout << "Text: " << output_en.first << endl;

  // VigenereCryptanalysis vc_fr(french);
  // pair<string, string> output_fr = vc_fr.analyze(input);
 
  // cout << "Key: "  << output_fr.second << endl;
  // cout << "Text: " << output_fr.first << endl;

}
