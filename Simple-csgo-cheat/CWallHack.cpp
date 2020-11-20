#include "CWallHack.h"
#include "Offsets.h"

CWallHack::CWallHack(MODULE mModule, Process pProcess)
{
	this->mModule = mModule;
	this->pProcess = pProcess;
}

void CWallHack::Hack(bool _switch)
{
	DWORD dwLocal;
	DWORD dwLocalHP;
	DWORD dwLocalTeam;
	DWORD dwGlowObjectManager;
	while (true)
	{
		dwLocal = Read<DWORD>(mModule.dwBaseAddr + offset::dwLocalPlayer); 
		dwLocalHP = Read<DWORD>(dwLocal + offset::dwHealth); 
		dwLocalTeam = Read<DWORD>(dwLocal + offset::dwTeamNum); 
		dwGlowObjectManager = Read<DWORD>(mModule.dwBaseAddr + offset::dwGlowObjectManager);
		
		// Key F6 will turn on/off the wallhack
		if (GetAsyncKeyState(VK_F6) & 1)
		{
			_switch = !_switch;
			if (_switch)
			{
				std::cout << "Wallhack activated!\n";
			}
			else
			{
				std::cout << "Wallhack disabled!\n";
			}
			Sleep(250);
		}
		if (_switch)
		{
			Sleep(10);
			if (!dwLocalHP) // If a player is dead, we turn off the wallhack
			{
				continue;
			}
			for (int i = 0;i < 32;i++)
			{
				DWORD dwEntity = Read<DWORD>(mModule.dwBaseAddr + offset::dwEntityList + (i - 1) * 0x10);
				DWORD dwEntityHP = Read<DWORD>(dwEntity + offset::dwHealth); 
				if (dwEntityHP <= 0) // If another player is dead, do not show it on the screen.
				{
					continue;
				}
				bool Dormant = Read<DWORD>(dwEntity + 0xED);
				if (Dormant)
				{
					continue;
				}
				DWORD dwEntityTeam = Read<DWORD>(dwEntity + offset::dwTeamNum);
				DWORD dwGlowIndex = Read<DWORD>(dwEntity + offset::dwGlowIndex);

				//  If a player is not our teammate
				if (dwEntityTeam != dwLocalTeam)
				{
					Write<float>(dwGlowObjectManager + dwGlowIndex * 0x38 + 0x4, 255);// red
					Write<float>(dwGlowObjectManager + dwGlowIndex * 0x38 + 0x8, 0);// green
					Write<float>(dwGlowObjectManager + dwGlowIndex * 0x38 + 0xC, 0);// blue
					Write<float>(dwGlowObjectManager + dwGlowIndex * 0x38 + 0x10, 255);
					Write<bool>(dwGlowObjectManager + dwGlowIndex * 0x38 + 0x24, true);
					Write<bool>(dwGlowObjectManager + dwGlowIndex * 0x38 + 0x25, false);
				}
				else
				{
					Write<float>(dwGlowObjectManager + dwGlowIndex * 0x38 + 0x4, 0);// red
					Write<float>(dwGlowObjectManager + dwGlowIndex * 0x38 + 0x8, 0);// green
					Write<float>(dwGlowObjectManager + dwGlowIndex * 0x38 + 0xC, 255);// blue
					Write<float>(dwGlowObjectManager + dwGlowIndex * 0x38 + 0x10, 255);
					Write<bool>(dwGlowObjectManager + dwGlowIndex * 0x38 + 0x24, true);
					Write<bool>(dwGlowObjectManager + dwGlowIndex * 0x38 + 0x25, false);
				}
			}
			Sleep(10);
		}
	}
}
