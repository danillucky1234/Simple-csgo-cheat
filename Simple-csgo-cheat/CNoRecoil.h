#pragma once
#include "CMemory.h"
#include "CBaseCombatWeapon.h"

struct Vector2
{
	float x;
	float y;
};

class CNoRecoil
{
private:
	Memory mMemory;
	MODULE mModule;
	Process pProcess;
	MODULEENGINE mModuleEngine;
	CBaseCombatWeapon wWeapon;
public:
	CNoRecoil(MODULE mModule, Process pProcess, MODULEENGINE mModuleEngine);
	void Hack(bool _switch);
};