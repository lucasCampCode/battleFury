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
	file.write((char*)&m_player1, sizeof(Character));
	file.write((char*)&m_player2, sizeof(Character));
	file.write((char*)m_enemies, sizeof(Character) * 10);
	file.close();

	return true;
}

bool Game::load()
{
	int savedSlot = 0;
	std::fstream file;
	file.open("gameData.txt", std::ios::in | std::ios::binary);
	if (!file.is_open())
		return false;
	while (file.peek() != EOF)
	{
		file.read((char*)&m_roundNum, sizeof(int));
		file.read((char*)&m_player1, sizeof(Character));
		file.read((char*)&m_player2, sizeof(Character));
		file.read((char*)m_enemies, sizeof(Character) * 10);
		std::cout << "save: " << savedSlot << std::endl;
		std::cout << "round: " << m_roundNum << std::endl;
		std::cout << "player1 name: " << m_player1->getName() << std::endl;
		std::cout << "player1 health: " << m_player1->getHealth() << std::endl;
		std::cout << "player1 damage: " << m_player1->getDamage() << std::endl;
		if (m_player2->getName() != "???")
		{
			std::cout << "player2 name: " << m_player2->getName() << std::endl;
			std::cout << "player2 health: " << m_player2->getHealth() << std::endl;
			std::cout << "player2 damage: " << m_player2->getDamage() << std::endl;
		}
		savedSlot++;
	}
	file.seekg(std::ios::beg);
	std::cout << "what save do you want to load from" << std::endl;
	std::cin >> savedSlot;
	for (int i = 0; i < savedSlot; i++) {
		file.seekg(sizeof(int), std::ios::cur);
		file.seekg(sizeof(Character) * 12, std::ios::cur);
	}

	file.read((char*)&m_roundNum, sizeof(int));
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
