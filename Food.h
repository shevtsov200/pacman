#pragma once
#include "SFML/Graphics.hpp"
#include "GameConstants.h"
class Food : public sf::Drawable, public sf::Transformable
{
public:
	// Состояние еды
	enum states { PRESENT, // есть
				  DEVOURED // съеденная
				};

	Food();
	// Загрузить таблицу спрайтов
	void setTexture(sf::Texture &spriteSheet);
	// Отрисовать еду
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	// Возвратить состояние еды
	int getState();
	// Возвратить прямоугольник еды для проверки столкновений
	sf::FloatRect getCollisionRectangle();
	// Установить позицию еды
	void setPosition(sf::Vector2f position);
	// Установить состояние еды 
	void setState(states state);

private:
	sf::Sprite m_sprite;
	states m_state;
};