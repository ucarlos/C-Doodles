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

#include <list>
#include <vector>

enum class Tile_Char {blank = 0, fruit, snake };

const char ch_blank = '-';
const char ch_fruit = '$';
const char ch_snake = '@';

class Tile {
public:
	Tile() =default;
	enum Tile_Char get_tile_character() const { return character; }
	void set_tile_character(enum Tile_Char &t) { character = t; }
	void clear_tile() { character = Tile_Char::blank; }
private:
	enum Tile_Char character{Tile_Char::blank};
	
};

class Snake_Node {
public:
	Snake_Node() =default;
	
private:
	Tile *pointer;
};

class Snake {
public:
	Snake() =default;
	
private:
	std::vector<Snake_Node> list;
};



#endif
