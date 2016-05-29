#pragma once
#include <SFML\Graphics.hpp>
#include "GameConstants.h"
#include "Maze.h"
class Character : public sf::Drawable, public sf::Transformable
{
public:
	// направления движения
	enum directionStates {UP, // Вверх
						LEFT, // Налево
						DOWN, // Вниз
						RIGHT, // Направо
						NOWHERE // Никуда
	};

	Character();
	// Отрисовать персонажа
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	// Подвинуть персонажа
	void move(float dx, float dy);
	// Подвинуть вверх
	void moveUp();
	// Подвинуть влево
	void moveLeft();
	// Подвинуть вниз
	void moveDown();
	// Подвинуть вправо
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
	// Перевести координату в пикселях в координату тайлов
	static int pixelToIndex(float x, float dx);
	// Перевести координаты в пикселях в координаты тайлов
	sf::Vector2i pixelsToIndexes(sf::Vector2f position, sf::Vector2f dr);
	// Перевести координаты тайлов в координаты в пикселях
	static sf::Vector2f tileToPixels(sf::Vector2i tilePosition);
	// Вернуть прямоугольник для проверки коллизий
	sf::RectangleShape getCollisionBox() const;
	// Вернуть направление движения
	directionStates getMovingState() const;
	// Вернуть свободно ли вверху
	bool getIsUpFree() const;
	// Вернуть, свободно ли слева
	bool getIsLeftFree() const;
	// Вернуть, свободно ли внизу
	bool getIsDownFree() const;
	// Вернуть, свободно ли справа
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
	// Установить, свободно ли вверху
	void setIsUpFree(bool isValidPath);
	// Установить, свободно ли слева
	void setIsLeftFree(bool isValidPath);
	// Установить, свободно ли внизу
	void setIsDownFree(bool isValidPath);
	// Установить, свободно ли справа
	void setIsRightFree(bool isValidPath);

protected:

	directionStates m_movingState;

	bool m_isUpFree, m_isDownFree, m_isRightFree, m_isLeftFree, m_isVisible;
	sf::RectangleShape m_currentTile;
	sf::Vector2i m_tilePosition, m_lastTilePosition, m_checkTile, m_spawnPosition;
	sf::Vector2f m_pixelPosition;
	sf::Sprite m_sprite;
	sf::Texture m_spriteSheet;

	sf::RectangleShape m_collisionBox;
	float m_speed, m_lastFrameTime;
	int m_frameX, m_frameY, m_frameIndex;



};