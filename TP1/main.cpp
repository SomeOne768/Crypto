#include <iostream>

int div1(int n);
int div2(int n, int i);
int mult(int n);
int mult(int n, int k);
unsigned int deplacementBit(unsigned int n, unsigned k);
unsigned int decremente(unsigned int i);
unsigned int incremente(unsigned int i);
unsigned int deplacementBit(unsigned int n, unsigned int k);
unsigned int deplacementBitV2(unsigned int n, unsigned int k);
unsigned int deplacementBitV4(unsigned int n, unsigned int k);

int main(){


    // 1.
    // std::cout << "size of:" << "\n";
    // std::cout << "int \t\t:" << sizeof(int) <<"\n";
    // std::cout << "unsigned int \t:" << sizeof(unsigned int) <<"\n";
    // std::cout << "short int \t:" << sizeof(short int) <<"\n";
    // std::cout << "float \t\t:" <<  sizeof(float) <<"\n";
    // std::cout << "double \t\t:" << sizeof(double) <<"\n";

    // // 2.
    // int val1 = 435435,
    //     val2 = 324436493;
    
    // std::cout<< "au départ:\n";
    // std::cout<<"val1: "<< val1 << "\t val2: " << val2 << std::endl;

    // // Permutation de valeur
    // val1 += val2;
    // val2 = val1 -val2;
    // val1 -= val2;

    // std::cout<< "ensuite:\n";
    // std::cout<<"val1: "<< val1 << "\t val2: " << val2 << std::endl;

    // // 3.

    // std::cout << "\n\nQuestion 3\n" << "Division de 2 par 2: " << div1(2);
    // std::cout << "\n\nQuestion 4\n" << "Division de 8 par 2²: " << div2(8, 2);
    // std::cout << "\n\nQuestion 5\n" << "Multiplication de 8 par 2: " << mult(8);
    // std::cout << "\n\nQuestion 5-2\n" << "Multiplication de 8 par 32: " << mult(8, 32);

    // // 6.
    // std::cout << "\n\nQuestion 6\n" << "test: " << deplacementBit(10, 2) << "\n";

    printf("%x %x\n", 1, deplacementBitV4(0x1, 5));

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

int mult(int n)
{
    // n entier positif
    return n<<1;
}

int mult(int n, int k)
{
    // n entier positif par
    // k nombre creux
    while(!(k & 1))
    {
        // n est pair
        k = div1(k);
        n = mult(n);
    }

    return n;
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
    return (n << (31-k)) | (n>>k);
}