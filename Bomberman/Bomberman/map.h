#ifndef BOMBERMAN_MAP_H
#define BOMBERMAN_MAP_H

#include <SFML\Graphics.hpp>
const int HEIGHT_MAP = 19;
const int WIDTH_MAP = 29;
const int TILE_SIZE = 32;
const int DELTA_TIME = 10; // milliseconds

/*
* '0' - base
* 'b' - brick
* ' ' - grass
* '*' - bomb
* '+' - explosion centre
* '-' - explosion horisontal
* '|' - explosion vertical
*/

extern sf::String TileMap[HEIGHT_MAP]; /* = {
	"00000000000000000000000000000",
	"0   b    b         b    b   0",
	"0 0b0b0 0 0b0 0 0b0 0 0b0b0 0",
	"0 bbb       b   b       bbb 0",
	"0b0b0b0 0 0b0 0 0b0 0 0b0b0b0",
	"0 b b        b b        b b 0",
	"0 0 0 0 0 0 0 0 0 0 0 0 0 0 0",
	"0b                         b0",
	"0 0b0 0 0 0b0b0b0b0 0 0 0b0 0",
	"0   bbb     bbbbb     bbb   0",
	"0 0b0 0 0 0b0b0b0b0 0 0 0b0 0",
	"0b                         b0",
	"0 0 0 0 0 0 0 0 0 0 0 0 0 0 0",
	"0 b b        b b        b b 0",
	"0b0b0b0 0 0b0 0 0b0 0 0b0b0b0",
	"0 bbb       b   b       bbb 0",
	"0 0b0b0 0 0b0 0 0b0 0 0b0b0 0",
	"0   b    b         b    b   0",
	"00000000000000000000000000000",
};
*/

#endif