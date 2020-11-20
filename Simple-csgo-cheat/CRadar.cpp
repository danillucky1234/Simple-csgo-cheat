#include "Offsets.h"
#include "CRadar.h"

Radar::Radar(MODULE mModule, Process pProcess)
{
	this->mModule = mModule;
	this->pProcess = pProcess;
}

void Radar::Hack(bool _switch)
{
	DWORD dwLocal;
	DWORD dwLocalHP;
	DWORD dwLocalTeam;
	while (true)
	{
		dwLocal = Read<DWORD>(mModule.dwBaseAddr + offset::dwLocalPlayer); 
		dwLocalHP = Read<DWORD>(dwLocal + offset::dwHealth); 
		dwLocalTeam = Read<DWORD>(dwLocal + offset::dwTeamNum); // find out which team our player is in.
		// The F5 key will enable/disable the radarhack
		if (GetAsyncKeyState(VK_F5) & 1)
		{
			_switch = !_switch;
			if (_switch)
			{
				std::cout << "Radarhack activated!\n";
			}
			else
			{
				std::cout << "Radarhack disabled!\n";
			}
			Sleep(250);
		}
		if (_switch)
		{
			if (!dwLocalHP) // If a player is dead, do not enable the radarhack
			{
				continue;
			}
			// We walk through 32 players (max. number of players on the server).
			for (DWORD i = 0;i <= 32;i++)
			{
				// We find the base address of another player, add the offset to it, find the next player in the list and multiply by 0x10.
																// 0х10 - это sizeof CEntityClient
				DWORD dwEntity = Read<DWORD>(mModule.dwBaseAddr + offset::dwEntityList + (i - 1) * 0x10);
				DWORD dwEntityHP = Read<DWORD>(dwEntity + offset::dwHealth); // We read the health of another player
				if (dwEntityHP <= 0) // If he is dead, do not show him on the screen
				{
					continue;
				}
				DWORD dwEntityTeam = Read<DWORD>(dwEntity + offset::dwTeamNum); // We read which team the other player is in.
				//  If this player is in our team - do not show him on the screen
				if (dwEntityTeam == dwLocalTeam)
				{
					continue;
				}
				DWORD dwEntitySpotted = Read<bool>(dwEntity + offset::m_bSpotted); // Will we find out if a player has been spotted by anyone on our team?
				if (dwEntitySpotted) // If noticed, we don't write it. 
				{
					continue;
				}
				Write<DWORD>(dwEntity + offset::m_bSpotted, TRUE); // Show the point where the other player is on the radar
			}
			Sleep(5);
		}
	}
}