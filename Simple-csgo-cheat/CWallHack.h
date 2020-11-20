#pragma once
#include "CMemory.h"

class CWallHack : public Memory
{
public:
	CWallHack(MODULE mModule, Process pProcess);
	void Hack(bool _switch);
};