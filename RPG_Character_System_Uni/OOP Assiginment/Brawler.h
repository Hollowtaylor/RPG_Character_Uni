#pragma once
#include "GameCharacter.h"
class Brawler :
	public GameCharacter
{
private:
	int punchDamage_;
	int strength_;
public:
	Brawler(std::string name, float health, float weight, int food, CharacterState state, int punchdamage, int strength);
	virtual ~Brawler();

	virtual bool Attack(GameCharacter &character);
	bool Brawl(GameCharacter &character);

	int GetPunchDamage() const;
	void SetPunchDamage(int);

	float GenerateRandomNumber();
	float GenerateRandomNumber2();
	virtual void Sleep();
};

