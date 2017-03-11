#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include "Tour.h"

#define TEMPERATURE 10000
#define COOLRATE 0.003

//get acceptance probability of change
static double acceptanceProbability(int energy, int newEnergy, double temperature) {
	if (newEnergy < energy) {
		return 1.0;
	}
	return exp((energy - newEnergy) / temperature);
}

//get city list randomly
void RandomTour(City a[]) {
	int index, i;
	srand(time(NULL));
	for (i = CITY_MAX - 1; i > 0; i--) {
		index = rand() % i;
		SwapCity(a + i, a + index);
	}
}

//some point uesd to test
void InitDefault(City* map) {
	InitCityWithPoint(map + 0, 60, 200);
	InitCityWithPoint(map + 1, 180, 200);
	InitCityWithPoint(map + 2, 80, 180);
	InitCityWithPoint(map + 3, 140, 180);
	InitCityWithPoint(map + 4, 20, 160);
	InitCityWithPoint(map + 5, 100, 160);
	InitCityWithPoint(map + 6, 200, 160);
	InitCityWithPoint(map + 7, 140, 140);
	InitCityWithPoint(map + 8, 40, 120);
	InitCityWithPoint(map + 9, 100, 120);
	InitCityWithPoint(map + 10, 180, 100);
	InitCityWithPoint(map + 11, 60, 80);
	InitCityWithPoint(map + 12, 120, 80);
	InitCityWithPoint(map + 13, 180, 60);
	InitCityWithPoint(map + 14, 20, 40);
	InitCityWithPoint(map + 15, 100, 40);
	InitCityWithPoint(map + 16, 200, 40);
	InitCityWithPoint(map + 17, 20, 20);
	InitCityWithPoint(map + 18, 60, 20);
	InitCityWithPoint(map + 19, 160, 20);
}

//initial map of first tour
City* InitMap() {
	int cityIndex = 0;
	City* map = (City *)malloc(sizeof(City) * CITY_MAX);
	for (cityIndex = 0; cityIndex < CITY_MAX; cityIndex++) {
		// InitCity(map + cityIndex);
		InitDefault(map);
	}
	RandomTour(map);
	return map;
}

//do simulated annealing
static Tour* SA(FILE* file) {
	double temperature = TEMPERATURE;
	double coolRate = COOLRATE;
	Tour* best;
	Tour* currentSolution;
	Tour* newSolution;
	int randomCityIndex1, randomCityIndex2;
	int currentEnergy, neighbourEnergy;

	//initial configuration
	currentSolution = InitTourWithMap(InitMap());
	SetDistance(currentSolution);
	printf("Initial solution distance: %d\n", currentSolution->distance);
	fprintf(file, "Initial solution distance: %d\n", currentSolution->distance);

	//use current solution to be best solution
	best = InitTour();
	CopyTour(best, currentSolution);
	SetDistance(best);

	while (temperature > 1) {
		newSolution = InitTour();
		CopyTour(newSolution, currentSolution);
		//swap random city on current tour
		srand((unsigned)(temperature*100000) % 100);	//need real random function!!!! better random function can improve result!
		randomCityIndex1 = rand() % 20;
		randomCityIndex2 = rand() % 20;
		SwapCity(newSolution->tour + randomCityIndex1, newSolution->tour + randomCityIndex2);
		SetDistance(newSolution);
		//calculate energy
		currentEnergy = currentSolution->distance;
		neighbourEnergy = newSolution->distance;
		fprintf(file, "%d %d\n", currentEnergy, neighbourEnergy);
		//accept new configuration by probability
		if (acceptanceProbability(currentEnergy, neighbourEnergy, temperature) > ((double)rand() / RAND_MAX)) {
			CopyTour(currentSolution, newSolution);
			currentSolution->distance = 0;
			SetDistance(currentSolution);
		}
		//check if new solution is best from now
		if (currentSolution->distance < best->distance) {
			CopyTour(best, currentSolution);
			best->distance = 0;
			SetDistance(best);
		}
		//annealing
		temperature *= (1 - coolRate);
		Free(newSolution);
	}
	Free(currentSolution);
	return best;
}

int main() {
	FILE* file = fopen("C:\\Users\\AMXPC\\Desktop\\a.txt", "w");
	Tour* best;
	best = SA(file);
	printf("Final solution distance: %d\n", best->distance);
	fprintf(file, "Final solution distance: %d\n", best->distance);
	Free(best);
	system("pause");
	return 0;
}
