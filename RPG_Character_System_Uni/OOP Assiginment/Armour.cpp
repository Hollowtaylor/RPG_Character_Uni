#include "Armour.h"



Armour::~Armour()  {
}

Armour::Armour(std::string armourName, int value, float weight, int armourStrength, int armourHealth, ArmourType armourType)
	:Item(armourName, value, weight), defence_(armourStrength), armourHealth_(armourHealth), armourType_(armourType)  {
}


int Armour::GetDefence() const  {
	return defence_;
}

void Armour::SetDefence(int defence)  {
	defence_ = defence;
}

int Armour::GetArmourHealth() const  {
	return armourHealth_;
}

void Armour::SetArmourHealth(int armourHealth)  {
	armourHealth_ = armourHealth;
}
void Armour::SetArmourType(ArmourType armourType)  {
	armourType_ = armourType;
}

ArmourType Armour::GetArmourType() const  {
	return armourType_;
}

