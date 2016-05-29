#include "PacmanGame.h"

PacmanGame::PacmanGame() : m_food(GameConstants::MAZE_HEIGHT, std::vector<Food>(GameConstants::MAZE_WIDTH)), ghosts(4)
{
	m_spriteSheet.loadFromFile("resources/spriteSheetTransparent.png");
	m_pacmanSpriteSheet.loadFromFile("resources/spriteSheetTransparent.png");

	m_maze.setTexture(m_spriteSheet);

	ghosts[0].setName("Blinky");
	ghosts[1].setName("Pinky");
	ghosts[2].setName("Inky");
	ghosts[3].setName("Clyde");


	m_maze.buildMapMatrix(GameConstants::MAZE_HEIGHT, GameConstants::MAZE_WIDTH, "mazeMap.txt");
	m_maze.placeWalls(*m_walls, GameConstants::MAZE_HEIGHT, GameConstants::MAZE_WIDTH);
	m_maze.placeFood(m_food, GameConstants::MAZE_HEIGHT, GameConstants::MAZE_WIDTH);

	sf::Vector2i initialPacmanPosition(GameConstants::PACMAN_SPAWNJ, GameConstants::PACMAN_SPAWNI);
	m_pacman.setInitialPosition();

	m_isPacmanDead = false;
	m_score = 0;
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
	//if (!m_isPacmanDead)
	//{
		m_maze.update();


		resolveCollision();

		for (int i = 0; i < 4; i++)
		{
			ghosts[i].changeDirection();
		}

		m_pacman.update(clock);

		for (int i = 0; i < 4; i++)
		{
			ghosts[i].setTarget(m_pacman.getTilePosition(), m_pacman.getMovingState());
			ghosts[i].update();
		}
	//}
}

void PacmanGame::draw(sf::RenderTarget & target)
{
	target.clear(sf::Color::Black);
	target.draw(m_maze);

	for (int i = 0; i < GameConstants::MAZE_HEIGHT; i++)
	{
		for (int j = 0; j < GameConstants::MAZE_WIDTH; j++)
		{
			target.draw(m_food[i][j]);
		}
	}

	target.draw(m_pacman);
	
	for (int i = 0; i < 4; i++)
	{
		target.draw(ghosts[i]);
	}

	if (GameConstants::IS_DEBUGGING)
	{
		debugDraw(target);
	}
	
}
void PacmanGame::onPacmanDeath()
{
	if (!m_isPacmanDead)
	{
		m_pacman.die();

		for (int i = 0; i < 4; i++)
		{
			ghosts[i].hide();
		}
		/*
		m_isPacmanDead = true;
		sf::Clock clock;
		clock.restart();
		float timeSinceDeath = 0;
		while (timeSinceDeath < GameConstants::RESPAWN_TIME)
		{
			timeSinceDeath = clock.getElapsedTime().asSeconds();

		}*/
		
		respawn();
	}
}
void PacmanGame::respawn()
{
	m_pacman.setInitialPosition();
	m_pacman.respawn();
	for (int i = 0; i < 4; i++)
	{
		ghosts[i].setInitialPosition();
		ghosts[i].makeVisible();
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

	for (int i = 0; i < 4; i++)
	{
		ghosts[i].checkWallCollisions(m_maze.getMazeVector(), GameConstants::MAZE_HEIGHT, GameConstants::MAZE_WIDTH);
		checkCharactersCollision(m_pacman, ghosts[i]);
	}
	Food &currentFood = m_food[m_pacman.getTilePosition().y][m_pacman.getTilePosition().x];
	if (currentFood.getState() != currentFood.DEVOURED)
	{
		currentFood.setState(currentFood.DEVOURED);
		m_score += GameConstants::FOOD_SCORE;
	}
}

void PacmanGame::checkCharactersCollision(Pacman & pacman, Enemy & enemy)
{
	if (pacman.getCollisionBox().getGlobalBounds().intersects(enemy.getCollisionBox().getGlobalBounds()))
	{
		onPacmanDeath();
		
	}
}

void PacmanGame::endGame()
{

}
