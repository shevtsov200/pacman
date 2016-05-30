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
	// ���������� �������
	void processEvent(sf::Event event);
	// �������� ������� �������
	void update(sf::Clock clock);
	// ���������
	void draw(sf::RenderTarget & target);
	// �������, ����������� �� ����
	bool getIsGameOver();

private:
	// ������� ��������� � �������� � ���������� ������
	int pixelsToIndex(float x);
	// ���������� ��������.
	void resolveCollision();
	// ���������� �������� ����� �����������
	void checkCharactersCollision(Pacman &pacman, Enemy &enemy);
	// ��������� ��������, ����� ������ ����
	void onPacmanDeath();
	// ������������ ������� � ���������
	void respawn();
	// ������� ����
	void endGame();

	// ���� �� ������, ���� �� �������������� � ����������� �� ����
	bool m_isPacmanDead, m_isRespawn, m_gameOver;
	// ������� ��������
	sf::Texture m_spriteSheet;
	// ��������
	Maze m_maze;
	// ������
	Pacman m_pacman;
	// ����� ���������
	sf::RectangleShape m_walls[GameConstants::MAZE_HEIGHT][GameConstants::MAZE_WIDTH];
	// ������� ���
	FoodMatrix m_food;
	// ��������
	std::vector<Enemy> ghosts;
	// ������ �������
	sf::Sprite m_lifeSprite;
	// ����, �������
	int m_score, m_lives;
	// ����� �����
	sf::Font font;
	// ����� �����
	sf::Text m_scoreString;
	// �����
	sf::SoundBuffer m_introBuffer;
	sf::SoundBuffer m_deathBuffer;
	sf::SoundBuffer m_chompBuffer;
	sf::Sound m_introSound;
	sf::Sound m_deathSound;
	sf::Sound m_chompSound;
};