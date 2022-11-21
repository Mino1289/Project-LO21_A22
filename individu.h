#ifndef __INDIVIDU_H__
#define __INDIVIDU_H__

#include <bit.h>

/**
 * @brief Structure d'un individu
 * 
 * @param longIndiv unsigned int - taille de la liste de bits
 * @param bits Bits  - liste de bits
 * @param next Individu* - pointeur vers le prochain individu
 */
typedef struct _elem_Individu {
    uint longIndiv;
    Bits bits;
    struct _elem_Individu *next;
} Individu;

typedef Individu* Individus;


/**
 * @brief Affiche la liste d'individus récursivement
 * 
 * @param indiv Individus - liste d'individus
 */
void printIndiv(Individus indiv);

/**
 * @brief Affiche 1 individu
 * 
 * @param indiv Individus - liste d'individus
 */
void print1Indiv(Individus indiv);

/**
 * @brief ajout d'un individu en tête d'une liste d'individus
 * 
 * @param indiv Individus - liste d'individu
 * @param size unsigned int - taille de la liste de bits
 * @return Individus  
 */
Individus ajouterIndiv_tete(Individus indiv, uint size);

/**
 * @brief ajout d'un individu en queue d'une liste d'individus
 * 
 * @param indiv Individus - liste d'individu
 * @param size unsigned int - taille de la liste de bits
 * @return Individus  
 */
Individus ajouterIndiv_queue(Individus indiv, uint size);

/**
 * @brief Supprime un individu en tête d'une liste d'individus
 * 
 * @param l Individus - liste d'individus
 * @return Individu* 
 */
Individus supprimerIndiv_tete(Individus l);

/**
 * @brief Supprime un individu en queue d'une liste d'individus
 * 
 * @param l Individus - liste d'individus
 * @return Individus  
 */
Individus supprimerIndiv_queue(Individus l);

/**
 * @brief ajout d'un individu en tête d'une liste d'individus
 * 
 * @param indiv Individus - liste d'individu
 * @param bits Bits - liste de bits
 * @return Individus  
 */
Individus ajouterIndivWithBits_tete(Individus indiv, Bits bits);

/**
 * @brief ajout d'un individu en queue d'une liste d'individus
 * 
 * @param indiv Individus - liste d'individu
 * @param bits Bits - liste de bits
 * @return Individus  
 */
Individus ajouterIndivWithBits_queue(Individus indiv, Bits bits);

/**
 * @brief Récupère le dernier individu d'une liste d'individus 
 * 
 * @param indiv Individus - liste d'individus
 * @return Individus  
 */
Individu* lastIndiv(Individu* indiv);

/**
 * @brief Initialisation d'un individu
 * 
 * @param longIndiv int - taille de la liste de bits
 * @return Individus  
 */
Individus initIndividu(uint longIndiv);

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
 * @param first Individus - premier individu de la liste
 * @param last Individus - dernier individu de la liste
 * @param a float - parametre de la fonction d'évaluation
 * @param b float - parametre de la fonction d'évaluation
 * @param *f float - fonction d'évaluation
 *  
 * @return Individus  - le pointeur sur l'élément "charnière"
 */
Individus partition(Individus first, Individus last, float a, float b, float (*f)(float x));

/**
 * @brief Tri rapide d'une liste d'individus récursif dans l'ordre décroissant.
 * 
 * @param first Individus - premier individu de la liste
 * @param last Individus - dernier individu de la liste
 * @param a float - parametre de la fonction d'évaluation
 * @param b float - parametre de la fonction d'évaluation
 * @param *f float - fonction d'évaluation
 *  
 */
void quicksortIndiv(Individus first, Individus last, float a, float b, float (*f)(float x));

/**
 * @brief Calcule la qualité d'un individu
 * 
 * @param indiv Individus - individu à évaluer
 * @param a float - borne inférieure
 * @param b float - borne supérieure
 * @param *f float - fonction d'évaluation 
 * @return float 
 */
float qualiteIndividu(Individus indiv, float a, float b, float (*f)(float x));

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
 * @param indiv Individus - liste d'individus
 */
void freeIndividu(Individus indiv);

#endif // __INDIVIDU_H__
