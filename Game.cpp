#include "Game.h"
#include <iostream>
#include <fstream>

void Game::run()
{
	start();

	while (!getGameOver())
	{
		update();
		draw();
	}

	end();
}

char Game::getInput(char input, const char* option1, const char* option2, const char* query)
{
	input = ' ';
	std::cout << query << std::endl;
	std::cout << option1 << std::endl;
	std::cout << option2 << std::endl;
	while (input != '1' && input != '2')
	{
		std::cin >> input;
		if (input != '1' && input != '2')
		{
			std::cout << "invalid input!";
		}
	}
	return input;
}

bool Game::save()
{
	std::fstream file;
	file.open("gameData.txt", std::ios::app | std::ios::binary);
	if (!file.is_open())
		return false;
	file.write((char*)&m_roundNum, sizeof(int));
	file.write((char*)&m_player1, sizeof(Character));
	file.write((char*)&m_player2, sizeof(Character));
	file.write((char*)m_enemies, sizeof(Character) * 10);

	file.close();
	return true;
}

bool Game::load()
{
	std::fstream file;
	file.open("gameData.txt", std::ios::in | std::ios::binary);
	if (!file.is_open())
		return false;
	file.read((char*)&m_roundNum, sizeof(int));
	file.read((char*)&m_player1, sizeof(Character));
	file.read((char*)&m_player2, sizeof(Character));
	file.read((char*)m_enemies, sizeof(Character) * 10);

	file.close();
	return true;
}

void Game::start()
{
}

void Game::update()
{
}

void Game::draw()
{
}

void Game::end()
{
}
