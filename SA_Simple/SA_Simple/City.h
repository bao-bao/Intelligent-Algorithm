#pragma once
#include <math.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct City {
	int x;
	int y;
}City;

//initial random city points
void InitCity(City* city) {
	city->x = rand() % 200;
	city->y = rand() % 200;
}
//initial determined city points
void InitCityWithPoint(City* city, int x, int y) {
	city->x = x;
	city->y = y;
}

//calculate diatance bewteen two citys
double distance(City* city_A, City* city_B) {
	int xDistance = abs(city_A->x - city_B->x);
	int yDistance = abs(city_A->y - city_B->y);
	double distance = sqrt((xDistance * xDistance) + (yDistance * yDistance));
	return distance;
}

//swap city
void SwapCity(City* a, City* b) {
	City* temp = (City *)malloc(sizeof(City));
	temp->x = a->x;
	temp->y = a->y;
	a->x = b->x;
	a->y = b->y;
	b->x = temp->x;
	b->y = temp->y;
	free(temp);
}

//copy from an old city
void CopyCity(City* target, City* source) {
	target->x = source->x;
	target->y = source->y;
}