#ifndef BOMBERMAN_HERO_H
#define BOMBERMAN_HERO_H

#include <SFML\Graphics.hpp>
#include "entity.h"

class Hero : public Entity {
public:
	enum controlScheme {wasd = 0, arrows} cs;
	Hero(sf::Image &image, float X, float Y, int W, int H, controlScheme pControlScheme, sf::String Name, int pBombRange = 2, int Health = 100);

	// Complex function that updates hero's state and position. It is called in every iteration of game lifecycle. In details it:
	// controls hero's movement and animation according to pressed keys and walls/bombs that the hero meets on their way
	// kills the hero when it is needed
	float update(float time);

	// returns range of bombs planted by the hero
	// in map tiles
	// 2 by defauls
	int getBombRange();

	// returns the last time when the hero planted a bomb
	// in milliseconds
	float getLastBombTime();

	// returns bomb cooldown
	// in milliseconds
	float getBombCooldown();

	// sets the last time when the hero planted a bomb =/
	void setLastBombTime(float lbt);

private:
	bool gameOver;
	int bombRange;
	float lastBombTime = -5000, bombCooldown = 1500;

	void control();
};

#endif