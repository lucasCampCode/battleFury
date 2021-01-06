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

void Game::startBattle(Character* enemy)
{
}

bool Game::save()
{
	std::fstream file;
	file.open("gameData.txt", std::ios::app | std::ios::binary);
	if (!file.is_open())
		return false;
	file.write((char*)&m_roundNum, sizeof(int));
	file.close();

	file.open("CharacterData.txt", std::ios::app | std::ios::binary);
	if (!file.is_open())
		return false;
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
	file.close();

	file.open("CharacterData.txt", std::ios::in | std::ios::binary);
	if (!file.is_open())
		return false;
	file.read((char*)&m_player1, sizeof(Character));
	file.read((char*)&m_player2, sizeof(Character));
	file.read((char*)m_enemies, sizeof(Character) * 10);
	file.close();

	return true;
}

void Game::start()
{
	srand(time(NULL));
	for (int i = 0; i < sizeof(m_enemies) / sizeof(Character); i++) {
		m_enemies[i] = new Character(rand() % 60 + 40, rand() % 5 + 5);
	}
	m_player2 = new Character();
	char input = ' ';
	char name[16];
	std::cout << "morning stranger, what's your name?" << std::endl;
	std::cin >> name;
	m_player1 = new Character(100, 10, name);
}

void Game::update()
{
	char input = ' ';
	input = getInput(input,"[1] continue","[2] save","you found a safe ground");
	if (input == 1)
	{
		startBattle(m_enemies[m_roundNum]);
	}
	else
		save();
}	

void Game::draw()
{
}

void Game::end()
{
	delete m_player1;
	delete m_player2;
	delete[] m_enemies;
}
