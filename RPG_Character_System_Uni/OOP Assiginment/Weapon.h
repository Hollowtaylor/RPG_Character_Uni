#pragma once
#include "Item.h"
#include <string>

class Weapon :
	public Item
{
private:
	int weaponHitStrength_;
	int weaponHealth_;
public:
	
	virtual ~Weapon();

	Weapon(std::string weaponName, int value, float weight, int hitStrength, int health);

	void SetWeaponHitStrength(int hitStrength);
	int GetWeaponHitStrength()  const;

	void SetWeaponHealth(int health);
	int GetWeaponHealth()  const;
};

