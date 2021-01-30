#include "Orc.h"




Orc::Orc(std::string name, float health, float weight, int food, CharacterState state, int ferociuosness, int strength)
	: GameCharacter(name, health, weight, food, state), ferociuosness_(ferociuosness), strength_(strength)  {
}


Orc::~Orc()  {
}

//LOGIC:: //Cant attack if theres no weapon	//Health is below 20  //target character is dead
bool Orc::Attack(GameCharacter & character)  {
	//These variables will be used later on, theyre done up here for aesthedics
	float newHealth{ 0.0f };
	int armourHealth;
	int newArmourHealth;
	int equipped;
	double damage;

	if (this->GetEquippedWeapon() == -1 || this->GetHealth() <= 20 || this->GetState() == CharacterState::Dead)  {
		return false;	//Attack unsuccessful, return false
	}

	//Attack here, if successful then you move on to see what damage is dealt

	//Determine chance of success from attack logic 
	float attackChance;
	if (character.GetEquippedArmour() == -1)  {  //If the target has no armour, 80% chance
	
		attackChance = 0.80f;
	}
	else if (this->GetWeapon(this->GetEquippedWeapon()).GetWeaponHitStrength() < character.GetArmour(character.GetEquippedArmour()).GetDefence())  { //if weapon dmg < defence value of defending, 20% of attack
		attackChance = 0.20f;
	}
	else { //else there is a 60% chance of attack
		attackChance = 0.60f;
	}

	//Try to attack

	if (GenerateRandomNumber() < attackChance) { // If chance of success is 35, and the GenerateRandomNumber() is anywhere between 1 and 100, theres a 35% chance of success

		//do nothing and let code continue on
		//should weapon health be changed at all here


	//dmg increased by 5% for every 10 strength
		damage = 5 * (strength_*0.10);

		//If method makes it this far, attack was successful as equip weapon returns to main if its not valid

		if (character.GetState() == CharacterState::Defending) {  //If enemy character is defending, do whats in the else

			//10% total damage dealth
			newHealth = character.GetHealth() - (character.GetHealth() / 100 * (damage + 10));
			armourHealth = character.GetArmour(character.GetEquippedArmour()).GetArmourHealth();
			newArmourHealth = armourHealth / 100 * 90;
			equipped = character.GetEquippedArmour();
		}
		else if (character.GetState() == CharacterState::Sleeping) {
			//Instant kill
			character.SetHealth(0);
			return true; // end method
		}
		else if (character.GetState() == CharacterState::Dead) {
			return false; //dead, so nothing happens
		}
		else {
			//– 20% health to the character being attacked for all other states. 
			newHealth = character.GetHealth() - (character.GetHealth() / 5);
		}
	}
	else //attack fails, so return and do not deal dmg
	{
		if (character.GetEquippedArmour() != -1) {
			this->GetWeapon(this->GetEquippedWeapon()).SetWeaponHealth(this->GetWeapon(this->GetEquippedWeapon()).GetWeaponHealth() - (this->GetWeapon(this->GetEquippedWeapon()).GetWeaponHealth() / GenerateRandomNumber2()));
		}
		//attacking characters weapon heath goes down by between 10 and 20
		return false; //stop this method in its tracks
	}
	character.SetHealth(newHealth);
	//Ricky, does this need to be here?
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

void Orc::Scream(GameCharacter & character)  {
	//20% chance of making target flee, 5% increase with each level of ferociousness
	const int baseChance = 20; //20% is always the base chance

	int chanceOfSuccess = baseChance;  //chance of success starts at baseChance then goes up depending on ferociousness
	chanceOfSuccess += (ferociuosness_ * 5); //Increase % chance depending on lvl of ferociousness

	if (GenerateRandomNumber() < chanceOfSuccess)  { // If chance of success is 35, and the GenerateRandomNumber() is anywhere between 1 and 100, theres a 35% chance of success
	
		//Set bad guys state to Fleeing (Running)
		character.SetState(CharacterState::Running);
	}
}

void Orc::Sleep()  {
	//heals by 15%
	this->SetHealth(this->GetHealth() * 1.2f);
	if (this->GetHealth() > 100.0f) {
		this->SetHealth(100.0f);
	}
}


int Orc::GetFerociousness() const  {
	return ferociuosness_;
}

void Orc::SetFerociousness(int ferociousness)  {
	ferociuosness_ = ferociousness;
}



int Orc::GetStrength() const  {
	return strength_;
}

void Orc::SetStrength(int strength)  {
	strength_ = strength;
}


float Orc::GenerateRandomNumber()  {
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
float Orc::GenerateRandomNumber2()  {
	std::random_device rd; //The random number device. Will be used to obtain a seed for the random number engine
						   //Call the constructor of the object rd and use the RD engine to create a mersenne_twister_engine
						   //The mersenne_twister_engine is based on the Mersenne twister algorithm
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
							//Create a new distribution object with min and max values. So the range the random number should fall between
	std::uniform_real_distribution<> dis(0.1, 0.2);

	//Generate the randome number passing in the mersenne_twister_engine generator
	float outcome = dis(gen);
	std::cout << "Outcome " << outcome << std::endl;

	return outcome;
}

