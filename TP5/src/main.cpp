//
//  TP6_RSA
//

#include <stdio.h>
#include <iostream>
#include <gmp.h>
#include <stdlib.h>   
#include <time.h>       
#define TAILLE_MAX  16
#define BASE 62
#define BITSTRENGTH 14              /* size of modulus (n) in bits */
#define PRIMESIZE (BITSTRENGTH / 2) /* size of the primes p and q  */

/* Declare global variables */

mpz_t d, e, n;
mpz_t M, c;



char genChar62()
{
    int r = rand() %3;
    char c;
    if(r == 0) // minuscule
    {
        r = rand()% 26;
        c = 'a' + r;
    }
    else if(r == 1) // majuscule
    {
        r = rand()% 26;
        c = 'A' + r;
    }
    else // chiffre
    {
        r = rand()% 10;
        c = '0' + r;
    }

    return c;
}


/* Main subroutine */
int main()
{
    /* Initialize the GMP integers */
    mpz_init(d);
    mpz_init(e);
    mpz_init(n);

    mpz_init(M);
    mpz_init(c);

    /* This function creates the keys. The basic algorithm is...
     *
     *  1. Generate two large distinct primes p and q randomly
     *  2. Calculate n = pq and x = (p-1)(q-1)
     *  3. Select a random integer e (1<e<x) such that gcd(e,x) = 1
     *  4. Calculate the unique d such that ed = 1(mod x)
     *  5. Public key pair : (e,n), Private key pair : (d,n)
     *
     */

    /*
     *  Step 1 : Get two large primes.
     */
    mpz_t p, q, min, base, r, tmp;
    gmp_randstate_t state;
    gmp_randinit_default(state);
    gmp_randseed_ui(state, 656215);

    unsigned long int exposant = 1023;
    mpz_init(p);
    mpz_init(q);
    mpz_init(min);
    mpz_init(base);
    mpz_init(r);
    mpz_init(tmp);

    mpz_init_set_str(p, "47", 0);
    mpz_init_set_str(q, "71", 0);
    mpz_init_set_str(base, "2", 0);
    char p_str[1000];
    char q_str[1000];
    mpz_get_str(p_str, 10, p);
    mpz_get_str(q_str, 10, q);

    // void mpz_urandomb (mpz t rop, gmp randstate t state, mp bitcnt t n )
    //  mpz_add
    //  mpz_pow
    //  mpz_nextprime

    // Valeur minimal de notre nombre premier
    mpz_pow_ui(min, base, exposant);

    /************************* generation de p ***********************************/
    // Génération d'un nombre aléatoire
    mpz_urandomb(r, state, 1023);
    mpz_add(tmp, r, min);

    // Génération d'un nombre premier
    mpz_nextprime(p, tmp);

    /************************* generation de q ***********************************/
    do
    {
        // Génération d'un nombre aléatoire
        mpz_urandomb(r, state, 1023);
        mpz_add(tmp, r, min);

        // Génération d'un nombre premier
        mpz_nextprime(q, tmp);

    } while (!mpz_cmp(p, q));

    mpz_get_str(p_str, 10, p);
    mpz_get_str(q_str, 10, q);
    std::cout << "Random Prime 'p' = " << p_str << std::endl;
    std::cout << "Random Prime 'q' = " << q_str << std::endl;

    /*
     *  Step 2 : Calculate n (=pq) ie the 1024 bit modulus
     *  and x (=(p-1)(q-1)).
     */
    char n_str[1000];
    mpz_t x;
    mpz_init(x);

    /* Calculate n... */
    mpz_mul(n, p, q);
    mpz_get_str(n_str, 10, n);
    std::cout << "\t n = " << n_str << std::endl;

    /* Calculate x... */
    mpz_t p_minus_1, q_minus_1;
    mpz_init(p_minus_1);
    mpz_init(q_minus_1);

    mpz_sub_ui(p_minus_1, p, (unsigned long int)1);
    mpz_sub_ui(q_minus_1, q, (unsigned long int)1);

    mpz_mul(x, p_minus_1, q_minus_1);
    char phi_str[1000];
    mpz_get_str(phi_str, 10, x);
    std::cout << "\t phi(n) = " << phi_str << std::endl;

    /*
     *  Step 3 : Get small odd integer e such that gcd(e,x) = 1.
     */
    mpz_t increment;
    mpz_init(e);
    mpz_init(increment);
    mpz_init_set_str(e, "2", 0);
    mpz_init_set_str(increment, "1", 0);
    do
    {
        mpz_add(e, e, increment);
        mpz_gcd(tmp, x, e);
    } while (mpz_even_p(e) || mpz_cmp_ui(tmp, 1) != 0);

    char e_str[1000];
    mpz_get_str(e_str, 10, e);
    std::cout << "\t e = " << e_str << std::endl;

    /*
     *  Step 4 : Calculate unique d such as ed = 1(mod x)
     */
    mpz_init(d);
    mpz_invert(d, e, x);
    char d_str[1000];
    mpz_get_str(d_str, 10, d);
    std::cout << "\t d = " << d_str << std::endl
              << std::endl;

    /*
     *  Step 5 : Print the public and private key pairs...
     */
    std::cout << "Public Keys  (e,n): ( " << e_str << " , " << n_str << " )" << std::endl;
    std::cout << "Private Keys (d,n): ( " << d_str << " , " << n_str << " )" << std::endl;
    

    /*
     *  Encrypt
     */

    mpz_t message, ciphered, deciphered;
    
    char Message[TAILLE_MAX]; 
    Message[0] = 'A' ; 
    for(int i=1; i<TAILLE_MAX; i++)
    {
        Message[i] = genChar62();
    }
    
    mpz_init(message);
    mpz_init(ciphered);
    mpz_init(deciphered);
    mpz_set_str(message, Message, BASE);

    // Encrypt
    mpz_powm(ciphered, message, e, n);
    char ciphered_str[1000];
    mpz_get_str(ciphered_str, 10, ciphered);

    // Decrypt
    mpz_powm(deciphered, ciphered, d, n);
    char deciphered_str[1000];
    mpz_get_str(deciphered_str, BASE, deciphered);

    std::cout << "\nCheck:\n";
    mpz_t check1;
    mpz_mul(check1, d, e);
    mpz_mod(check1, check1, x);
    char Check1[1000];
    mpz_get_str(Check1, 10, check1);
    std::cout << "e * d [n]=" << Check1 << "\n";

    std::cout << "Message: " << Message << std::endl;
    std::cout << "Ciphered message: " << ciphered_str << std::endl;
    std::cout << "Deciphered message: " << deciphered_str << std::endl;

    /* Clean up the GMP integers */
    mpz_clear(p_minus_1);
    mpz_clear(q_minus_1);
    mpz_clear(x);
    mpz_clear(p);
    mpz_clear(q);

    mpz_clear(d);
    mpz_clear(e);
    mpz_clear(n);

    mpz_clear(M);
    mpz_clear(c);

    mpz_clear(increment);
    mpz_clear(tmp);
    mpz_clear(r);
    mpz_clear(min);
    mpz_clear(base);
}
