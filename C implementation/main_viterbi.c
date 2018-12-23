

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#include "viterbi_declarations.h"
#include "function_prototypes.h"


unsigned char const info_bits[ROWS][MSG_SIZE] = {

											  {0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0},
									 	 	  {1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0},
											  {1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0},
											  {0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0}
											};



float const inputs[ROWS][MSG_SIZE] = {

									{-4.6603, 2.3645, -4.1881, 5.1290, -2.3949, 4.4369, 2.5954, 5.7897,
									3.6508, -3.9725, -3.1503, 4.9661, 4.6208, -4.3589, -3.4489, -5.2625,
									4.1029, -4.2269, 3.2083,  -3.9124, -3.8839, 4.0562, 2.9026, -3.4037, -5.2025},

									{3.7385, 2.4024, -4.8758, -3.4647, -5.6109, -3.6842, 4.2594, -5.1139,
									3.6566, -5.3171, 4.3617, 5.9946, -5.4171, -2.9390, -3.7365, 5.3667,
									-3.7328, 4.1144, -6.2369, -4.3799, -3.7813, 5.2040, -4.3240, 3.8373, -3.5690},

									{5.6859, -3.9107, 4.2082, -3.2664, -3.8141, 5.8281, 4.3965, 3.7773,
									3.4448, -2.2193, 3.4111, 5.6402, -3.4105, -3.9524, -2.9227, -5.7180,
									-5.8493, 4.5350, 5.8290, -4.4214, 2.8989, -3.6294, 3.7557, -3.4033, -4.0244},

									{-6.4612, 2.6010, 5.4156, -4.0020, -4.4753, 5.0595, -3.7035, -4.4767,
									4.6358, -4.6346, -3.6278, -5.1393, -3.5853, -5.8942, -4.1861, -4.3771,
									-3.3732, 5.0026, 5.6186, -5.3951, -4.9099, 4.5908, -4.7093, 4.8508, -1.9328}

								  };


int main(void) {

	unsigned char t, err = 0;
	unsigned char state, decoded_message[ROWS][MSG_SIZE];
	float distance[ROWS][MSG_SIZE + 1], metric[2 * ROWS][MSG_SIZE];



	for(t = 0; t < ROWS; ++t) {

		// Initialize state metrics for the 4 states
		distance[0][0] = 0;
		distance[1][0] = 100000;
		distance[2][0] = 100000;
		distance[3][0] = 100000;

		// Calculate branch metrics and state metrics for each state
		CalculateMetricsDistances(metric, distance, t, inputs);

		// Find final state of trellis with minimum state metric
		state = FindLastState(distance);

		// Find previous states and traceback trellis
		FindPreviousStates(state, distance, MSG_SIZE - 1, decoded_message, t);

		// Check and print if message was successfully decoded
		PrintMessage(err, decoded_message, info_bits, t);

	}

	return EXIT_SUCCESS;
}
