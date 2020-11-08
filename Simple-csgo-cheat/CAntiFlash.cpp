#include "CAntiFlash.h"
#include "Offsets.h"

CAntiFlash::CAntiFlash(MODULE mModule, Process pProcess)
{
	this->mModule = mModule;
	this->pProcess = pProcess;
	mMemory.setProcess(this->pProcess);
	mMemory.setModule(this->mModule);
}

void CAntiFlash::Hack(bool _switch)
{
	DWORD dwLocal;
	DWORD dwLocalHP;
	while (true)
	{
		dwLocal = mMemory.Read<DWORD>(mModule.dwBaseAddr + offset::dwLocalPlayer); // read the player's location
		dwLocalHP = mMemory.Read<DWORD>(dwLocal + offset::dwHealth); // read the player's health bar
		if (GetAsyncKeyState(VK_F8) & 1)
		{
			_switch = !_switch;
		
			if (_switch)
			{
				std::cout << "AntiFlash activated!\n";
			}
			else
			{
				std::cout << "AntiFlash disabled!\n";
			}
			Sleep(250);
		}
		if (_switch)
		{
			Sleep(10);
			// If our player is dead, let him catch flash grenades( some kind of optimization)
			if (!dwLocalHP)
			{
				continue;
			}
			DWORD dwFlashDur = mMemory.Read<int>(dwLocal + offset::m_flFlashDuration);
			if (dwFlashDur > 0)
			{
				mMemory.Write<DWORD>(dwLocal + offset::m_flFlashDuration, 0); // take the dazzle out of flash grenades
			}
			Sleep(5);
		}
	}
}

