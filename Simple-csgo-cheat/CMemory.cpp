#include <iostream>
#include "CMemory.h"
#include "Offsets.h"

bool Memory::AddModule(std::string nameOfDll)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pProcess.dwPID); // Находим хендл снапшота 
	if (hSnapshot == INVALID_HANDLE_VALUE)
	{
		return false;
	}
	MODULEENTRY32 meModuleEntry;
	meModuleEntry.dwSize = sizeof(meModuleEntry);
	Module32First(hSnapshot, &meModuleEntry);
	do
	{
		if (!_stricmp(meModuleEntry.szModule, nameOfDll.c_str()))
		{
			if (nameOfDll == "client.dll")
			{
				mModule.dwBaseAddr = (DWORD)meModuleEntry.modBaseAddr;
				mModule.dwBaseSize = meModuleEntry.dwSize;
				mModule.hHandle = meModuleEntry.hModule;
			}
			else if(nameOfDll == "engine.dll")
			{
				mModuleEngine.dwBaseAddr = (DWORD)meModuleEntry.modBaseAddr;
				mModuleEngine.dwBaseSize = meModuleEntry.dwSize;
				mModuleEngine.hHandle = meModuleEntry.hModule;
			}
			CloseHandle(hSnapshot);
			return true;
		}
		else
		{
			Sleep(1);
		}
	} while (Module32Next(hSnapshot, &meModuleEntry));
	return false;
}

DWORD Memory::SetPIDAndHandle(const char* AProcessName)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE)
	{
		return 0;
	}
	PROCESSENTRY32 peProcessEntry;
	peProcessEntry.dwSize = sizeof(peProcessEntry);
	Process32First(hSnapshot, &peProcessEntry);
	do
	{
		if (strcmp(peProcessEntry.szExeFile, AProcessName) == 0) // if the process names are the same
		{
			pProcess.dwPID = peProcessEntry.th32ProcessID; // record the pid our process
			pProcess.hHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pProcess.dwPID); // record the process handle
			CloseHandle(hSnapshot); 
			return pProcess.dwPID;
		}
	} while (Process32Next(hSnapshot, &peProcessEntry));
	return 0;
}

void Memory::setProcess(Process pProcess)
{
	this->pProcess = pProcess;
}

void Memory::setModule(MODULE mModule)
{
	this->mModule = mModule;
}

Memory::~Memory()
{
}
