
#include "viterbi_declarations.h"

void FindPreviousStates(unsigned char curr_state, float distance[ROWS][MSG_SIZE + 1],
		short int loop_start, unsigned char decoded_message[ROWS][MSG_SIZE], unsigned char t)
{


	// The function "FindPreviousStates" performs traceback in trellis and decodes the message starting from
    //	the last state of trellis with minimum state metric

	unsigned char prev_state;
	short int i;


   // Perform traceback for trellis starting from the last state with minimum state metric
	for (i = loop_start; i >= 0; --i) {

			if(curr_state == 0 || curr_state == 1) {

					if (distance[0][i] <= distance[2][i])

						prev_state = 0;

					else

						prev_state = 2;

					if (curr_state == 0)

						decoded_message[t][i] = 0;

					else

						decoded_message[t][i] = 1;
			}


			else {

					if (distance[1][i] <= distance[3][i])

						prev_state = 1;

					else

						prev_state = 3;

					if (curr_state == 2)

						decoded_message[t][i] = 0;

					else

						decoded_message[t][i] = 1;

			}

   		    curr_state = prev_state;
	}

}
