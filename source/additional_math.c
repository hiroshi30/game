#include "additional_math.h"


double tan_sum(double tan_alpha, double tan_beta) {
	return (tan_alpha + tan_beta) / (1 - tan_alpha / tan_beta);
}

double tan_dif(double tan_alpha, double tan_beta) {
	return (tan_alpha - tan_beta) / (1 + tan_alpha / tan_beta);
}