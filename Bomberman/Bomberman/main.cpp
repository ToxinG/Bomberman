#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <ctime>
#include <cmath>
#include "map.h"
#include "bomb.h"
#include "entity.h"
#include "enemy.h"
#include "hero.h"

int main() {
	srand(time(0));

	sf::RenderWindow window(sf::VideoMode(WIDTH_MAP * TILE_SIZE, HEIGHT_MAP * TILE_SIZE), "Bomberman");

	sf::Image map_image;
	map_image.loadFromFile("images/map_tiles.png");
	sf::Texture map;
	map.loadFromImage(map_image);
	sf::Sprite s_map;
	s_map.setTexture(map);

	sf::Image heroWhiteImage;
	heroWhiteImage.loadFromFile("images/tileset_white.png");
	heroWhiteImage.createMaskFromColor(sf::Color(64, 144, 56));

	sf::Image heroBlackImage;
	heroBlackImage.loadFromFile("images/tileset_black.png");
	heroBlackImage.createMaskFromColor(sf::Color(64, 144, 56));

	sf::Image enemyImage;
	enemyImage.loadFromFile("images/enemy_tiles.png");
	enemyImage.createMaskFromColor(sf::Color(64, 144, 56));

	std::list<Hero*> heroes;
	std::list<Hero*>::iterator it_heroes;

	std::list<Bomb*> bombs;
	std::list<Bomb*>::iterator it_bombs;

	std::list<Enemy*> enemies;
	std::list<Enemy*>::iterator it_enemies;

	// creating and setting heroes
	Hero* heroWhite = new Hero(heroWhiteImage, 37, TILE_SIZE, 17, 25, Hero::wasd, sf::String("Player1"));
	heroes.push_back(heroWhite);
	Hero* heroBlack = new Hero(heroBlackImage, 869, 544, 17, 25, Hero::arrows, sf::String("Player2"));
	heroes.push_back(heroBlack);

	// creating and setting enemies
	Enemy* enemy1 = new Enemy(enemyImage, 354, 34, 28, 28, sf::String("Enemy1"));
	enemies.push_back(enemy1);
	Enemy* enemy2 = new Enemy(enemyImage, 418, 34, 28, 28, sf::String("Enemy2"));
	enemies.push_back(enemy2);
	Enemy* enemy3 = new Enemy(enemyImage, 226, 418, 28, 28, sf::String("Enemy3"));
	enemies.push_back(enemy3);
	Enemy* enemy4 = new Enemy(enemyImage, 674, 418, 28, 28, sf::String("Enemy4"));
	enemies.push_back(enemy4);

	float allTime = 0;
	sf::Clock clock;

	while (window.isOpen()) {
		float time = clock.getElapsedTime().asMilliseconds();
		allTime += time;
		clock.restart();

		//	std::cout << time << "\n";

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		} 

		for (it_enemies = enemies.begin(); it_enemies != enemies.end(); it_enemies++) {
			(*it_enemies)->update(time, allTime);
		}

		for (it_heroes = heroes.begin(); it_heroes != heroes.end(); it_heroes++) {
			(*it_heroes)->setCurrentFrame((*it_heroes)->update(time));
			if ((*it_heroes)->state == (*it_heroes)->bomb) {
				if ((*it_heroes)->getLastBombTime() + (*it_heroes)->getBombCooldown() < allTime &&
					TileMap[(int)(((*it_heroes)->getY() + (*it_heroes)->getH() / 2) / TILE_SIZE)][(int)(((*it_heroes)->getX() + (*it_heroes)->getW() / 2) / TILE_SIZE)] == ' ') {
					bombs.push_back(new Bomb(allTime, ((*it_heroes)->getX() + (*it_heroes)->getW() / 2) / TILE_SIZE, ((*it_heroes)->getY() + (*it_heroes)->getH() / 2) / TILE_SIZE, (*it_heroes)->getBombRange()));
					(*it_heroes)->setLastBombTime(allTime);
				}
			}

			for (it_enemies = enemies.begin(); it_enemies != enemies.end(); it_enemies++) {
				if ((*it_enemies)->getRect().intersects((*it_heroes)->getRect()))
					(*it_heroes)->state = (*it_heroes)->dead;
			}
		}

		// checking if explosions should be set or removed
		for (it_bombs = bombs.begin(); it_bombs != bombs.end();) {
			if ((*it_bombs)->getSpawnTime() + (*it_bombs)->getDuration() < allTime) {
				// removing explosions
				if ((*it_bombs)->getSpawnTime() + (*it_bombs)->getDuration() + 200 < allTime) {
					TileMap[(*it_bombs)->getY()][(*it_bombs)->getX()] = ' ';
					for (int i = 1; i <= (*it_bombs)->getRange(); i++) {
						if (TileMap[(*it_bombs)->getY()][(*it_bombs)->getX() + i] == '-')
							TileMap[(*it_bombs)->getY()][(*it_bombs)->getX() + i] = ' ';
						else if (TileMap[(*it_bombs)->getY()][(*it_bombs)->getX() + i] == 'b') {
							TileMap[(*it_bombs)->getY()][(*it_bombs)->getX() + i] = ' ';
							break;
						}
						else
							break;
					}
					for (int i = 1; i <= (*it_bombs)->getRange(); i++) {
						if (TileMap[(*it_bombs)->getY()][(*it_bombs)->getX() - i] == '-')
							TileMap[(*it_bombs)->getY()][(*it_bombs)->getX() - i] = ' ';
						else if (TileMap[(*it_bombs)->getY()][(*it_bombs)->getX() - i] == 'b') {
							TileMap[(*it_bombs)->getY()][(*it_bombs)->getX() - i] = ' ';
							break;
						}
						else
							break;
					}
					for (int i = 1; i <= (*it_bombs)->getRange(); i++) {
						if (TileMap[(*it_bombs)->getY() + i][(*it_bombs)->getX()] == '|')
							TileMap[(*it_bombs)->getY() + i][(*it_bombs)->getX()] = ' ';
						else if (TileMap[(*it_bombs)->getY() + i][(*it_bombs)->getX()] == 'b') {
							TileMap[(*it_bombs)->getY() + i][(*it_bombs)->getX()] = ' ';
							break;
						}
						else
							break;
					}
					for (int i = 1; i <= (*it_bombs)->getRange(); i++) {
						if (TileMap[(*it_bombs)->getY() - i][(*it_bombs)->getX()] == '|')
							TileMap[(*it_bombs)->getY() - i][(*it_bombs)->getX()] = ' ';
						else if (TileMap[(*it_bombs)->getY() - i][(*it_bombs)->getX()] == 'b') {
							TileMap[(*it_bombs)->getY() - i][(*it_bombs)->getX()] = ' ';
							break;
						}
						else
							break;
					}
				//	collisionMapHero[(*it_bombs)->getY()][(*it_bombs)->getX()] = false;
				//	collisionMapEnemy[(*it_bombs)->getY()][(*it_bombs)->getX()] = false;
					it_bombs = bombs.erase(it_bombs);
				} else {
					// setting explosions
					TileMap[(*it_bombs)->getY()][(*it_bombs)->getX()] = '+';
					for (int i = 1; i <= (*it_bombs)->getRange(); i++)
						if (TileMap[(*it_bombs)->getY()][(*it_bombs)->getX() + i] == ' ')
							TileMap[(*it_bombs)->getY()][(*it_bombs)->getX() + i] = '-';
						else
							break;
					for (int i = 1; i <= (*it_bombs)->getRange(); i++)
						if (TileMap[(*it_bombs)->getY()][(*it_bombs)->getX() - i] == ' ')
							TileMap[(*it_bombs)->getY()][(*it_bombs)->getX() - i] = '-';
						else
							break;
					for (int i = 1; i <= (*it_bombs)->getRange(); i++)
						if (TileMap[(*it_bombs)->getY() + i][(*it_bombs)->getX()] == ' ')
							TileMap[(*it_bombs)->getY() + i][(*it_bombs)->getX()] = '|';
						else
							break;
					for (int i = 1; i <= (*it_bombs)->getRange(); i++)
						if (TileMap[(*it_bombs)->getY() - i][(*it_bombs)->getX()] == ' ')
							TileMap[(*it_bombs)->getY() - i][(*it_bombs)->getX()] = '|';
						else
							break;
					it_bombs++;
				}

			} else {
				it_bombs++;
			}
		}

		// deleting dead enemies
		for (it_enemies = enemies.begin(); it_enemies != enemies.end();) {
			if ((*it_enemies)->state == (*it_enemies)->dead)
				it_enemies = enemies.erase(it_enemies);
			else
				it_enemies++;
		}

		
/*		for (it_heroes = heroes.begin(); it_heroes != heroes.end(); it_heroes++) {
			for (it_bombs = bombs.begin(); it_bombs != bombs.end(); it_bombs++) {
				if ((*it_bombs)->wasLeft == false && !(*it_bombs)->getRect().intersects((*it_heroes)->getRect())) {
					(*it_bombs)->wasLeft = true;
					collisionMapHero[(*it_bombs)->getY()][(*it_bombs)->getX()] = true;
				}
			}
		}
		*/

		window.clear();

		//drawing map
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == '|') s_map.setTextureRect(sf::IntRect(TILE_SIZE * 6, TILE_SIZE * 0, TILE_SIZE * 1, TILE_SIZE * 1));
				if (TileMap[i][j] == '-') s_map.setTextureRect(sf::IntRect(TILE_SIZE * 5, TILE_SIZE * 0, TILE_SIZE * 1, TILE_SIZE * 1));
				if (TileMap[i][j] == '+') s_map.setTextureRect(sf::IntRect(TILE_SIZE * 4, TILE_SIZE * 0, TILE_SIZE * 1, TILE_SIZE * 1));
				if (TileMap[i][j] == '*') s_map.setTextureRect(sf::IntRect(TILE_SIZE * 3, TILE_SIZE * 0, TILE_SIZE * 1, TILE_SIZE * 1));
				if (TileMap[i][j] == ' ') s_map.setTextureRect(sf::IntRect(TILE_SIZE * 2, TILE_SIZE * 0, TILE_SIZE * 1, TILE_SIZE * 1));
				if (TileMap[i][j] == 'b') s_map.setTextureRect(sf::IntRect(TILE_SIZE * 1, TILE_SIZE * 0, TILE_SIZE * 1, TILE_SIZE * 1));
				if (TileMap[i][j] == '0') s_map.setTextureRect(sf::IntRect(TILE_SIZE * 0, TILE_SIZE * 0, TILE_SIZE * 1, TILE_SIZE * 1));

				s_map.setPosition(j * TILE_SIZE, i * TILE_SIZE);
				window.draw(s_map);
			}

		// drawing heroes
		for (it_heroes = heroes.begin(); it_heroes != heroes.end(); it_heroes++) {
			window.draw((*it_heroes)->getSprite());
		}
		// drawing enemies
		for (it_enemies = enemies.begin(); it_enemies != enemies.end(); it_enemies++) {
				window.draw((*it_enemies)->getSprite());
		}
		window.display();
	}

	return 0;
}