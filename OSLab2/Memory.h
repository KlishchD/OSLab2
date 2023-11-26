#pragma once

#include <memory>
#include "Process.h"

class Memory {
public:
	static Memory& Get();

	void LoadProcess(const std::shared_ptr<Process>& process);
	std::shared_ptr<Process> GetLoadedProcess() const;

	int ReadByte(int address);
	void Put(int address, int value);

	int Claim(int size);

private:
	static const int MEMORY_SIZE = 65536;
	int m_Memory[MEMORY_SIZE];

	int m_ProcessBaseAddress;
	int m_ProcessAddressSize;

	int m_FirstUnclaimedAddress = 0;

	std::shared_ptr<Process> m_LoadedProcess;

	Memory() = default;
};