#ifndef __POPULATION_H__
#define __POPULATION_H__

#include <stdio.h>
#include <stdlib.h>

#include <individu.h>


/**
 * @brief Structure de population
 * 
 * @param individus Individus - Liste chainée des individus de la population (premier individu)
 * @param taille int - Taille de la population
 */
typedef struct Population {
    Individus individus;
    int taille;
} Population;

/**
 * @brief Affiche la population
 * 
 * @param population Population - Population à afficher
 * @param eval Evaluation - Structure d'évaluation
 */
void printPopulation(Population population, Evaluation eval);

/**
 * @brief Initialise une population de taille donnée
 * 
 * @param taille int - Taille de la population
 * @param sizeIndiv int - Taille des individus
 * @return Population 
 */
Population initPopulation(int taille, int sizeIndiv);

/**
 * @brief Trie la population dans l'ordre décroissant de la qualité des individus
 * 
 * @param population Population - Population d'individus à trier par rapport à leur qualité
 * @param eval Evaluation - structure d'évaluation
 */
void quicksortPopulation(Population population, Evaluation eval);

/**
 * @brief Sélectionne les meilleurs éléments de la population
 * 
 * @param population Population - Population à sélectionner
 * @param tselect int - Nombre d'éléments à sélectionner et à recopier à la suite  (ne doit pas être plus grand que la taille de la population)
 * @param eval Evaluation - structure d'évaluation
 */
void selectPopulation(Population population, int tselect, Evaluation eval);

/**
 * @brief Croisement de la population, selection aléatoire de deux individus et croisement entre eux puis ajout à la nouvelle population
 * 
 * @param population Population - Population à croiser
 * @param pCroise float - Probabilité de croisement entre les individus
 * 
 * @return Population 
 */
Population croisementPopulation(Population population, float pCroise);

/**
 * @brief Copie et Alloue une population à partir d'une autre avec les mêmes individus
 * 
 * @param p Population - Population à copier
 * @return Population 
 */
Population copyPopulation(Population p);

#endif // __POPULATION_H__
