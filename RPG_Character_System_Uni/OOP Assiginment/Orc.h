#pragma once
#include "GameCharacter.h"
class Orc :
	public GameCharacter
{
private:
	int ferociuosness_;
	int strength_;
public:
	Orc(std::string name, float health, float weight, int food, CharacterState state, int ferociuosness, int strength);
	virtual ~Orc();

	virtual bool Attack(GameCharacter &character);
	void Scream(GameCharacter &character);

	int GetFerociousness() const;
	void SetFerociousness(int);

	int GetStrength() const;
	void SetStrength(int);

	float GenerateRandomNumber();
	float GenerateRandomNumber2();
	virtual void Sleep();
};

