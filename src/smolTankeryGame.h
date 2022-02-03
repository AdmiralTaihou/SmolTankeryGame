#pragma once

#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>


typedef std::size_t tankType;
typedef std::size_t Accuracy;
typedef std::size_t Damage;
typedef std::size_t Tactics;
typedef std::size_t crewRole;
typedef std::size_t Experience;
typedef std::string Name;

const Tactics maneuver = 0;
const Tactics angle = 1;

const tankType light = 1;
const tankType medium = 2;
const tankType tankDestroyer = 3;
const tankType heavy = 4;
const tankType superHeavy = 5;

const crewRole blank = 0;
const crewRole driver = 1;
const crewRole gunner = 2;
const crewRole loader = 3;
const crewRole radio = 4;
const crewRole commander = 5;


class Tank {
public:
	typedef int Health;
	typedef int Evasion;
	typedef int Damage;

	Health health = 1;
	Evasion evasion = 1;
	Damage damage = 1;
	Name name = "";
	tankType type = 1;

	Tank(const tankType&);

};

class Crew {
public:

	Name name = "";
	crewRole role = 0;
	Experience experience = 0;

	Crew(const crewRole&);

};

void addStaticCrewValues(Tank&, const Crew&);
Accuracy calculateAccuracy(const Tank&, const Tank&);
int calculateDamage(const Tactics&,const Tactics&, const Accuracy&, const Tank&, Tank&);
void dealDamage(const int&, Tank&);
Tactics declareTactics(const Tank&);
void checkMediumTankFlag(Tank&, bool&);
void checkVictoryConditions(const Tank&, bool&);
void announceStartOfTurn(const Tank&, const Tank&);
void announceTactics(const Tactics&, const Tank&);
void victoryWrapper();
