#pragma once
#include "CMemory.h"

class Radar : public Memory
{
public:
	Radar(MODULE mModule, Process pProcess);
	void Hack(bool _switch);
};