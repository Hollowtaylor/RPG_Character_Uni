#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Assignment_UnitTests
{
	TEST_CLASS(CharacterManagement)
	{
	public:

		TEST_METHOD(TestBrawlerConstructor)
		{
			//Arrange the data
			std::string expectedName{ "Jim" };
			Brawler brawler{ "Jim", 100.0f, 120.0f, 50, CharacterState::Idle, 60, 80 };

			//Act
			std::string characterName = brawler.GetName();

			//Assert
			Assert::AreEqual(expectedName, characterName);
		}

		TEST_METHOD(TestEatConsumesFood)
		{
			//Tests that food gets consumed by eat function
			//Arrange the data
			int expectedFood{ 16 }, actualFood;
			Brawler brawler{ "Jim", 100.0f, 120.0f, 20, CharacterState::Idle, 60, 80 };

			//Act
			brawler.Eat();
			actualFood = brawler.GetFood();

			//Assert
			Assert::AreEqual(expectedFood, actualFood);
		}

		TEST_METHOD(TestEatIncreasesHealth)
		{

			//	Consumes 20% of the available food. Each unit (1) of food consumed will add 0.25 units of health to the character.
			//Tests that health increases correctly by eat function 
			//Arrange the data
			float expectedHealth{ 52.5f }, actualHealth; //(health should not exceed 100)
			Brawler brawler{ "Jim", 50.0f, 120.0f, 50, CharacterState::Idle, 60, 80 };

			//Act
			brawler.Eat();
			actualHealth = brawler.GetHealth();

			//Assert
			Assert::AreEqual(expectedHealth, actualHealth);
		}

		TEST_METHOD(TestHealthCapped)
		{
			//Tests that health does not exceed 100 by eat function 
			//Arrange the data
			float expectedHealth{ 100.0f }, actualHealth; //(health should not exceed 100)
			Brawler brawler{ "Jim", 100.0f, 120.0f, 50, CharacterState::Idle, 60, 80 };
			

			//Act
			brawler.Eat();
			actualHealth = brawler.GetHealth();

			//Assert
			Assert::AreEqual(expectedHealth, actualHealth);
		}

	};

}


namespace Conflict_UnitTests
{
	TEST_CLASS(Conflict)
	{
	public:
		TEST_METHOD(Defend1)
		{
			//Test that the character enters defending state
			//Arrange the data
			int expectedState{ 4 }, actualState;
			Brawler brawler{ "Jim", 100.0f, 120.0f, 50, CharacterState::Idle, 60, 80 };

			//Act
			brawler.Defend(1); //invalid index! no armour in vector
			actualState = static_cast<int>(brawler.GetState());

			//Assert
			Assert::AreEqual(expectedState, actualState);
		}

		TEST_METHOD(Defend2)
		{
			//Test that the character selected armour remains -1 
			//Arrange the data
			int expectedIndex{ -1 }, actualIndex;
			Brawler brawler{ "Jim", 100.0f, 120.0f, 50, CharacterState::Idle, 60, 80 };

			//Act
			brawler.Defend(0); //invalid index! no armour in vector
			actualIndex = brawler.GetEquippedArmour();

			//Assert
			Assert::AreEqual(expectedIndex, actualIndex);
		}
		TEST_METHOD(AttackFail)
		{
			bool attack;
			BlackWitch blackwitch{ "Scarlett", 100.0f, 120.0f, 30, CharacterState::Idle, 30, 50 };
			Brawler brawler{ "Jim", 100.0f, 120.0f, 50, CharacterState::Idle, 60, 80 };
			Armour glove{ "Leather glove", 3, 0.25f, 1, 100, ArmourType::Leather };
			Armour chainMail{ "Chain Mail", 45, 85.0f, 200, 100, ArmourType::Steel };

			brawler.PickUpArmour(chainMail);

			attack = blackwitch.Attack(brawler);

			Assert::IsFalse(attack);

		}
		TEST_METHOD(AttackSuccessNoArmour)
		{
			bool attack = true;
			BlackWitch blackwitch{ "Scarlett", 100.0f, 120.0f, 30, CharacterState::Idle, 30, 50 };
			Brawler brawler{ "Jim", 100.0f, 120.0f, 50, CharacterState::Idle, 60, 80 };
			Armour glove{ "Leather glove", 3, 0.25f, 1, 100, ArmourType::Leather };
			Armour chainMail{ "Chain Mail", 45, 85.0f, 200, 100, ArmourType::Steel };
			Weapon spear{ "spear", 15, 6.0f , 25, 100 };
			Weapon bow{ "bow", 15, 3.0f , 25, 100 };

			
			blackwitch.PickUpWeapon(spear);
			blackwitch.EquipWeapon(0);
			blackwitch.PickUpArmour(chainMail);
			

			attack = blackwitch.Attack(brawler);

			Assert::IsTrue(attack);
		}
		TEST_METHOD(AttackBrawler)
		{
			float health{ 50.0f };
			float healthResult;
			BlackWitch blackwitch{ "Scarlett", 100.0f, 120.0f, 30, CharacterState::Idle, 30, 50 };
			Brawler brawler{ "Jim", 100.0f, 120.0f, 50, CharacterState::Idle, 60, 40 };
			Armour glove{ "Leather glove", 3, 0.25f, 1, 100, ArmourType::Leather };
			Armour chainMail{ "Chain Mail", 45, 85.0f, 200, 100, ArmourType::Steel };
			Weapon spear{ "spear", 15, 6.0f , 25, 100 };
			Weapon bow{ "bow", 15, 3.0f , 25, 100 };

			blackwitch.PickUpWeapon(bow);
			blackwitch.PickUpArmour(glove);
			brawler.PickUpWeapon(spear);
			brawler.PickUpArmour(chainMail);
			blackwitch.Defend(0);
			blackwitch.EquipWeapon(0);
			brawler.EquipWeapon(0);

			brawler.Attack(blackwitch);

			healthResult = blackwitch.GetHealth();
			
			Assert::AreEqual(health, healthResult);
		}
		TEST_METHOD(DefendingAmrDamage)
		{
			int armourhealth{ 90 };
			int armourhealthresult;
			BlackWitch blackwitch{ "Scarlett", 100.0f, 120.0f, 30, CharacterState::Idle, 30, 50 };
			Brawler brawler{ "Jim", 100.0f, 120.0f, 50, CharacterState::Idle, 60, 80 };
			Armour glove{ "Leather glove", 3, 0.25f, 1, 100, ArmourType::Leather };
			Armour chainMail{ "Chain Mail", 45, 85.0f, 200, 100, ArmourType::Steel };
			Weapon spear{ "spear", 15, 6.0f , 25, 100 };
			Weapon bow{ "bow", 15, 3.0f , 25, 100 };

			blackwitch.PickUpWeapon(bow);
			blackwitch.PickUpArmour(glove);
			brawler.PickUpWeapon(spear);
			brawler.PickUpArmour(chainMail);
			blackwitch.Defend(0);
			blackwitch.EquipWeapon(0);
			brawler.EquipWeapon(0);

			brawler.Attack(blackwitch);

		armourhealthresult = blackwitch.GetArmour(0).GetArmourHealth();

			Assert::AreEqual(armourhealth, armourhealthresult);
		}
		TEST_METHOD(WeaponHealth)
		{
			int weaponhealth{ 90 };
			int weaponhealthresult;
			BlackWitch blackwitch{ "Scarlett", 100.0f, 120.0f, 30, CharacterState::Idle, 30, 50 };
			Brawler brawler{ "Jim", 100.0f, 120.0f, 50, CharacterState::Idle, 60, 80 };
			Armour glove{ "Leather glove", 3, 0.25f, 1, 100, ArmourType::Leather };
			Armour chainMail{ "Chain Mail", 45, 85.0f, 200, 100, ArmourType::Steel };
			Weapon spear{ "spear", 15, 6.0f , 25, 100 };
			Weapon bow{ "bow", 15, 3.0f , 25, 100 };

			blackwitch.PickUpWeapon(bow);
			blackwitch.PickUpArmour(chainMail);
			brawler.PickUpWeapon(spear);
			brawler.PickUpArmour(glove);
			blackwitch.Defend(0);
			blackwitch.EquipWeapon(0);
			brawler.EquipWeapon(0);

			brawler.Attack(blackwitch);

			weaponhealthresult = brawler.GetWeapon(0).GetWeaponHealth();

			Assert::AreEqual(weaponhealth, weaponhealthresult);
		}
	};
}

namespace Inventory_UnitTests
{
	TEST_CLASS(InventoryManagement)
	{
	public:

		TEST_METHOD(TestAddItemWeight)
		{
			//Test that adding items above weight limit fails
			//Arrange the data
			bool addItemResult;
			//No point initialising vectors as character should start off with no items.
			Brawler brawler{ "Jim", 100.0f, 10.0f, 0, CharacterState::Idle, 60, 80 };
			Armour glove{ "Leather glove", 3, 0.25f, 1, 100, ArmourType::Leather };
			Armour chainMail{ "Chain Mail", 45, 85.0f, 200, 100, ArmourType::Steel };
			Weapon spear{ "spear", 15, 6.0f , 25, 100 };
			Weapon bow{ "bow", 15, 3.0f , 25, 100 };


			//Act
			addItemResult = brawler.PickUpWeapon(spear);
			addItemResult = brawler.PickUpArmour(glove);
			addItemResult = brawler.PickUpArmour(chainMail);

			//Assert - add weapon should be false as the weight exceeds the limit
			Assert::IsFalse(addItemResult);
		}

		TEST_METHOD(TestAddWeaponWeight)
		{
			//Test that adding items above weight limit fails
			//Arrange the data
			bool addWeaponResult;
			//No point initialising vectors as character should start off with no items.
			Brawler brawler{ "Jim", 100.0f, 10.0f, 0, CharacterState::Idle, 60, 80 };
			Weapon spear{ "spear", 15, 6.0f , 25, 100};
			Weapon bow{ "bow", 15, 6.0f , 25, 100};


			//Act
			addWeaponResult = brawler.PickUpWeapon(spear);
			addWeaponResult = brawler.PickUpWeapon(bow);

			//Assert - add weapon should be false as the weight exceeds
			Assert::IsFalse(addWeaponResult);
		}

		TEST_METHOD(TestAddArmourWeight)
		{
			//Test that adding items above weight limit fails
			//Arrange the data
			bool addArmourResult;
			//No point initialising vectors as character should start off with no items.
			Brawler brawler{ "Jim", 100.0f, 40.0f, 0, CharacterState::Idle, 60, 80 };
			Armour shield{ "Shield", 40, 40.0f, 50, 100, ArmourType::Leather };
			Armour hat{ "Tinfoil Hat", 2, 0.5f, 1, 100, ArmourType::Cardboard };

			//Act
			addArmourResult = brawler.PickUpArmour(shield);
			addArmourResult = brawler.PickUpArmour(hat);

			//Assert - add weapon should be false as the weight exceeds
			Assert::IsFalse(addArmourResult);
		}

		TEST_METHOD(TestAddWeapons)
		{
			//Arrange the data
			Brawler brawler{ "Jim", 100.0f, 120.0f, 0, CharacterState::Idle, 60, 80 };
			Weapon spear{ "spear", 15, 6.0f , 25, 100};
			Weapon bow{ "bow", 15, 3.0f , 25, 100};
			Weapon spear2{ "Lance of Longinus", 10, 2.0f , 2, 70};
			Weapon arrow{ "arrow", 15, 6.0f , 25, 100};

			brawler.PickUpWeapon(spear);
			brawler.PickUpWeapon(bow);
			brawler.PickUpWeapon(spear2);
			brawler.PickUpWeapon(arrow);
			brawler.PickUpWeapon(arrow);
			brawler.PickUpWeapon(arrow);
			brawler.PickUpWeapon(arrow);

			std::string expectedWeaponName{ "Lance of Longinus" };

			//Act
			Weapon tempWeapon = brawler.GetWeapon(2);
			std::string weaponName = tempWeapon.GetItemName();

			//Assert
			Assert::AreEqual(expectedWeaponName, weaponName);
		}

		TEST_METHOD(TestDropWeapon)
		{
			//Test Drop weapon
			//Arrange the data
			std::string expectedWeaponName{ "spear" };
			Brawler brawler{ "Jim", 100.0f, 120.0f, 0, CharacterState::Idle, 60, 80 };
			Weapon spear1{ "spear", 15, 6.0f , 25, 100};
			Weapon bow{ "bow", 15, 3.0f , 25, 100};
			Weapon spear2{ "spear", 10, 2.0f , 2, 70};

			brawler.PickUpWeapon(spear1);
			brawler.PickUpWeapon(bow);
			brawler.PickUpWeapon(spear2);

			//Act

			brawler.DropItem(spear2); //Weapon spear2 should be removed not spear2 - same name different attributes!

			Weapon tempWeapon = brawler.GetWeapon(0);
			std::string actualWeaponName = tempWeapon.GetItemName();

			//Assert
			Assert::AreEqual(expectedWeaponName, actualWeaponName);
		}

		TEST_METHOD(TestDropArmour)
		{
			//Test Drop weapon
			//Arrange the data
			std::string expectedArmourName{ "Cardboard suit of armour" };
			Brawler brawler{ "Jim", 100.0f, 120.0f, 0, CharacterState::Idle, 60, 80 };
			Armour shield{ "Shield", 40, 40, 50, 100, ArmourType::Leather };
			Armour hat{ "Tinfoil Hat", 2, 0.5f, 1, 100, ArmourType::Cardboard };
			Armour glove1{ "Leather glove", 1, 0.23f, 1, 100, ArmourType::Leather };
			Armour suit{ "Cardboard suit of armour", 10, 2.0f, 15, 100, ArmourType::Cardboard };
			Armour glove2{ "Leather glove", 1, 0.2f, 1, 75, ArmourType::Leather };

			brawler.PickUpArmour(shield);
			brawler.PickUpArmour(hat);
			brawler.PickUpArmour(glove1);
			brawler.PickUpArmour(suit);
			brawler.PickUpArmour(glove2);

			//Act
			brawler.DropItem(glove1); //Weapon spear2 should be removed not spear2 - same name different attributes!

			Armour tempArmour = brawler.GetArmour(2);
			std::string actualArmourName = tempArmour.GetItemName();

			//Assert
			Assert::AreEqual(expectedArmourName, actualArmourName);

		}

	};
}