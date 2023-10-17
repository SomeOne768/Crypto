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
	int keySizeMax = 16;
	string language = "eng";

	vector<string> textsEncoded { 
		"zbpuevpuqsdlzgllksousvpasfpddggaqwptdgptzweemqzrdjtddefekeferdprrcyndgluaowcnbptzzzrbvpssfpashpncotemhaeqrferdlrlwwertlussfikgoeuswotfdgqsyasrlnrzppdhtticfrciwurhcezrpmhtpuwiyenamrdbzyzwelzucamrptzqseqcfgdrfrhrpatsepzgfnaffisbpvblisrplzgnemswaqoxpdseehbeeksdptdttqsdddgxurwnidbdddplncsd", 
		"gmyxzoocxziancxktanmyolupjrztgxwshctzluibuicyzwxyqtvqxzukibkotuxkagbknmimmzzyajvjzampqyzloinoiqknaumbknknvkaiakgwtnilvvzvqydmvjcximrvzkilxzqtomrgqmdjrzyazvzmmyjgkoaknkuiaivknvvy", 
		"iefomntuohenwfwsjbsfftpgsnmhzsbbizaomosiuxycqaelrwsklqzekjvwsivijmhuvasmvwjewlzgubzlavclhgmuhwhakookakkgmrelgeefvwjelksedtyhsgghbamiyweeljcemxsohlnzujagkshakawwdxzcmvkhuwswlqwtmlshojbsguelgsumlijsmlbsixuhsdbysdaolfatxzofstszwryhwjenuhgukwzmshbagigzzgnzhzsbtzhalelosmlasjdttqzeswwwrklfguzl",
		"MOMUDEKAPVTQEFMOEVHPAJMIICDCTIFGYAGJSPXYALUYMNSMYHVUXJELEPXJFXGCMJHKDZRYICUHYPUSPGIGMOIYHFWHTCQKMLRDITLXZLJFVQGHOLWCUHLOMDSOEKTALUVYLNZRFGBXPHVGALWQISFGRPHJOOFWGUBYILAPLALCAFAAMKLGCETDWVOELJIKGJBXPHVGALWQCSNWBUBYHCUHKOCEXJEYKBQKVYKIIEHGRLGHXEOLWAWFOJILOVVRHPKDWIHKNATUHNVRYAQDIVHXFHRZVQWMWVLGSHNNLVZSJLAKIFHXUFXJLXMTBLQVRXXHRFZXGVLRAJIEXPRVOSMNPKEPDTLPRWMJAZPKLQUZAALGZXGVLKLGJTUIITDSUREZXJERXZSHMPSTMTEOEPAPJHSMFNBYVQUZAALGAYDNMPAQOWTUHDBVTSMUEUIMVHQGVRWAEFSPEMPVEPKXZYWLKJAGWALTVYYOBYIXOKIHPDSEVLEVRVSGBJOGYWFHKBLGLXYAMVKISKIEHYIMAPXUOISKPVAGNMZHPWTTZPVXFCCDTUHJHWLAPFYULTBUXJLNSIJVVYOVDJSOLXGTGRVOSFRIICTMKOJFCQFKTINQBWVHGTENLHHOGCSPSFPVGJOKMSIFPRZPAASATPTZFTPPDPORRFTAXZPKALQAWMIUDBWNCTLEFKOZQDLXBUXJLASIMRPNMBFZCYLVWAPVFQRHZVZGZEFKBYIOOFXYEVOWGBBXVCBXBAWGLQKCMICRRXMACUOIKHQUAJEGLOIJHHXPVZWJEWBAFWAMLZZRXJEKAHVFASMULVVUTTGK"	
	};

	
		for (long unsigned int i = 0; i < textsEncoded.size(); i++){

			textsEncoded[i] = toUpperCase(textsEncoded[i]);

			std::cout << "\n##############################################################################" << std::endl; 
			std::cout << "############################# ENCODED TEXT ###################################" << std::endl; 
			std::cout << "##############################################################################\n\n" << std::endl; 
			std::cout << textsEncoded[i] << std::endl << std::endl; 

			for (auto language : languages)
    		{

				std::cout << "\n##############################################################################" << std::endl; 
				std::cout << "#                           Language " << language.first << "                                     #" << std::endl; 
				std::cout << "##############################################################################" << std::endl; 

				VigenereCryptanalysis(textsEncoded[i], language.first, keySizeMax);

		};
	}
}
