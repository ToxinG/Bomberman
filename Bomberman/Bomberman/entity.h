#ifndef BOMBERMAN_ENTITY_H
#define BOMBERMAN_ENTITY_H

#include <SFML\Graphics.hpp>
#include "map.h"

class Entity {
protected:
	float x, y, vx, vy, speed, moveTimer, speedMultiplier, currentFrame;
	int w, h, health, onBombX, onBombY;
	bool life, onBomb;
	sf::Texture texture;
	sf::String name;
	sf::Sprite sprite;

	const float DEFAULT_SPEED = 0.1;

	// does not allow entities to go through walls and bombs
	void checkCollisionWithMap(float Vx, float Vy);

public:

	enum { left, right, up, down, stay, bomb, dead } state;

	Entity(sf::Image &image, float X, float Y, int W, int H, sf::String Name, int Health = 100);

	// returns a rectangle occupied by entity's sprite
	sf::FloatRect getRect();

	// returns speed multiplier =/
	float getSpeedMultiplier();

	// returns x-coordinate
	// in pixels
	float getX();

	// returns y-coordinate
	// in pixels
	float getY();

	// returns width
	// in pixels
	int getW();

	// returns height
	// in pixels
	int getH();

	// returns "Current Frame", number used to control animation, defines what rectangle of a tileset to show
	// tileset - kind of a table of images where each image shows certain state of an entity or whatever
	float getCurrentFrame();

	// returns sprite, an SFML feature used to work with images (tilesets, for example)
	// when we see an entity in the game we actually see its sprite
	sf::Sprite getSprite();

	// sets speed multiplier =/
	void setSpeedMultiplier(float sm);

	// sets current frame =/
	void setCurrentFrame(float cf);
};

#endif