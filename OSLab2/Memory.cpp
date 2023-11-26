#include "Memory.h"
#include <iostream>

Memory& Memory::Get()
{
	static Memory memory;
	return memory;
}

void Memory::LoadProcess(const std::shared_ptr<Process>& process)
{
	if (process)
	{
		m_ProcessBaseAddress = process->GetBaseAddress();
		m_ProcessAddressSize = process->GetAddressSize();
		m_LoadedProcess = process;

		std::cout << "Process " << process->GetId() << " loaded" << std::endl;
	}
	else
	{
		m_ProcessBaseAddress = -1;
		m_ProcessAddressSize = -1;
		m_LoadedProcess = nullptr;
	}
}

std::shared_ptr<Process> Memory::GetLoadedProcess() const
{
	return m_LoadedProcess;
}

int Memory::ReadByte(int address)
{
	if (address < 0 || address > m_ProcessAddressSize)
	{
		std::cout << "Error: invalid address" << std::endl;
		return -1;
	}
	return m_Memory[m_ProcessBaseAddress + address];
}

void Memory::Put(int address, int value)
{
	m_Memory[address] = value;
}

int Memory::Claim(int size)
{
	int claimed = std::min(size, MEMORY_SIZE - m_FirstUnclaimedAddress);
	m_FirstUnclaimedAddress += claimed;
	return m_FirstUnclaimedAddress - claimed;
}
