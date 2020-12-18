/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 12/17/2020 at 10:31 PM
 * 
 * Snake.cc
 * 
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <cstdint>
#include <vector>
#include <tuple>
#include "Snake.h"

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


int main(void) {
	const std::vector<Tile> tile_vector{max_rows * max_cols};
	draw_screen(std::cout, tile_vector);
}
