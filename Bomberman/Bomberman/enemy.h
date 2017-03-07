#ifndef BOMBERMAN_ENEMY_H
#define BOMBERMAN_ENEMY_H

#include <SFML\Graphics.hpp>
#include "entity.h"

class Enemy : public Entity {
	// Now the game have the only type of monsters - Chaotic Being. They have no goals in their life, they just wanders on the map.
	// However their touch kills a hero immediately. Just kill them.
	// Or give them a hug - they are really cute-looking (no)
public:
	Enemy(sf::Image &image, float X, float Y, int W, int H, sf::String Name, int Health = 100);

	// Complex function that updates enemy's state and position. It is called in every iteration of game lifecycle. In details it:
	// controls enemy's movement according to direction of movement which changes randomly on "crossing tiles" whith limited frequency
	// kills the enemy when it is needed
	void update(float time, float allTime);

private:
	float lastDirChangeTime;

	void control();
};

#endif