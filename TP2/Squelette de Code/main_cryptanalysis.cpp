#include <algorithm>
#include <array>
#include <cctype>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cmath>

#include "vigenere.hpp"
#include "vigenereCryptanalysis.hpp"

using namespace std;

typedef array<pair<char, double>, 26> FreqArray;

double Approx(double v, int n)
{
	v = v * pow(10, n);

	return round(v) / pow(10, n);
}

std::string toUpperCase(const std::string &str)
{
	std::string result = str;
	for (char &c : result)
	{
		c = std::toupper(c);
	}
	return result;
}

int main()
{


	// int maxKeySize = 15;

	string input = "YOU HAVE TO COPY THE CIPHERTEXT FROM THE ATTACHED FILES OR "
					"FROM YOUR CIPHER ALGORITHM";

	// array<double, 26> english = {
	//     0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015,
	//     0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749,
	//     0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758,
	//     0.00978, 0.02360, 0.00150, 0.01974, 0.00074};

	// array<double, 26> french = {
	//     0.0811, 0.0081, 0.0338, 0.0428, 0.1769, 0.0113, 0.0119, 0.0074, 0.0724,
	//     0.0018, 0.0002, 0.0599, 0.0229, 0.0768, 0.0520, 0.0292, 0.0083, 0.0643,
	//     0.0887, 0.0744, 0.0523, 0.0128, 0.0006, 0.0053, 0.0026, 0.0012};


	// vector<double> english = {
	// 	8.55, 1.60, 3.16, 3.87, 12.10, 2.18, 2.09, 4.96, 7.33, 0.22, 0.81, 4.21, 2.53, 
	// 	7.17, 7.47, 2.07, 0.10, 6.33, 6.73, 8.94, 2.68, 1.06, 1.83, 0.19, 1.72, 0.11};

	// map<char, double> english = {
	// 	{'A', 8.55}, {'B', 1.60}, {'C', 3.16}, {'D', 3.87}, {'E', 12.10}, 
	// 	{'F', 2.18}, {'G', 2.09}, {'H', 4.96}, {'I', 7.33}, {'J', 0.22},
	// 	{'K', 0.81}, {'L', 4.21}, {'M', 2.53}, {'N', 7.17}, {'O', 7.47},
	// 	{'P', 2.07}, {'Q', 0.10}, {'R', 6.33}, {'S', 6.73}, {'T', 8.94},
	// 	{'U', 2.68}, {'V', 1.06}, {'W', 1.83}, {'X', 0.19}, {'Y', 1.72}, {'Z', 0.11}
	// };


	// // Calculer la periode pour chaque sequences + moyenne
	string cypher_exo2 =
	 	"MOMUDEKAPVTQEFMOEVHPAJMIICDCTIFGYAGJSPXYALUYMNSMYHVUXJELEPXJFXGCMJHKDZRYICUHYPUSPGIGMOIYHFWHTCQKMLRDITLXZLJFVQGHOLWCUHLOMDSOEKTALUVYLNZRFGBXPHVGALWQISFGRPHJOOFWGUBYILAPLALCAFAAMKLGCETDWVOELJIKGJBXPHVGALWQCSNWBUBYHCUHKOCEXJEYKBQKVYKIIEHGRLGHXEOLWAWFOJILOVVRHPKDWIHKNATUHNVRYAQDIVHXFHRZVQWMWVLGSHNNLVZSJLAKIFHXUFXJLXMTBLQVRXXHRFZXGVLRAJIEXPRVOSMNPKEPDTLPRWMJAZPKLQUZAALGZXGVLKLGJTUIITDSUREZXJERXZSHMPSTMTEOEPAPJHSMFNBYVQUZAALGAYDNMPAQOWTUHDBVTSMUEUIMVHQGVRWAEFSPEMPVEPKXZYWLKJAGWALTVYYOBYIXOKIHPDSEVLEVRVSGBJOGYWFHKBLGLXYAMVKISKIEHYIMAPXUOISKPVAGNMZHPWTTZPVXFCCDTUHJHWLAPFYULTBUXJLNSIJVVYOVDJSOLXGTGRVOSFRIICTMKOJFCQFKTINQBWVHGTENLHHOGCSPSFPVGJOKMSIFPRZPAASATPTZFTPPDPORRFTAXZPKALQAWMIUDBWNCTLEFKOZQDLXBUXJLASIMRPNMBFZCYLVWAPVFQRHZVZGZEFKBYIOOFXYEVOWGBBXVCBXBAWGLQKCMICRRXMACUOIKHQUAJEGLOIJHHXPVZWJEWBAFWAMLZZRXJEKAHVFASMULVVUTTGK";


	string cypher_encoded = toUpperCase(cypher_exo2);
	string language = "eng";

	int keySize = 16;

	VigenereCryptanalysis analysis(cypher_encoded, language, keySize);


	// std::cout << "\nTest Period calcul\n";
	// res = VigenereCryptanalysis::getSubSequences(cypher_exo2, 2);
	// double mean_IC_2 = VigenereCryptanalysis::calculateThePeriod(res[1]) * VigenereCryptanalysis::calculateThePeriod(res[0]) / 2.0;
	// std::cout << VigenereCryptanalysis::calculateThePeriod(res[0]) << "\n";
	// std::cout << VigenereCryptanalysis::calculateThePeriod(res[1]) << "\n";
	// std::cout << mean_IC_2 << "\n";

	// vector<double> averages = VigenereCryptanalysis::getAverages(cypher_exo2, maxKeySize);

	// for (long unsigned int i = 0; i < averages.size(); i++) {
	// 	std::cout << "Value of keySize = " << i << " = " << averages.at(i) << std::endl;
	// }

	// VigenereCryptanalysis vc_en(english);
	// pair<string, string> output_en = vc_en.analyze(input);

	// cout << "Key: " << output_en.second << endl;
	// cout << "Text: " << output_en.first << endl;

	// VigenereCryptanalysis vc_fr(french);
	// pair<string, string> output_fr = vc_fr.analyze(input);

	// cout << "Key: " << output_fr.second << endl;
	// cout << "Text: " << output_fr.first << endl;
}
