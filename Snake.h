/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 12/17/2020 at 09:14 PM
 * 
 * Snake.h
 * A Small version of Snake using ASCII characters.
 * -----------------------------------------------------------------------------
 */

#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include <list>
#include <cstdint>
#include <vector>
#include <tuple>

enum class Tile_Char {blank = 0, fruit, snake };

const char ch_blank = '-';
const char ch_fruit = '$';
const char ch_snake = '@';

class Tile {
public:
	Tile() =default;
	enum Tile_Char get_tile_character() const { return character; }
	void set_tile_character(const enum Tile_Char t) { character = t; }
	void clear_tile() { character = Tile_Char::blank; }
private:
	enum Tile_Char character{Tile_Char::blank};
	
};


enum class Direction { north = 0, south, east, west };

static std::tuple<Direction, std::int32_t>
create_direction(const Direction dir, const std::int32_t index) {
	return std::make_tuple(dir, index);
}

class Snake_Node {
public:
	Snake_Node() =default;
	const Tile* node_pointer() { return pointer; }
	
	void change_pointer(Tile *new_ptr) {
		// Clear the tile that is pointed by pointer.
		if (this->pointer)
			this->pointer->clear_tile();		   

		// Now set the new pointer and change its tile if it exists.
		this->pointer = new_ptr;

		if (new_ptr)
			this->pointer->set_tile_character(Tile_Char::snake);		
	}
	
private:
	Tile *pointer{nullptr};
};

class Snake {
private:
	std::vector<Snake_Node> list{4};
	std::list<std::tuple<Direction, std::int32_t>> direction_list;


public:
	Snake() =default;	
	void clear_direction_list() { direction_list.clear(); }
	void insert_direction(std::tuple<Direction, std::int32_t> tuple);
	void remove_front_direction();
	void remove_back_direction();
};



// Additional Function declarations
void draw_screen(std::ostream &os, const std::vector<Tile> &tile_vector);

void main_menu();
#endif
