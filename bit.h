#ifndef __BIT_H__
#define __BIT_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define F	f2

#define A	0.1
#define B	5

#define POW2(x)     (1 << (x))
#define ABS(a)      ((a) < 0 ? -(a) : (a))
#define MAX(a, b)   ((a + b + ABS(a-b)) / 2)
#define MIN(a, b)   ((a) < (b) ? (a) : (b))
#define SWAP(a, b, T)   {T tmp = a; a = b; b = tmp;}

#define EMPTY(l) (!l)
#define HEAD(l) ((l)->val)
#define RESTE(l) ((l)->next)

#define uchar unsigned char
#define uint unsigned int


#ifdef DEBUG
#define DEBUGPRINT(_msg, ...) fprintf(stderr, ".\\%s:%d " _msg, __FILE__, __LINE__, ##__VA_ARGS__);
#else
#define DEBUGPRINT(_msg, ...) // do nothing
#endif

/**
 * @brief Structure d'un bit
 * 
 * @param val unsigned char - valeur du bit
 * @param next Bit* - pointeur vers le bit suivant
 */
typedef struct _elem_Bit {
    uchar val;
    struct _elem_Bit *next;
} Bit;

typedef struct {
    Bit *bit1;
    Bit *bit2;
} DeuxBit;


/**
 * @brief Génération d'un bit aléatoire
 * 
 * @return unsigned char 
 */
uchar generateBit();

/**
 * @brief Affichage de la liste de bits récursivement
 * 
 * @param bits Bit* - liste de bits
 */
void printBits(Bit *bits);

/**
 * @brief Créer une liste de bits de manière itérative
 * 
 * @param size unsigned int - taille de la liste de bits
 */
Bit *initIterBits(uint size);

/**
 * @brief Créer une liste de bits de manière récursive
 * 
 * @param size unsigned int - taille de la liste de bits
 */
Bit *initRecurBits(uint size);

/**
 * @brief Donne la taille d'une liste de bits, récursivement
 * 
 * @param bit Bit* - liste de bits
 * @return unsigned int 
 */
uint longueurBit(Bit *bit);

/**
 * @brief ajout d'un bit en tête d'une liste de bits
 * 
 * @param bit Bit* - liste de bits
 * @param bitVal unsigned char - valeur du bit à ajouter
 * @return Bit* 
 */
Bit *ajouterBit_tete(Bit *bit, uchar bitVal);

/**
 * @brief ajout d'un bit en queue d'une liste de bits
 * 
 * @param bit Bit* - liste de bits
 * @param bitVal unsigned char - valeur du bit à ajouter
 * @return Bit* 
 */
Bit *ajouterBit_queue(Bit *bit, uchar bitVal);

/**
 * @brief Supprime un bit en tête d'une liste de bits
 * 
 * @param bits Bit* - liste de bits
 * @return Bit* 
 */
Bit *supprimerBit_tete(Bit *bits);

/**
 * @brief Supprime un bit en queue d'une liste de bits
 * 
 * @param bits Bit* - liste de bits
 * @return Bit* 
 */
Bit *supprimerBit_queue(Bit *bits);

/**
 * @brief Croise deux listes de bits avec une probabilité de croisement
 * 
 * @param bit1 Bit * - liste de bit à croiser
 * @param bit2 Bit * - liste de bit à croiser
 * @param pCroise float - probabilité de croisement
 * @return DeuxBit 
 */
DeuxBit croisementBits(Bit *bit1, Bit *bit2, float pCroise);

/**
 * @brief Alloue et Copie une liste de bits
 * 
 * @param bit Bit* - liste de bits à copier
 * @return Bit* 
 */
Bit *copyBit(Bit *bit);

/**
 * @brief Free une liste de bits récursivement
 * 
 * @param bits Bit* - liste de bits
 */
void freeBit(Bit *bits);


#endif // __BIT_H__