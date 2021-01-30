#include <iostream>
#include "BlackWitch.h"
#include "Brawler.h"
#include "Cleric.h"
#include "Orc.h"

using namespace std;
int main()  {

	//std::string name, float health, float weight, int food, CharacterState state, int punchdamage, int strength)
	BlackWitch blackwitch{ "Scarlett", 100.0f, 120.0f, 30, CharacterState::Idle, 30, 10000000 };
	Brawler brawler{ "Jim", 100.0f, 120.0f, 50, CharacterState::Idle, 60, 80 };
	Armour glove{ "Leather glove", 3, 0.25f, 1, 100, ArmourType::Leather };
	Armour chainMail{ "Chain Mail", 45, 85.0f, 200, 100, ArmourType::Steel };
	Weapon spear{ "spear", 15, 6.0f , 25, 100 };
	Weapon bow{ "bow", 15, 3.0f , 25, 100 };

	cout << "Brawlers name is " << brawler.GetName() << endl;
	cout << "Blackwitch name is " << blackwitch.GetName() << endl;


	blackwitch.PickUpWeapon(bow);
	blackwitch.PickUpArmour(glove);
	blackwitch.EquipWeapon(0);
	cout << "Blackwitch has equipped Armour: " << blackwitch.GetEquippedArmour() << " and Weapon: " << blackwitch.GetEquippedWeapon() << endl;
	brawler.PickUpWeapon(spear);
	brawler.PickUpArmour(chainMail);
	brawler.EquipWeapon(0);
	cout << "Brawler has equipped Armour: " << brawler.GetEquippedArmour() << " and Weapon: " << brawler.GetEquippedWeapon() << endl;

	blackwitch.Defend(0);

	cout << brawler.GetName() << " attacks the blackwitch " << blackwitch.GetName() << endl;
	cout << blackwitch.GetName() << "'s health was " << blackwitch.GetHealth() << endl;
	cout << blackwitch.GetName() << "'s armour health was " << blackwitch.GetArmour(0).GetArmourHealth() << endl;

	brawler.Attack(blackwitch);

	cout << blackwitch.GetName() << "'s health is now " << blackwitch.GetHealth() << endl;
	cout << blackwitch.GetName() << "'s armour health is now " << blackwitch.GetArmour(0).GetArmourHealth() << endl;

	cout << brawler.GetName() << "'s weapon health is now " << brawler.GetWeapon(brawler.GetEquippedWeapon()).GetWeaponHealth() << endl;
	
}