#pragma once

#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>


typedef std::size_t tankType;

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