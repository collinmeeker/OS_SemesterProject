#include "./include/console.h"
// Collin Meeker
//moved the clear terminal function to the console.c file

void main() {
	
	clear_terminal();
	print_string("HELLO");
	print_line("WORLD");
	print_string("TODAY");	

	//char* const VGA_BUFFER = (char*) 0xb8000;
	//char* str = "Hello World";

	//for (int i=0; str[i] != '\0'; i++) {
	//	VGA_BUFFER[i*2] = str[i];
	//}
	
	return;
}
