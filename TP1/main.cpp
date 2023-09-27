#include <iostream>

int div1(int n);
int div2(int n, int i);
unsigned int div3(unsigned int n, unsigned int i);
int mult(int n);
unsigned int mult(unsigned int n, unsigned int k);
unsigned int deplacementBit(unsigned int n, unsigned k);
unsigned int decremente(unsigned int i);
unsigned int incremente(unsigned int i);
unsigned int deplacementBit(unsigned int n, unsigned int k);
unsigned int deplacementBitV2(unsigned int n, unsigned int k);
unsigned int deplacementBitV4(unsigned int n, unsigned int k);
template <typename T>
void switchValue(T &v1, T &v2);
template <typename T>
void switchValueXor(T &v1, T &v2);

int main(){


    // 1.
    // std::cout << "size of:" << "\n";
    // std::cout << "int \t\t:" << sizeof(int) <<"\n";
    // std::cout << "unsigned int \t:" << sizeof(unsigned int) <<"\n";
    // std::cout << "short int \t:" << sizeof(short int) <<"\n";
    // std::cout << "float \t\t:" <<  sizeof(float) <<"\n";
    // std::cout << "double \t\t:" << sizeof(double) <<"\n";

    // 2.
    // int val1 = 435435,
    //     val2 = 324436493;
    
    // std::cout<< "au départ:\n";
    // std::cout<<"val1: "<< val1 << "\t val2: " << val2 << std::endl;

    // // Permutation de valeur
    // switchValueXor(val1, val2);
    // std::cout<< "ensuite:\n";
    // std::cout<<"val1: "<< val1 << "\t val2: " << val2 << std::endl;

    // // 3.

    // std::cout << "\nQuestion 3\n" << "Division de 2 par 2: " << div1(2) << "\n";
    // std::cout << "\nQuestion 3-2\n" << "Division de 8 par 2²: " << div2(8, 2) << "\n";
    // std::cout << "\nQuestion 4\n" << "reste de 7 par 2²: " << div3(7, 2) << "\n";
    // std::cout << "\nQuestion 5\n" << "Multiplication de 8 par 2: " << mult(8) << "\n";
    // std::cout << "\nQuestion 5-2\n" << "Multiplication de 8 par 32: " << mult(8, 32) << "\n";

    // // 6.
    // std::cout << "\n\nQuestion 6\n" << "test: " << deplacementBit(10, 2) << "\n";
    unsigned int val = 0x000000ff,
                 offset = 4;
    printf("\nQuestion 6\nDeplacement de 0x%x de %d bits : 0x%x\n", val, offset, deplacementBitV4(val, offset));

    // //TEST
    // unsigned int test = 0;
    // while(test < 10)
    // {
    //     std::cout<< "test: " << test << std::endl;
    //     test = incremente(test);
    // }

    std::cout<<"\n";
    return 0;
}


template <typename T>
void switchValueXor(T &v1, T &v2)
{
    v1 = v1 ^ v2;
    v2 = v1 ^ v2;
    v1 = v1 ^ v2;
}


template <typename T>
void switchValue(T &v1, T &v2)
{
    v1 += v2;
    v2 = v1 - v2;
    v1 = v1 - v2;
}


int div1(int n){
    // n: entier positif pair
    return n>>1;
}

int div2(int n, int i)
{
    // n: entier positif pair
    // i: entier 
    return n >> i;
}

unsigned int div3(unsigned int n, unsigned int i)
{
    // n: entier positif pair
    // i: entier positif
    // int reste = 0xFFFFFFFF >> (32 - i);
    // return reste & n;
    return (n << (32-i)) >> (32 -i);
}

int mult(int n)
{
    // n entier positif
    return n<<1;
}

unsigned int mult(unsigned int n, unsigned int k)
{
    // n entier positif par
    // k nombre creux

    // On va decomposer k en une somme de puissance de 2 
    // Ex: k = 6 et n = 2 => k = 0110 et n = 0010
    // On fait n * ( 4 + 2) ce qui revient à faire n * (2² + 2¹)
    // de cette manière on pourra utiliser l'opérateur >> et << pour multiplier
    unsigned int somme = 0,
                 puissance_2 = 0;
    while(k)
    {
        if(k & 1)
        {
            somme += n << puissance_2;
        }

        k >>= 1;
        puissance_2++;
    }

    return somme;
}

int find1(unsigned int n)
{

}

unsigned int incremente(unsigned int i)
{
    if(! (i & 1) )
    {
        // le dernier bit est un 0
        i = i | 1;
    }
    else{
        // il faut trouver le 1er bit à 0
        unsigned int count = 0;
        while( i&1 )
        {
            i>>1;
            if(count&1)
            {
                // count est pair
                count = count | 1;
            }
            else
            {

            }
        }
        
    }

    return i;
}

unsigned int deplacementBit(unsigned int n, unsigned int k)
{
    // n: vecteur booléen
    // k: décalage à effectuer k € [0; 31]

    // On récupere les k plus petits bits + decalage à droite (>>)
    unsigned int    dernier_bit,
                    res = 0;

    while(k != 0){
        dernier_bit = 1 & n;
        dernier_bit = dernier_bit << 31;
        n = n >> 1;
        res = res >> 1;
        res = dernier_bit | res;

        k--;
    }

    // res contient les bits supprimés de n, au bon emplacement

    // on recupère les bits restants de n
    res = res | n;

    return res;
}


unsigned int deplacementBitV2(unsigned int n, unsigned int k)
{
    // n: vecteur booléen
    // k: décalage à effectuer k € [0; 31]

    // On récupere les k plus petits bits + decalage à droite (>>)
    unsigned int mask = 0,
                 i = 0;

    
    // On crée un masque
    while(i != k){
        mask = mask<<1;
        mask++;
        i++;
        std::cout << "mask: " << mask << "\n";
    }

    // On recupère les bits
    unsigned int res = mask & n;

    // On decale
    res = res << (31-k);
    n = n >> (k); 

    std::cout << "res: " << res << "\nn: " << n << "\n";

    // On combine les différents nombre
    res = res | n;

    return res;
}


unsigned int deplacementBitV3(unsigned int n, unsigned int k)
{
    // n: vecteur booléen
    // k: décalage à effectuer k € [0; 31]

    // On récupere les k plus petits bits + decalage à droite (>>)
    unsigned int mask;

    // On crée un masque
    mask = 0xFFFFFFFF << k;
    mask = 0xFFFFFFFF ^ mask;

    // On recupère les bits
    unsigned int res = mask & n;

    // On decale
    res = res << (31-k);
    n = n >> (k); 

    std::cout << "res: " << res << "\nn: " << n << "\n";

    // On combine les différents nombre
    res = res | n;

    return res;
}

unsigned int deplacementBitV4(unsigned int n, unsigned int k)
{
    return (n << (32-k)) | (n>>k);
}