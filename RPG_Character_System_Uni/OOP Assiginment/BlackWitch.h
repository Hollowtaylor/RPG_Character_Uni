#pragma once
#include "GameCharacter.h"
class BlackWitch :
	public GameCharacter
{
private:
	int magicProficiency_;
	int darkPower_;
public:
	
	BlackWitch(std::string name, float health, float weight, int food, CharacterState state, int magicproficiency, int darkpower);
	virtual ~BlackWitch();

	virtual bool Attack(GameCharacter &character);
	void Bewitch(GameCharacter &character);

	int GetMagicProficiency() const;
	void SetMagicProficiency(int);

	int GetDarkPower() const;
	void SetDarkPower(int);

	float GenerateRandomNumber();
	float GenerateRandomNumber2();
	virtual void Sleep();
};

