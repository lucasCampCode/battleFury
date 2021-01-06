#pragma once
class Character
{
public:
	Character();
	Character(float health, float damage);
	Character(float health, float damage, const char* name);


	void attack(Character* other);
	float takeDamage(float damageAmount);
	void printStats();

	char* getName() { return m_name; }
	float getDamage() { return m_damage; }
	float getHealth() { return m_health; }
	bool isAlive() { return m_health > 0; }

private:
	char m_name[16];
	float m_health;
	float m_damage;
};
