#include <population.h>

/**
 * @brief Affiche la liste de population 
 * 
 * @param population 
 */
void printPopulation(Population population) {
    Individu *indiv = population.individus;
    int i = 1;
    printf("Population de taille %d.\n", population.taille);
    printf("Individus de taille %d.\n\n", population.individus->longIndiv);
    
    printf("Individu n°k\tDecode\t->\tQualité\t0b.bits..\n\n");
    while (!EMPTY(indiv)) {
        printf("Individu n°%d\t", i);
        // printf("%d\t->\t%f\t0b", decodeIndividu(*indiv), qualiteIndividu(indiv, A, B, F));
        print1Indiv(indiv);
        indiv = RESTE(indiv);
        ++i;
    }
}

/**
 * @brief Initialise une population de taille donnée
 * 
 * @param taille int - Taille de la population
 * @param sizeIndiv int - Taille des individus
 * @return Population 
 */
Population initPopulation(int taille, int sizeIndiv) {
    Population population;
    population.taille = taille;
    population.individus = NULL;

    while (taille != 0) {
        population.individus = ajouterIndiv_tete(population.individus, sizeIndiv);
        --taille;
    }
    return population;
}

/**
 * @brief Trie la population dans l'ordre décroissant de la qualité des individus
 * 
 * @param population Population - Population d'individus à trier par rapport à leur qualité
 * @param a float - parametre de la fonction d'évaluation
 * @param b float - parametre de la fonction d'évaluation
 * @param *f float - fonction d'évaluation
 */
void quicksortPopulation(Population population, float a, float b, float (*f)(float x)) {
    Individu *tmp = lastIndiv(population.individus);
    quicksortIndiv(population.individus, tmp, a, b, f);
}

/**
 * @brief Sélectionne les meilleurs éléments de la population
 * 
 * @param population Population - Population à sélectionner
 * @param tselect int - Nombre d'éléments à sélectionner et à recopier à la suite  (ne doit pas être plus grand que la taille de la population)
 * @param a float - parametre de la fonction d'évaluation
 * @param b float - parametre de la fonction d'évaluation
 * @param *f float - fonction d'évaluation
 * 
 * @return Population 
 */
Population selectPopulation(Population population, int tselect, float a, float b, float (*f)(float x)) {
    if (tselect > population.taille) {
        return copyPopulation(population); 
    }
    Population population2;
    population2.taille = population.taille;
    population2.individus = NULL;

    quicksortPopulation(population, a, b, f);

    Individu *indiv = population.individus, *tmp = NULL;
    Bit* bits = NULL;

    for (int i = 0; i < tselect; ++i) {
        bits = copyBit(indiv->bits); 
        population2.individus = ajouterIndivWithBits_queue(population2.individus, bits);
        indiv = RESTE(indiv);
    }
    indiv = population2.individus;
    tmp = indiv;

    int i = tselect, j = 0;
    while (i < population2.taille) {
        bits = copyBit(indiv->bits); 
        population2.individus = ajouterIndivWithBits_queue(population2.individus, bits);
        indiv = RESTE(indiv);
        ++i;
        ++j;
        if (j == tselect) {
            j = 0;
            indiv = tmp;
        }
    }

    return population2;
}

/**
 * @brief Croisement de la population, selection aléatoire de deux individus et croisement entre eux puis ajout à la nouvelle population
 * 
 * @param population Population - Population à croiser
 * @param pCroise float - Probabilité de croisement entre les individus
 * @return Population 
 */
Population croisementPopulation(Population population, float pCroise) {
    Population population2;
    population2.taille = population.taille;
    population2.individus = NULL;

    int k = 0;
    while (k < population2.taille) {
        // on choisis les numéro puis on recupère 2 meks
        int prem = rand() % population2.taille;
        int deux = rand() % population2.taille;
        while (prem == deux) {
            deux = rand() % population2.taille;
        }

        Individu *tmp = population.individus, *indiv1 = NULL, *indiv2 = NULL;
        for (int i = 0; i <= MAX(prem, deux); ++i) {
            if (prem == i) {
                indiv1 = tmp;
            } else if (deux == i) {
                indiv2 = tmp;
            }
            tmp = RESTE(tmp);
        }
        DeuxBit croised = croisementBits(indiv1->bits, indiv2->bits, pCroise);
        
        population2.individus = ajouterIndivWithBits_tete(population2.individus, croised.bit1);
        population2.individus = ajouterIndivWithBits_tete(population2.individus, croised.bit2);
        k += 2;
    }
    return population2;
}

/**
 * @brief Copie et Alloue une population à partir d'une autre avec les mêmes individus
 * 
 * @param p Population - Population à copier
 * @return Population 
 */
Population copyPopulation(Population p) {
    Population population2;
    population2.taille = p.taille;
    population2.individus = NULL;

    Individu *indiv = p.individus;
    while (!EMPTY(indiv)) {
        population2.individus = ajouterIndivWithBits_tete(population2.individus, copyBit(indiv->bits));
        indiv = RESTE(indiv);
    }
    return population2;
}
