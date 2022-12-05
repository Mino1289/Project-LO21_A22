#ifndef __BIT_H__
#define __BIT_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define F	f2 // f1 ou f2

#define A	0.1	// valeur de A
#define B	5	// valeur de B

#define POW2(x)         (1 << (x))
#define ABS(a)          ((a) < 0 ? -(a) : (a))
#define MAX(a, b)       ((a + b + ABS(a-b)) / 2)
#define MIN(a, b)       ((a + b - ABS(a-b)) / 2)
#define SWAP(a, b, T)   {T tmp = a; a = b; b = tmp;}

#define EMPTY(l)        (!(l))
#define HEAD(l)         ((l)->val)
#define RESTE(l)        ((l)->next)

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
 * @param next Bits - pointeur vers le bit suivant
 */
typedef struct _elem_Bit {
    uchar val;
    struct _elem_Bit *next;
} Bit;

typedef Bit* Bits;

/**
 * @brief Produit cartésien de deux listes de bits
 * 
 * @param bit1 Bits - liste de bits
 * @param bit2 Bits - liste de bits
 */
typedef struct {
    Bits bit1;
    Bits bit2;
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
 * @param bits Bits  - liste de bits
 */
void printBits(Bits bits);

/**
 * @brief Créer une liste de bits de manière itérative
 * 
 * @param size unsigned int - taille de la liste de bits
 * @return Bits  
 */
Bits initIterBits(uint size);

/**
 * @brief Créer une liste de bits de manière récursive
 * 
 * @param size unsigned int - taille de la liste de bits
 * @return Bits  
 */
Bits initRecurBits(uint size);

/**
 * @brief Donne la taille d'une liste de bits, récursivement
 * 
 * @param bit Bits  - liste de bits
 * @return unsigned int 
 */
uint longueurBit(Bits bit);

/**
 * @brief ajout d'un bit en tête d'une liste de bits
 * 
 * @param bit Bits  - liste de bits
 * @param bitVal unsigned char - valeur du bit à ajouter
 * @return Bits  
 */
Bits ajouterBit_tete(Bits bit, uchar bitVal);

/**
 * @brief ajout d'un bit en queue d'une liste de bits
 * 
 * @param bit Bits  - liste de bits
 * @param bitVal unsigned char - valeur du bit à ajouter
 * @return Bits  
 */
Bits ajouterBit_queue(Bits bit, uchar bitVal);

/**
 * @brief Décode une liste de Bit en un nombre
 * 
 * @param bits Bits - liste de Bit à décoder
 * @return unsigned int 
 */
uint decodeBit(Bits bits);

/**
 * @brief Croise deux listes de bits avec une probabilité de croisement
 * 
 * @param bit1 Bits  - liste de bit à croiser
 * @param bit2 Bits  - liste de bit à croiser
 * @param pCroise float - probabilité de croisement
 * @return DeuxBit 
 */
DeuxBit croisementBits(Bits bit1, Bits bit2, float pCroise);

/**
 * @brief Alloue et Copie une liste de bits
 * 
 * @param bit Bits  - liste de bits à copier
 * @return Bits  
 */
Bits copyBit(Bits bit);

/**
 * @brief Free une liste de bits récursivement
 * 
 * @param bits Bits  - liste de bits
 */
void freeBit(Bits bits);


#endif // __BIT_H__