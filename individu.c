#include <individu.h>

/**
 * @brief Affiche la liste d'individus récursivement
 * 
 * @param indiv Individus - liste d'individus
 */
void printIndiv(Individus indiv) {
    if (!EMPTY(indiv)) {
        printf("%d\t->\t%f\t0b", decodeIndividu(*indiv), qualiteIndividu(indiv, A, B, F));
        printBits(indiv->bits);
        printIndiv(indiv->next);
    }
}

/**
 * @brief Affiche 1 individu
 * 
 * @param indiv Individus - liste d'individus
 */
void print1Indiv(Individus indiv) {
    if (!EMPTY(indiv)) {
        printf("%d\t->\t%f\t0b", decodeIndividu(*indiv), qualiteIndividu(indiv, A, B, F));
        printBits(indiv->bits);
    }
}

/**
 * @brief ajout d'un individu en tête d'une liste d'individus
 * 
 * @param indiv Individus - liste d'individu
 * @param size unsigned int - taille de la liste de bits
 * @return Individus  
 */
Individus ajouterIndiv_tete(Individus indiv, uint size) {
    Individus newIndiv = initIndividu(size);
    newIndiv->next = indiv;
    return newIndiv;
}

/**
 * @brief ajout d'un individu en queue d'une liste d'individus
 * 
 * @param indiv Individus - liste d'individu
 * @param size unsigned int - taille de la liste de bits
 * @return Individus  
 */
Individus ajouterIndiv_queue(Individus indiv, uint size) {
    Individus newIndiv = initIndividu(size);
    if (EMPTY(indiv)) {
        return newIndiv;
    }
    Individus tmp = lastIndiv(indiv);
    tmp->next = newIndiv;
    return indiv;
}

/**
 * @brief Supprime un individu en tête d'une liste d'individus
 * 
 * @param indiv Individus - liste d'individus
 * @return Individus  
 */
Individus supprimerIndiv_tete(Individus indiv) {
    if (EMPTY(indiv)) {
        return NULL;
    } else {
        Individus tmp = RESTE(indiv);
        free(indiv);
        return tmp;
    }
}

/**
 * @brief Supprime un individu en queue d'une liste d'individus
 * 
 * @param indiv Individus - liste d'individus
 * @return Individus  
 */
Individus supprimerIndiv_queue(Individus indiv) {
    if (EMPTY(indiv)) {
        return NULL;
    } else if (EMPTY(RESTE(indiv))) {
        free(indiv);
        return NULL;
    } else {
        Individus tmp = indiv;
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
 * @param indiv Individus - liste d'individu
 * @param bits Bits - liste de bits
 * @return Individus  
 */
Individus ajouterIndivWithBits_tete(Individus indiv, Bits bits) {
    Individus newIndiv = malloc(sizeof(Individu));
    newIndiv->bits = bits;
    newIndiv->next = indiv;
    newIndiv->longIndiv = longueurBit(bits);
    return newIndiv;
}

/**
 * @brief ajout d'un individu en queue d'une liste d'individus
 * 
 * @param indiv Individus - liste d'individu
 * @param bits Bits - liste de bits
 * @return Individus  
 */
Individus ajouterIndivWithBits_queue(Individus indiv, Bits bits) {
    Individus newIndiv = malloc(sizeof(Individu));
    newIndiv->bits = bits;
    newIndiv->next = NULL;
    newIndiv->longIndiv = longueurBit(bits);
    if (EMPTY(indiv)) {
        return newIndiv;
    }
    Individus tmp = lastIndiv(indiv);
    tmp->next = newIndiv;
    return indiv;
}

/**
 * @brief Récupère le dernier individu d'une liste d'individus 
 * 
 * @param indiv Individus - liste d'individus
 * @return Individus  
 */
Individus lastIndiv(Individu* indiv) {
    Individus tmp = indiv;
    while(!EMPTY(tmp) && !EMPTY(RESTE(tmp))) {
        tmp = RESTE(tmp);
    }
    return tmp;
}

/**
 * @brief Initialisation d'un individu
 * 
 * @param longIndiv int - taille de la liste de bits
 * @return Individus  
 */
Individus initIndividu(uint longIndiv) {
    Individus indiv = (Individu*) malloc(sizeof(Individu));
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
    Bits bits = indiv.bits; 

    while (!EMPTY(bits)) {
        res = res * 2 + HEAD(bits);
        bits = RESTE(bits);
    }

    return res;
}

/**
 * @brief Partionnement de la liste d'individus en deux listes d'individus 
 *  
 * @param first Individus - premier individu de la liste
 * @param last Individus - dernier individu de la liste
 * @param a float - parametre de la fonction d'évaluation
 * @param b float - parametre de la fonction d'évaluation
 * @param *f float - fonction d'évaluation
 *  
 * @return Individu* - le pointeur sur l'élément "charnière"
 */
Individus partition(Individus first, Individus last, float a, float b, float (*f)(float x)) {
	Individus pivot = first;
	Individus front = first;
	while (!EMPTY(front) && front != last) {
		if (qualiteIndividu(front, a, b, f) > qualiteIndividu(last, a, b, f)) {
			pivot = first;

			SWAP(first->bits, front->bits, Bits);

			first = RESTE(first);
		}

		front = RESTE(front);
	}

	SWAP(first->bits, last->bits, Bits);
	return pivot;
}

/**
 * @brief Tri rapide d'une liste d'individus récursif dans l'ordre décroissant.
 * 
 * @param first Individus - premier individu de la liste
 * @param last Individus - dernier individu de la liste
 * @param a float - parametre de la fonction d'évaluation
 * @param b float - parametre de la fonction d'évaluation
 * @param *f float - fonction d'évaluation
 */
void quicksortIndiv(Individus first, Individus last, float a, float b, float (*f)(float x)) {
	if (first == last) {
		return;
	}
	Individus pivot = partition(first, last, a, b, f); // "effectue la coupe en 2 parties et renvoie le pointeur sur l'élément charnière"

	if (!EMPTY(pivot) && !EMPTY(RESTE(pivot))) {
		quicksortIndiv(RESTE(pivot), last, a, b, f);
	}

	if (!EMPTY(pivot) && first != pivot) {
		quicksortIndiv(first, pivot, a, b, f);
	}
}

/**
 * @brief Calcule la qualité d'un individu
 * 
 * @param indiv Individus - individu à évaluer
 * @param a float - borne inférieure
 * @param b float - borne supérieure
 * @param *f float - fonction d'évaluation 
 * @return float 
 */
float qualiteIndividu(Individus indiv, float a, float b, float (*f)(float x)) {
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
 * @param indiv Individus - liste d'individus
 */
void freeIndividu(Individus indiv) {
    if (!EMPTY(indiv)) {
        freeBit(indiv->bits);
        DEBUGPRINT("\tFREE Individu at %p\n", (void*) indiv);
        freeIndividu(indiv->next);
        free(indiv);
    }
}

