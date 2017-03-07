#include <SFML\Graphics.hpp>
#include "entity.h"
#include "hero.h"
#include "map.h"

Hero::Hero(sf::Image &image, float X, float Y, int W, int H, controlScheme pControlScheme, sf::String Name, int pBombRange, int Health) : Entity(image, X, Y, W, H, Name, Health) {
	gameOver = false;
	cs = pControlScheme;
	bombRange = pBombRange;
	state = stay;
	speedMultiplier = 1;
	speed = DEFAULT_SPEED * speedMultiplier;
}

void Hero::control() {
	if (sf::Keyboard::isKeyPressed) {
		if ((cs == arrows && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) || (cs == wasd && sf::Keyboard::isKeyPressed(sf::Keyboard::A))) {
			state = left;
		}
		if ((cs == arrows && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) || (cs == wasd && sf::Keyboard::isKeyPressed(sf::Keyboard::W))) {
			state = up;
		}
		if ((cs == arrows && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) || (cs == wasd && sf::Keyboard::isKeyPressed(sf::Keyboard::D))) {
			state = right;
		}
		if ((cs == arrows && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) || (cs == wasd && sf::Keyboard::isKeyPressed(sf::Keyboard::S))) {
			state = down;
		}
		if ((cs == arrows && sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0)) || (cs == wasd && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))) {
			if (!onBomb) {
				state = bomb;
				onBomb = true;
				onBombX = (int)((x + w / 2) / TILE_SIZE);
				onBombY = (int)((y + h / 2) / TILE_SIZE);
			}
		}
	}
}

float Hero::update(float time) {
	if (gameOver)
		return -1;
	if (state == dead) {
		currentFrame += 0.005 * time;
		if (currentFrame > 6)
			gameOver = true;
		else
			sprite.setTextureRect(sf::IntRect(25 * (int(currentFrame)) + 4, 50, 17, 25));
		return currentFrame;
	}
	state = stay;
	control();
	switch (state) {
		case right:
			vx = speed;
			vy = 0;
			currentFrame += 0.005 * time;
			if (currentFrame > 4) currentFrame -= 4;
			sprite.setTextureRect(sf::IntRect(25 * ((int(currentFrame) % 2) * ((int(currentFrame) + 1) / 2)) + 4, 0, 17, 25));
		break;
		case up:
			vy = -speed;
			vx = 0;
			currentFrame += 0.005 * time;
			if (currentFrame > 4) currentFrame -= 4;
			sprite.setTextureRect(sf::IntRect(25 * ((int(currentFrame) % 2) * ((int(currentFrame) + 1) / 2)) + 4, 25, 17, 25));
		break;
		case left:
			vx = -speed;
			vy = 0;
			currentFrame += 0.005 * time;
			if (currentFrame > 4) currentFrame -= 4;
			sprite.setTextureRect(sf::IntRect(75 + 25 * ((int(currentFrame) % 2) * ((int(currentFrame) + 1) / 2)) + 4, 25, 17, 25));
		break;
		case down:
			vy = speed;
			vx = 0;
			currentFrame += 0.005 * time;
			if (currentFrame > 4) currentFrame -= 4;
			sprite.setTextureRect(sf::IntRect(75 + 25 * ((int(currentFrame) % 2) * ((int(currentFrame) + 1) / 2)) + 4, 0, 17, 25));
		break;
		case stay:
			vx = 0;
			vy = 0;
			currentFrame = 0;
			sprite.setTextureRect(sf::IntRect(80, 0, w, h));
		break;
	}
	x += vx * (time > DELTA_TIME ? DELTA_TIME : time);
	checkCollisionWithMap(vx, 0);
	y += vy * (time > DELTA_TIME ? DELTA_TIME : time);
	checkCollisionWithMap(0, vy);
	if (!getRect().intersects(sf::FloatRect(onBombX * TILE_SIZE, onBombY * TILE_SIZE, TILE_SIZE, TILE_SIZE)))
		onBomb = false;
	sprite.setPosition(x + w / 2, y + h / 2);
	return currentFrame;
}

int Hero::getBombRange() {
	return bombRange;
}

float Hero::getLastBombTime() {
	return lastBombTime;
}

float Hero::getBombCooldown() {
	return bombCooldown;
}

void Hero::setLastBombTime(float lbt) {
	lastBombTime = lbt;
}