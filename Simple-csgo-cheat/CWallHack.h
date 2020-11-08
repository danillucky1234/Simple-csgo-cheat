#pragma once
#include "CMemory.h"

class CWallHack
{
private:
	Memory mMemory;
	MODULE mModule;
	Process pProcess;
public:
	CWallHack(MODULE mModule, Process pProcess);
	void Hack(bool _switch);
};