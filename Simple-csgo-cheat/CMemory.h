#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>

struct MODULE
{
	DWORD dwBaseAddr;
	DWORD dwBaseSize;
	HANDLE hHandle;
};

struct MODULEENGINE
{
	DWORD dwBaseAddr;
	DWORD dwBaseSize;
	HANDLE hHandle;
};

struct Process
{
	HANDLE hHandle;
	DWORD dwPID;
};

class Memory
{
private:
	Process pProcess;
	MODULE mModule;
	MODULEENGINE mModuleEngine;
public:
	bool AddModule(std::string nameOfDll);
	MODULE getModule() { return mModule; };
	DWORD SetPIDAndHandle(const char* AProcessName);
	HANDLE getProcessHandle() { return pProcess.hHandle; };
	Process getProcess() { return pProcess; };
	DWORD getBaseAddr() { return mModule.dwBaseAddr; };
	MODULEENGINE getModuleEngine() { return mModuleEngine; };

	void setProcess(Process pProcess);
	void setModule(MODULE mModule);

	~Memory();

	template<class T>
	T Read(const DWORD dwAddress)
	{
		T returned;
		ReadProcessMemory(pProcess.hHandle, (LPVOID)dwAddress, &returned, sizeof(T), NULL);
		return returned;
	}

	template<typename T>
	void Write(DWORD dwAddress, T tValue)
	{
		WriteProcessMemory(pProcess.hHandle, (LPVOID)dwAddress, &tValue, sizeof(T), NULL);
	}
};