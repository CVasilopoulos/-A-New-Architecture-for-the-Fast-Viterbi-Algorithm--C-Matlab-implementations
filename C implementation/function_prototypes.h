
#ifndef FUNCTION_PROTOTYPES_H_
#define FUNCTION_PROTOTYPES_H_

#include "viterbi_declarations.h"



unsigned char FindLastState(float distance[ROWS][MSG_SIZE + 1]);

void FindPreviousStates(unsigned char curr_state, float distance[ROWS][MSG_SIZE + 1],
		short int loop_start, unsigned char decoded_message[ROWS][MSG_SIZE], unsigned char t);

void CalculateMetricsDistances(float metric[2 * ROWS][MSG_SIZE], float distance[ROWS][MSG_SIZE + 1],
		unsigned char t, float const inputs[ROWS][MSG_SIZE]);

void PrintMessage(unsigned char err, unsigned char decoded_message[ROWS][MSG_SIZE],
		unsigned char const info_bits[ROWS][MSG_SIZE], unsigned char t);



#endif /* FUNCTION_PROTOTYPES_H_ */
