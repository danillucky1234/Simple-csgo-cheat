#include "CNoRecoil.h"
#include "Offsets.h"

CNoRecoil::CNoRecoil(MODULE mModule, Process pProcess, MODULEENGINE mModuleEngine, Player pPlayer)
{
	this->mModule = mModule;
	this->pProcess = pProcess;
	this->mModuleEngine = mModuleEngine;
	mMemory.setProcess(this->pProcess);
	mMemory.setModule(this->mModule);
	this->pPlayer = pPlayer;
}

void CNoRecoil::Hack(bool _switch)
{
	DWORD dwClientState;
	Vector2 CurrentViewAngles;
	Vector2 vPunch;
	Vector2 NewViewAngles;
	Vector2 OldAimPunch;
	OldAimPunch.x = OldAimPunch.y = 0;

	while (true)
	{
		if (GetAsyncKeyState(VK_F9))
		{
			_switch = !_switch;
			Sleep(250);
			if (_switch)
			{
				std::cout << "No recoil activated!\n";
			}
			else
			{
				std::cout << "No recoil disabled!\n";
			}
		}
		if (_switch)
		{
			vPunch = mMemory.Read<Vector2>(pPlayer.dwLocal + offset::m_aimPunchAngle); // Get The Aim Punch Angle
			int pShotsFired = mMemory.Read<int>(pPlayer.dwLocal + offset::m_iShotsFired); // Get The Number Of Shots Fired

			if (pShotsFired >= 1)
			{
				unsigned long ulWeapon = 0;
				DWORD dwEntity = mMemory.Read<DWORD>(mModule.dwBaseAddr + offset::dwEntityList + (i - 1) * 0x10);
				//DWORD dwEntityHP = mMemory.Read<DWORD>(dwEntity + offset::dwHealth); // Считываем здоровье другого игрока
				//if (dwEntityHP <= 0) // Если он мертв - не показываем его на экране
				//{
				//	continue;
				//}
				DWORD iCurWeaponAdress = mMemory.Read<
				ulWeapon = mMemory.Read<unsigned long>(dwEntity + offset::m_hActiveWeapon);
				



				dwClientState = mMemory.Read<DWORD>(mModuleEngine.dwBaseAddr + offset::dwClientState);	//Read ClientState
				CurrentViewAngles = mMemory.Read<Vector2>(dwClientState + offset::dwClientState_ViewAngles);//Read The ViewAngles Using The ClientState
				
				NewViewAngles.x = ((CurrentViewAngles.x + OldAimPunch.x) - (vPunch.x * 2.f));		//Get The AimPunch Angle Relative To Previous (Otherwise To Current vAngle)
				NewViewAngles.y = ((CurrentViewAngles.y + OldAimPunch.y) - (vPunch.y * 2.f));

				//v Angle Normalization (Prevents Being Untrusted)

				while (NewViewAngles.y > 180)
				{
					NewViewAngles.y -= 360;
				}
				while (NewViewAngles.y < -180)
				{
					NewViewAngles.y += 360;
				}
				if (NewViewAngles.x > 89.0f)
				{
					NewViewAngles.x = 89.0f;
				}
				if (NewViewAngles.x < -89.0f)
				{
					NewViewAngles.x = -89.0f;
				}
				// Angle Normalization (Prevents Being Untrusted)

				OldAimPunch.x = vPunch.x * 2.f; //Set Previous Punch To Current
				OldAimPunch.y = vPunch.y * 2.f;

				mMemory.Write<Vector2>(dwClientState + offset::dwClientState_ViewAngles, NewViewAngles);// Write The vAngles 
			}
			else
			{
				OldAimPunch.x = OldAimPunch.y = 0; //If You Don't Fire, Then There Is No Previous Punch
			}
			Sleep(1);
		}

	}
}