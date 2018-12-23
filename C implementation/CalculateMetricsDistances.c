
# include <math.h>
#include "viterbi_declarations.h"



void CalculateMetricsDistances(float metric[2 * ROWS][MSG_SIZE], float distance[ROWS][MSG_SIZE + 1],
		unsigned char t, float const inputs[4][MSG_SIZE])
{
	short int  i;
	float temp1, temp2;

	// The function "CalculateMetricsDistances" creates trellis and computes the branch metrics
	// and the state metrics and performs Add-Compare- Select (ACS) operation as described in
	// paper "A New Architecture for the Fast Viterbi Algorithm", Inkyu Lee, Jeff L. Sonntag

	for (i = 0; i < MSG_SIZE; ++i) {

		temp1 = abs(-1 - inputs[t][i]);
		temp2 = abs(+1 - inputs[t][i]);

		metric[0][i] = temp1;	// Metric for transition from state 00 to 00
		metric[1][i] = temp2;	// Metric for transition from state 00 to 01
		metric[2][i] = temp1;	// Metric for transition from state 10 to 00
		metric[3][i] = temp2;	// Metric for transition from state 10 to 01
		metric[4][i] = temp1;	// Metric for transition from state 01 to 11
		metric[5][i] = temp2;	// Metric for transition from state 01 to 10
		metric[6][i] = temp1;	// Metric for transition from state 11 to 11
		metric[7][i] = temp2;	// Metric for transition from state 11 to 10


		// Find the minimum previous state metric for states sharing the same starting states
		temp1 = fmin(distance[0][i] , distance[2][i]);
		temp2 = fmin(distance[3][i], distance[1][i]);
		distance[0][i + 1] = temp1 + metric[0][i]; // Minimum distance to reach state 00 at time i, state metric for 00 at next stage
		distance[1][i + 1] = temp1 + metric[1][i]; // Minimum distance to reach state 01 at time i, state metric for 01 at next stage
		distance[2][i + 1] = temp2 + metric[5][i]; // Minimum distance to reach state 10 at time i, state metric for 10 at next stage
		distance[3][i + 1] = temp2 + metric[6][i]; // Minimum distance to reach state 11 at time i, state metric for 11 at next stage
	}

}


