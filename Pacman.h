#pragma once
#include <SFML\Graphics.hpp>
#include "GameConstants.h"
#include "Character.h"

class Pacman : public Character
{
public: 
	Pacman();
	// Изменить направление
	void changeDirection();
	// Обновить пакмана
	void update(sf::Clock clock);
	// Убить пакмана
	void die();
	// Отреспаунить пакмана
	void respawn();
	// Проиграть анимацию движения
	void playAnimation(sf::Clock clock);
	// Проиграть анимацию смерти
	bool playDeathAnimation(sf::Clock clock);
private:
	bool isAlive;
};
