#include <iostream>



int div1(int n);
int div2(int n, int i);
int mult(int n);
int mult(int n, int k);
unsigned int deplacementBit(unsigned int n, unsigned k);
unsigned int decremente(unsigned int i);

int main(){


    // 1.
    std::cout << "size of:" << "\n";
    std::cout << "int \t\t:" << sizeof(int) <<"\n";
    std::cout << "unsigned int \t:" << sizeof(unsigned int) <<"\n";
    std::cout << "short int \t:" << sizeof(short int) <<"\n";
    std::cout << "float \t\t:" <<  sizeof(float) <<"\n";
    std::cout << "double \t\t:" << sizeof(double) <<"\n";

    // 2.
    int val1 = 435435,
        val2 = 324436493;
    
    std::cout<< "au départ:\n";
    std::cout<<"val1: "<< val1 << "\t val2: " << val2 << std::endl;

    // Permutation de valeur
    val1 += val2;
    val2 = val1 -val2;
    val1 -= val2;

    std::cout<< "ensuite:\n";
    std::cout<<"val1: "<< val1 << "\t val2: " << val2 << std::endl;

    // 3.

    std::cout << "\n\nQuestion 3\n" << "Division de 2 par 2: " << div1(2);
    std::cout << "\n\nQuestion 4\n" << "Division de 8 par 2²: " << div2(8, 2);
    std::cout << "\n\nQuestion 5\n" << "Multiplication de 8 par 2: " << mult(8);
    std::cout << "\n\nQuestion 5-2\n" << "Multiplication de 8 par 32: " << mult(8, 32);

    // 6.
    std::cout << "\n\nQuestion 6\n" << "test: " << decremente(10);

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

void incremente(unsigned int &i)
{
    if(i & 1)
    {
        // le dernier bit est un 1
        i >> 1;
        i << 1; // le dernier bit est devenu un 0
        i << 1; // i a été incrémenté de 1
    }
    else{
        i = i | 1;
    }
}

unsigned int deplacementBit(unsigned int n, unsigned int k)
{
    // n: vecteur booléen
    // k: décalage à effectuer k € [0; 31]

    // On récupere les k plus petits bits + decalage à droite (>>)
    unsigned int    dernier_bit = 0,
                    res = 0,
                    max = 1 << 32;
    while(k != 0){
        dernier_bit = 1 & n;
        n >> 1;
        res = res >> 1;
        res = (max & (dernier_bit<<32)) | res;
    }

    // On decale ces bits de 32 - k vers la gauche (<<)
    // On fait un | car normalement le premiers sont devenus des 0

}