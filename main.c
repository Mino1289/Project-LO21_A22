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
	float pCroise = get_float_input("Quelle probabilité de croisement souhaitez-vous ? (0.1-1): ", 0.1, 1);
	uint taillePop = get_integer_input("Quelle taille de population souhaitez-vous ? (8-256): ", 8, 256);
	float tSelectp = get_float_input("Quel taux de sélection souhaitez-vous ? (0.1-0.9): ", 0.1, 0.9);
	uint nGen = get_integer_input("Combien de génération souhaitez-vous ? (4-256): ", 4, 256);
	
	uint tSelect = tSelectp*taillePop; // on préfère le nombre qu'un pourcentage de la population
	printf("%d\n", tSelect);

	
	Population p = initPopulation(taillePop, longIndiv), tmp;
	quicksortPopulation(p, A, B, F);
	printPopulation(p);

	int i = 0;
	printf("Valeur\t->\tQualité\t\tBits\n");
	while (i < nGen) {
		tmp = croisementPopulation(p, pCroise);
		freeIndividu(p.individus);
		// quicksortPopulation(p); // pas besoin de trier, c'est fait dans select
		p = selectPopulation(tmp, tSelect, A, B, F);
		freeIndividu(tmp.individus);
		++i;
	}
	printPopulation(p);
	// // print1Indiv(p.individus);

	freeIndividu(p.individus);
	// freeIndividu(tmp.individus);	

	// Population p = initPopulation(20, 8);

	// Population pop = selectPopulation(p, 5);

	// freeIndividu(p.individus);
	// freeIndividu(pop.individus);

	printf("Fin du programme\n");

	return EXIT_SUCCESS;
}
