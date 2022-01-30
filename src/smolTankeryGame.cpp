#include "smolTankeryGame.h"
#include <string>

typedef std::size_t tactics;

const tactics maneuver = 0;
const tactics angle = 1;

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

int main(int argc, char* argv[])
{
	bool victory = false;
	tankType type; std::string name;

	std::cout << "Please, input the number corresponding to the class of Tank 1." << std::endl;
	std::cout << "1 - Light Tank" << std::endl; std::cout << "2 - Medium Tank" << std::endl; std::cout << "3 - Tank Destroyer" << std::endl; std::cout << "4 - Heavy Tank" << std::endl; std::cout << "5 - Super Heavy Tank" << std::endl;
	std::cin >> type;
	Tank tank1(type);
	std::cout << "Input the tank model:" << std::endl;
	std::cin.ignore();
	std::getline(std::cin,name);
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

		std::cout << "################ NEXT TURN ################" << std::endl;
		std::cout << "Attacker Tank is: " << tank1.name << "." << std::endl;
		std::cout << "Defendar Tank is: " << tank2.name << "." << std::endl;

		std::cout << "What will " << tank1.name << " do?" << std::endl;
		std::cout << "0 - Maneuver" << std::endl; std::cout << "1 - Angle" << std::endl;
		tactics tactics = 0;
		std::cin >> tactics;

		if (tactics > 1 || tactics < 0) {
			throw std::exception("Incorrect value for chosen tactics.");
		}

		if (tactics == 0) {
			std::cout << tank1.name << " is maneuvering." << std::endl;
		}
		else {
			std::cout << tank1.name << " is angling." << std::endl;
		}

		int attackRoll = rand() % 100 + 1;

		std::cout << tank1.name << " rolled a " << attackRoll << "." << std::endl;
		std::cout << tank2.name << " has evasion of " << tank2.evasion << std::endl;

		if (attackRoll >= tank2.evasion) {

			int damageRoll = rand() % tank1.damage + 1;

			if (attackRoll < 95) {
				tank2.health -= damageRoll + tactics * 5;
				std::cout << tank1.name << " deals " << damageRoll + tactics * 5 << " points of damage." << std::endl;
			}
			else {
				tank2.health -= (damageRoll + tactics * 5) * 2;
				std::cout << "A critical hit from the " << tank1.name << " taking" << (damageRoll + tactics * 5) * 2 << " damage!" << std::endl;
			}
			std::cout << tank2.name << "'s health has been lowered to " << tank2.health << "!" << std::endl;

			if (tank2.type == medium && tank2.health <= 0 && tank2Flag == true) {
				tank2Flag = false;
				tank2.health = 1;
				std::cout << tank2.name << " has avoided getting disabled, but is at 1HP!" << std::endl;
			}

			if (tank2.health <= 0) {
				victory = true;
			}
		}
		else {
			std::cout << "It's a miss!" << std::endl;
			if (tank1.type == light) {

				int attackRoll = rand() % 100 + 1;

				std::cout << tank1.name << " is a light tank! It quickly reloads and shoots again!" << std::endl;
				std::cout << tank1.name << " rolled a " << attackRoll << "." << std::endl;
				std::cout << tank2.name << " has evasion of " << tank2.evasion << std::endl;

				if (attackRoll >= tank2.evasion) {
					int damageRoll = rand() % tank1.damage + 1;

					if (attackRoll < 95) {
						tank2.health -= damageRoll + tactics * 5;
						std::cout << tank1.name << " deals " << damageRoll + tactics * 5 << " points of damage." << std::endl;
					}
					else {
						tank2.health -= (damageRoll + tactics * 5) * 2;
						std::cout << "A critical hit by " << tank1.name << " dealing" << (damageRoll + tactics * 5) * 2 << " damage to" << tank2.name << "!" << std::endl;
					}
					std::cout << tank2.name << "'s health has been lowered to " << tank2.health << "!" << std::endl;
				}

				if (tank2.type == medium && tank2.health <= 0 && tank2Flag == true) {
					tank2Flag = false;
					tank2.health = 1;
					std::cout << tank2.name << " has avoided getting disabled, but is at 1HP!" << std::endl;
				}

				if (tank2.health <= 0) {
					victory = true;
				}

			}
		}
		system("pause");

	}
	std::cout << tank2.name << " has been disabled!" << std::endl;
	std::cout << tank1.name << " wins!" << std::endl;
	system("pause");
	return 0;
}