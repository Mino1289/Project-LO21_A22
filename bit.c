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
 * @param bits Bits  - liste de bits
 */
void printBits(Bits bits) {
    if (!EMPTY(bits)) {
        printf("%d", HEAD(bits));
        printBits(RESTE(bits));
    } else {
        printf("\n");
    }
}

/**
 * @brief Créer une liste de bits de manière itérative
 * 
 * @param size unsigned int - taille de la liste de bits
 */
Bits initIterBits(uint size) {
    Bits bits = NULL;
    for (uint i = 0; i < size; i++) {
        bits = ajouterBit_tete(bits, generateBit());
    }
    return bits;
}

/**
 * @brief Créer une liste de bits de manière récursive
 * 
 * @param size unsigned int - taille de la liste de bits
 */
Bits initRecurBits(uint size) {
    if (!size) {
        return NULL;
    } else {
        return ajouterBit_tete(initRecurBits(size - 1), generateBit());
    }
}

/**
 * @brief Donne la taille d'une liste de bits, récursivement
 * 
 * @param bit Bits - liste de bits
 * @return unsigned int 
 */
uint longueurBit(Bits bit) {
    if (EMPTY(bit)) {
        return 0;
    }
    return 1 + longueurBit(RESTE(bit));
}

/**
 * @brief ajout d'un bit en tête d'une liste de bits
 * 
 * @param bit Bits - liste de bits
 * @param bitVal unsigned char - valeur du bit à ajouter
 * @return Bits 
 */
Bits ajouterBit_tete(Bits bit, uchar bitVal) {
    Bits newBit = (Bits) malloc(sizeof(Bit));
    newBit->val = bitVal;
    newBit->next = bit;
    return newBit;
}

/**
 * @brief ajout d'un bit en queue d'une liste de bits
 * 
 * @param bit Bits - liste de bits
 * @param bitVal unsigned char - valeur du bit à ajouter
 * @return Bits 
 */
Bits ajouterBit_queue(Bits bit, uchar bitVal) {
    Bits newBit = (Bits)malloc(sizeof(Bit));
    newBit->val = bitVal;
    newBit->next = NULL;
    if (bit == NULL) {
        return newBit;
    }
    Bits tmp = bit;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = newBit;
    return bit;
}

/**
 * @brief Décode une liste de Bit en un nombre
 * 
 * @param bits Bits - liste de Bit à décoder
 * @return unsigned int 
 */
uint decodeBit(Bits bits) {
    int res = 0;
    while (!EMPTY(bits)) {
        res = res * 2 + HEAD(bits);
        bits = RESTE(bits);
    }
    return res;
}

/**
 * @brief Croise deux listes de bits avec une probabilité de croisement
 * 
 * @param bit1 Bits  - liste de bit à croiser
 * @param bit2 Bits  - liste de bit à croiser
 * @param pCroise float - probabilité de croisement
 * @return DeuxBit 
 */
DeuxBit croisementBits(Bits bit1, Bits bit2, float pCroise) {
    Bits tmp1 = bit1, tmp2 = bit2;
    Bits croise1 = NULL, croise2 = NULL;
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
 * @param bit Bits - liste de bits à copier
 * @return Bits 
 */
Bits copyBit(Bits bit) {
    Bits newBit = NULL;
    while (!EMPTY(bit)) {
        newBit = ajouterBit_queue(newBit, HEAD(bit));
        bit = RESTE(bit);
    }
    return newBit;
}

/**
 * @brief Free une liste de bits récursivement
 * 
 * @param bits Bits - liste de bits
 */
void freeBit(Bits bits) {
    if (!EMPTY(bits)) {
        DEBUGPRINT("\t\tFREE Bit at %p\n", (void *) bits);
        freeBit(RESTE(bits));
        free(bits);
    }
}

