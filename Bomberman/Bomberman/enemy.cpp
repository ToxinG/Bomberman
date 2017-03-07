#include <SFML\Graphics.hpp>
#include "entity.h"
#include "enemy.h"
#include "map.h"

Enemy::Enemy(sf::Image &image, float X, float Y, int W, int H, sf::String Name, int Health) : Entity(image, X, Y, W, H, Name, Health) {
	speedMultiplier = 2;
	speed = DEFAULT_SPEED * speedMultiplier;
	lastDirChangeTime = 0;
}

void Enemy::control() {
	int dir = rand() % 4;
	switch (dir) {
	case 0:
		state = up;
		break;
	case 1:
		state = right;
		break;
	case 2:
		state = down;
		break;
	case 3:
		state = left;
		break;
	}
}

void Enemy::update(float time, float allTime) {
	if (allTime - lastDirChangeTime > 10) {
		lastDirChangeTime = allTime;
		if (((int)ceil(x + TILE_SIZE) % (TILE_SIZE * 2) <= 4 && (int)ceil(y + TILE_SIZE) % (TILE_SIZE * 2) <= 4 && 
			(int)floor(x + TILE_SIZE) % (TILE_SIZE * 2) <= 4 && (int)floor(y + TILE_SIZE) % (TILE_SIZE * 2) <= 4)
			|| (vx == 0 && vy == 0)) {
			control();

		}
	}
	switch (state) {
	case right:
		vx = speed;
		vy = 0;
		break;
	case up:
		vy = -speed;
		vx = 0;
		break;
	case left:
		vx = -speed;
		vy = 0;
		break;
	case down:
		vy = speed;
		vx = 0;
		break;
	}
	x += vx * (time > DELTA_TIME ? DELTA_TIME : time);
	checkCollisionWithMap(vx, 0);
	y += vy * (time > DELTA_TIME ? DELTA_TIME : time);
	checkCollisionWithMap(0, vy);
	sprite.setPosition(x + w / 2, y + h / 2);
}