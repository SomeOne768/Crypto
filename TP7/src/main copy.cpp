//
//  TP7_Shamir's Secret Sharing Scheme
//

#include <stdio.h>
#include <iostream>
#include <gmp.h>
#include <vector>
#include <time.h>

#define BITSTRENGTH 14 /* size of prime number (p) in bits */
#define DEBUG true
#define MAXRAND 100000000000

void evaluateYi(mpz_t S, mpz_t Y[], mpz_t coeffs[], int i)
{
    // evaluate the yi
    mpz_t yi;
    mpz_init(yi);
    mpz_set_str(yi, "0", 2);
    mpz_add(yi, yi, S);

    for (int j = 1; j < k; j++)
    {
        // yi += aiX^j
        mpz_t X;
        mpz_init(X);
        mpz_t Y;
        mpz_init(Y);
        mpz_set_ui(Y,i);
        // mpz_set_ui(Y, x^j);

        mpz_pow_ui(X, Y, j);
        mpz_mul(X, X, coeffs[j]);
        mpz_add(yi, yi, X);
        mpz_mod(yi, yi, p);
        mpz_clear(X);
        mpz_clear(Y);
    }

    mpz_init(Y[x - 1]);
    mpz_set(Y[x - 1], yi);
    mpz_clear(yi);
}
    


/* Main subroutine */
int main()
{
    srand(time(NULL));
    /* Declare variables */
    int n = 4; // Numbers of users (max)
    int k = 3; // Threshold : minimal number of users => secret
    mpz_t coeffs[k];
    mpz_t *Y[n];
    mpz_t alphas[k];

    mpz_t p;  // Prime number
    mpz_t S;  // Secret
    mpz_t Sr; // Reconstruction of the Secret
    mpz_t temp;

    mpz_t neutre;

    mpz_init(neutre);
    mpz_set_str(neutre, "0", 10);

    /* This function creates the shares computation. The basic algorithm is...
     *
     *  1. Initialize Prime Number : we work into Z/pZ
     *  2. Initialize Secret Number : S
     *  3. Compute a random polynom of order k-1
     *  4. Shares computation for each users (xi, yi) for i in [1,n]
     *  5. Reconstruct the secret with k users or more
     *
     */

    /*
     *  Step 1: Initialize Prime Number : we work into Z/pZ
     */

    // Inititialisation du nombre aléatoire et de la seed
    mpz_init(p);
    gmp_randstate_t state;
    gmp_randinit_default(state);

    int r = rand() % MAXRAND + 1;
    std::cout << r << "\n";
    gmp_randseed_ui(state, r);
    std::cout << "\n\n\n\n\n\n\n";

    /************************* generation de p ***********************************/
    // Génération d'un nombre aléatoire < a 2¹⁰⁰
    mpz_urandomb(p, state, 100);

    // Récupération du 1er nombre premier plus grand que p
    mpz_nextprime(p, p);

    if (DEBUG)
    {
        char p_str[1000];
        mpz_get_str(p_str, 10, p);
        std::cout << "Random Prime 'p' = " << p_str << std::endl;
    }

    /*
     *  Step 2: Initialize Secret Number
     */
    /************************* generation de key modulus p so S < P ***********************************/

    mpz_init(S);

    // Generate random key
    mpz_urandomb(S, state, 100);
    // Ensure key is inferior to p
    mpz_mod(S, S, p);

    if (DEBUG)
    {
        char S_str[1000];
        mpz_get_str(S_str, 10, S);
        std::cout << "Secret number 'S' = " << S_str << std::endl;
    }

    /*
     *  Step 3: Initialize Coefficient of polynom
     */

    mpz_init(coeffs[0]);
    mpz_add(coeffs[0], S, neutre);

    for (int i = 1; i < k; i++)
    {
        mpz_init(coeffs[i]);

        // Generate random coeff
        mpz_urandomb(coeffs[i], state, 100);
        // Ensure coeff is inferior to p
        mpz_mod(coeffs[i], coeffs[i], p);
    }

    // evaluate the yi
    for (int x = 1; x <= n; x++)
    {
        // evaluate polynome
        // yi += a0 = S
        mpz_t yi;
        mpz_init(yi);
        mpz_set_str(yi, "0", 2);
        mpz_add(yi, yi, S);

        for (int j = 1; j < k; j++)
        {
            // yi += aiX^j
            mpz_t X;
            mpz_init(X);
            mpz_t Y;
            mpz_init(Y);
            mpz_set_ui(Y, x);
            // mpz_set_ui(Y, x^j);

            mpz_pow_ui(X, Y, j);
            mpz_mul(X, X, coeffs[j]);
            mpz_add(yi, yi, X);
            mpz_mod(yi, yi, p);
            mpz_clear(X);
            mpz_clear(Y);
        }

        mpz_init(Y[x - 1]);
        mpz_set(Y[x - 1], yi);
        mpz_clear(yi);
    }

    // TODO: Delete this part and compute the coeffiecients randomly ( warning: inside Z/pZ )

    if (DEBUG)
    {
        std::cout << "Polynom 'P(X)' = ";
        for (int i = 0; i < k; i++)
        {
            char a1_str[1000];
            mpz_get_str(a1_str, 10, coeffs[i]);
            std::cout << a1_str << "X^" << i << " + ";
        }
        std::cout << "\n";
    }

    /*
     *  Step 4: Shares computation for each users (xi, yi)
     */

    // TODO: Delete this part and compute the shares of all users with public login

    if (DEBUG)
    {
        std::cout << "Login and share of each users : \n";
        for (int x = 1; x <= n; x++)
        {
            char x1_str[1000];
            sprintf(x1_str, "%d", x);
            char y1_str[1000];
            mpz_get_str(y1_str, 10, Y[x - 1]);

            std::cout << "( x" << x << "=" << x1_str << " ; y" << x << "=" << y1_str << " ) \n";
        }
    }

    /*
     *  Step 5: Sample for reconstruct the secret with 3 users (x1, x2, x3)
     */
    // evaluate the alphai
    for (unsigned int xi = 1; xi <= k; xi++)
    {
        mpz_t ai;
        mpz_init(ai);
        mpz_set_str(ai, "1", 10);

        for (unsigned int xj = 1; xj <= k; xj++)
        {
            if (xj != xi)
            {
                // ai *= xj / (xj - xi)

                mpz_t X;
                mpz_init(X);

                mpz_t Xi;
                mpz_init(Xi);
                mpz_set_ui(Xi, xi);
                // ai *= xj
                mpz_set_ui(X, xj);
                mpz_mul(ai, X, ai);

                // ai *= (xj - xi)^(-1)
                mpz_sub(X, X, Xi);
                mpz_invert(X, X, p); // the modular inverse
                mpz_mul(ai, ai, X);

                mpz_mod(ai, ai, p);

                mpz_clear(X);
                mpz_clear(Xi);
            }
        }

        mpz_init(alphas[xi - 1]);
        mpz_set(alphas[xi - 1], ai);
        mpz_clear(ai);
    }

    // TODO: Delete this part and automatically compute the secret with k or more shares

    // Compute Secret = sum_{i=1}^{k} alpha_i x y_i
    mpz_init(Sr);
    // mpz_init_set_str(Sr, "0", 10);

    mpz_init(temp);

    for (unsigned int i = 1; i <= k; i++)
    {
        mpz_set_str(temp, "0", 10);
        // Sr += alphas[i-1] * Y[i-1];
        mpz_mul(temp, alphas[i - 1], Y[i - 1]);
        mpz_add(Sr, Sr, temp);
    }

    mpz_mod(Sr, Sr, p);

    if (DEBUG)
    {
        char Sr_str[1000];
        mpz_get_str(Sr_str, 10, Sr);
        std::cout << "Reconstruction of the secret : S = " << Sr_str << std::endl;
    }

    /* Clean up the GMP integers */
    for (int i = 0; i < k; i++)
    {
        mpz_clear(coeffs[i]);
        mpz_clear(alphas[i]);
        mpz_clear(Y[i]);
    }
    mpz_clear(Sr);
    mpz_clear(temp);
    mpz_clear(S);
    mpz_clear(p);
    mpz_clear(neutre);
    gmp_randclear(state);
}

// Question 2: Dans un second temps, vous allez rajouter des fonctionnalités sur l’algorithme :
//  Sans changer les parts déjà données, l’algorithme devra pouvoir modifier le seuil k.:

// Réponse:
// Si l'on souhaite modifier k, il nous faut modifier la fonction / polynôme. Pour cela, nous allons
// avoir besoin de k points (anciens et nouveaux si besoin) pour le definir.
// Si nous avions n points t.q: n != ancien k et n != nouveau K; nous avons beaucoup trop de points à respecter
// Et par définition, nous ne pouvons construire un polynôme de degré nouveau K-1 passant par n points.