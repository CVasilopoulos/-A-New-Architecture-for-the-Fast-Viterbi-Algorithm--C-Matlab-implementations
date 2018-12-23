#include <stdio.h>
#include "viterbi_declarations.h"

void PrintMessage(unsigned char err, unsigned char decoded_message[ROWS][MSG_SIZE],
		unsigned char const info_bits[ROWS][MSG_SIZE], unsigned char t)

{
	// The function "PrintMessage" checks and prints if the message processed
	// each time is decoded successfully

	short int i;

	for (i = 0; i < MSG_SIZE; ++i) {

		if (decoded_message[t][i] != info_bits[t][i]) {
			err = 1;
			break;
		}
	}

	// Print if decoding was successful or not
	if (err == 0)

		printf("Message %d is decoded successfully!\n", t + 1);

	else

		printf("Message %d isn't decoded successfully!\n", t + 1);


}



