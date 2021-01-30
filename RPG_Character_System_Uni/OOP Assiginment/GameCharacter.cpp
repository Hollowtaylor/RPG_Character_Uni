#include "GameCharacter.h"




GameCharacter::GameCharacter(std::string name, float health, float weight, int food, CharacterState state)
	: characterName_(name), health_(health), weigthLimit_(weight), food_(food), state_(state)  {
}


GameCharacter::~GameCharacter()  {
}

void GameCharacter::Defend(int armour)  {
	//Equips armour at index int armour
	if (armourary_.empty()) {
		equippedArmour_ = -1;
	}
	else {
		equippedArmour_ = armour;
		state_ = CharacterState::Defending;
		
	}
	//armour[i]
	//changes state to defending
	state_ = CharacterState::Defending;
}

void GameCharacter::Walk()  {
	state_ = CharacterState::Walking;
}

void GameCharacter::Run()  {
	state_ = CharacterState::Running;
}

void GameCharacter::Sleep()  {
	//Not sure this has to be here, virtual?
	state_ = CharacterState::Sleeping;
}

Weapon& GameCharacter::GetWeapon(int index)  {
	//return copy of weapon at index
	// E.G items.[index] = weopan
	return weapons_[index];
}

Armour& GameCharacter::GetArmour(int index)  {
	//returns copy of weopan at index
	//E.G items.[index] = armour
	return armourary_[index];
}

bool GameCharacter::PickUpWeapon(Weapon & weapon)  {
	float totalWeight{ 0.0f };
	//Tries to add weapon to characters woepan vector
	//true if added, false if it isnt added
	for (std::vector<int>::size_type i = 0; i != weapons_.size(); i++) {
		totalWeight += weapons_[i].GetWeight();
	}
	for (std::vector<int>::size_type i = 0; i != armourary_.size(); i++) {
		totalWeight += armourary_[i].GetWeight();
	}
	if ((weapon.GetWeight() + totalWeight) > weigthLimit_) {
		return false;
	}
	else {
		weapons_.push_back(weapon);
		return true;
	}
	//If ITEM WEIGHT + TotalWeight of other items doesnt exeed weightLimit
}

bool GameCharacter::PickUpArmour(Armour & armour)  {
	//Tries to add armour to characters armour vector
	//true if added, falise if it isnt

	float totalWeight{ 0.0f };
	//Tries to add weapon to characters woepan vector
	//true if added, false if it isnt added
	for (std::vector<int>::size_type i = 0; i != armourary_.size(); i++) {
		totalWeight += armourary_[i].GetWeight();
	}
	for (std::vector<int>::size_type i = 0; i != weapons_.size(); i++) {
		totalWeight += weapons_[i].GetWeight();
	}
	if ((armour.GetWeight() + totalWeight) > weigthLimit_) {
		return false;
	}
	else {
		armourary_.push_back(armour);
		return true;
	}
	//Item can only be added if the item weight plus total weight of other items in nventory (weapons and armour) doesnt exceed weightLimit
}

void GameCharacter::DropItem(Armour &item)  {
	//remove armour from characters inventory
	for (std::vector<int>::size_type i = 0; i != armourary_.size(); i++) {
		if (item.GetItemName() == armourary_[i].GetItemName()) {
			if (item.GetItemValue() == armourary_[i].GetItemValue()) {
				if (item.GetWeight() == armourary_[i].GetWeight()) {
					armourary_.erase(armourary_.begin() + i);
				}
			}
		}
	}
	//items.push_back[item];
}

void GameCharacter::DropItem(Weapon &weapon)  {
	//remove weapon from characters inventory
	for (std::vector<int>::size_type i = 0; i != weapons_.size(); i++) {
		if (weapon.GetItemName() == weapons_[i].GetItemName()) {
			if (weapon.GetItemValue() == weapons_[i].GetItemValue()) {
				if (weapon.GetWeight() == weapons_[i].GetWeight()) {
					int b = i;
					weapons_.erase(weapons_.begin() + b);
					return;
				}
			}
		}
	}
	//items.push_back[weapon];
}

bool GameCharacter::EquipWeapon(int weapon)  {
	//sets weapom_ to index of inventory that points at the weopan, if successful return true
	if (weapons_.empty()) {
		equippedWeapon_ = -1;
		return false;
	}
	else {
		equippedWeapon_ = weapon;
		return true;
	}
	// IF theres no weapon, set it to -1 to indicate no weapon
	//This will stop the attack
	
}

CharacterState& GameCharacter::GetState()  {
	//return current state, sleeping walking etc
	return state_;
}

void GameCharacter::SetState(CharacterState state)  {
	state_ = state;
}

void GameCharacter::AddFood(int amount)  {
	food_ += amount;
}

void GameCharacter::Eat()  {
	//consumes 20% of available food
	int tempfood;
	tempfood = food_;
	food_ = (food_  / 5) * 4;
	tempfood -= food_;

	//each unit (1) of food adds 0.25 units of health
	for (int i = 0; i != tempfood; i++) {
		health_ += 0.25f;
	}
	if (health_ > 100.0f) {
		health_ = 100.0f;
	}
}

float GameCharacter::GetHealth() const  {
	return health_;
}

void GameCharacter::SetHealth(float health)  {

	if (health > 100.0f)  {
		health_ = 100.0f;
		return;
	}
	else if (health <= 0)  {
		health_ = 0.0f;
		state_ = CharacterState::Dead;
		return;
	}
	else  {
		health_ = health;
	}
}

float GameCharacter::GetWeightLimit() const  {
	return weigthLimit_;
}

void GameCharacter::SetWeightLimit(float weightLimit)  {
	weigthLimit_ += weightLimit;
}




int GameCharacter::GetFood() const  {
	return food_;
}

void GameCharacter::SetFood(int food)  {
	food_ += food;
}

int GameCharacter::GetEquippedWeapon() const  {
	return equippedWeapon_;
}

int GameCharacter::GetEquippedArmour() const  {
	return equippedArmour_;
}

std::string GameCharacter::GetName() const  {
	return characterName_;
}
