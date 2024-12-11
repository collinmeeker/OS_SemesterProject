#include "console.h"
#include "keyboard.h"
#include "portmap.h"
#include <stdint.h>
// Collin Meeker
//moved the clear terminal function to the console.c file

void main() {
	
	clear_terminal();

	uint8_t byte;

	while(1) {

    		while ( byte = scan()) {

          		print_character(charmap[byte]);

     		}

	}
}
