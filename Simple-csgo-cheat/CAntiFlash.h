#pragma once
#include "CMemory.h"

class CAntiFlash : public Memory
{
public:
	CAntiFlash(MODULE mModule, Process pProcess);
	void Hack(bool _switch);
};