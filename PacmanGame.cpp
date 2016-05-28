#include "PacmanGame.h"

PacmanGame::PacmanGame() : m_food(GameConstants::MAZE_HEIGHT, std::vector<Food>(GameConstants::MAZE_WIDTH))
{
	m_spriteSheet.loadFromFile("resources/spriteSheetTransparent.png");
	m_pacmanSpriteSheet.loadFromFile("resources/spriteSheetTransparent.png");

	m_maze.setTexture(m_spriteSheet);

	m_maze.buildMapMatrix(GameConstants::MAZE_HEIGHT, GameConstants::MAZE_WIDTH, "mazeMap.txt");
	m_maze.placeWalls(*m_walls, GameConstants::MAZE_HEIGHT, GameConstants::MAZE_WIDTH);
	m_maze.placeFood(m_food, GameConstants::MAZE_HEIGHT, GameConstants::MAZE_WIDTH);

	sf::Vector2i initialPacmanPosition(GameConstants::PACMAN_SPAWNJ, GameConstants::PACMAN_SPAWNI);
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
	
	
	resolveCollision();

	m_blinky.changeDirection();
	m_pinky.changeDirection();
	m_inky.changeDirection();
	m_clyde.changeDirection();
	
	m_pacman.update(clock);

	m_blinky.setTarget(m_pacman.getTilePosition());
	m_pinky.setTarget(m_pacman.getTilePosition());
	m_inky.setTarget(m_pacman.getTilePosition());
	m_clyde.setTarget(m_pacman.getTilePosition());

	m_blinky.update();
	m_pinky.update();
	m_inky.update();
	m_clyde.update();

	
	
}

void PacmanGame::draw(sf::RenderTarget & target)
{
	target.clear(sf::Color::Black);
	target.draw(m_maze);

	for (int i = 0; i < GameConstants::MAZE_HEIGHT; i++)
	{
		for (int j = 0; j < GameConstants::MAZE_WIDTH; j++)
		{
			//target.draw(m_food[i*GameConstants::MAZE_WIDTH+j]);
			target.draw(m_food[i][j]);
		}
	}

	target.draw(m_pacman);
	//target.draw(m_enemy);
	target.draw(m_blinky);
	target.draw(m_pinky);
	target.draw(m_inky);
	target.draw(m_clyde);

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
}

int PacmanGame::pixelsToIndex(float x)
{
	return x / GameConstants::TILE_SIZE;
}

void PacmanGame::resolveCollision()
{
	m_pacman.checkWallCollisions(m_maze.getMazeVector(), GameConstants::MAZE_HEIGHT, GameConstants::MAZE_WIDTH);

	m_blinky.checkWallCollisions(m_maze.getMazeVector(), GameConstants::MAZE_HEIGHT, GameConstants::MAZE_WIDTH);
	m_pinky.checkWallCollisions(m_maze.getMazeVector(), GameConstants::MAZE_HEIGHT, GameConstants::MAZE_WIDTH);
	m_inky.checkWallCollisions(m_maze.getMazeVector(), GameConstants::MAZE_HEIGHT, GameConstants::MAZE_WIDTH);
	m_clyde.checkWallCollisions(m_maze.getMazeVector(), GameConstants::MAZE_HEIGHT, GameConstants::MAZE_WIDTH);

	checkCharactersCollision(m_pacman, m_blinky);
	checkCharactersCollision(m_pacman, m_pinky);
	checkCharactersCollision(m_pacman, m_inky);
	checkCharactersCollision(m_pacman, m_clyde);

	Food &currentFood = m_food[m_pacman.getTilePosition().y][m_pacman.getTilePosition().x];
	currentFood.setState(currentFood.DEVOURED);
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

	m_blinky.hide();
	m_pinky.hide();
	m_inky.hide();
	m_clyde.hide();
}
