#include "Weapon.h"




Weapon::~Weapon()
{
}

Weapon::Weapon(std::string weaponName, int value, float weight, int hitStrength, int health)
	:Item(weaponName, value, weight), weaponHitStrength_(hitStrength), weaponHealth_(health)
{
}


int Weapon::GetWeaponHitStrength() const
{
	return weaponHitStrength_;
}

void Weapon::SetWeaponHitStrength(int hitStrength)
{
	weaponHitStrength_ = hitStrength;
}



int Weapon::GetWeaponHealth()  const
{
	return weaponHealth_;
}

void Weapon::SetWeaponHealth(int health)
{
	weaponHealth_ = health;
}

