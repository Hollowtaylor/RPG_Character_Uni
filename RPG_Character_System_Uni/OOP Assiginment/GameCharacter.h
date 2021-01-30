#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "Weapon.h"
#include "Armour.h"


enum class CharacterState {
	Idle,
	Running,
	Sleeping,
	Walking,
	Defending,
	Dead,
};

class GameCharacter
{
private:
	std::string characterName_;
	float health_;
	float weigthLimit_;
	int equippedWeapon_ = -1;
	int equippedArmour_ = -1;
	std::vector<Weapon> weapons_;
	std::vector<Armour> armourary_;
	int food_;
	CharacterState state_{ CharacterState::Idle };

public:
	GameCharacter(std::string name, float health, float weight, int food, CharacterState state);
	virtual ~GameCharacter();

	virtual bool Attack(GameCharacter &character) = 0;
	void Defend(int armour);
	void Walk();
	void Run();
	virtual void Sleep();
	Weapon& GetWeapon(int index);
	Armour& GetArmour(int index);
	virtual bool PickUpWeapon(Weapon &weapon);
	virtual bool PickUpArmour(Armour &armour);
	void DropItem(Armour &item);
	void DropItem(Weapon &weapon);
	bool EquipWeapon(int weapon);

	CharacterState& GetState();
	void SetState(CharacterState state);


	void AddFood(int amount);
	void Eat();

	float GetHealth() const;
	void SetHealth(float health);

	float GetWeightLimit() const;
	void SetWeightLimit(float);

	int GetFood() const;
	void SetFood(int);

	int GetEquippedWeapon() const;
	
	int GetEquippedArmour() const;
	
	std::string GetName() const;
};