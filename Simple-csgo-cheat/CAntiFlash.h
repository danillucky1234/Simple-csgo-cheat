#pragma once
#include "CMemory.h"

class CAntiFlash
{
private:
	Memory mMemory;
	MODULE mModule;
	Process pProcess;
public:
	CAntiFlash(MODULE mModule, Process pProcess);
	void Hack(bool _switch);
};