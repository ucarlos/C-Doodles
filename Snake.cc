/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 12/17/2020 at 10:31 PM
 * 
 * Snake.cc
 * 
 * -----------------------------------------------------------------------------
 */

#include <cstdlib>
#include <iostream>
#include <cctype>
#include "Snake.h"

const char max_line_cols = 80;
const std::uint32_t max_rows = 20;
const std::uint32_t max_cols = 60;


inline void draw_tile(std::ostream &os, const Tile &tile) {
	auto character = tile.get_tile_character();
	if (character == Tile_Char::blank)
		os << ch_blank;
	else if (character == Tile_Char::fruit)
		os << ch_fruit;
	else
		os << ch_snake;

}

void draw_screen(std::ostream &os, const std::vector<Tile> &tile_vector) {
	// Draw the first character

	for (std::size_t i = 0; i < tile_vector.size(); i++) {
		draw_tile(os, tile_vector.at(i));
		// Append a newline for max_cols
		if (!((i + 1) % max_cols))
			os << std::endl;			
	}
}


inline void dash_line(std::ostream &os) {
	for (char i = 0; i < max_line_cols; i++)
		os << "-";
	os << std::endl;

}

inline void snake_banner(std::ostream &os) {
	os << "  ____              _        " << std::endl
	   << " / ___| _ __   __ _| | _____ " << std::endl
	   << " \\___ \\| '_ \\ / _` | |/ / _ \\" << std::endl
	   << "  ___) | | | | (_| |   <  __/" << std::endl
	   << " |____/|_| |_|\\__,_|_|\\_\\___|" << std::endl;
}


void play_game() {}

void main_menu() {
	dash_line(std::cout);
	snake_banner(std::cout);
	std::cout << "An snake clone by Ulysses Carlos\n";
	dash_line(std::cout);
	
	std::cout << "Please choose an option:\n";
	std::cout << "a) Play Game\n";
	std::cout << "q) Quit\n";
	char user_input;
	std::cin >> user_input;
	user_input = tolower(user_input);

	while (!((user_input == 'a') || (user_input == 'q'))) {
		std::cout << "Invalid input. Try again.\n";
		std::cin >> user_input;
		user_input = tolower(user_input);
	}

	switch (user_input) {
	case 'a':
		play_game();
		break;
	case 'q':
		exit(EXIT_SUCCESS);
	default:
		exit(EXIT_SUCCESS);
	}

}


int main(void) {
	// const std::vector<Tile> tile_vector{max_rows * max_cols};
	// draw_screen(std::cout, tile_vector);
	main_menu();
}
