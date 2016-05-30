#pragma once
#include <vector>
#include <cstdlib>
#include <ctime>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "GameConstants.h"
#include "Character.h"
#include "Pacman.h"
#include "Maze.h"
#include "Food.h"
#include "Enemy.h"

class PacmanGame
{
public:
	PacmanGame();
	// Обработать событие
	void processEvent(sf::Event event);
	// Обновить игровые объекты
	void update(sf::Clock clock);
	// Отрисовка
	void draw(sf::RenderTarget & target);
	// Вернуть, закончилась ли игра
	bool getIsGameOver();

private:
	// Перевод координат в пикселях в координаты тайлов
	int pixelsToIndex(float x);
	// Обработать коллизии.
	void resolveCollision();
	// Обработать коллизии между персонажами
	void checkCharactersCollision(Pacman &pacman, Enemy &enemy);
	// Выполнить действия, когда пакман умер
	void onPacmanDeath();
	// Отреспаунить пакмана и призраков
	void respawn();
	// Закрыть игру
	void endGame();

	// Умер ли пакман, надо ли отреспауниться и закончилась ли игра
	bool m_isPacmanDead, m_isRespawn, m_gameOver;
	// Таблица спрайтов
	sf::Texture m_spriteSheet;
	// Лабиринт
	Maze m_maze;
	// Пакман
	Pacman m_pacman;
	// Стены лабиринта
	sf::RectangleShape m_walls[GameConstants::MAZE_HEIGHT][GameConstants::MAZE_WIDTH];
	// Матрица еды
	FoodMatrix m_food;
	// Призраки
	std::vector<Enemy> ghosts;
	// Спрайт попытки
	sf::Sprite m_lifeSprite;
	// Счёт, попытки
	int m_score, m_lives;
	// Шрифт счёта
	sf::Font font;
	// Текст счёта
	sf::Text m_scoreString;
	// Звуки
	sf::SoundBuffer m_introBuffer;
	sf::SoundBuffer m_deathBuffer;
	sf::SoundBuffer m_chompBuffer;
	sf::Sound m_introSound;
	sf::Sound m_deathSound;
	sf::Sound m_chompSound;
};