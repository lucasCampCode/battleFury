#include "Character.h"
#include <iostream>

Character::Character()
{
m_health = 100;
m_damage = 10;
strncpy_s(m_name, "???", 16);
}

Character::Character(float health, float damage)
{
	m_health = health;
	m_damage = damage;
	strncpy_s(m_name, "???", 16);
}

Character::Character(float health, float damage, const char* name)
{
	m_health = health;
	m_damage = damage;
	strncpy_s(m_name, name, 16);
}

void Character::attack(Character* other)
{
	other->takeDamage(getDamage());
}

float Character::takeDamage(float damageAmount)
{
	m_health -= damageAmount;
	return damageAmount;
}
void Character::printStats()
{
	std::cout << "name: " << m_name << "\n";
	std::cout << "health: " << m_health << "\n";
	std::cout << "damage: " << m_damage << std::endl;
	std::cout << "------------" << std::endl;
}
