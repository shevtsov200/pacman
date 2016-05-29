#pragma once
#include <vector>
#include <iostream>
#include <SFML\Graphics.hpp>
#include "GameConstants.h"
#include "Food.h"
class Maze : public sf::Drawable, sf::Transformable
{
public:
	// Варианты тайлов
	enum tile { SPACE, // пусто
				FOOD, // еда
				WALL // стена
			}; 
	Maze();
	// Загрузить текстуру лабиринта
	void setTexture(sf::Texture &spriteSheet);
	// Отрисовать лабиринт
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	// Построить матрицу тайлов
	void buildMapMatrix(int dim1, int dim2, std::string mapName);
	// Поставить стены там, где стена в матрице тайлов
	void placeWalls(sf::RectangleShape *walls, int dim1, int dim2);
	// Разместить еду там, где еда в матрице тайлов
	void placeFood(FoodMatrix &food, int dim1, int dim2);
	// Вернуть матрицу тайлов
	IntMatrix &getMazeVector();
	// Проверяет, есть ли стена на данном тайле
	bool isItWall(sf::Vector2i wallPosition) const;
private:
	// Матрица тайлов
	IntMatrix m_tiles;
	// Спрайт лабиринта
	sf::Sprite m_mazeSprite;
	// Таблица спрайтов
	sf::Texture m_spriteSheet;
};