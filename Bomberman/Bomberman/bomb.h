#ifndef BOMBERMAN_BOMB_H
#define BOMBERMAN_BOMB_H

#include <SFML\Graphics.hpp>

class Bomb {
public:
	Bomb(float pSpawnTime, int pX, int pY, int pRange);

	// returns a rectangle occupied by entity's sprite
	sf::FloatRect getRect();

	// returns x-coordinate in
	// map tiles
	int getX();

	// returns y-coordinate
	// in map tiles
	int getY();

	// returns range of bomb's explosion
	// in map tiles
	int getRange();

	// returns duration of bomb's "life" - time from planting to explosion
	// in milliseconds
	float getDuration();

	// returns time when the bomb was planted
	// in milliseconds
	float getSpawnTime();

private:
	float spawnTime, duration;
	int x, y, range; // coordinates means blocks, not pixels
	bool wasLeft;

};

#endif