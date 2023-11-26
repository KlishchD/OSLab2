#pragma once

#include <cstdint>

enum class ProcessStatus {
	GO, 
	IO_BLOCK,
	EXIT,
	ERROR
};

class Process {
public:
	Process(int32_t id, int32_t baseAddress, int32_t addressSize, int32_t priority);

	int32_t GetId() const;

	int32_t GetUtilization() const;
	void IncrementUtilization();

	int GetBaseAddress() const;
	int GetAddressSize() const;

	void SetBlockTime(int32_t time);
	void DecrementBlockTime();
	bool IsBlocked() const;

	int32_t GetInstrucitonPointer() const;
	void SetInstructionPointer(int32_t instructionPointer);
private:
	int m_Id;
	int m_BlockTime = 0;
	int m_BaseAddress;
	int m_AddressSize;
	int m_InstructionPointer = 0;
	int m_Priority;
	int m_Utilization = 0;
};