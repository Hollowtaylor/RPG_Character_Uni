#pragma once
#include "Item.h"
#include <string>

enum class ArmourType { Cardboard, Leather, Wood, Iron, Steel };

class Armour :
	public Item
{
private:
	int defence_;
	int armourHealth_;
	ArmourType armourType_;
public:
	
	virtual ~Armour();

	Armour(std::string armourName, int value, float weight, int armourStrength, int armourHealth, ArmourType amourType);

	void SetDefence(int defence);
	int GetDefence() const;

	void SetArmourHealth(int armourHealth);
	int GetArmourHealth() const;

	void SetArmourType(ArmourType armourType);
	ArmourType GetArmourType() const;
};
