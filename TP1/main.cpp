#include <iostream>



int div1(int n);
int div2(int n, int i);
int mult(int n);

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