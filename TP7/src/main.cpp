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
#define MAXN 50


/**
 * @brief evaluate a new shares of the secret
 * 
 * @param coeffs the coefficient of our current polynome
 * @param Y array where shares are saved
 * @param S Secret
 * @param p prime modulus
 * @param x numero of the shares to be evaluate (must be croissant)
 * @param k Threshold, the number of required shares to find the secret
*/
void evaluateYi(mpz_t coeffs[], mpz_t Y[], mpz_t S, mpz_t p, int x, int k)
{
    // evaluate the yi = a0 + a1X + a2X² ... 
    mpz_t yi;
    mpz_init(yi);

    // a0 = S
    mpz_set_str(yi, "0", 2);
    mpz_add(yi, yi, S);

    // In our case xi = i
    for (int j = 1; j < k; j++)
    {
        // yi += aiX^j
        mpz_t X;
        mpz_init(X);
        mpz_t Y;
        mpz_init(Y);

        // Y = x_i
        mpz_set_ui(Y, x);

        // X = x_i^j
        mpz_pow_ui(X, Y, j);

        // X = a_i * x_i^j
        mpz_mul(X, X, coeffs[j]);

        // yi += a_i * x_i^j
        mpz_add(yi, yi, X);
        mpz_mod(yi, yi, p);

        mpz_clear(X);
        mpz_clear(Y);
    }

    // inserting new value
    mpz_init(Y[x - 1]);
    mpz_set(Y[x - 1], yi);
    mpz_clear(yi);
}

void displayShares(mpz_t Y[], int n)
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

/* Main subroutine */
int main()
{
    srand(time(NULL));
    /* Declare variables */
    int n = 4; // Numbers of users (max)
    int k = 3; // Threshold : minimal number of users => secret
    
    mpz_t coeffs[k]; // represent the value of the ai (coefficients of the polynome)
    mpz_t Y[MAXN]; // represent the value of the yi
    mpz_t alphas[k]; // represent the value of alphas considering lagrange polynome (alpha_i = Li (0))

    mpz_t p;  // Prime number
    mpz_t S;  // Secret
    mpz_t Sr; // Reconstruction of the Secret
    mpz_t temp;

    mpz_t neutre;
    mpz_init(neutre);
    mpz_set_str(neutre, "0", 10);

    // Inititialisation du nombre aléatoire et de la seed
    mpz_init(p);
    gmp_randstate_t state; 
    gmp_randinit_default(state);
    int r = rand() % MAXRAND + 1;
    std::cout << r << "\n";
    gmp_randseed_ui(state, r);

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

    // Initialize Coefficient of polynom
    mpz_init(coeffs[0]);

    // coeffs[0] = key
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
        evaluateYi(coeffs, Y, S, p, x, k);
    }


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

    // Shares computation for each users (xi, yi)
    if (DEBUG)
    {
        displayShares(Y, n);
    }


    // Sample for reconstruct the secret with k users
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
                mpz_set_ui(X, xj);

                // ai *= xj
                mpz_mul(ai, X, ai);

                // ai *= (xj - xi)^(-1) // => ai /= (xj - xi)
                mpz_sub(X, X, Xi);
                mpz_invert(X, X, p); // the modular inverse
                mpz_mul(ai, ai, X);
                mpz_mod(ai, ai, p);

                // clear
                mpz_clear(X);
                mpz_clear(Xi);
            }
        }

        // Insert values into corresponding tab
        mpz_init(alphas[xi - 1]);
        mpz_set(alphas[xi - 1], ai);
        mpz_clear(ai);
    }

    // Compute Secret = sum_{i=1}^{k} alpha_i x y_i to find the secret
    mpz_init(Sr);
    mpz_init(temp);
    for (unsigned int i = 1; i <= k; i++)
    {
        mpz_set_str(temp, "0", 10);
        // Sr += alphas[i-1] * Y[i-1];
        mpz_mul(temp, alphas[i - 1], Y[i - 1]);
        mpz_add(Sr, Sr, temp);
    }

    mpz_mod(Sr, Sr, p);

    // Display the secret
    if (DEBUG)
    {
        char Sr_str[1000];
        mpz_get_str(Sr_str, 10, Sr);
        std::cout << "Reconstruction of the secret : S = " << Sr_str << std::endl;
    }


    // Menu to do everything above and add the possiblity have more shares
    int choice;
    do
    {
        std::cout << "\nMenu:\n";
        std::cout << "1. Afficher le polynome\n";
        std::cout << "2. Augmenter le nombre de parts\n";
        std::cout << "3. Quitter\n";
        std::cout << "Entrez votre choix (1-3): ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            // Afficher le polynôme
            std::cout << "Polynome 'P(X)' = ";
            for (int i = 0; i < k; i++)
            {
                char a1_str[1000];
                mpz_get_str(a1_str, 10, coeffs[i]);
                std::cout << a1_str << "X^" << i << " + ";
            }
            std::cout << "\n";
            displayShares(Y, n);
            break;

        case 2:
            // Augmenter le nombre de parts
            std::cout << "Entrez le nombre de nouvelles parts à ajouter : ";
            int increasing;
            std::cin >> increasing;

            for (int j = 1; j <= increasing; j++)
                evaluateYi(coeffs, Y, S, p, n + j, k);

            n += increasing;

            std::cout << "Parts mises à jour après augmentation :\n";
            displayShares(Y, n);
            break;
        case 3:
            // Quitter le programme
            break;
        default:
            std::cout << "Choix invalide. Veuillez réessayer.\n";
        }
    } while (choice != 3);



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