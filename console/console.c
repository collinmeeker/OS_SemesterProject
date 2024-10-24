#include "../include/console.h"

static int terminal_position = 0;
char* const VGA_MEMORY = (char*) 0xb8000;

void clear_terminal() {
	char* const VGA_BUFFER = (char*) 0xb8000;
	int screen_size = 80 * 25;

	for(int i = 0; i < screen_size; i++) {
		VGA_BUFFER[i * 2] = '\0';
		VGA_BUFFER[i * 2 + 1] = 0x07;
	}

}

void print_character(char c) {
	
	if(c == '\n') {
		int row = terminal_position / VGA_WIDTH;
		row++;
		terminal_position = row * VGA_WIDTH;
	} else {

	VGA_MEMORY[terminal_position * VGA_BYTES_PER_CHARACTER] = c;
	VGA_MEMORY[terminal_position * VGA_BYTES_PER_CHARACTER + 1] = 0x07;

	terminal_position++;
	
	}
}

void print_string(char* str) {
	
	for(int i = 0; str[i] != '\0'; i++) {
		print_character(str[i]);
	}
}

void print_line(char* str) {
	print_string(str);
	print_character('\n');
}
