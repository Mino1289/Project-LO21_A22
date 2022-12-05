#include <population.h>

/**
 * @brief Affiche la liste de population
 *
 * @param population Population - liste de population
 * @param eval Evaluation - structure d'évaluation
 */
void printPopulation(Population population, Evaluation eval) {
    Individu* indiv = population.individus;
    int i = 1;
    printf("Population de taille %d.\n", population.taille);
    printf("Individus de taille %d.\n\n", population.individus->longIndiv);

    printf("Individu n°k\tDecode\t->\tQualité\t\t0b.bits..\n\n");
    while (!EMPTY(indiv)) {
        printf("Individu n°%d\t", i);
        // printf("%d\t->\t%f\t0b", decodeIndividu(*indiv), qualiteIndividu(indiv, A, B, F));
        print1Indiv(indiv, eval);
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
 * @param eval Evaluation - structure d'évaluation
 */
void quicksortPopulation(Population population, Evaluation eval) {
    Individu* tmp = lastIndiv(population.individus);
    quicksortIndiv(population.individus, tmp, eval);
}

/**
 * @brief Sélectionne les meilleurs éléments de la population
 *
 * @param population Population - Population à sélectionner
 * @param tselect int - Nombre d'éléments à sélectionner et à recopier à la suite  (ne doit pas être plus grand que la taille de la population)
 * @param eval Evaluation - structure d'évaluation
 *
 * @return Population
 */
void selectPopulation(Population population, int tselect, Evaluation eval) {
    if (tselect > population.taille) {
        return;
    }
    quicksortPopulation(population, eval);

    Individus tmp = population.individus, indiv = population.individus;
    int i = 1;
    while (i < tselect) {
        tmp = RESTE(tmp);
        ++i;
    }
    freeIndividu(RESTE(tmp)); // On libère la mémoire des Individus qui ne sont pas sélectionnés
    RESTE(tmp) = NULL; 
    tmp = population.individus;

    i = 0;
    while (i < population.taille - tselect) {
        tmp = ajouterIndivWithBits_queue(tmp, copyBit(indiv->bits));

        if (i == tselect - 1) {
            indiv = population.individus;
        } else {
            indiv = RESTE(indiv);
        }
        ++i;
    }
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

        Individus tmp = population.individus, indiv1 = NULL, indiv2 = NULL;
        for (int i = 0; i <= MAX(prem, deux); ++i) {
            if (prem == i) {
                indiv1 = tmp;
            }
            else if (deux == i) {
                indiv2 = tmp;
            }
            tmp = RESTE(tmp);
        }
        DeuxBit croised = croisementBits(indiv1->bits, indiv2->bits, pCroise);

        population2.individus = ajouterIndivWithBits_tete(population2.individus, croised.bit1);
        ++k;
        if (k < population2.taille) {
            population2.individus = ajouterIndivWithBits_tete(population2.individus, croised.bit2);
            ++k;
        }
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

    Individu* indiv = p.individus;
    while (!EMPTY(indiv)) {
        population2.individus = ajouterIndivWithBits_tete(population2.individus, copyBit(indiv->bits));
        indiv = RESTE(indiv);
    }
    return population2;
}
