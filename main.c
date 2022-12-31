#include <population.h>
#include <gui.h>


int main(int argc, char* argv[]) {
	long seed = time(0);
	srand(seed);
	DEBUGPRINT("Seed: %ld\n", seed);

	Evaluation eval = {
		.a = A,
		.b = B,
		.f = F,
	};


	// -Longueur d'un individu : longIndiv = 8 
	// -Probabilité de croisement : pCroise = 0.5 
	// -Taille de la Population : 20 ≤ TaillePop ≤ 200 
	// -Taux de sélection : 10% ≤ tSelect ≤ 90% 
	// -Nombre de générations : 20 ≤ nGen ≤ 200

	uint longIndiv = 16;
	float pCroise = 0.5;
	uint taillePop = get_integer_input("Quelle taille de population souhaitez-vous ? (20-200): ", 20, 200);
	float tSelectp = get_float_input("Quel taux de sélection souhaitez-vous ? (0.1-0.9): ", 0.1, 0.9);
	uint nGen = get_integer_input("Combien de génération souhaitez-vous ? (20-200): ", 20, 200);

	printf("Taille des individus : %d\n", longIndiv);
	printf("Probabilité de croisement : %.2f\n", pCroise);
	printf("Taille de la population : %d\n", taillePop);
	printf("Taux de sélection : %.2f\n", tSelectp);
	printf("Nombre de génération : %d\n", nGen);

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
		selectPopulation(tmp, tSelect, eval);
		p = tmp;
	}
	// Fin 
	quicksortPopulation(p, eval); // on trie pour afficher le meilleur individu
	// Afficher le meilleur Individu de la Population
	printf("\nMeilleur individu :\n");
	printf("Valeur\t->\tQualité\t\tBits\n");
	print1Indiv(p.individus, eval);

	freeIndividu(p.individus);

	DEBUGPRINT("Fin du programme\n");
	return EXIT_SUCCESS;
}
