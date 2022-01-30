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

void calculateDamage(const Tactics& tankATactics, const Accuracy& attackRoll, const Tank& tankA, Tank& tankB)
{
	if (attackRoll >= tankB.evasion) {

		int damageRoll = rand() % tankA.damage + 1;

		if (attackRoll < 95) {
			tankB.health -= damageRoll + tankATactics * 5;
			std::cout << tankA.name << " deals " << damageRoll + tankATactics * 5 << " points of damage." << std::endl;
		}
		else {
			tankB.health -= (damageRoll + tankATactics * 5) * 2;
			std::cout << "A critical hit by " << tankA.name << " dealing" << (damageRoll + tankATactics * 5) * 2 << " damage to" << tankB.name << "!" << std::endl;
		}
		std::cout << tankB.name << "'s health has been lowered to " << tankB.health << "!" << std::endl;
	}
}

Tactics declareTactics(const Tank& tank)
{
	std::cout << "What will " << tank.name << " do?" << std::endl;
	std::cout << "0 - Maneuver" << std::endl; std::cout << "1 - Angle" << std::endl;
	Tactics tanktactics = 0;
	std::cin >> tanktactics;

	return tanktactics;
}

void checkMediumTankFlag(Tank& tank, bool tankFlag)
{
	if (tank.type == medium && tank.health <= 0 && tankFlag == true) {
		tankFlag = false;
		tank.health = 1;
		std::cout << tank.name << " has avoided getting disabled, but is at 1HP!" << std::endl;
	}
}

void checkVictoryConditions(const Tank& tank, bool victory)
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

int main(int argc, char* argv[])
{
	srand(time(0));
	bool victory = false;
	tankType type; std::string name;

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

	bool tank1Flag = true;
	bool tank2Flag = true;

	while (victory != true) {

		announceStartOfTurn(tank1, tank2);

		Tactics tank1tactics = declareTactics(tank1);

		announceTactics(tank1tactics, tank1);

		Accuracy attackRoll = calculateAccuracy(tank1, tank2);

		if (attackRoll >= tank2.evasion) {

			calculateDamage(tank1tactics, attackRoll, tank1, tank2);

			checkMediumTankFlag(tank2, tank2Flag);

			checkVictoryConditions(tank2, victory);

		}

		else {

			std::cout << "It's a miss!" << std::endl;

			if (tank1.type == light) {

				std::cout << tank1.name << " is a light tank! It quickly reloads and shoots again!" << std::endl;

				if (attackRoll >= tank2.evasion) {

					Accuracy attackRoll = calculateAccuracy(tank1, tank2);

					calculateDamage(tank1tactics, attackRoll, tank1, tank2);

					checkMediumTankFlag(tank2, tank2Flag);

				}
			}
			checkVictoryConditions(tank2, victory);
			system("pause");

		}
		std::cout << tank2.name << " has been disabled!" << std::endl;
		std::cout << tank1.name << " wins!" << std::endl;
		system("pause");
		return 0;
	}
}