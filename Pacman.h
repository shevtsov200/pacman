#pragma once
#include <SFML\Graphics.hpp>
class Pacman : public sf::Drawable, public sf::Transformable
{
public: 
	Pacman();
	//~Pacman();
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void changeDirection();
	void update(sf::Clock clock);
	void playAnimation(sf::Clock clock);

private:
	sf::Sprite sprite;
	sf::Texture spriteSheet;

	sf::Vector2f velocity;

	float lastFrameTime;
	float frameDuration = 250;
	int numberOfFrames = 3;
	int frameWidth = 15;
	int frameHeight = frameWidth;
	int frameOffsetX = 2;
	int frameOffsetY = frameOffsetX;
	int frameX;
	int frameY;
	int frameIndex;


};
