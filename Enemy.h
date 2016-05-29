#pragma once
#include <SFML\Graphics.hpp>
#include "Character.h"
class Enemy : public Character
{
public:
	Enemy();
	// Изменить направление движения
	void changeDirection();
	// Изменить направление движения на горизонтальное
	void changeHorizontalDirection();
	// Изменить направление движения на вертикальное
	void changeVerticalDirection();
	// Обновить врага
	void update();
	// Изменить спрайт врага в соответствии с направлением
	void updateSprite();
	// Вернуть цель
	sf::Vector2i getTarget();
	// Установить имя врага
	void setName(std::string name);
	// Установить цель врага
	void setTarget(sf::Vector2i target);
	// Установить цель врага в зависимости от направления
	void setTarget(sf::Vector2i target, directionStates direction);
	// Установить цель Блинки
	void setBlinkyTarget(sf::Vector2i target);
	// Установить цель Пинки
	void setPinkyTarget(sf::Vector2i target, directionStates direction);
	// Установить цель Инки
	void setInkyTarget(sf::Vector2i target, directionStates direction);
	// Установить цель Клайда
	void setClydeTarget(sf::Vector2i target);
protected:
	// Имя призрака
	std::string m_name;
	// Цель
	sf::Vector2i m_target;
	// Смещение кадра для выбора спрайта призрака
	int m_frameOffsetY;
};
