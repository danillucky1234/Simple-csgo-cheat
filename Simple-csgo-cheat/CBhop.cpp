#include <bitset>
#include "CBhop.h"
#include "Offsets.h"

#define FL_ONGROUND (1<<0)    //0001

std::bitset<8> DoJump{ 0b0000'0001 };

CBhop::CBhop(MODULE mModule, Process pProcess)
{
	this->mModule = mModule;
	this->pProcess = pProcess;
	mMemory.setProcess(this->pProcess);
	mMemory.setModule(this->mModule);
}

void CBhop::Hack(bool _switch)
{
	DWORD dwLocal;
	int Flag{ 0 };
	BYTE jumpState{ 0 };
	while (true)
	{
		dwLocal = mMemory.Read<DWORD>(mModule.dwBaseAddr + offset::dwLocalPlayer); // read te player`s location
		if (GetAsyncKeyState(VK_F7) & 1)
		{
			_switch = !_switch;
			if (_switch)
			{
				std::cout << "Bunnyhop activated!\n";
			}
			else
			{
				std::cout << "Bunnyhop disabled!\n";
			}
			Sleep(250);
		}
		if (_switch && (GetAsyncKeyState(VK_SPACE)))
		{
			Flag = mMemory.Read<int>(dwLocal + offset::dwFlags);
			jumpState = mMemory.Read<byte>(mModule.dwBaseAddr + offset::dwForceJump);
			std::bitset<32> DoJump{ jumpState };

			if (Flag & FL_ONGROUND)
			{
				DoJump.set();
				jumpState = DoJump.to_ulong();
				PatchEx((BYTE*)(mModule.dwBaseAddr + offset::dwForceJump), (BYTE*)& jumpState, sizeof(jumpState), pProcess.hHandle);
			}
			else
			{
				DoJump.reset();
				jumpState = DoJump.to_ulong();
				PatchEx((BYTE*)(mModule.dwBaseAddr + offset::dwForceJump), (BYTE*)& jumpState, sizeof(jumpState), pProcess.hHandle);
			}
		}
		Sleep(5);
	
	}
}

void CBhop::PatchEx(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProcess)
{
	DWORD oldprotect;
	VirtualProtectEx(hProcess, dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	WriteProcessMemory(hProcess, dst, src, size, nullptr);
	VirtualProtectEx(hProcess, dst, size, oldprotect, &oldprotect);
}