#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include "City.h"
#define CITY_MAX 20

typedef struct Tour {
	City* tour;
	int distance;
}Tour;

void Free(Tour* t) {
	free(t->tour);
	free(t);
}

//initial void tour
Tour* InitTour() {
	Tour* t = (Tour *)malloc(sizeof(Tour));
	int i = 0;
	t->tour = (City*)malloc(sizeof(City) * CITY_MAX);
	for (i = 0; i < CITY_MAX; i++) {
		t->tour[i].x = t->tour[i].y = 0;
	}
	t->distance = 0;
	return t;
}

//initial tour by map
Tour* InitTourWithMap(City* map) {
	Tour* t = (Tour *)malloc(sizeof(Tour));
	t->tour = map;
	t->distance = 0;
	return t;
}

//copy from an old tour
void CopyTour(Tour* target, Tour* source) {
	int i = 0;
	for (i = 0; i < CITY_MAX; i++) {
		target->tour[i].x = source->tour[i].x;
		target->tour[i].y = source->tour[i].y;
	}
}


//calculate tatal distance
int SetDistance(Tour* t) {
	int cityIndex = 0;
	int tourDistance = 0;
	City fromCity, destinationCity;
	if (t->distance == 0) {
		for (cityIndex = 0; cityIndex < CITY_MAX; cityIndex++) {
			CopyCity(&fromCity, t->tour + cityIndex);
			if (cityIndex + 1 < CITY_MAX) {
				CopyCity(&destinationCity, t->tour + cityIndex + 1);
			}
			else {
				CopyCity(&destinationCity, t->tour);
			}
			tourDistance += distance(&fromCity, &destinationCity);
		}
		t->distance = tourDistance;
	}
}