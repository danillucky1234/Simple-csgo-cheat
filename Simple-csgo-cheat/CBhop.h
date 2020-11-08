#pragma once
#include "CMemory.h"

class CBhop
{
private:
	Memory mMemory;
	MODULE mModule;
	Process pProcess;
public:
	CBhop(MODULE mModule, Process pProcess);
	void Hack(bool _switch);
	void PatchEx(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProcess);
};