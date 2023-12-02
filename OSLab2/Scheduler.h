#pragma once

#include <vector>
#include <memory>
#include "Process.h"

class Scheduler {
public:
	void AddProcesses(const std::vector<std::shared_ptr<Process>>& processes);

	void AddProcess(const std::shared_ptr<Process>& process);
	void RemoveProcess(const std::shared_ptr<Process>& process);
	const std::vector<std::shared_ptr<Process>>& GetProcesses() const;

	std::shared_ptr<Process> GetNextProcess();
	
	bool HasProcesses();

	void UpdateCurrentTime();
private:
	std::vector<std::shared_ptr<Process>> m_Processes;

	int32_t m_CurrentTime = 1;
};