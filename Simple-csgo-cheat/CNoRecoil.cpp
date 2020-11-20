#include "CNoRecoil.h"
#include "Offsets.h"

CNoRecoil::CNoRecoil(MODULE mModule, Process pProcess, MODULEENGINE mModuleEngine)
{
	this->mModule = mModule;
	this->pProcess = pProcess;
	this->mModuleEngine = mModuleEngine;
}

void CNoRecoil::Hack(bool _switch)
{
	DWORD dwClientState;
	Vector2 CurrentViewAngles;
	Vector2 vPunch;
	Vector2 NewViewAngles;
	Vector2 OldAimPunch;
	OldAimPunch.x = 0;
	OldAimPunch.y = 0;

	DWORD dwLocal;
	while (true)
	{
		dwLocal = Read<DWORD>(mModule.dwBaseAddr + offset::dwLocalPlayer);
		if (GetAsyncKeyState(VK_F9) & 1)
		{
			_switch = !_switch;
			if (_switch)
			{
				std::cout << "No recoil activated!\n";
			}
			else
			{
				std::cout << "No recoil disabled!\n";
			}
			Sleep(250);
		}
		if (_switch)
		{
			vPunch = Read<Vector2>(dwLocal + offset::m_aimPunchAngle); // Get The Aim Punch Angle
			int pShotsFired = Read<int>(dwLocal + offset::m_iShotsFired); // Get The Number Of Shots Fired

			if (pShotsFired >= 1)
			{
				DWORD activeWeapon = Read<DWORD>(dwLocal + offset::m_hActiveWeapon) & 0xFFF;
				activeWeapon = Read<DWORD>(mModule.dwBaseAddr + offset::dwEntityList + (activeWeapon - 1) * 0x10);
				if (!activeWeapon)
				{
					continue;
				}

				short weaponIndex = Read<short>(activeWeapon + offset::m_iItemDefinitionIndex);
				std::string weaponName = wWeapon.getWeaponNameByIndex(weaponIndex);
				if (weaponName == "0")
				{
					std::cout << "Weapon name is undefined!\n";
					continue;
				}
				// no recoil weapons
				if (weaponName == "AK-47" || weaponName == "AUG" || weaponName == "FAMAS" || weaponName == "G3SG1"
					|| weaponName == "Galil AR" || weaponName == "M249" || weaponName == "M4A4" || weaponName == "MAC-10"
					|| weaponName == "P90" || weaponName == "MP5-SD" || weaponName == "UMP-45" || weaponName == "PP-Bizon"
					|| weaponName == "Negev" || weaponName == "MP7" || weaponName == "MP9" || weaponName == "SG 553"
					|| weaponName == "M4A1-S" || weaponName == "CZ75-Auto")
				{
					dwClientState = Read<DWORD>(mModuleEngine.dwBaseAddr + offset::dwClientState);	//Read ClientState
					CurrentViewAngles = Read<Vector2>(dwClientState + offset::dwClientState_ViewAngles);//Read The ViewAngles Using The ClientState
					
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

					Write<Vector2>(dwClientState + offset::dwClientState_ViewAngles, NewViewAngles);// Write The vAngles 
				}
			}
			else
			{
				OldAimPunch.x = OldAimPunch.y = 0; //If You Don't Fire, Then There Is No Previous Punch
			}
			Sleep(1);
		}

	}
}