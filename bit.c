#include <bit.h>


/**
 * @brief Génération d'un bit aléatoire
 * 
 * @return unsigned char 
 */
uchar generateBit() {
    return rand() % 2;
}

/**
 * @brief Affichage de la liste de bits récursivement
 * 
 * @param bits Bit* - liste de bits
 */
void printBits(Bit *bits) {
    if (!EMPTY(bits)) {
        printf("%d", HEAD(bits));
        printBits(RESTE(bits));
    } else {
        printf("\n");
    }
}

/**
 * @brief Créer une liste de bits
 * 
 * @param size unsigned int - taille de la liste de bits
 */
Bit *initBits(uint size) {
    Bit *bits = NULL;
    for (uint i = 0; i < size; i++) {
        bits = ajouterBit_tete(bits, generateBit());
    }
    return bits;
}

/**
 * @brief Donne la taille d'une liste de bits, récursivement
 * 
 * @param bit Bit* - liste de bits
 * @return unsigned int 
 */
unsigned int longueurBit(Bit *bit) {
    if (bit == NULL) {
        return 0;
    }
    return 1 + longueurBit(RESTE(bit));
}

/**
 * @brief ajout d'un bit en tête d'une liste de bits
 * 
 * @param bit Bit* - liste de bits
 * @param bitVal unsigned char - valeur du bit à ajouter
 * @return Bit* 
 */
Bit* ajouterBit_tete(Bit *bit, uchar bitVal) {
    Bit *newBit = (Bit*)malloc(sizeof(Bit));
    newBit->val = bitVal;
    newBit->next = bit;
    return newBit;
}

/**
 * @brief ajout d'un bit en queue d'une liste de bits
 * 
 * @param bit Bit* - liste de bits
 * @param bitVal unsigned char - valeur du bit à ajouter
 * @return Bit* 
 */
Bit *ajouterBit_queue(Bit *bit, uchar bitVal) {
    Bit *newBit = (Bit*)malloc(sizeof(Bit));
    newBit->val = bitVal;
    newBit->next = NULL;
    if (bit == NULL) {
        return newBit;
    }
    Bit *tmp = bit;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = newBit;
    return bit;
}

/**
 * @brief Supprime un bit en tête d'une liste de bits
 * 
 * @param bits Bit* - liste de bits
 * @return Bit* 
 */
Bit *supprimerBit_tete(Bit *bits) {
    if (bits == NULL) {
        return NULL;
    }
    Bit *tmp = bits->next;
    free(bits);
    return tmp;
}

/**
 * @brief Supprime un bit en queue d'une liste de bits
 * 
 * @param bits Bit* - liste de bits
 * @return Bit* 
 */
Bit *supprimerBit_queue(Bit *bits) {
    if (EMPTY(bits)) {
        return NULL;
    } else if (EMPTY(RESTE(bits))) {
        free(bits);
        return NULL;
    } else {
        Bit *tmp = bits;
        while (!EMPTY(RESTE(RESTE(bits)))) {
            tmp = RESTE(tmp);
        }
        free(RESTE(tmp));
        RESTE(tmp) = NULL;
        return bits;
    }
}

/**
 * @brief Croise deux listes de bits avec une probabilité de croisement
 * 
 * @param bit1 Bit * - liste de bit à croiser
 * @param bit2 Bit * - liste de bit à croiser
 * @param pCroise float - probabilité de croisement
 * @return DeuxBit 
 */
DeuxBit croisementBits(Bit *bit1, Bit *bit2, float pCroise) {
    Bit *tmp1 = bit1, *tmp2 = bit2;
    Bit *croise1 = NULL, *croise2 = NULL;
    while (!EMPTY(tmp1) && !EMPTY(tmp2)) {
        if (rand() % 100 < pCroise * 100) {
            croise1 = ajouterBit_queue(croise1, HEAD(tmp1));
            croise2 = ajouterBit_queue(croise2, HEAD(tmp2));
        } else {
            croise1 = ajouterBit_queue(croise1, HEAD(tmp2));
            croise2 = ajouterBit_queue(croise2, HEAD(tmp1));
        }
        tmp1 = RESTE(tmp1);
        tmp2 = RESTE(tmp2);
    }
    DeuxBit deuxBit = {croise1, croise2};
    return deuxBit;
}


/**
 * @brief Alloue et Copie une liste de bits
 * 
 * @param bit Bit* - liste de bits à copier
 * @return Bit* 
 */
Bit *copyBit(Bit *bit) {
    Bit *newBit = NULL;
    while (!EMPTY(bit)) {
        newBit = ajouterBit_queue(newBit, HEAD(bit));
        bit = RESTE(bit);
    }
    return newBit;
}

/**
 * @brief Free une liste de bits récursivement
 * 
 * @param bits Bit* - liste de bits
 */
void freeBit(Bit *bits) {
    if (!EMPTY(bits)) {
        DEBUGPRINT("\t\tFREE Bit at %p\n", (void*) bits);
        freeBit(RESTE(bits));
        free(bits);
    }
}

