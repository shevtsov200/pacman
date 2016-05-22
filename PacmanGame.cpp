#include "PacmanGame.h"

PacmanGame::PacmanGame()
{
	m_spriteSheet.loadFromFile("resources/spriteSheet3.png");
	m_pacmanSpriteSheet.loadFromFile("resources/spriteSheet2.png");

	m_maze.setTexture(m_spriteSheet);
	
	m_food = std::vector<Food>(GameConstants::MAZE_HEIGHT*GameConstants::MAZE_WIDTH, Food(m_spriteSheet));

	m_maze.buildMapMatrix(GameConstants::MAZE_HEIGHT, GameConstants::MAZE_WIDTH, "mazeMap.txt");
	m_maze.placeWalls(*m_walls, GameConstants::MAZE_HEIGHT, GameConstants::MAZE_WIDTH);
	m_maze.placeFood(m_food, GameConstants::MAZE_HEIGHT, GameConstants::MAZE_WIDTH);

	sf::Vector2i initialPacmanPosition(11, 13);
	//m_pacman.setPosition(GameConstants::TILE_SIZE * 11, GameConstants::TILE_SIZE * 13);
	m_pacman.setInitialPosition(initialPacmanPosition);
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
	
	resolveCollision();

	m_enemy.update(clock);
	
	m_enemy.setTarget(m_pacman.getTilePosition());
	
	m_enemy.changeDirection();
	
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
	//target.draw(m_debugPacmanCurrentTile);
	//target.draw(m_debugEnemyCurrentTile);
}

int PacmanGame::pixelsToIndex(float x)
{
	return x / GameConstants::TILE_SIZE;
}

void PacmanGame::resolveCollision()
{
	//checkWallCollisions(m_pacman);
	//checkWallCollisions(m_enemy);
	m_pacman.checkWallCollisions(m_maze.getMazeVector(), GameConstants::MAZE_HEIGHT, GameConstants::MAZE_WIDTH);
	m_enemy.checkWallCollisions(m_maze.getMazeVector(), GameConstants::MAZE_HEIGHT, GameConstants::MAZE_WIDTH);
	checkCharactersCollision(m_pacman, m_enemy);
	
	Food &currentFood = m_food[m_pacman.getTilePosition().x*GameConstants::MAZE_WIDTH + m_pacman.getTilePosition().y];

	if (m_pacman.getCollisionBox().getGlobalBounds().intersects(currentFood.getCollisionRectangle()))
	{
		currentFood.setState(currentFood.DEVOURED);
	}
}

void PacmanGame::checkWallCollisions(Character & character)
{
	/*int characterJ = pixelsToIndex(character.getCollisionBox().getGlobalBounds().left + character.getCollisionBox().getOrigin().x);
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

	character.setCurrentTilePosition(GameConstants::TILE_SIZE*characterJ, GameConstants::TILE_SIZE*characterI);*/
}

void PacmanGame::checkCharactersCollision(Pacman & pacman, Enemy & enemy)
{
	if (pacman.getCollisionBox().getGlobalBounds().intersects(enemy.getCollisionBox().getGlobalBounds()))
	{
		endGame();
		
	}
}

void PacmanGame::endGame()
{
	m_pacman.Die();
	m_enemy.hide();
}
