#include "Process.h"

Process::Process(int32_t id, int32_t baseAddress, int32_t addressSize, int32_t priority) :
    m_Id(id), m_BaseAddress(baseAddress), m_AddressSize(addressSize),
    m_Priority(priority)
{

}

int32_t Process::GetId() const
{
    return m_Id;
}

int Process::GetUtilization() const
{
    return m_Utilization;
}

void Process::SetBlockTime(int32_t time)
{
    m_BlockTime = time;
}

void Process::DecrementBlockTime()
{
    m_BlockTime--;
}

void Process::IncrementUtilization()
{
    m_Utilization++;
}

int Process::GetBaseAddress() const
{
    return m_BaseAddress;
}

int Process::GetAddressSize() const
{
    return m_AddressSize;
}

bool Process::IsBlocked() const
{
    return m_BlockTime > 0;
}

int32_t Process::GetInstrucitonPointer() const
{
    return m_InstructionPointer;
}

void Process::SetInstructionPointer(int32_t instructionPointer)
{
    m_InstructionPointer = instructionPointer;
}
