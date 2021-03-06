#include "PacmanGame.h"

PacmanGame::PacmanGame() : m_food(GameConstants::MAZE_HEIGHT, std::vector<Food>(GameConstants::MAZE_WIDTH)), ghosts(4)
{
	m_spriteSheet.loadFromFile("resources/spriteSheetTransparent.png");

	m_maze.setTexture(m_spriteSheet);

	font.loadFromFile("resources/arcadeClassic.ttf");

	m_introBuffer.loadFromFile("resources/sounds/beginning.wav");
	m_introSound.setBuffer(m_introBuffer);
	m_chompBuffer.loadFromFile("resources/sounds/chomp.wav");
	m_chompSound.setBuffer(m_chompBuffer);
	m_deathBuffer.loadFromFile("resources/sounds/death.wav");
	m_deathSound.setBuffer(m_deathBuffer);

	m_scoreString.setPosition(GameConstants::SCOREX, GameConstants::SCOREY);
	m_scoreString.setFont(font);
	m_scoreString.setColor(sf::Color::White);
	m_scoreString.setCharacterSize(50);

	m_scoreString.setString(std::to_string(m_score));

	ghosts[0].setName("Blinky");
	ghosts[1].setName("Pinky");
	ghosts[2].setName("Inky");
	ghosts[3].setName("Clyde");

	for (int i = 0; i < 4; i++)
	{
		ghosts[i].setTexture(m_spriteSheet);
	}
	m_pacman.setTexture(m_spriteSheet);


	m_maze.buildMapMatrix(GameConstants::MAZE_HEIGHT, GameConstants::MAZE_WIDTH, "mazeMap.txt");
	m_maze.placeWalls(*m_walls, GameConstants::MAZE_HEIGHT, GameConstants::MAZE_WIDTH);
	m_maze.placeFood(m_food, GameConstants::MAZE_HEIGHT, GameConstants::MAZE_WIDTH);

	sf::Vector2i initialPacmanPosition(GameConstants::PACMAN_SPAWNJ, GameConstants::PACMAN_SPAWNI);
	m_pacman.setInitialPosition();

	m_isPacmanDead = false;
	m_score = 0;
	m_lives = 3;
	m_lifeSprite.setTexture(m_spriteSheet);
	m_lifeSprite.setTextureRect(sf::IntRect(GameConstants::LIFE_FRAME_OFFSET, 0, GameConstants::FRAME_WIDTH, GameConstants::FRAME_HEIGHT));
	m_lifeSprite.setScale(GameConstants::SCALE, GameConstants::SCALE);
	m_lifeSprite.setPosition(GameConstants::LIFEX, GameConstants::LIFEY);

	m_introSound.play();
	m_isRespawn = false;
	m_gameOver = false;

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
		if (m_isRespawn)
		{
			if (!m_pacman.playDeathAnimation(clock))
			{
				m_lives--;
				if (m_lives > 0)
				{
					respawn();
				}
				else
				{
					endGame();
				}
				m_isRespawn = false;
			}
		}
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

	for (int i = 0; i < m_lives; i++)
	{
		m_lifeSprite.setPosition(GameConstants::LIFEX, GameConstants::LIFEY + m_lifeSprite.getGlobalBounds().height*i);
		target.draw(m_lifeSprite);
	}

	target.draw(m_scoreString);	
}
void PacmanGame::onPacmanDeath()
{
	if (!m_isPacmanDead && !m_isRespawn)
	{
		m_pacman.die();
		if (m_deathSound.getStatus() != m_deathSound.Playing)
		{
			m_deathSound.play();
		}
		for (int i = 0; i < 4; i++)
		{
			ghosts[i].stop();
			ghosts[i].hide();
		}
		
		
		sf::Clock clock;
		clock.restart();
		float timeSinceDeath = 0;
		float startTime = clock.getElapsedTime().asMilliseconds();

		m_isRespawn = true;
	}
}
void PacmanGame::respawn()
{
	m_pacman.setInitialPosition();
	m_pacman.respawn();
	for (int i = 0; i < 4; i++)
	{
		ghosts[i].setInitialPosition();
		ghosts[i].checkWallCollisions(m_maze.getMazeVector(), GameConstants::MAZE_HEIGHT, GameConstants::MAZE_WIDTH);
		ghosts[i].makeVisible();
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
		m_scoreString.setString(std::to_string(m_score));

		m_chompSound.play();
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
	m_gameOver = true;
}
bool PacmanGame::getIsGameOver()
{
	return m_gameOver;
}