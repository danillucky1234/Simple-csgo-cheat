#pragma once
#include <iostream>
#include "CMemory.h"

class Radar
{
private:
	Memory mMemory;
	MODULE mModule;
	Process pProcess;
public:
	Radar(MODULE mModule, Process pProcess);
	void Hack(bool _switch);
};