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
	Process(int32_t id, int32_t baseAddress, int32_t addressSize, int32_t weight, int32_t time);

	int32_t GetId() const;

	int32_t GetUtilization() const;
	void IncrementUtilization();

	int GetBaseAddress() const;
	int GetAddressSize() const;

	int32_t GetWeight() const;
	int32_t GetCreationTime() const;

	void SetBlockTime(int32_t time);
	void DecrementBlockTime();
	bool IsBlocked() const;

	int32_t GetInstrucitonPointer() const;
	void SetInstructionPointer(int32_t instructionPointer);
private:
	int32_t m_Id;
	int32_t m_BlockTime = 0;
	int32_t m_BaseAddress;
	int32_t m_AddressSize;
	int32_t m_InstructionPointer = 0;
	int32_t m_Weight = 1;
	int32_t m_Utilization = 0;
	int32_t m_CreationTime = 0;
};