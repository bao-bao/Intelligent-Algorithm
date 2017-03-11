#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdint.h>

#define TEMPERATURE 10
#define COOLRATE 0.00002


typedef struct Point {
	double x;
	double y;
}Point;

double Schaffer(Point point) {
	double schaffer = 0, temp_square_sum = point.x*point.x + point.y*point.y;
	double numerator, denominator, temp;
	temp = sin(sqrt(temp_square_sum));
	numerator = temp * temp - 0.5;
	temp = 1 + 0.001* temp_square_sum;
	denominator = temp * temp;
	schaffer = 0.5 + (numerator / denominator);
	return schaffer;
}

double Random() {
	double x = rand() * 1.0 / RAND_MAX;
	if (rand() & 1) x *= -1;
//	printf("%lf\n", x);
	return x;
}

Point RandomPoint(static Point* old, double tem) {
	Point ran_point;
	if (old == NULL) {
		ran_point.x = Random() * 10;
		ran_point.y = Random() * 10;
	}
	else {
		ran_point.x = max(min((old->x + min(0.2, (tem*10)) * Random()), 10), -10);
		ran_point.y = max(min((old->y + min(0.2, (tem*10)) * Random()), 10), -10);
	}
//	printf("(%.3lf, %.3lf)\n", ran_point.x, ran_point.y);
	return ran_point;
}

static double acceptanceProbability(double energy, double newEnergy, double temperature) {
	if (newEnergy < energy) {
		return 1.0;
	}
//	printf("%lf\n", exp((energy - newEnergy) / temperature));
	return exp((energy - newEnergy) / temperature/5);
}

Point SA() {
	double temperature = TEMPERATURE;
	double coolRate = COOLRATE;
	Point best, current, neighbour;
	double cur_energy, nei_energy, bes_energy;
	clock_t start, end;
	int i = 0;

	start = clock();
	current = RandomPoint(NULL, temperature);
	cur_energy = Schaffer(current);
	best = current;
	bes_energy = cur_energy;
	printf("Initial:(%lf, %lf)\t%.8lf\n", best.x, best.y, Schaffer(best));

	while (temperature > 1e-10) {
		i++;
		neighbour = RandomPoint(&current, temperature);
		cur_energy = Schaffer(current);
		nei_energy = Schaffer(neighbour);
		if (acceptanceProbability(cur_energy, nei_energy, temperature) > (rand() * 1.0 / RAND_MAX)) {
			current = neighbour;
		}
		if (cur_energy < bes_energy) {
			best = current;
			bes_energy = cur_energy;
		}

		temperature *= (1 - coolRate);
	}
	end = clock();
	printf("Result:\t(%lf, %lf)\t%.8lf\n", best.x, best.y, Schaffer(best));
	printf("Times: %d\t%.3lf s\n\n", i, (double)(end - start) / CLOCKS_PER_SEC);
	return best;
}

int main() {
	char ch[4] = { 0 };
	int i = 0;
	double result = 0, tmp = 0;
	srand(time(NULL));
	while (1) {
		result = 1e99;
		scanf("%s", &ch);
		if (!strcmp(ch, "SA")) {
			for (i = 0; i < 30; i++) {
				tmp = Schaffer(SA());
				result = min(tmp, result);
			}
		}
		if (&ch == "GDT") {
			for (i = 0; i < 30; i++) {
//				result = min(Schaffer(GDT()), result);
			}

		}
		printf("Final Result:\t%.12lf\n",result);
	}
	return 0;
}