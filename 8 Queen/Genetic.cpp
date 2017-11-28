#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

/*---------------------
    Global Variable
---------------------*/

const short POP  = 4;
const short SIZE = 4;
const short maxWeight = (SIZE * (SIZE - 1)) / 2;

short answers[SIZE];

/*---------------
    Functions
---------------*/

short getRand(short mod){
	if (mod == 0) return 0;
	else return rand() % mod;
}

void printArray(short array[]) {
	for (short i = 0; i < SIZE - 1; i++)
		printf("(%i,%i),", i, array[i]);

	printf("(%i,%i)", SIZE - 1, array[SIZE - 1]);

	printf("\n");
}

short getWeight(short array[]) {
	short weight = maxWeight;

	for (short queen = 0; queen < SIZE; queen++) {
		for (short nextqueen = queen + 1; nextqueen < SIZE; nextqueen++) {
			if (array[queen] == array[nextqueen] ||
                abs(queen - nextqueen) == abs(array[queen] - array[nextqueen])) {
				weight--;
			}
		}
	}

	return weight;
}

void geneticAlgorithm() {

	short weightProb[maxWeight * SIZE];
	short children[POP][SIZE];
	short population[POP][SIZE];

	short wpl  = 0; //weightProb[] length
	bool  done = false;
	float mutProb = 0.2; //higher prob yields faster times. works decently anyways. bug: prob = 0

	for (short i = 0; i < POP; i++)
        for (short j = 0; j < SIZE; j++)
            population[i][j] = getRand(SIZE);
            
	while (!done) {

		for (short i = 0; i < POP; i++) {
			if (getWeight(children[i]) == maxWeight) {
				printf("solution: ");
				printArray(children[i]);
				done = true;
			}
		}

		for (short i = 0; i < wpl; i++)
            weightProb[i] = (short)NULL;

		wpl = 0;

		//weighted probability distribution
		for (short i = 0; i < POP; i++) {
			short w = getWeight(population[i]);
			for (short j = 0; j<w; j++)
				weightProb[wpl++] = i; //fill array with member number w times
		}

		//reproduce
		for (short i = 0; i < POP; i += 2){
			short par1 = weightProb[getRand(wpl)];
			short par2 = weightProb[getRand(wpl)];
			short split = getRand(SIZE);
			//crossover
			for (short j = 0; j<split; j++){
				children[i][j] = population[par1][j];
				children[i + 1][j] = population[par2][j];
			}
			for (short j = split; j<SIZE; j++){
				children[i][j] = population[par2][j];
				children[i + 1][j] = population[par1][j];
			}
			//mutation
			if (getRand(1000000) <= mutProb * 1000000){
				short child = getRand(2);
				if (child == 0) children[i][getRand(SIZE)] = getRand(SIZE);
				else children[i + 1][getRand(SIZE)] = getRand(SIZE);
			}
		}

		for (short i = 0; i<POP; i++)
            for (short j = 0; j<SIZE; j++)
                population[i][j] = children[i][j];

		wpl = 0;
	}
}

void main() {

	srand(time(0));
	geneticAlgorithm();
	_getch();

}