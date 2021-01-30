#pragma once
#include "GameCharacter.h"
class Cleric :
	public GameCharacter
{
private:
	int pietyLevel_;
public:
	Cleric(std::string name, float health, float weight, int food, CharacterState state, int pietylevel);
	virtual ~Cleric();

	virtual bool Attack(GameCharacter &character);
	void PrayFor(GameCharacter &character);

	int GetPietyLevel() const;
	void SetPietyLevel(int);

	float GenerateRandomNumber();
	float GenerateRandomNumber2();
	virtual void Sleep();
};
