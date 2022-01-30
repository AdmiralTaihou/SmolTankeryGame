#pragma once

#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>


typedef std::size_t tankType;
typedef double Accuracy;
typedef std::size_t Tactics;

const Tactics maneuver = 0;
const Tactics angle = 1;

const tankType light = 1;
const tankType medium = 2;
const tankType tankDestroyer = 3;
const tankType heavy = 4;
const tankType superHeavy = 5;


class Tank {
public:
	typedef int Health;
	typedef int Evasion;
	typedef int Damage;
	typedef std::string Name;

	Health health = 1;
	Evasion evasion = 1;
	Damage damage = 1;
	Name name = "";
	tankType type = 6;

	Tank(const tankType&);

};


Accuracy calculateAccuracy(const Tank&, const Tank&);
void calculateDamage(const Tactics&, const Accuracy&, const Tank&, Tank&);
Tactics declareTactics(const Tank&);
void checkMediumTankFlag(Tank&, bool);
void checkVictoryConditions(const Tank&, bool);
void announceStartOfTurn(const Tank&, const Tank&);
void announceTactics(const Tactics&, const Tank&);
