#include <population.h>
#include <gui.h>


int main(int argc, char* argv[]) {
	long seed = time(0);
	srand(seed);
	DEBUGPRINT("Seed: %ld\n", seed);


	// -Longueur d'un individu : longIndiv = 8 
	// -Probabilité de croisement : pCroise = 0.5 
	// -Taille de la Population : 20 ≤ TaillePop ≤ 200 
	// -Taux de sélection : 10% ≤ tSelect ≤ 90% 
	// -Nombre de générations : 20 ≤ nGen ≤ 200

	uint longIndiv = 16;
	float pCroise = 0.5;
	uint taillePop = get_integer_input("Quelle taille de population souhaitez-vous ? (8-256): ", 20, 200);
	float tSelectp = get_float_input("Quel taux de sélection souhaitez-vous ? (0.1-0.9): ", 0.1, 0.9);
	uint nGen = get_integer_input("Combien de génération souhaitez-vous ? (4-256): ", 20, 200);
	
	uint tSelect = tSelectp*taillePop; 
	// on préfère le nombre qu'un pourcentage de la population


	// Initialiser la Population 
	Population p = initPopulation(taillePop, longIndiv), tmp;
	// Répéter nGen fois 
	// Début 	
	for (int i = 0; i < nGen; ++i) {
		// Croiser la Population 
		tmp = croisementPopulation(p, pCroise);
		freeIndividu(p.individus);
		// Trier la Population 
		// quicksortPopulation(p); // pas besoin de trier, c'est fait dans select
		// Sélectionner la Population 
		p = selectPopulation(tmp, tSelect, A, B, F);
		freeIndividu(tmp.individus);
	}
	// Fin 
	quicksortPopulation(p, A, B, F); // on trie pour afficher le meilleur individu
	// Afficher le meilleur Individu de la Population
	printf("Meilleur individu : ");
	printf("Valeur\t->\tQualité\t\tBits\n");
	print1Indiv(p.individus);

	freeIndividu(p.individus);

	printf("Fin du programme\n");

	return EXIT_SUCCESS;
}
