#include <individu.h>

/**
 * @brief Affiche la liste d'individus récursivement
 * 
 * @param indiv Individu* - liste d'individus
 */
void printIndiv(Individu *indiv) {
    if (!EMPTY(indiv)) {
        printf("%d\t->\t%f\t0b", decodeIndividu(*indiv), qualiteIndividu(indiv, A, B, F));
        printBits(indiv->bits);
        printIndiv(indiv->next);
    }
}

/**
 * @brief Affiche 1 individu
 * 
 * @param indiv Individu* - liste d'individus
 */
void print1Indiv(Individu *indiv) {
    if (!EMPTY(indiv)) {
        printf("%d\t->\t%f\t0b", decodeIndividu(*indiv), qualiteIndividu(indiv, A, B, F));
        printBits(indiv->bits);
    }
}

/**
 * @brief ajout d'un individu en tête d'une liste d'individus
 * 
 * @param indiv Individu* - liste d'individu
 * @param size unsigned int - taille de la liste de bits
 * @return Individu* 
 */
Individu *ajouterIndiv_tete(Individu *indiv, uint size) {
    Individu *newIndiv = initIndividu(size);
    newIndiv->next = indiv;
    return newIndiv;
}

/**
 * @brief ajout d'un individu en queue d'une liste d'individus
 * 
 * @param indiv Individu* - liste d'individu
 * @param size unsigned int - taille de la liste de bits
 * @return Individu* 
 */
Individu *ajouterIndiv_queue(Individu *indiv, uint size) {
    Individu *newIndiv = initIndividu(size);
    if (EMPTY(indiv)) {
        return newIndiv;
    }
    Individu *tmp = lastIndiv(indiv);
    tmp->next = newIndiv;
    return indiv;
}

/**
 * @brief Supprime un individu en tête d'une liste d'individus
 * 
 * @param indiv Individu* - liste d'individus
 * @return Individu* 
 */
Individu *supprimerIndiv_tete(Individu *indiv) {
    if (EMPTY(indiv)) {
        return NULL;
    } else {
        Individu *tmp = RESTE(indiv);
        free(indiv);
        return tmp;
    }
}

/**
 * @brief Supprime un individu en queue d'une liste d'individus
 * 
 * @param indiv Individu* - liste d'individus
 * @return Individu* 
 */
Individu *supprimerIndiv_queue(Individu *indiv) {
    if (EMPTY(indiv)) {
        return NULL;
    } else if (EMPTY(RESTE(indiv))) {
        free(indiv);
        return NULL;
    } else {
        Individu *tmp = indiv;
        while (!EMPTY(RESTE(RESTE(indiv)))) {
            tmp = RESTE(tmp);
        }
        free(RESTE(tmp));
        RESTE(tmp) = NULL;
        return indiv;
    }
}

/**
 * @brief ajout d'un individu en tête d'une liste d'individus
 * 
 * @param indiv Individu* - liste d'individu
 * @param bits Bit* - liste de bits
 * @return Individu* 
 */
Individu *ajouterIndivWithBits_tete(Individu *indiv, Bit *bits) {
    Individu *newIndiv = malloc(sizeof(Individu));
    newIndiv->bits = bits;
    newIndiv->next = indiv;
    newIndiv->longIndiv = longueurBit(bits);
    return newIndiv;
}

/**
 * @brief ajout d'un individu en queue d'une liste d'individus
 * 
 * @param indiv Individu* - liste d'individu
 * @param bits Bit* - liste de bits
 * @return Individu* 
 */
Individu *ajouterIndivWithBits_queue(Individu *indiv, Bit *bits) {
    Individu *newIndiv = malloc(sizeof(Individu));
    newIndiv->bits = bits;
    newIndiv->next = NULL;
    newIndiv->longIndiv = longueurBit(bits);
    if (EMPTY(indiv)) {
        return newIndiv;
    }
    Individu *tmp = lastIndiv(indiv);
    tmp->next = newIndiv;
    return indiv;
}

/**
 * @brief Récupère le dernier individu d'une liste d'individus 
 * 
 * @param indiv Individu* - liste d'individus
 * @return Individu* 
 */
Individu *lastIndiv(Individu* indiv) {
    Individu *tmp = indiv;
    while(!EMPTY(tmp) && !EMPTY(RESTE(tmp))) {
        tmp = RESTE(tmp);
    }
    return tmp;
}

/**
 * @brief Initialisation d'un individu
 * 
 * @param longIndiv int - taille de la liste de bits
 * @return Individu* 
 */
Individu *initIndividu(uint longIndiv) {
    Individu *indiv = (Individu*) malloc(sizeof(Individu));
    indiv->longIndiv = longIndiv;
    indiv->next = NULL;
    indiv->bits = initRecurBits(longIndiv);
    return indiv;
}

/**
 * @brief Décode un individu (convertit une liste de bits en un nombre)
 * 
 * @param indiv Individu - individu à décoder
 * @return unsigned int 
 */
uint decodeIndividu(Individu indiv) {
    int res = 0;
    int power = 1;
    Bit *tmp = NULL, *bits = indiv.bits; 

    while (!EMPTY(bits)) {
        tmp = ajouterBit_tete(tmp, HEAD(bits));
        bits = RESTE(bits);
    }
    bits = tmp;
    
    for (int i = 0; i < indiv.longIndiv; i++) {
        res += HEAD(bits) * power;
        power *= 2;
        bits = RESTE(bits);
    }
    freeBit(tmp);
    return res;
}

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
Individu *partition(Individu *first, Individu *last, float a, float b, float (*f)(float x)) {
	Individu *pivot = first;
	Individu *front = first;
	while (front != NULL && front != last) {
		if (qualiteIndividu(front, a, b, f) > qualiteIndividu(last, a, b, f)) {
			pivot = first;

			SWAP(first->bits, front->bits, Bit*);

			first = RESTE(first);
		}

		front = RESTE(front);
	}

	SWAP(first->bits, last->bits, Bit*);
	return pivot;
}

/**
 * @brief Tri rapide d'une liste d'individus récursif dans l'ordre décroissant.
 * 
 * @param first Individu* - premier individu de la liste
 * @param last Individu* - dernier individu de la liste
 * @param a float - parametre de la fonction d'évaluation
 * @param b float - parametre de la fonction d'évaluation
 * @param *f float - fonction d'évaluation
 */
void quicksortIndiv(Individu *first, Individu *last, float a, float b, float (*f)(float x)) {
	if (first == last) {
		return;
	}
	Individu *pivot = partition(first, last, a, b, f);

	if (!EMPTY(pivot && !EMPTY(RESTE(pivot)))) {
		quicksortIndiv(RESTE(pivot), last, a, b, f);
	}

	if (!EMPTY(pivot) && first != pivot) {
		quicksortIndiv(first, pivot, a, b, f);
	}
}

/**
 * @brief Calcule la qualité d'un individu
 * 
 * @param indiv Individu* - individu à évaluer
 * @param a float - borne inférieure
 * @param b float - borne supérieure
 * @param *f float - fonction d'évaluation 
 * @return float 
 */
float qualiteIndividu(Individu *indiv, float a, float b, float (*f)(float x)) {
    float X = (decodeIndividu(*indiv))/((float)(POW2(indiv->longIndiv)))*(b-a)+a;
    return -f(X);
}

/**
 * @brief Fonction d'évaluation pour la qualité d'un individu 
 *  X |--> -X^2
 * 
 * @param x float - valeur à évaluer
 * @return float 
 */
float f1(float x) {
    return -(x*x);
}

/**
 * @brief Fonction d'évaluation pour la qualité d'un individu
 *  X |--> -ln(X)
 * 
 * @param x float - valeur à évaluer
 * @return float 
 */
float f2(float x) {
    return -log(x);
}

/**
 * @brief Free une liste d'individus récursivement
 * 
 * @param indiv Individu* - liste d'individus
 */
void freeIndividu(Individu *indiv) {
    if (!EMPTY(indiv)) {
        freeBit(indiv->bits);
        DEBUGPRINT("\tFREE Individu at %p\n", (void*) indiv);
        freeIndividu(indiv->next);
        free(indiv);
    }
}

