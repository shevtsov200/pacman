#pragma once
#include <SFML\Graphics.hpp>
#include "GameConstants.h"
#include "Maze.h"
class Character : public sf::Drawable, public sf::Transformable
{
public:
	// направления движения (Вверх, Налево, Вниз и никуда)
	enum directionStates {UP, LEFT, DOWN, RIGHT, NOWHERE};
	Character();
	// Отрисовать персонажа
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	// Подвинуть персонажа
	void move(float dx, float dy);
	// Подвинуть вверх, влево, вниз или вправо
	void moveUp();
	void moveLeft();
	void moveDown();
	void moveRight();
	// Остановить
	void stop();
	// Обновить персонажа
	virtual void update(sf::Clock clock);
	// Перестать отрисовывать персонажа
	void hide();
	// Начать отрисовывать персонажа
	void makeVisible();
	// Проверить столкновение со стенами
	void checkWallCollisions(IntMatrix &map, int dim1, int dim2);
	// Перевести координаты в пикселях в координаты тайлов
	sf::Vector2i pixelsToIndexes(sf::Vector2f position, sf::Vector2f dr);
	// Перевести координаты тайлов в координаты в пикселях
	static sf::Vector2f tileToPixels(sf::Vector2i tilePosition);
	// Вернуть прямоугольник для проверки коллизий
	sf::RectangleShape getCollisionBox() const;
	// Вернуть направление движения
	directionStates getMovingState() const;
	// Вернуть свободно ли вверху, слева, внизуи справа
	bool getIsUpFree() const;
	bool getIsLeftFree() const;
	bool getIsDownFree() const;
	bool getIsRightFree()const;
	// Вернуть скорость
	float getSpeed()const;
	// Вернуть, свободно ли в данном направлении
	bool getIsFree(int direction)const;
	// Вернуть позицию в пикселях
	sf::Vector2f getPixelPosition()const;
	// Вернуть позицию тайла
	sf::Vector2i getTilePosition()const;
	// Установить таблицу спрайтов
	void setTexture(sf::Texture & spriteSheet);
	// Установить позицию в пикселях
	void setPixelPosition(float x, float y);
	// Установить позицию тайла
	void setTilePosition(sf::Vector2i tilePosition);
	// Инициализировать позицию
	void setInitialPosition();
	// Инициализировать позицию в данном тайле
	void setInitialPosition(sf::Vector2i position);
	// Установить направление движения
	void setMovingState(directionStates directionState);
	// Установить, свободно ли вверху, слева, внизу или справа
	void setIsUpFree(bool isValidPath);
	void setIsLeftFree(bool isValidPath);
	void setIsDownFree(bool isValidPath);
	void setIsRightFree(bool isValidPath);

protected:
	// Направление движения
	directionStates m_movingState;
	// Свободно ли в направлении
	bool m_isUpFree, m_isDownFree, m_isRightFree, m_isLeftFree, m_isVisible;
	// Позиция в тайлах, прошлая позиция в тайлах, проверяемый тайл и позиция спауна
	sf::Vector2i m_tilePosition, m_checkTile, m_spawnPosition;
	// Позиция в пикселях
	sf::Vector2f m_pixelPosition;
	// Спрайт персонажа
	sf::Sprite m_sprite;
	// Таблица спрайтов
	sf::Texture m_spriteSheet;
	// Прямоугольник для столкновений
	sf::RectangleShape m_collisionBox;
	// Скорость, время прошлого кадра
	float m_speed, m_lastFrameTime;
	// Координаты кадра, номер кадра
	int m_frameX, m_frameY, m_frameIndex;
private:
	// Перевести координату в пикселях в координату тайлов
	static int pixelToIndex(float x, float dx);
};