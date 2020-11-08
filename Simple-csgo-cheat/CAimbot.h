#pragma once
#include "CMemory.h"

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
	Player pPlayer;
	MODULEENGINE mModuleEngine;

public:
	CNoRecoil(MODULE mModule, Process pProcess, MODULEENGINE mModuleEngine, Player pPlayer);
	void Hack(bool _switch);
};