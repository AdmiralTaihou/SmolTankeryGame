#include "smolTankeryGame.h"
#include <string>



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

Accuracy calculateAccuracy(const Tank& tankA, const Tank& tankB)
{

	Accuracy attackRoll = rand() % 100 + 1;

	std::cout << tankA.name << " rolled a " << attackRoll << "." << std::endl;
	std::cout << tankB.name << " has evasion of " << tankB.evasion << std::endl;

	return attackRoll;
}

void calculateDamage(const Tactics& tankATactics, const Tactics& tankBTactics, const Accuracy& attackRoll, const Tank& tankA, Tank& tankB)
{

	int damageRoll = rand() % tankA.damage + 1;

	if (attackRoll < 95 && tankB.type == 3 && tankBTactics == 0) {
		std::cout << tankB.name << " is a Tank Destroyer and it's not angled...!" << std::endl;
		std::cout << tankB.name << " takes 5 extra points of damage...!" << std::endl;
		tankB.health -= damageRoll + tankATactics * 5;
		std::cout << tankA.name << " deals " << damageRoll + tankATactics * 5 + 5 << " points of damage." << std::endl;
	}
	else if (attackRoll < 95 && tankB.type == 5) {
		std::cout << tankA.name << " is a Super Heavy...!" << std::endl;
		std::cout << tankA.name << " deals 10 extra points of damage...!" << std::endl;
		tankB.health -= damageRoll + tankATactics * 5;
		std::cout << tankA.name << " deals " << damageRoll + tankATactics * 5 + 10 << " points of damage." << std::endl;
	}
	else if(attackRoll < 95){
		tankB.health -= damageRoll + tankATactics * 5;
		std::cout << tankA.name << " deals " << damageRoll + tankATactics * 5 << " points of damage." << std::endl;
	}
	else if(attackRoll >= 95 && tankB.type == 3 && tankBTactics == 0){
		std::cout << tankB.name << " is a Tank Destroyer and it's not angled...!" << std::endl;
		std::cout << tankB.name << " takes 5 extra points of damage...!" << std::endl;
		tankB.health -= (damageRoll + tankATactics * 5) * 2 + 5;
		std::cout << "A critical hit by " << tankA.name << " dealing" << (damageRoll + tankATactics * 5) * 2 + 5 << " points of damage to " << tankB.name << "!" << std::endl;
	}
	else if (attackRoll > 95 && tankB.type == 5) {
		std::cout << tankA.name << " is a Super Heavy...!" << std::endl;
		std::cout << tankA.name << " deals 10 extra points of damage...!" << std::endl;
		tankB.health -= (damageRoll + tankATactics * 5) * 2 + 10;
		std::cout << "A critical hit by " << tankA.name << " dealing" << (damageRoll + tankATactics * 5) * 2 + 10 << " points of damage to " << tankB.name << "!" << std::endl;
	}
	else if(attackRoll >= 95) {
		tankB.health -= (damageRoll + tankATactics * 5) * 2;
		std::cout << "A critical hit by " << tankA.name << " dealing" << (damageRoll + tankATactics * 5) * 2 << " points of damage to " << tankB.name << "!" << std::endl;
	}
	std::cout << tankB.name << "'s health has been lowered to " << tankB.health << "!" << std::endl;


}

Tactics declareTactics(const Tank& tank)
{
	std::cout << "What will " << tank.name << " do?" << std::endl;
	std::cout << "0 - Maneuver" << std::endl; std::cout << "1 - Angle" << std::endl;
	Tactics tanktactics = 0;
	std::cin >> tanktactics;

	return tanktactics;
}

void checkMediumTankFlag(Tank& tank, bool& tankFlag)
{
	if (tank.type == medium && tank.health <= 0 && tankFlag == true) {
		tankFlag = false;
		tank.health = 1;
		std::cout << tank.name << " has avoided getting disabled, but is at 1HP!" << std::endl;
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
	std::cout << "Defendar Tank is: " << tankB.name << "." << std::endl;
}

void announceTactics(const Tactics& tactics, const Tank& tank)
{
	if (tactics > 1 || tactics < 0) {
		throw std::exception("Incorrect value for chosen tactics.");
	}

	if (tactics == 0) {
		std::cout << tank.name << " is maneuvering." << std::endl;
	}
	else {
		std::cout << tank.name << " is angling." << std::endl;
	}
}

void victoryWrapper() {
	std::cout << "The game is over! Thanks for playing!" << std::endl;
	std::cout << "Go RP this, and after that you can close this window!" << std::endl;
}

int main(int argc, char* argv[])
{

	bool victory = false;
	tankType type; std::string name;

	std::cout << "Insert a random integer number to create a fight seed." << std::endl;
	std::cout << "If you share it with your friend and choose the same options, the same battle will be recreated." << std::endl;
	int seed;
	std::cin >> seed;
	srand(seed);

	std::cout << "Please, input the number corresponding to the class of Tank 1." << std::endl;
	std::cout << "1 - Light Tank" << std::endl; std::cout << "2 - Medium Tank" << std::endl; std::cout << "3 - Tank Destroyer" << std::endl; std::cout << "4 - Heavy Tank" << std::endl; std::cout << "5 - Super Heavy Tank" << std::endl;
	std::cin >> type;
	Tank tank1(type);
	std::cout << "Input the tank model:" << std::endl;
	std::cin.ignore();
	std::getline(std::cin, name);
	tank1.name = name;

	std::cout << "Please, input the number corresponding to the class of Tank 2." << std::endl;
	std::cout << "1 - Light Tank" << std::endl; std::cout << "2 - Medium Tank" << std::endl; std::cout << "3 - Tank Destroyer" << std::endl; std::cout << "4 - Heavy Tank" << std::endl; std::cout << "5 - Super Heavy Tank" << std::endl;
	std::cin >> type;
	Tank tank2(type);
	std::cout << "Input the tank model:" << std::endl;
	std::cin.ignore();
	std::getline(std::cin, name);
	tank2.name = name;

	bool tank1MediumFlag = true;
	bool tank2MediumFlag = true;
	bool tank1SuperHeavyFlag = true;
	bool tank2SuperHeavyFlag = true;
	Tactics tank2Tactics = 0;

	while (victory != true) {

		announceStartOfTurn(tank1, tank2);

		Tactics tank1Tactics = declareTactics(tank1);

		announceTactics(tank1Tactics, tank1);

		Accuracy attackRoll1 = calculateAccuracy(tank1, tank2);

		if ((tank1.type == 5 && tank1SuperHeavyFlag == true) || (tank1.type != 5)) {

			tank1SuperHeavyFlag = false;

		if (attackRoll1 >= tank2.evasion - tank2Tactics * 5) {

			calculateDamage(tank1Tactics, tank2Tactics, attackRoll1, tank1, tank2);

		}

		else {

			std::cout << "It's a miss!" << std::endl;

			if (tank1.type == light) {

				std::cout << tank1.name << " is a light tank! It quickly reloads and shoots again!" << std::endl;

				Accuracy attackRoll1B = calculateAccuracy(tank1, tank2);

				if (attackRoll1B >= tank2.evasion - tank2Tactics * 5) {

					calculateDamage(tank1Tactics, tank2Tactics, attackRoll1B, tank1, tank2);

				}
			}

			checkMediumTankFlag(tank2, tank2MediumFlag);
			checkVictoryConditions(tank2, victory);

			if (victory == true && tank1.health > 0) {
				std::cout << tank2.name << " has been disabled!" << std::endl;
				std::cout << tank1.name << " wins!" << std::endl;
			}

			while (victory == true) {
				victoryWrapper();
			}

			system("pause");

		}

		}
		else {
			std::cout << tank1.name << " is a Super Heavy tank and needs to take one turn to be operational again!" << std::endl;
			tank1SuperHeavyFlag = true;
		}


		// SECOND PLAYER TURN

		Tactics tank2Tactics = declareTactics(tank2);

		announceTactics(tank2Tactics, tank2);

		Accuracy attackRoll2 = calculateAccuracy(tank2, tank1);

		if ((tank2.type == 5 && tank2SuperHeavyFlag == true) || (tank2.type != 5)) {

			tank2SuperHeavyFlag = false;

		if (attackRoll2 >= tank1.evasion - tank1Tactics * 5) {

			calculateDamage(tank2Tactics, tank1Tactics, attackRoll2, tank2, tank1);

		}

		else {

			std::cout << "It's a miss!" << std::endl;

			if (tank2.type == light) {

				std::cout << tank2.name << " is a light tank! It quickly reloads and shoots again!" << std::endl;

				Accuracy attackRoll2B = calculateAccuracy(tank2, tank1);

				if (attackRoll2B >= tank1.evasion - tank1Tactics * 5) {

					calculateDamage(tank2Tactics, tank1Tactics, attackRoll2B, tank2, tank1);

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

			system("pause");
		}


		}
		else {
		std::cout << tank2.name << " is a Super Heavy tank and needs to take one turn to be operational again!" << std::endl;
		tank2SuperHeavyFlag = true;
		}

		system("pause");
		return 0;
	}
}