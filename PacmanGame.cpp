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

	int pacmanJ = pixelsToIndex(m_pacman.getCollisionBox().getGlobalBounds().left + m_pacman.getCollisionBox().getOrigin().x);
	int pacmanI = pixelsToIndex(m_pacman.getCollisionBox().getGlobalBounds().top + m_pacman.getCollisionBox().getOrigin().y);

	bool testMovingUp = !m_pacman.getCollisionBox().getGlobalBounds().intersects(m_walls[pacmanI - 1][pacmanJ].getGlobalBounds());
	bool testMovingLeft = !m_pacman.getCollisionBox().getGlobalBounds().intersects(m_walls[pacmanI][pacmanJ - 1].getGlobalBounds());
	bool testMovingDown = !m_pacman.getCollisionBox().getGlobalBounds().intersects(m_walls[pacmanI + 1][pacmanJ].getGlobalBounds());
	bool testMovingRight = !m_pacman.getCollisionBox().getGlobalBounds().intersects(m_walls[pacmanI][pacmanJ + 1].getGlobalBounds());

	m_pacman.setTestMovingUp(testMovingUp);
	m_pacman.setTestMovingLeft(testMovingLeft);
	m_pacman.setTestMovingDown(testMovingDown);
	m_pacman.setTestMovingRight(testMovingRight);

	m_debugPacmanCurrentTile.setPosition(GameConstants::TILE_SIZE*pacmanJ, GameConstants::TILE_SIZE*pacmanI);

	lastPacmanIJ.x = pacmanI;
	lastPacmanIJ.y = pacmanJ;
	//checkWallCollisions(m_pacman);


	int enemyJ = pixelsToIndex(m_enemy.getCollisionBox().getGlobalBounds().left + m_enemy.getCollisionBox().getOrigin().x);
	int enemyI = pixelsToIndex(m_enemy.getCollisionBox().getGlobalBounds().top + m_enemy.getCollisionBox().getOrigin().y);

	testMovingUp = !m_enemy.getCollisionBox().getGlobalBounds().intersects(m_walls[enemyI - 1][enemyJ].getGlobalBounds());
	testMovingLeft = !m_enemy.getCollisionBox().getGlobalBounds().intersects(m_walls[enemyI][enemyJ - 1].getGlobalBounds());
	testMovingDown = !m_enemy.getCollisionBox().getGlobalBounds().intersects(m_walls[enemyI + 1][enemyJ].getGlobalBounds());
	testMovingRight = !m_enemy.getCollisionBox().getGlobalBounds().intersects(m_walls[enemyI][enemyJ + 1].getGlobalBounds());
	
	m_enemy.setTestMovingUp(testMovingUp);
	m_enemy.setTestMovingLeft(testMovingLeft);
	m_enemy.setTestMovingDown(testMovingDown);
	m_enemy.setTestMovingRight(testMovingRight);

	m_enemy.changeDirection(pacmanI, pacmanJ, enemyI, enemyJ);

	m_debugEnemyCurrentTile.setPosition(GameConstants::TILE_SIZE*enemyJ, GameConstants::TILE_SIZE*enemyI);


	lastEnemyIJ.x = enemyI;
	lastEnemyIJ.y = enemyJ;

	

	Food &currentFood = m_food[pacmanI*GameConstants::MAZE_WIDTH + pacmanJ];

	if (m_pacman.getCollisionBox().getGlobalBounds().intersects(currentFood.getCollisionRectangle()))
	{
		currentFood.setState(currentFood.DEVOURED);
	}
}

void PacmanGame::checkWallCollisions(Character & character)
{
	//character.m_characterJ = pixelsToIndex(character.getCollisionBox().getGlobalBounds().left + character.getCollisionBox().getOrigin().x);
	int characterJ = pixelsToIndex(character.getCollisionBox().getGlobalBounds().left + character.getCollisionBox().getOrigin().x);
	character.setCharacterJ(characterJ);
	//character.m_characterI = pixelsToIndex(character.getCollisionBox().getGlobalBounds().top + character.getCollisionBox().getOrigin().y);
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

	//character.changeDirection(pacmanI, pacmanJ, characterI, characterJ);

	//character.m_currentTile.setPosition(GameConstants::TILE_SIZE*characterJ, GameConstants::TILE_SIZE*characterI);
	character.setCurrentTilePosition(GameConstants::TILE_SIZE*characterJ, GameConstants::TILE_SIZE*characterI);

	//lastEnemyIJ.x = enemyI;
	//lastEnemyIJ.y = enemyJ;
}
