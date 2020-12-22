/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 12/17/2020 at 10:31 PM
 * 
 * Snake.cc
 * 
 * -----------------------------------------------------------------------------
 */

#include "Snake.h"
#include <cstdlib>
#include <cctype>
#include <unistd.h>
#include <sys/wait.h>
#include <thread>

// Global variables

const char max_line_cols = 80;
const std::uint32_t max_rows = 20;
const std::uint32_t max_cols = 60;

const char frame_rate = 10;

bool is_game_over = false;


//------------------------------------------------------------------------------
// Snake class Definitions
//------------------------------------------------------------------------------

/**
 * Insert a new direction in the direction queue
 * @param tuple A tuple containing a direction and the index when the direction
 *              occurred.
 */
void Snake::insert_direction(std::tuple<Direction, std::int32_t> tuple) {
	if (direction_list.empty()) {
		direction_list.push_back(tuple);
		return;
	}

	// Consecutive directions are not allowed, so prevent them:
	if (std::get<0>(tuple) == std::get<0>(direction_list.back()))
		return;
	else
		direction_list.push_back(tuple);			   	
}



/**
 * Draw an individual title on a specified ostream.
 * @param os ostream to write to
 * @param tile holds the Tile_Char enum that states what type of tile it is
 */

inline void draw_tile(std::ostream &os, const Tile &tile) {
	auto character = tile.get_tile_character();
	if (character == Tile_Char::blank)
		os << ch_blank;
	else if (character == Tile_Char::fruit)
		os << ch_fruit;
	else
		os << ch_snake;

}


/**
 * Draw all tiles onto a ostream
 * @param os The Ostream to write to
 * @param tile_vector Vector containing all tiles used for the game.
 */

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

//------------------------------------------------------------------------------
// Thread functions
//------------------------------------------------------------------------------


void set_screen(std::vector<Tile> &tile_screen, enum Tile_Char tc) {
	for (auto &i : tile_screen)
		i.set_tile_character(tc);
}

/**
 * Handles drawing the screen at a constant framerate.
 * @param os ostream to write to
 * @param tile_vector vector containing all tiles used by the snake game.
 */
void draw_thread(std::ostream &os, std::vector<Tile> &tile_vector) {
	const int32_t wait_time = static_cast<int>(1000000.0 / frame_rate);
	
	// while (!is_game_over) {
	// 	draw_screen(os, tile_vector);
	// 	usleep(wait_time);
	// }


	for (int32_t i = 0; i < frame_rate * 3 ; i++) {
		std::system("clear");
		if (!(i % 3))
			set_screen(tile_vector, Tile_Char::snake);
		else if (i % 3 == 1)
			set_screen(tile_vector, Tile_Char::blank);
		else
			set_screen(tile_vector, Tile_Char::fruit);
		
		draw_screen(os, tile_vector);
		usleep(wait_time);
	}

	os << "Too fast!" << std::endl;
}


/**
 * Function that handles the move thread, which allows for the user to move
 * the snake (using WASD)
 *
 * @param tile_vector vector containing all tiles used by the snake game
 */
void move_thread(std::vector<Tile> &tile_vector) {
	

}



void play_game() {
	std::vector<Tile> tile_vector{max_rows * max_cols};
	// std::thread thread_draw{draw_thread, std::ref(std::cout),
	// 	std::ref(tile_vector)};

	draw_thread(std::cout, tile_vector);
	// thread_draw.join();

	
}

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
	std::vector<Tile> tile_vector{max_rows * max_cols};
	draw_thread(std::cout, tile_vector);
	// draw_screen(std::cout, tile_vector);
	// main_menu();
	
}
