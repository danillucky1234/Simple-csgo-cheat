#pragma once
#include "CMemory.h"

class CBhop : public Memory
{
private:
	void PatchEx(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProcess);
public:
	CBhop(MODULE mModule, Process pProcess);
	void Hack(bool _switch);

};