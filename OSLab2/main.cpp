#include <vector>
#include <string>
#include <memory>
#include <fstream>

#include "Process.h"
#include "Memory.h"
#include "Scheduler.h"
#include "Instructions.h"
#include <iostream>

#define DEFAULT_PRIORITY 1
#define CLOCK_PER_TIMER 100

int32_t FreeProcessId = 0;

std::vector<std::shared_ptr<Process>> LoadProcesses(const std::vector<std::string>& files) {
	std::vector<std::shared_ptr<Process>> processes;
	for (const std::string& path : files)
	{
		std::fstream file(path, std::ios_base::in);

		int32_t size = -1;
		int32_t address = -1;

		Memory& memory = Memory::Get();

		std::string line;
		while (std::getline(file, line))
		{
			int32_t value = std::stoi(line);
			if (size == -1)
			{
				size = value;
				address = memory.Claim(size);
			}
			else
			{
				memory.Put(address, value);
				address++;
			}
		}

		std::shared_ptr<Process> process = std::make_shared<Process>(FreeProcessId, address - size, size, 60);
		FreeProcessId++;

		processes.push_back(process);

		file.close();
	}

	return processes;
}

ProcessStatus runProcessNextInstruction(const std::shared_ptr<Process>& process, Memory& memory)
{
	int32_t instructionPointer = process->GetInstrucitonPointer();
	int32_t instruction = memory.ReadByte(instructionPointer);
	instructionPointer++;

	if (instruction >= Instructions::BRANCH_MIN && instruction <= Instructions::BRANCH_MAX)
	{
		int32_t destinationAddress = (memory.ReadByte(instructionPointer) << 8) | memory.ReadByte(instructionPointer + 1);
		instructionPointer += 2;

		if (Instructions::IsBranching(instruction))
		{
			instructionPointer = destinationAddress;
		}
		process->SetInstructionPointer(instructionPointer);
		return ProcessStatus::GO;
	}

	process->SetInstructionPointer(instructionPointer);
	switch (instruction)
	{
	case Instructions::COMPUTE: return ProcessStatus::GO;
	case Instructions::IO_BLOCK: return ProcessStatus::IO_BLOCK;
	case Instructions::EXIT: return ProcessStatus::EXIT;
	default: return ProcessStatus::ERROR;
	}
}

int main(int argc, char* argv[])
{
	std::vector<std::string> files;
	for (int32_t i = 1; i < argc; ++i)
	{
		files.push_back(argv[i]);
	}

	Scheduler scheduler;
	scheduler.AddProcesses(LoadProcesses(files));

	int32_t timer = CLOCK_PER_TIMER;
	Memory& memory = Memory::Get();

	while (scheduler.HasProcesses())
	{
		std::shared_ptr<Process> process = memory.GetLoadedProcess();

		if (process) 
		{
			ProcessStatus status = runProcessNextInstruction(process, memory);
			process->IncrementUtilization();

			switch (status)
			{
			case ProcessStatus::GO: break;
			case ProcessStatus::IO_BLOCK: {
				int32_t time = Instructions::CalculateBlockWait();
				process->SetBlockTime(time);

				std::cout << "Process: " << process->GetId() << " is blocked for " << time << " cycles." << std::endl;

				memory.LoadProcess(scheduler.GetNextProcess());
				timer = CLOCK_PER_TIMER;

				break;
			}
			case ProcessStatus::ERROR:
				std::cout << "Process: " << process->GetId() << " has faced error." << std::endl;
			default:
				std::cout << "Process: " << process->GetId() << " is exiting." << std::endl;
				scheduler.RemoveProcess(process);
				memory.LoadProcess(scheduler.GetNextProcess());
				timer = CLOCK_PER_TIMER;
				break;
			}
			--timer;
		}

		if (!process || timer <= 0)
		{
			memory.LoadProcess(scheduler.GetNextProcess());
			timer = CLOCK_PER_TIMER;
		}

		for (const std::shared_ptr<Process>& process : scheduler.GetProcesses())
		{
			process->DecrementBlockTime();
		}
	}

	return 0;
}