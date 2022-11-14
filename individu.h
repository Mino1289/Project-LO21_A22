#ifndef __INDIVIDU_H__
#define __INDIVIDU_H__

#include <bit.h>

/**
 * @brief Structure d'un individu
 * 
 * @param longIndiv unsigned int - taille de la liste de bits
 * @param bits Bit* - liste de bits
 * @param next Individu* - pointeur vers le prochain individu
 */
typedef struct _elem_Individu {
    uint longIndiv;
    Bit *bits;
    struct _elem_Individu *next;
} Individu;


/**
 * @brief Affiche la liste d'individus récursivement
 * 
 * @param indiv Individu* - liste d'individus
 */
void printIndiv(Individu *indiv);

/**
 * @brief Affiche 1 individu
 * 
 * @param indiv Individu* - liste d'individus
 */
void print1Indiv(Individu *indiv);

/**
 * @brief ajout d'un individu en tête d'une liste d'individus
 * 
 * @param indiv Individu* - liste d'individu
 * @param size unsigned int - taille de la liste de bits
 * @return Individu* 
 */
Individu *ajouterIndiv_tete(Individu *indiv, uint size);

/**
 * @brief ajout d'un individu en queue d'une liste d'individus
 * 
 * @param indiv Individu* - liste d'individu
 * @param size unsigned int - taille de la liste de bits
 * @return Individu* 
 */
Individu *ajouterIndiv_queue(Individu *indiv, uint size);

/**
 * @brief Supprime un individu en tête d'une liste d'individus
 * 
 * @param l Individu* - liste d'individus
 * @return Individu* 
 */
Individu *supprimerIndiv_tete(Individu *l);

/**
 * @brief Supprime un individu en queue d'une liste d'individus
 * 
 * @param l Individu* - liste d'individus
 * @return Individu* 
 */
Individu *supprimerIndiv_queue(Individu *l);

/**
 * @brief ajout d'un individu en tête d'une liste d'individus
 * 
 * @param indiv Individu* - liste d'individu
 * @param bits Bit* - liste de bits
 * @return Individu* 
 */
Individu *ajouterIndivWithBits_tete(Individu *indiv, Bit *bits);

/**
 * @brief ajout d'un individu en queue d'une liste d'individus
 * 
 * @param indiv Individu* - liste d'individu
 * @param bits Bit* - liste de bits
 * @return Individu* 
 */
Individu *ajouterIndivWithBits_queue(Individu *indiv, Bit *bits);

/**
 * @brief Récupère le dernier individu d'une liste d'individus 
 * 
 * @param indiv Individu* - liste d'individus
 * @return Individu* 
 */
Individu* lastIndiv(Individu* indiv);

/**
 * @brief Initialisation d'un individu, initialisation de la liste de bits aléatoirement de manière itérative
 * 
 * @param longIndiv unsigned int - taille de la liste de bits
 * @return Individu* 
 */
Individu *initIterIndividu(uint longIndiv);

/**
 * @brief Initialisation d'un individu, initialisation de la liste de bits aléatoirement de manière récursive
 * 
 * @param bits Bit* - liste de bits
 * @param size unsigned int - nombre d'itération restante
 * @param longIndiv unsigned int - taille de la liste de bits
 * @return Individu* 
 */
Individu *initRecurIndividu(Bit* bits, uint size, uint longIndiv);

/**
 * @brief Décode un individu
 * 
 * @param indiv Individu - individu à décoder
 * @return unsigned int 
 */
uint decodeIndividu(Individu indiv);

/**
 * @brief Partionnement de la liste d'individus en deux listes d'individus 
 *  
 * @param first Individu* - premier individu de la liste
 * @param last Individu* - dernier individu de la liste
 * @param a float - parametre de la fonction d'évaluation
 * @param b float - parametre de la fonction d'évaluation
 * @param *f float - fonction d'évaluation
 *  
 * @return Individu* - le pointeur sur l'élément "charnière"
 */
Individu *partition(Individu *first, Individu *last, float a, float b, float (*f)(float x));

/**
 * @brief Tri rapide d'une liste d'individus récursif dans l'ordre décroissant.
 * 
 * @param first Individu* - premier individu de la liste
 * @param last Individu* - dernier individu de la liste
 * @param a float - parametre de la fonction d'évaluation
 * @param b float - parametre de la fonction d'évaluation
 * @param *f float - fonction d'évaluation
 *  
 */
void quicksortIndiv(Individu *first, Individu *last, float a, float b, float (*f)(float x));

/**
 * @brief Calcule la qualité d'un individu
 * 
 * @param indiv Individu* - individu à évaluer
 * @param a float - borne inférieure
 * @param b float - borne supérieure
 * @param *f float - fonction d'évaluation 
 * @return float 
 */
float qualiteIndividu(Individu *indiv, float a, float b, float (*f)(float x));

/**
 * @brief Fonction d'évaluation pour la qualité d'un individu 
 *  X |--> -X^2
 * 
 * @param x float - valeur à évaluer
 * @return float 
 */
float f1(float x);

/**
 * @brief Fonction d'évaluation pour la qualité d'un individu
 *  X |--> -ln(X)
 * 
 * @param x float - valeur à évaluer
 * @return float 
 */
float f2(float x);

/**
 * @brief Free une liste d'individus récursivement
 * 
 * @param indiv Individu* - liste d'individus
 */
void freeIndividu(Individu *indiv);

#endif // __INDIVIDU_H__
