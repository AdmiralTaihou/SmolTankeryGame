#include "smolTankeryGame.h"
#include <string>

bool tank1MediumFlag = true;
bool tank2MediumFlag = true;
bool tank1SuperHeavyFlag = true;
bool tank2SuperHeavyFlag = true;
bool victory = false;

Tactics tank1Tactics = 0;
Tactics tank2Tactics = 0;
std::string loaderChoice = "";

tankType type; std::string name; crewRole role; Experience experience;


Tank::Tank(const tankType& type) {

	switch(type){
	case light:
		Tank::health = 45;
		Tank::evasion = 70;
		Tank::damage = 20;
		Tank::type = light;
		break;
	case medium:
		Tank::health = 60;
		Tank::evasion = 50;
		Tank::damage = 30;
		Tank::type = medium;
		break;
	case tankDestroyer:
		Tank::health = 70;
		Tank::evasion = 50;
		Tank::damage = 30;
		Tank::type = tankDestroyer;
		break;
	case heavy:
		Tank::health = 80;
		Tank::evasion = 30;
		Tank::damage = 40;
		Tank::type = heavy;
		break;
	case superHeavy:
		Tank::health = 110;
		Tank::evasion = 20;
		Tank::damage = 40;
		Tank::type = superHeavy;
		break;
	default:
		throw std::exception("Incorrect input for tank type.");
	}
}

Crew::Crew(const crewRole& role) {
	switch (role) {
	case driver:
		Crew::role = driver;
		break;
	case gunner:
		Crew::role = gunner;
		break;
	case loader:
		Crew::role = loader;
		break;
	case radio:
		Crew::role = radio;
		break;
	case commander:
		Crew::role = commander;
		break;
	default:
		Crew::role = blank;
	}
}

void addStaticCrewValues(Tank& tank, const Crew& crew) 
{
	if (crew.experience != 0) {

		switch (crew.role) {
		case driver:
			std::cout << crew.name << " increases " << tank.name << "'s evasion by " << crew.experience * 5 << " points." << std::endl << std::endl;
			tank.evasion += crew.experience * 5;
			break;
		case gunner:
			std::cout << crew.name << " increases " << tank.name << "'s damage output by " << crew.experience * 5 << " points." << std::endl << std::endl;
			tank.damage += crew.experience * 5;
			break;
		case radio:
			std::cout << crew.name << " increases " << tank.name << "'s health by " << crew.experience * 5 << " points." << std::endl << std::endl;
			tank.health += crew.experience * 5;
			break;
		case commander:
			switch (crew.experience) {
			case 1:
				std::cout << crew.name << " increases " << tank.name << "'s evasion by 5 points." << std::endl << std::endl;
				tank.evasion += 5;
				break;
			case 2:
				std::cout << crew.name << " increases " << tank.name << "'s evasion and damage output by 5 points." << std::endl << std::endl;
				tank.evasion += 5;
				tank.damage += 5;
				break;
			}
			break;

		default:
			break;
		}
	}
	else {
		std::cout << crew.name << " does not contribute to this battle with their experience." << std::endl << std::endl;
	}
}

Accuracy calculateAccuracy(const Tank& tankA, const Tank& tankB)
{

	Accuracy attackRoll = rand() % 100 + 1;

	std::cout << tankA.name << " rolled a " << attackRoll << "." << std::endl;
	std::cout << tankB.name << " has an evasion value of " << tankB.evasion << "." << std::endl << std::endl;

	return attackRoll;
}

int calculateDamage(const Tactics& tankATactics, const Tactics& tankBTactics, const Accuracy& attackRoll, const Tank& tankA, Tank& tankB)
{

	int damageRoll = rand() % tankA.damage + 1;

	if (attackRoll < 95 && tankB.type == 3 && tankBTactics == 0) {
		std::cout << tankB.name << " is a Tank Destroyer and it's not angled...!" << std::endl;
		std::cout << tankB.name << " will take 5 extra points of damage...!" << std::endl;
		std::cout << tankA.name << " is dealing " << (damageRoll + tankATactics * 5 + 5) << " points of damage." << std::endl;
		std::cout << tankB.name << "'s health will be lowered to " << tankB.health - (damageRoll + tankATactics * 5 + 5) << "!" << std::endl << std::endl;
	}
	else if (attackRoll < 95 && tankA.type == 5) {
		std::cout << tankA.name << " is a Super Heavy...!" << std::endl;
		std::cout << tankA.name << " will deal 10 extra points of damage...!" << std::endl;
		std::cout << tankA.name << " is dealing " << (damageRoll + tankATactics * 5 + 10) << " points of damage." << std::endl;
		std::cout << tankB.name << "'s health will be lowered to " << tankB.health - (damageRoll + tankATactics * 5 + 10) << "!" << std::endl << std::endl;
	}
	else if(attackRoll < 95){
		std::cout << tankA.name << " is dealing " << (damageRoll + tankATactics * 5) << " points of damage." << std::endl;
		std::cout << tankB.name << "'s health will be lowered to " << tankB.health - (damageRoll + tankATactics * 5) << "!" << std::endl << std::endl;
	}
	else if(attackRoll >= 95 && tankB.type == 3 && tankBTactics == 0){
		std::cout << tankB.name << " is a Tank Destroyer and it's not angled...!" << std::endl;
		std::cout << tankB.name << " will take 5 extra points of damage...!" << std::endl;
		std::cout << "A critical hit by " << tankA.name << " is dealing" << ((damageRoll + tankATactics * 5) * 2 + 5) << " points of damage to " << tankB.name << "!" << std::endl;
		std::cout << tankB.name << "'s health will be lowered to " << tankB.health - ((damageRoll + tankATactics * 5) * 2 + 5) << "!" << std::endl << std::endl;
	}
	else if (attackRoll > 95 && tankA.type == 5) {
		std::cout << tankA.name << " is a Super Heavy...!" << std::endl;
		std::cout << tankA.name << " deals 10 extra points of damage...!" << std::endl;
		std::cout << "A critical hit by " << tankA.name << " is dealing" << ((damageRoll + tankATactics * 5) * 2 + 10) << " points of damage to " << tankB.name << "!" << std::endl;
		std::cout << tankB.name << "'s health will be lowered to " << tankB.health - ((damageRoll + tankATactics * 5) * 2 + 10) << "!" << std::endl << std::endl;
	}
	else if(attackRoll >= 95) {
		std::cout << "A critical hit by " << tankA.name << " is dealing" << ((damageRoll + tankATactics * 5) * 2) << " points of damage to " << tankB.name << "!" << std::endl;
		std::cout << tankB.name << "'s health will be lowered to " << tankB.health - ((damageRoll + tankATactics * 5) * 2) << "!" << std::endl << std::endl;
	}
	
	return damageRoll;
}

void dealDamage(const int& damage, const Tactics& tankATactics, const Tactics& tankBTactics, const Accuracy& attackRoll, Tank& tank)
{

	if (attackRoll < 95 && tank.type == 3 && tankBTactics == 0) {
		tank.health -= (damage + tankATactics * 5 + 5);
	}
	else if (attackRoll < 95 && tank.type == 5) {
		tank.health -= (damage + tankATactics * 5 + 10);
	}
	else if (attackRoll < 95) {
		tank.health -= (damage + tankATactics * 5);
	}
	else if (attackRoll >= 95 && tank.type == 3 && tankBTactics == 0) {
		tank.health -= ((damage + tankATactics * 5) * 2 + 5);
	}
	else if (attackRoll > 95 && tank.type == 5) {
		tank.health -= ((damage + tankATactics * 5) * 2 + 10);
	}
	else if (attackRoll >= 95) {
		tank.health -= ((damage + tankATactics * 5) * 2);
	}
	std::cout << tank.name << "'s health is now " << tank.health << "!" << std::endl << std::endl;
}

Tactics declareTactics(const Tank& tank)
{
	std::cout << "What will " << tank.name << " do?" << std::endl;
	std::cout << "0 - Maneuver (No Stat change) (DEFAULT)" << std::endl; std::cout << "1 - Angle (+5 Damage if hit, -5 EVA when enemy attacks)" << std::endl;
	Tactics tanktactics = 0;
	std::cin >> tanktactics;
	std::cout << "" << std::endl;
	return tanktactics;
}

void checkMediumTankFlag(Tank& tank, bool& tankFlag)
{
	if (tank.type == medium && tank.health <= 0 && tankFlag == true) {
		tankFlag = false;
		tank.health = 1;
		std::cout << tank.name << " has avoided getting disabled, but is at 1HP!" << std::endl << std::endl;
	}
}

void checkVictoryConditions(const Tank& tank, bool& victory)
{
	if (tank.health <= 0) {
		victory = true;
	}
}

void announceStartOfTurn(const Tank& tankA, const Tank& tankB)
{
	std::cout << "################ NEXT TURN ################" << std::endl;
	std::cout << "Attacker Tank is: " << tankA.name << "." << std::endl;
	std::cout << "Defender Tank is: " << tankB.name << "." << std::endl << std::endl;
}

void announceTactics(const Tactics& tactics, const Tank& tank)
{
	if (tactics == 1) {
		std::cout << tank.name << " is angling." << std::endl << std::endl;
	}
	else {
		std::cout << tank.name << " is maneuvering." << std::endl << std::endl;
	}
}

void victoryWrapper() 
{
	std::cout << "The game is over! Thanks for playing!" << std::endl;
	std::cout << "Go RP this, and after that you can close this window!" << std::endl;
	system("pause");

}

int main(int argc, char* argv[])
{
	std::cout << "Insert a random integer number to create a fight seed." << std::endl;
	std::cout << "If you share it with your friend and choose the same options, the same battle will be recreated." << std::endl << std::endl;
	int seed;
	std::cin >> seed;
	srand(seed);

	std::cout << "Please, input the number corresponding to the class of Tank 1." << std::endl;
	std::cout << "1 - Light Tank" << std::endl; std::cout << "2 - Medium Tank" << std::endl; std::cout << "3 - Tank Destroyer" << std::endl; std::cout << "4 - Heavy Tank" << std::endl; std::cout << "5 - Super Heavy Tank" << std::endl;
	std::cin >> type;
	Tank tank1(type);
	std::cout << "" << std::endl;
	std::cout << "Input the tank model:" << std::endl;
	std::cin.ignore();
	std::getline(std::cin, name);
	tank1.name = name;
	std::cout << "" << std::endl;

	std::cout << "Please choose the role of the crewmember you will use during this battle." << std::endl;
	std::cout << "If you don't want to use bonuses this battle, choose 0." << std::endl;
	std::cout << "0 - Blank/No Role" << std::endl; std::cout << "1 - Driver" << std::endl; std::cout << "2 - Gunner" << std::endl; std::cout << "3 - Loader" << std::endl; std::cout << "4 - Radio Operator" << std::endl; std::cout << "5 - Commander" << std::endl;
	std::cin >> role;
	Crew crew1(role);
	std::cout << "" << std::endl;
	if (role != 0) {
		std::cout << "Please choose how experienced the crewmember is." << std::endl;
		std::cout << "0 - Rookie" << std::endl; std::cout << "1 - Expert" << std::endl; std::cout << "2 - Ace" << std::endl;
		std::cin >> experience;
		crew1.experience = experience;
	}
	std::cout << "" << std::endl;
	std::cout << "Input the crewmember's name:" << std::endl;
	std::cin.ignore();
	std::getline(std::cin, name);
	crew1.name = name;
	std::cout << "" << std::endl;

	std::cout << "Please, input the number corresponding to the class of Tank 2." << std::endl;
	std::cout << "1 - Light Tank" << std::endl; std::cout << "2 - Medium Tank" << std::endl; std::cout << "3 - Tank Destroyer" << std::endl; std::cout << "4 - Heavy Tank" << std::endl; std::cout << "5 - Super Heavy Tank" << std::endl;
	std::cin >> type;
	Tank tank2(type);
	std::cout << "" << std::endl;
	std::cout << "Input the tank model:" << std::endl;
	std::cin.ignore();
	std::getline(std::cin, name);
	tank2.name = name;
	std::cout << "" << std::endl;

	std::cout << "Please choose the role of the crewmember you will use during this battle." << std::endl;
	std::cout << "If you don't want to use bonuses this battle, choose 0." << std::endl;
	std::cout << "0 - Blank/No Role" << std::endl; std::cout << "1 - Driver" << std::endl; std::cout << "2 - Gunner" << std::endl; std::cout << "3 - Loader" << std::endl; std::cout << "4 - Radio Operator" << std::endl; std::cout << "5 - Commander" << std::endl;
	std::cin >> role;
	Crew crew2(role);
	std::cout << "" << std::endl;
	if (role != 0) {
		std::cout << "Please choose how experienced the crewmember is." << std::endl;
		std::cout << "0 - Rookie" << std::endl; std::cout << "1 - Expert" << std::endl; std::cout << "2 - Ace" << std::endl;
		std::cin >> experience;
		crew2.experience = experience;
	}
	std::cout << "" << std::endl;
	std::cout << "Input the crewmember's name:" << std::endl;
	std::cin.ignore();
	std::getline(std::cin, name);
	crew2.name = name;
	std::cout << "" << std::endl;

	addStaticCrewValues(tank1, crew1);
	addStaticCrewValues(tank2, crew2);

	while (victory != true) {

		if ((tank1.type == superHeavy && tank1SuperHeavyFlag == true) || (tank1.type != 5)) {

		announceStartOfTurn(tank1, tank2);

		Tactics tank1Tactics = declareTactics(tank1);

		announceTactics(tank1Tactics, tank1);

		Accuracy attackRoll1 = calculateAccuracy(tank1, tank2);


		tank1SuperHeavyFlag = false;

			if (attackRoll1 >= tank2.evasion - tank2Tactics * 5) {

				Damage damageRoll = calculateDamage(tank1Tactics, tank2Tactics, attackRoll1, tank1, tank2);

				if (crew1.role == loader && crew1.experience != 0) {
					std::cout << crew1.name << " is an experience loader! Do you want to reroll the damage? y / n(default)" << std::endl;
					std::cin.ignore();
					std::getline(std::cin, loaderChoice);
					if (loaderChoice == "y") {
						damageRoll = calculateDamage(tank1Tactics, tank2Tactics, attackRoll1, tank1, tank2) + (crew1.experience - 1) * 5;
					}
					else {
						//If "n" or other input -> Do nothing
					}
				}
				dealDamage(damageRoll, tank1Tactics, tank2Tactics, attackRoll1, tank2);
			}

			else {

				std::cout << "It's a miss!" << std::endl;
				std::cout << "" << std::endl;

				if (tank1.type == light) {

					std::cout << tank1.name << " is a light tank! It quickly reloads and shoots again!" << std::endl;
					std::cout << "" << std::endl;

					Accuracy attackRoll1B = calculateAccuracy(tank1, tank2);

					if (attackRoll1B >= tank2.evasion - tank2Tactics * 5) {

						Damage damageRoll = calculateDamage(tank1Tactics, tank2Tactics, attackRoll1B, tank1, tank2);

						if (crew1.role == loader && crew1.experience != 0) {
							std::cout << crew1.name << " is an experience loader! Do you want to reroll the damage? y / n(default)" << std::endl;
							std::cin.ignore();
							std::getline(std::cin, loaderChoice);
							if (loaderChoice == "y") {
								damageRoll = calculateDamage(tank1Tactics, tank2Tactics, attackRoll1B, tank1, tank2) + (crew1.experience - 1) * 5;
							}
							else {
								//If "n" or other input -> Do nothing
							}
						}
						dealDamage(damageRoll, tank1Tactics, tank2Tactics, attackRoll1B, tank2);
					}
				}
			}

			checkMediumTankFlag(tank2, tank2MediumFlag);
			checkVictoryConditions(tank2, victory);

			if (victory == true && tank1.health > 0) {
				std::cout << tank2.name << " has been disabled!" << std::endl;
				std::cout << tank1.name << " wins!" << std::endl << std::endl;
			}

			while (victory == true) {
				victoryWrapper();
			}
		}

		else {
			std::cout << "################ NEXT TURN ################" << std::endl;
			std::cout << tank1.name << " is a Super Heavy tank and needs to take one turn to be operational again!" << std::endl;
			std::cout << "" << std::endl;
			tank1SuperHeavyFlag = true;
		}

		std::cout << "################ PLAYER 2 TURN ################" << std::endl << std::endl;
		// SECOND PLAYER TURN

		if ((tank2.type == 5 && tank2SuperHeavyFlag == true) || (tank2.type != 5)) {
		Tactics tank2Tactics = declareTactics(tank2);

		announceTactics(tank2Tactics, tank2);

		Accuracy attackRoll2 = calculateAccuracy(tank2, tank1);

		tank2SuperHeavyFlag = false;

		if (attackRoll2 >= tank1.evasion - tank1Tactics * 5) {

			Damage damageRoll = calculateDamage(tank2Tactics, tank1Tactics, attackRoll2, tank2, tank1);

			if (crew2.role == loader && crew2.experience != 0) {
				std::cout << crew2.name << " is an experience loader! Do you want to reroll the damage? y / n(default)" << std::endl;
				std::cin.ignore();
				std::getline(std::cin, loaderChoice);
				if (loaderChoice == "y") {
					damageRoll = calculateDamage(tank2Tactics, tank1Tactics, attackRoll2, tank2, tank1) + (crew2.experience - 1) * 5;
				}
				else {
					//If "n" or other input -> Do nothing
				}
			}
			dealDamage(damageRoll, tank2Tactics, tank1Tactics, attackRoll2, tank1);
		}

		else {

			std::cout << "It's a miss!" << std::endl;

			if (tank2.type == light) {

				std::cout << tank2.name << " is a light tank! It quickly reloads and shoots again!" << std::endl;
				std::cout << "" << std::endl;

				Accuracy attackRoll2B = calculateAccuracy(tank2, tank1);

				if (attackRoll2B >= tank1.evasion - tank1Tactics * 5) {

					Damage damageRoll = calculateDamage(tank2Tactics, tank1Tactics, attackRoll2B, tank2, tank1);

					if (crew2.role == loader && crew2.experience != 0) {
						std::cout << crew2.name << " is an experience loader! Do you want to reroll the damage? y / n(default)" << std::endl;
						std::cin.ignore();
						std::getline(std::cin, loaderChoice);
						if (loaderChoice == "y") {
							damageRoll = calculateDamage(tank2Tactics, tank1Tactics, attackRoll2B, tank2, tank1) + (crew2.experience - 1) * 5;
						}
						else {
							//If "n" or other input -> Do nothing
						}
					}
					dealDamage(damageRoll, tank2Tactics, tank1Tactics, attackRoll2B, tank1);

				}
			}

			checkMediumTankFlag(tank1, tank1MediumFlag);
			checkVictoryConditions(tank1, victory);

			if (victory == true && tank2.health > 0) {
				std::cout << tank1.name << " has been disabled!" << std::endl;
				std::cout << tank2.name << " wins!" << std::endl;
			}

			while (victory == true) {
				victoryWrapper();
			}
		}
		}
		else {
		std::cout << "################ NEXT TURN ################" << std::endl;
		std::cout << tank2.name << " is a Super Heavy tank and needs to take one turn to be operational again!" << std::endl;
		std::cout << "" << std::endl;
		tank2SuperHeavyFlag = true;
		}
		system("pause");
	}
	return 0;
}