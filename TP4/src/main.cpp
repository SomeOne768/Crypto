#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <algorithm>
using namespace std;

/*  Boite S et son inverse */
static const uint8_t S[16] = {0x3, 0xE, 0x1, 0xA, 0x4, 0x9, 0x5, 0x6,
                              0x8, 0xB, 0xF, 0x2, 0xD, 0xC, 0x0, 0x7};

static const uint8_t S_inv[16] = {0xE, 0x2, 0xB, 0x0, 0x4, 0x6, 0x7, 0xF,
                                  0x8, 0x5, 0x3, 0x9, 0xD, 0xC, 0x1, 0xA};

/* Cipher to cryptanalyse */
class Cipher
{
private:
    uint8_t k0;
    uint8_t k1;

    uint8_t roundFunc(uint8_t input)
    {
        // plaintext -> xor -> S - xor ->cipher
        uint8_t cypher = XOR(input, k0);
        cypher = evaluateS(cypher);
        cypher = XOR(cypher, k1);

        return cypher;
    }

    uint8_t roundFunc_inv(uint8_t input)
    {
        // cipher -> xor -> S -> xor -> plaintext
        uint8_t plain = XOR(input, k1);
        plain = evaluateSinv(plain);
        plain = XOR(plain, k0);

        return plain;
    }

public:
    std::vector<std::pair<uint8_t, uint8_t>> cipher_pair{};

    Cipher()
    {
        k0 = rand() % 16; // Create random subkey0
        k1 = rand() % 16; // Create random subkey1

        printf(" First sub-key k0 = %x\n", k0);
        printf(" Second sub-key k1 = %x\n\n", k1);
    }

    Cipher(uint8_t key0, uint8_t key1)
    {
        k0 = key0;
        k1 = key1;
    }

    uint8_t encrypt(uint8_t input)
    {
        // TODO
        uint8_t cypher = input;
        for (int i = 0; i < 16; i++)
            cypher = roundFunc(cypher);
        return cypher;
    }

    uint8_t decrypt(uint8_t input)
    {
        // TODO
        uint8_t plain = input;
        for (int i = 0; i < 16; i++)
            plain = roundFunc_inv(plain);
        return plain;
    }

    static uint8_t XOR(const uint8_t &input, const uint8_t &key)
    {
        return input ^ key;
    }

    static uint8_t evaluateS(const uint8_t &input)
    {
        return S[input];
    }

    static uint8_t evaluateSinv(const uint8_t &input)
    {
        return S_inv[input];
    }
};

class Cryptanalysis
{
private:
    // Vector to store the plaintexts and cipertexts
    // Plaintexts
    uint8_t knownP0[1000];
    uint8_t knownP1[1000];

    // Ciphertexts
    uint8_t knownC0[1000];
    uint8_t knownC1[1000];

    uint8_t goodP0, goodP1, goodC0, goodC1;

    int chardatmax;
    int chardat0[16];

public:
    uint8_t T[16][16];
    std::vector<std::pair<uint8_t, uint8_t>> bestProba;
    Cryptanalysis() { chardatmax = 0; }

    using tuple4 = std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>;
    using listTuple4 = std::vector<tuple4>; // List of quadruplet
    listTuple4 xAndXprime[16];
    listTuple4 yAndYprime[16];

    std::map<uint8_t, std::map<uint8_t, listTuple4>> linkStruct{}; // structure to access directly of the corresponding cypher and plain text

    /* Difference Distribution Table of the S-boxe */
    void findBestDiffs(void)
    {
        uint8_t i, j;
        uint8_t X, Xp, Y, Yp, DX, DY;

        for (i = 0; i < 16; ++i)
        {
            for (j = 0; j < 16; ++j)
            {
                T[i][j] = 0;
            }
        }

        printf("\n Creating XOR differential table:\n");

        /* Question 1 : compléter le code afin d'afficher la matrice T des différences */

        for (X = 0; X < 16; X++)
        {
            for (Xp = 0; Xp < 16; Xp++)
            {

                Y = Cipher::evaluateS(X);
                Yp = Cipher::evaluateS(Xp);

                DX = (X ^ Xp);
                DY = (Y ^ Yp);

                if (DX != 0)
                {
                    xAndXprime[DX].push_back(std::make_tuple(X, Xp, Y, Yp));
                    yAndYprime[DY].push_back(std::make_tuple(X, Xp, Y, Yp));
                }

                linkStruct[DX][DY].push_back(std::make_tuple(X, Xp, Y, Yp));
                T[DX][DY]++;
            }
        }

        /* Affichage des différences dans un tableau */
        for (i = 0; i < 16; ++i)
        {
            printf("[");
            for (j = 0; j < 16; ++j)
            {
                printf(" %u ", T[i][j]);
            }
            printf("]\n");
        }

        /* Identifier les différentielles apparaissant avec plus forte probabilité */
        /* Elles seront exploitées dans la suite de l'attaque */
        printf("\n Displaying most probable differentials:\n");

        // Find the best values
        uint8_t bestValue = 0;
        for (i = 0; i < 16; i++)
        {
            for (j = 0; j < 16; j++)
            {
                if (!(i == 0 && j == 0) && bestValue < T[i][j])
                {
                    bestValue = T[i][j];
                }
            }
        }
        printf("\nBest proba: %x/16\n", bestValue);
        // Take the dx, dy corresponding to this best value
        bestProba.clear();
        for (DX = 0; DX < 16; DX++)
        {
            for (DY = 0; DY < 16; DY++)
            {
                if (!(DX == 0 && DY == 0) && bestValue == T[DX][DY])
                {
                    bestProba.push_back(std::make_pair(DX, DY));
                }
            }
        }

        for (auto &elt : bestProba)
            printf("(Dx, Dy) -> (%x, %x) : %x/16\n", elt.first, elt.second, T[elt.first][elt.second]);
    }

    void genCharData(uint8_t diffIn, uint8_t diffOut)
    {
        printf("\n Generating possible intermediate values based on differential (%x --> %x):\n", diffIn, diffOut);

        if (linkStruct[diffIn][diffOut].size() == 0)
        {
            printf("\nNo value find\n");
            return;
        }

        printf("Possible values for (Dx, Dy) = (%x, %x):\n", diffIn, diffOut);
        uint8_t X, Xp, Y, Yp, DY;
        for (auto &elt : linkStruct[diffIn][diffOut])
        {
            printf("(X, Xp, Y, Yp) -> (%x, %x, %x, %x)\n",
                   get<0>(elt), get<1>(elt), get<2>(elt), get<3>(elt));
        }
    }

    void genPairs(Cipher &cipher, uint8_t diffIn, int nbPairs)
    {
        // Assuming nbPairs arguments is usefull because we looked at the array and find an interessing value (dx, dy)
        printf("\n Generating %i known pairs with input differential of %x.\n", nbPairs, diffIn);

        uint8_t X, Xp, Y, Yp, j, max = 0;
        // for (j = 0; j < 16; j++)
        // {
        //     max = (T[diffIn][j] > max) ? j : max;
        // }

        while (max < 16 && T[diffIn][max] != nbPairs)
            max++;

        if (max == 16)
        {
            printf("nbPairs invalid !\n");
            return;
        }

        // we find the index with max value

        // We now display the plain and their cypher
        for (auto &elt : linkStruct[diffIn][max])
        {
            X = get<0>(elt);
            Xp = get<1>(elt);
            Y = cipher.encrypt(X);
            Yp = cipher.encrypt(Y);
            printf("(X, Xp) -> (Y, Yp) <=> (%x, %x) -> (%x, %x)\n", X, Xp, Y, Yp);
        }
    }

    void findGoodPair(int diffOut, int nbPairs)
    {
        printf("\n Searching for good pair:\n");

        /* Question 4 : compléter le code afin de produire une paire avec la bonne
         * caractéristique en se basant sur le chiffrement */

        // chacun de ces blocs dans le système de chiffrement (qui utilise les clefs secrètes) pour obtenir C0
        // et C1. Vous venez de produire une paire choisie sur la base de votre caractéristique différentielle.
        // Si vous faites cela et que C0 ⊕C1 est égal à la différentielle de sortie de notre caractéristique
        // choisie, alors il s’agit d’une bonne paire. Une fois que vous en avez trouvé une, vous pouvez vous
        // arrêter. Conservez les autres mauvaises paires, mais mettez la bonne paire de côté pour l’étape
        // suivante. Les autres paires seront utilisées pour valider les suppositions de clefs

        // P0 -> P0 XOR diffInt = P1 -> algo = C0 et C1

        uint8_t P0 = rand() % 16, d1 = 0;
        uint8_t P1 = P0 ^ d1;

        // We are looking for a pair X, X' such as DY = diffOut ordered in function of their 'T score'

        uint8_t maxi = 0;
        for (uint8_t i = 1; i < 16; i++)
            maxi = (T[i][diffOut] > T[maxi][diffOut]) ? i : maxi;

        int min = (nbPairs < linkStruct[maxi][diffOut].size()) ? nbPairs : linkStruct[maxi][diffOut].size();
        for (int i = 0; i < min; ++i)
        {
            printf("Pair found : (X, Xp, Y, Yp) -> (%x, %x, %x, %x)\n",
                   std::get<0>(linkStruct[maxi][diffOut].at(i)),
                   std::get<1>(linkStruct[maxi][diffOut].at(i)),
                   std::get<2>(linkStruct[maxi][diffOut].at(i)),
                   std::get<3>(linkStruct[maxi][diffOut].at(i)));
        }
    }


    int testKey(int testK0, int testK1, int nbPairs)
    {

    }

    void crack(int nbPairs)
    {
        printf("\nBrute forcing reduced keyspace:\n");
    }
};

//////////////////////////////////////////////////////////////////
//                             MAIN                             //
//////////////////////////////////////////////////////////////////

int main()
{

    srand(time(NULL)); // Randomize values per run
    Cipher cipher;
    uint8_t message = rand() % 16;
    printf(" Producing a random message : %x\n", message);
    uint8_t ciphertext = cipher.encrypt(message);
    printf(" Encrypted message : %x\n", ciphertext);
    uint8_t plaintext = cipher.decrypt(ciphertext);
    printf(" Decrypted message : %x\n", plaintext);

    if (message == plaintext)
        printf(" --> Success\n");
    else
        printf(" --> Failure\n");

    int nbPairs = 6; // Define number of known pairs (note that 16 is a brut
                     // force)
    uint8_t diffIn = 1;
    uint8_t diffOut = 13;

    Cryptanalysis cryptanalysis;
    cryptanalysis.findBestDiffs();
    // Find some good differentials in the S-Boxes
    cryptanalysis.genCharData(diffIn, diffOut);
    // Find inputs that lead a certain characteristic
    cryptanalysis.genPairs(cipher, diffIn, nbPairs);
    // Generate chosen-plaintext pairs
    cryptanalysis.findGoodPair(diffOut, nbPairs);
    // // Choose a known pair that satisfies the characteristic

    // cryptanalysis.crack(nbPairs);
    // // Use charData and "good pair" in find key

    return 0;
}
