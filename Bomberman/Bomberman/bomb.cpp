#include <SFML\Graphics.hpp>
#include "bomb.h"
#include "map.h"

Bomb::Bomb(float pSpawnTime, int pX, int pY, int pRange) {
	duration = 2000;
	wasLeft = false;
	spawnTime = pSpawnTime;
	x = pX;
	y = pY;
	range = pRange;
	TileMap[y][x] = '*';
}

sf::FloatRect Bomb::getRect(){
	return sf::FloatRect(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
}

int Bomb::getX() {
	return x;
}

int Bomb::getY() {
	return y;
}

int Bomb::getRange() {
	return range;
}

float Bomb::getDuration() {
	return duration;
}

float Bomb::getSpawnTime() {
	return spawnTime;
}