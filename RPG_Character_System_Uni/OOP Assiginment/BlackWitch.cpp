#include "BlackWitch.h"




BlackWitch::BlackWitch(std::string name, float health, float weight, int food, CharacterState state, int magicproficiency, int darkpower)
	: GameCharacter(name, health, weight, food, state), magicProficiency_(magicproficiency), darkPower_(darkpower)  {
}


BlackWitch::~BlackWitch()
{
}

//LOGIC:: //Cant attack if theres no weapon	//Health is below 20  //target character is dead
bool BlackWitch::Attack(GameCharacter &character)  {
	
	//These variables will be used later on, theyre done up here for aesthedics
	float newHealth{ 0.0f };
	int armourHealth;
	int newArmourHealth;
	int equipped;
	int damage{ 0 };

	

	//Equip weapon testing

	//If no weapon is equipped, the Health of this character is below 20, or theyre dead then end this method in its tracks
	if (this->GetEquippedWeapon() == -1 || this->GetHealth() <= 20 || this->GetState() == CharacterState::Dead)  {
		return false;	//Attack unsuccessful, return false
	}


	//Attack here, if successful then you move on to see what damage is dealt

	//determine chance of success from attack logic 
	float attackChance;
	if (character.GetEquippedArmour() == -1)  { //else there is a 60% chance of attack
	
		attackChance = 0.80f;
	}
	else if (this->GetWeapon(this->GetEquippedWeapon()).GetWeaponHitStrength() < character.GetArmour(character.GetEquippedArmour()).GetDefence())  { //if weapon dmg < defence value of defending, 20% of attack 
		attackChance = 0.20f;
	}
	else { //else theres a 60% chance
		attackChance = 0.60f;
	}

	//Try to attack

	if (GenerateRandomNumber() < attackChance) { // If chance of success is 35, and the GenerateRandomNumber() is anywhere between 1 and 100, theres a 35% chance of success

		//do nothing and let code continue on
		//should weapon health be changed at all here



	//if dark power is at 100%, dmg increased by 20%
		if (darkPower_ == 100) {
			//percentages
			damage = 20;
		}

		//If method makes it this far, attack was successful as equip weapon returns to main if its not valid
		if (character.GetState() == CharacterState::Defending) {  //If enemy character is defending, do whats in the else

			//10% total damage dealt if defending
			newHealth = character.GetHealth() - (character.GetHealth() / 100 * (damage + 10));
			armourHealth = character.GetArmour(character.GetEquippedArmour()).GetArmourHealth();
			newArmourHealth = armourHealth / 100 * 90;
			equipped = character.GetEquippedArmour();

		}
		else if (character.GetState() == CharacterState::Sleeping) {
			//Instant kill
			character.SetHealth(0);
			return true;
		}
		else if (character.GetState() == CharacterState::Dead) {
			return false; //dead, so nothing happens to target
		}
		else {
			//– 20% health to the character being attacked for all other states. 
			newHealth = character.GetHealth() - (character.GetHealth() / 5);
		}
	}
	else { //attack fails, so return and do not deal dmg

		if (character.GetEquippedArmour() != -1) {
			this->GetWeapon(this->GetEquippedWeapon()).SetWeaponHealth(this->GetWeapon(this->GetEquippedWeapon()).GetWeaponHealth() - (this->GetWeapon(this->GetEquippedWeapon()).GetWeaponHealth() / GenerateRandomNumber2()));
		}
		//attacking characters weapon heath goes down by between 10 and 20
		return false; //stop this method in its tracks
	}
	
	//Deal damage to enemey character
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


	//Wamt sdhane do check my logic
}

void BlackWitch::Bewitch(GameCharacter & character)  {
	//Attempts to place target in sleeping state
	//10% chance of success, increased by 5% with each level of magicProfiviency
	//Magic Proficiency level*5 + 10 = chance of success
	//E.G if lvl 5, 5*5 = 25 +10 base chance = 35% chance of success

	const int baseChance = 10; //10% is always the base chance

	int chanceOfSuccess = baseChance;  //chance of success starts at baseChance
	chanceOfSuccess += (magicProficiency_ * 5); //Increase % chance depending on lvl of magicProficiency

	if (GenerateRandomNumber() < chanceOfSuccess)  { // If chance of success is 35, and the val is anywhere between 1 and 100, theres a 35% chance of success
	
		//Set bad guys state to sleeping
		character.SetState(CharacterState::Sleeping);
	}
}

void  BlackWitch::Sleep()  {
	//heals by 15%
	this->SetHealth(this->GetHealth() * 1.15f);
	if (this->GetHealth() > 100.0f) {
		this->SetHealth(100.0f);
	}
}

int BlackWitch::GetMagicProficiency() const  {
	return magicProficiency_;
}

void BlackWitch::SetMagicProficiency(int magicProficiency)  {
	magicProficiency_ = magicProficiency;
}

int BlackWitch::GetDarkPower() const  {
	return darkPower_;
}

void BlackWitch::SetDarkPower(int darkPower)  {
	darkPower_ = darkPower;
}

float BlackWitch::GenerateRandomNumber()  {
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
float BlackWitch::GenerateRandomNumber2()  {
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

