#include "console.h"
#include "portmap.h"
#include <stdint.h>
// Collin Meeker

static VGA_Color terminal_font_color = LIGHT_GRAY;
static VGA_Color terminal_background_color = BLACK;

static int terminal_position = 0;
static char* const VGA_MEMORY = (char*) 0xb8000;

void update_cursor() {
     /** I removed the shift to fix the cursor from lagging behind.
      Not really sure what the logic was for doing that but this fixes it.*/
     uint16_t cursor_position = terminal_position;

     outb(0x3D4, 0x0F);

     outb(0x3D5, (uint8_t) (cursor_position));

     outb(0x3D4, 0x0E);

     outb(0x3D5, (uint8_t) (cursor_position >> 8));

}


void clear_terminal() {
	int screen_size = VGA_WIDTH * VGA_HEIGHT;

	for(int i = 0; i < screen_size; i++) {
		VGA_MEMORY[i * VGA_BYTES_PER_CHARACTER] = '\0';
		VGA_MEMORY[i * VGA_BYTES_PER_CHARACTER + 1] = (terminal_background_color << 4) | terminal_font_color;
	}
	
	terminal_position = 0;
	update_cursor();
}

void print_character(char c) {
	print_character_with_color(c, terminal_background_color, terminal_font_color);
}

void print_character_with_color(char c, VGA_Color bg_color, VGA_Color font_color) {

	if(c == '\n') {
		int row = terminal_position / VGA_WIDTH;
		row++;
		terminal_position = row * VGA_WIDTH;
		
	} else {
	
		VGA_MEMORY[terminal_position * VGA_BYTES_PER_CHARACTER] = c;
		VGA_MEMORY[terminal_position * VGA_BYTES_PER_CHARACTER + 1] = (bg_color << 4) | font_color;

		terminal_position++;
		
	}
	update_cursor();
}



void print_string(char* str) {
	print_string_with_color(str, terminal_background_color, terminal_font_color);
}

void print_string_with_color(char* str, VGA_Color bg_color, VGA_Color font_color) {
	
	for(int i = 0; str[i] != '\0'; i++) {
		print_character_with_color(str[i], bg_color, font_color);
	}
}



void print_line(char* str) {
	print_line_with_color(str, terminal_background_color, terminal_font_color);
}

void print_line_with_color(char* str, VGA_Color bg_color, VGA_Color font_color) {
	print_string_with_color(str, bg_color, font_color);
	print_character_with_color('\n', bg_color, font_color);
}


void set_terminal_font_color(VGA_Color col) {

     terminal_font_color = col;

}

 

void set_terminal_background_color(VGA_Color col) {

     terminal_background_color = col;

}


