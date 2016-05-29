#pragma once
#include "SFML/Graphics.hpp"
#include "GameConstants.h"
class Food : public sf::Drawable, public sf::Transformable
{
public:
	// ��������� ���
	enum states { PRESENT, // ����
				  DEVOURED // ���������
				};

	Food();
	// ��������� ������� ��������
	void setTexture(sf::Texture &spriteSheet);
	// ���������� ���
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	// ���������� ��������� ���
	int getState();
	// ���������� ������������� ��� ��� �������� ������������
	sf::FloatRect getCollisionRectangle();
	// ���������� ������� ���
	void setPosition(sf::Vector2f position);
	// ���������� ��������� ��� 
	void setState(states state);

private:
	sf::Sprite m_sprite;
	states m_state;
};