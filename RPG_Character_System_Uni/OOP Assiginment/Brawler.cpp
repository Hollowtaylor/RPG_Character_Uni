#include "Brawler.h"




Brawler::Brawler(std::string name, float health, float weight, int food, CharacterState state, int punchdamage, int strength)
	: GameCharacter(name, health, weight, food, state), punchDamage_(punchdamage), strength_(strength)	{
}


Brawler::~Brawler()	{
}

//LOGIC:: //Health is below 20  //target character is dead
bool Brawler::Attack(GameCharacter & character)	 {
	//These variables will be used later on, theyre done up here for aesthedics
	float newHealth{ 0.0f };
	int armourHealth;
	int newArmourHealth;
	int equipped;
	double damage;

	

	//If the Health of this character is below 20, or theyre dead then end this method in its tracks
	if (this->GetHealth() <= 20 || this->GetState() == CharacterState::Dead)	{
		return false;	//Attack unsuccessful, return false and stop the program in its tracks
	}

	if (this->EquipWeapon(0) == false) {
		this->Brawl(character);
	}

	//Attack here, if successful then you move on to see what damage is dealt

	//determine chance of success from attack logic 
	float attackChance;
	if (character.GetEquippedArmour() == -1)	{  //If the target has no armour, theres a 80% chance
	
		attackChance = 0.80f;
	}
	else if (this->GetWeapon(this->GetEquippedWeapon()).GetWeaponHitStrength() 
		< character.GetArmour(character.GetEquippedArmour()).GetDefence()) { //if weapon dmg < defence value of defending, 20% of attack
		attackChance = 0.20f;
	}
	else { //else there is a 60% chance of attack
		attackChance = 0.60f;
	}


	//Try to attack

	if (GenerateRandomNumber() < attackChance)	{ // If chance of success is 35, and the GenerateRandomNumber() is anywhere between 1 and 100, theres a 35% chance of success
	
		//do nothing and let code continue on
		//should weapon health be changed at all here

	//Unique attack brawl called if there is no weapon equipped 
		if (character.GetEquippedWeapon() == -1)	{
			Brawl(character);
		}

	//dmg*0.05 for every 10 strength
		damage = 5 * (strength_*0.10);
	//If method makes it this far, attack was successful as equip weapon returns to main if its not valid

		if (character.GetState() == CharacterState::Defending)	{  //If enemy character is defending, do whats in the else
		
		//10% total damage dealth
			newHealth = character.GetHealth() - (character.GetHealth() / 100 * (damage + 10));
			armourHealth = character.GetArmour(character.GetEquippedArmour()).GetArmourHealth();
			newArmourHealth = armourHealth / 100 * 90;
			equipped = character.GetEquippedArmour();
		}
		else if (character.GetState() == CharacterState::Sleeping)	{
		//Instant kill, set health to 0
			character.SetHealth(0.0f);
			return true;
		}
		else if (character.GetState() == CharacterState::Dead)	{
			return false; //dead, so nothing happens
		}
		else {
		//20% health to the character being attacked for all other states. 
			newHealth = character.GetHealth() - (character.GetHealth() / 5);
		}
	}
	
	else	{ //attack fails, so return and do not deal dmg
	
		if (character.GetEquippedArmour() != -1) {
			this->GetWeapon(this->GetEquippedWeapon()).SetWeaponHealth((this->GetWeapon(this->GetEquippedWeapon()).GetWeaponHealth()) - (this->GetWeapon(this->GetEquippedWeapon()).GetWeaponHealth() * GenerateRandomNumber2()));
		}
		//attacking characters weapon heath goes down by between 10 and 20
		return false; //stop this method in its tracks
	}
	//The health of the defending characters armour will also be reduced by 10%

	//Deal damage to enenmy character and their armour
	character.SetHealth(newHealth);
	character.GetArmour(equipped).SetArmourHealth(newArmourHealth);

	if (this->GetWeapon(this->GetEquippedWeapon()).GetWeaponHealth() <= 0) {
		this->DropItem(this->GetWeapon(this->GetEquippedWeapon()));
	}
	if (character.GetArmour(character.GetEquippedArmour()).GetArmourHealth() <= 0) {
		character.DropItem(character.GetArmour(character.GetEquippedArmour()));
	}

	//After attacking the character goes idle
	this->SetState(CharacterState::Idle);
	return true;
}

bool Brawler::Brawl(GameCharacter & character)
{
	//Attempts to attack by punching
	//replace hitstrength with punchDamage
	//succeful hit = 50% of the damage of attacking with a weopan
	int attackChance;
	int armourHealth;
	int newArmourHealth;
	int equipped;
	double damage;
	float newHealth{ 0.0f };

	if (character.GetEquippedArmour() == -1)  { 	//if defending character has no armour, chance is 80%
	
		attackChance = 80;
	}
	else if (this->GetPunchDamage() < character.GetArmour(character.GetEquippedArmour()).GetDefence())   {  //if weapon dmg < defence value of defending, 20% of attack
	
		attackChance = 20;
	}
	else   {  //else there is a 60% chance of attack
	
		attackChance = 60;
	}

	//Try to attack

	if (GenerateRandomNumber() < attackChance)  {  // If chance of success is 35, and the GenerateRandomNumber() is anywhere between 1 and 100, theres a 35% chance of success
	
		//do nothing and let code continue on
		//should weapon health be changed at all here

		//dmg*0.05 for every 10 strength
		damage = 5 * (strength_*0.10);

		//If method makes it this far, attack was successful and no weapon needs to be equipped

		if (character.GetState() == CharacterState::Defending)  {  //If enemy character is defending, do whats in the else
		
			//10% total damage dealt, 50% dmg penalty for brawl method
			newHealth = character.GetHealth() - ((character.GetHealth() / 100 * (damage + 10) / 2));
			armourHealth = character.GetArmour(character.GetEquippedArmour()).GetArmourHealth();
			newArmourHealth = armourHealth / 100 * 90;
			equipped = character.GetEquippedArmour();
		}
		else if (character.GetState() == CharacterState::Sleeping)  {
		
			//Instant kill, set health to 0
			character.SetHealth(0);
			return true;
		}
		else if (character.GetState() == CharacterState::Dead)  {
		
			return false; //dead, so nothing happens, end this method
		}
		else  {
		
			//– 20% health to the character being attacked for all other states. Includes 50% penalty for brawl
			newHealth = (character.GetHealth() - (character.GetHealth() / 5)) / 2;
		}
	}
	else   {  //attack fails, so return and do not deal dmg
	
		if (character.GetEquippedArmour() != -1) {
			this->GetWeapon(this->GetEquippedWeapon()).SetWeaponHealth((this->GetWeapon(this->GetEquippedWeapon()).GetWeaponHealth()) - (this->GetWeapon(this->GetEquippedWeapon()).GetWeaponHealth() * GenerateRandomNumber2()));
		}
		//attacking characters weapon heath goes down by between 10 and 20
		return false; //stop this method in its tracks
	}

	//The health of the defending characters armour will also be reduced by 10%

	//Deal damage to enenmy character
	character.SetHealth(newHealth);
	character.GetArmour(equipped).SetArmourHealth(newArmourHealth);
	if (this->GetWeapon(this->GetEquippedWeapon()).GetWeaponHealth() <= 0) {
		this->DropItem(this->GetWeapon(this->GetEquippedWeapon()));
	}
	if (character.GetArmour(character.GetEquippedArmour()).GetArmourHealth() <= 0) {
		character.DropItem(character.GetArmour(character.GetEquippedArmour()));
	}
	//After attacking the character goes idle
	this->SetState(CharacterState::Idle);
	return true;
}

void Brawler::Sleep()  {
	//heals by 20%
	this->SetHealth(this->GetHealth() * 1.2f);
	if (this->GetHealth() > 100.0f) {
		this->SetHealth(100.0f);
	}
}

int Brawler::GetPunchDamage() const  {
	return punchDamage_;
}

void Brawler::SetPunchDamage(int punchDamage)  {
	punchDamage_ = punchDamage;
}



float Brawler::GenerateRandomNumber()  {
	std::random_device rd; //The random number device. Will be used to obtain a seed for the random number engine
						   //Call the constructor of the object rd and use the RD engine to create a mersenne_twister_engine
						   //The mersenne_twister_engine is based on the Mersenne twister algorithm
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
							//Create a new distribution object with min and max values. So the range the random number should fall between
	std::uniform_real_distribution<> dis(0, 1);

	//Generate the randome number passing in the mersenne_twister_engine generator
	float outcome = dis(gen);
	std::cout << "Outcome " << outcome << std::endl;

	return outcome;
}
float Brawler::GenerateRandomNumber2()  {
	std::random_device rd; //The random number device. Will be used to obtain a seed for the random number engine
						   //Call the constructor of the object rd and use the RD engine to create a mersenne_twister_engine
						   //The mersenne_twister_engine is based on the Mersenne twister algorithm
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
							//Create a new distribution object with min and max values. So the range the random number should fall between
	std::uniform_real_distribution<> dis(0.10, 0.20);

	//Generate the randome number passing in the mersenne_twister_engine generator
	float outcome = dis(gen);
	std::cout << "Outcome " << outcome << std::endl;

	return outcome;
}

