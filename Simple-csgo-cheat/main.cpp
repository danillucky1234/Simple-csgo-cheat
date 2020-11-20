#include <iostream>
#include <Windows.h>
#include <Tlhelp32.h>
#include <thread>
#include "CMemory.h"
#include "CRadar.h"
#include "CBhop.h"
#include "CWallHack.h"
#include "CAntiFlash.h"
#include "CNoRecoil.h"

int main(int argc, char* argv[])
{
	// First you need to find the process PID by name
	Memory mMemory;
	DWORD dwPID = mMemory.SetPIDAndHandle("csgo.exe");
	if (!dwPID) // if pid == 0, they didn't find csgo.exe
	{
		std::cout << "csgo.exe not found!\n";
		std::cout << "Run the game first, and then try again\n";
		return -1;
	}
	if (!mMemory.AddModule("engine.dll"))
	{
		std::cout << "engine.dll not found!\n";
		return -1;
	}
	else
	{
		std::cout << "engine.dll is found!\n";
	}
	if (!mMemory.AddModule("client.dll"))
	{
		std::cout << "client.dll not found!\n";
		return -1;
	}
	else
	{
		std::cout << "client.dll is found!\n";
	}
	std::cout << "PID = " << dwPID << std::endl;
	int input;
	bool _switch[] = { false, false, false, false, false };
	Radar rRadar(mMemory.getModule(), mMemory.getProcess());
	CBhop bBhop(mMemory.getModule(), mMemory.getProcess());
	CWallHack wWallHack(mMemory.getModule(), mMemory.getProcess());
	CAntiFlash aAntiFlash(mMemory.getModule(), mMemory.getProcess());
	CNoRecoil nNoRecoil(mMemory.getModule(), mMemory.getProcess(), mMemory.getModuleEngine());
	std::cout << "-----------------------------------" << std::endl;
	std::cout << "||        DANILLUCKY1234         ||" << std::endl;
	std::cout << "-----------------------------------" << std::endl;
	std::cout << "F5  - Radarhack\n"
		<< "F6  -  Wallhack\n"
		<< "F7  -  Bunnyhop\n"
		<< "F8  -  No flash\n"
		<< "F9  -  No recoil\n";
	// Run the thread with radar
	std::thread thrRadar(&Radar::Hack, rRadar, *(_switch + 0));
	thrRadar.detach();
	// Run the thread with bunnyhop
	std::thread thrBunnyHop(&CBhop::Hack, bBhop, *(_switch + 1));
	thrBunnyHop.detach();
	// Run the thread with wallhach
	std::thread thrWallHack(&CWallHack::Hack, wWallHack, *(_switch + 2));
	thrWallHack.detach();
	// Run the thread with no flash
	std::thread thrAntiFlash(&CAntiFlash::Hack, aAntiFlash, *(_switch + 3));
	thrAntiFlash.detach();
	// Run the thread with no recoil
	std::thread thrNoRecoil(&CNoRecoil::Hack, nNoRecoil, *(_switch + 4));
	thrNoRecoil.detach();

	while (true)
	{
		Sleep(1500);
	}
	return 0;
}