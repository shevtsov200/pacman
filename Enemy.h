#pragma once
#include <SFML\Graphics.hpp>
#include "Character.h"
class Enemy : public Character
{
public:
	Enemy();
	// �������� ����������� ��������
	void changeDirection();
	// �������� �����
	void update();
	// ������� ����
	sf::Vector2i getTarget();
	// ���������� ��� �����
	void setName(std::string name);
	// ���������� ���� �����
	void setTarget(sf::Vector2i target);
	// ���������� ���� ����� � ����������� �� �����������
	void setTarget(sf::Vector2i target, directionStates direction);
	// ���������� ���� ������
	void setBlinkyTarget(sf::Vector2i target);
	// ���������� ���� �����
	void setPinkyTarget(sf::Vector2i target, directionStates direction);
	// ���������� ���� ����
	void setInkyTarget(sf::Vector2i target, directionStates direction);
	// ���������� ���� ������
	void setClydeTarget(sf::Vector2i target);
private:
	// �������� ����������� �������� �� ��������������
	void changeHorizontalDirection();
	// �������� ����������� �������� �� ������������
	void changeVerticalDirection();
	// �������� ������ ����� � ������������ � ������������
	void updateSprite();
	// ��� ��������
	std::string m_name;
	// ����
	sf::Vector2i m_target;
	// �������� ����� ��� ������ ������� ��������
	int m_frameOffsetY;
};
