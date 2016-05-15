#include "PacmanGame.h"

PacmanGame::PacmanGame()
{
	m_spriteSheet.loadFromFile("resources/spriteSheet3.png");
	m_pacmanSpriteSheet.loadFromFile("resources/spriteSheet2.png");

	m_maze.setTexture(m_spriteSheet);
	
	m_food = std::vector<Food>(GameConstants::MAZE_HEIGHT*GameConstants::MAZE_WIDTH, Food(m_spriteSheet));

	m_maze.buildWallMatrix(*m_walls, m_food, GameConstants::MAZE_HEIGHT, GameConstants::MAZE_WIDTH);

	m_debugPacmanCurrentTile.setSize(sf::Vector2f(GameConstants::TILE_SIZE, GameConstants::TILE_SIZE));
	m_debugPacmanCurrentTile.setPosition(GameConstants::SPAWNX, GameConstants::SPAWNY);
	m_debugPacmanCurrentTile.setFillColor(sf::Color::White);

	m_debugEnemyCurrentTile.setSize(sf::Vector2f(GameConstants::TILE_SIZE, GameConstants::TILE_SIZE));
	m_debugEnemyCurrentTile.setPosition(GameConstants::SPAWNX, GameConstants::SPAWNY);
	m_debugEnemyCurrentTile.setFillColor(sf::Color::Green);

	float x = 12;
	float y = 5;

	
}

void PacmanGame::processEvent(sf::Event event)
{
	if (event.type = sf::Event::KeyPressed)
	{
		m_pacman.changeDirection();
	}
}

void PacmanGame::update(sf::Clock clock)
{
	m_maze.update();
	m_pacman.update(clock);
	m_enemy.update(clock);
	
	resolveCollision();
	m_enemy.changeDirection(m_pacman.getCharacterI(), m_pacman.getCharacterJ(), m_enemy.getCharacterI(), m_enemy.getCharacterJ());

}

void PacmanGame::draw(sf::RenderTarget & target)
{
	target.clear(sf::Color::Black);
	target.draw(m_maze);

	for (int i = 0; i < GameConstants::MAZE_HEIGHT; i++)
	{
		for (int j = 0; j < GameConstants::MAZE_WIDTH; j++)
		{
			target.draw(m_food[i*GameConstants::MAZE_WIDTH+j]);
		}
	}

	target.draw(m_pacman);
	target.draw(m_enemy);

	if (GameConstants::IS_DEBUGGING)
	{
		debugDraw(target);
	}
	
}

void PacmanGame::debugDraw(sf::RenderTarget & target) const
{
	for (int i = 0; i < GameConstants::MAZE_HEIGHT; i++)
	{
		for (int j = 0; j < GameConstants::MAZE_WIDTH; j++)
		{
			target.draw(m_walls[i][j]);
		}
	}
	target.draw(m_debugPacmanCurrentTile);
	target.draw(m_debugEnemyCurrentTile);
}

int PacmanGame::pixelsToIndex(float x)
{
	return x / GameConstants::TILE_SIZE;
}

void PacmanGame::resolveCollision()
{
	checkWallCollisions(m_pacman);
	checkWallCollisions(m_enemy);

	Food &currentFood = m_food[pacmanI*GameConstants::MAZE_WIDTH + pacmanJ];

	if (m_pacman.getCollisionBox().getGlobalBounds().intersects(currentFood.getCollisionRectangle()))
	{
		currentFood.setState(currentFood.DEVOURED);
	}
}

void PacmanGame::checkWallCollisions(Character & character)
{
	int characterJ = pixelsToIndex(character.getCollisionBox().getGlobalBounds().left + character.getCollisionBox().getOrigin().x);
	character.setCharacterJ(characterJ);

	int characterI = pixelsToIndex(character.getCollisionBox().getGlobalBounds().top + character.getCollisionBox().getOrigin().y);
	character.setCharacterI(characterI);

	bool testMovingUp = !character.getCollisionBox().getGlobalBounds().intersects(m_walls[characterI - 1][characterJ].getGlobalBounds());
	bool testMovingDown = !character.getCollisionBox().getGlobalBounds().intersects(m_walls[characterI + 1][characterJ].getGlobalBounds());
	bool testMovingLeft = !character.getCollisionBox().getGlobalBounds().intersects(m_walls[characterI][characterJ - 1].getGlobalBounds());
	bool testMovingRight = !character.getCollisionBox().getGlobalBounds().intersects(m_walls[characterI][characterJ + 1].getGlobalBounds());

	character.setTestMovingUp(testMovingUp);
	character.setTestMovingLeft(testMovingLeft);
	character.setTestMovingDown(testMovingDown);
	character.setTestMovingRight(testMovingRight);

	character.setCurrentTilePosition(GameConstants::TILE_SIZE*characterJ, GameConstants::TILE_SIZE*characterI);
}
