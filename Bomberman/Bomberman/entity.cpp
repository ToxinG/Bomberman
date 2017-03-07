#include <SFML\Graphics.hpp>
#include "entity.h"
#include "map.h"

Entity::Entity(sf::Image &image, float X, float Y, int W, int H, sf::String Name, int Health) {
	x = X;
	y = Y;
	w = W;
	h = H;
	onBomb = false;
	currentFrame = 0;
	health = Health;
	name = Name;
	moveTimer = 0;
	speed = 0;
	vx = 0;
	vy = 0;
	life = true;
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setOrigin(w / 2, h / 2);
}

void Entity::checkCollisionWithMap(float Vx, float Vy) {
	for (int i = y / TILE_SIZE; i < (y + h) / TILE_SIZE; i++)
		for (int j = x / TILE_SIZE; j < (x + w) / TILE_SIZE; j++) {
			if (TileMap[i][j] == '*' && !onBomb) {
				if ((y < i * TILE_SIZE + TILE_SIZE / 2) && (TileMap[i - 1][(int)x / TILE_SIZE] != 'b' && TileMap[i - 1][(int)x / TILE_SIZE] != '0' && TileMap[i - 1][(int)x / TILE_SIZE] != '*'
					&& TileMap[i - 1][(int)(x + w) / TILE_SIZE] != 'b' && TileMap[i - 1][(int)(x + w) / TILE_SIZE] != '0' && TileMap[i - 1][(int)(x + w) / TILE_SIZE] != '*'))
					y = (i - 1) * TILE_SIZE;
				else if ((x < j * TILE_SIZE + TILE_SIZE / 2) && (TileMap[(int)y / TILE_SIZE][j - 1] != 'b' && TileMap[(int)y / TILE_SIZE][j - 1] != '0' && TileMap[(int)y / TILE_SIZE][j - 1] != '*'
					&& TileMap[(int)(y + h) / TILE_SIZE][j - 1] != 'b' && TileMap[(int)(y + h) / TILE_SIZE][j - 1] != '0' && TileMap[(int)(y + h) / TILE_SIZE][j - 1] != '*'))
					x = (j - 1) * TILE_SIZE;
				else if ((y >= i * TILE_SIZE) && (TileMap[i + 1][(int)x / TILE_SIZE] != 'b' && TileMap[i + 1][(int)x / TILE_SIZE] != '0' && TileMap[i + 1][(int)x / TILE_SIZE] != '*'
					&& TileMap[i + 1][(int)(x + w) / TILE_SIZE] != 'b' && TileMap[i + 1][(int)(x + w) / TILE_SIZE] != '0' && TileMap[i + 1][(int)(x + w) / TILE_SIZE] != '*'))
					y = (i + 1) * TILE_SIZE;
				else if ((x >= j * TILE_SIZE) && (TileMap[(int)y / TILE_SIZE][j + 1] != 'b' && TileMap[(int)y / TILE_SIZE][j + 1] != '0' && TileMap[(int)y / TILE_SIZE][j + 1] != '*'
					&& TileMap[(int)(y + h) / TILE_SIZE][j + 1] != 'b' && TileMap[(int)(y + h) / TILE_SIZE][j + 1] != '0' && TileMap[(int)(y + h) / TILE_SIZE][j + 1] != '*'))
					x = (j + 1) * TILE_SIZE;
				else setSpeedMultiplier(0);
			}
			if (TileMap[i][j] == '0' || TileMap[i][j] == 'b' || (TileMap[i][j] == '*' && !(onBomb && onBombX == j && onBombY == i))) {
				if (Vy > 0) {
					y = i * TILE_SIZE - h;
					vy = 0;
				}
				if (Vy < 0) {
					y = i * TILE_SIZE + TILE_SIZE;
					vy = 0;
				}
				if (Vx > 0) {
					x = j * TILE_SIZE - w;
					vx = 0;
				}
				if (Vx < 0) {
					x = j * TILE_SIZE + TILE_SIZE;
					vx = 0;
				}
			}
			if (TileMap[i][j] == '+' || TileMap[i][j] == '-' || TileMap[i][j] == '|') {
				health = 0;
				state = dead;
			}
		}
}

sf::FloatRect Entity::getRect() {
	return sf::FloatRect(x, y, w, h);
}

float Entity::getSpeedMultiplier() {
	return speedMultiplier;
}

float Entity::getX() {
	return x;
}

float Entity::getY() {
	return y;
}

int Entity::getW() {
	return w;
}

int Entity::getH() {
	return h;
}

float Entity::getCurrentFrame() {
	return currentFrame;
}

sf::Sprite Entity::getSprite() {
	return sprite;
}

void Entity::setSpeedMultiplier(float sm) {
	speedMultiplier = sm;
	speed = DEFAULT_SPEED * sm;
}

void Entity::setCurrentFrame(float cf) {
	currentFrame = cf;
}
