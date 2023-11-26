#include "Scheduler.h"

void Scheduler::AddProcesses(const std::vector<std::shared_ptr<Process>>& processes)
{
	for (const std::shared_ptr<Process>& process : processes) 
	{
		m_Processes.push_back(process);
	}
}

void Scheduler::AddProcess(const std::shared_ptr<Process>& process)
{
	m_Processes.push_back(process);
}

void Scheduler::RemoveProcess(const std::shared_ptr<Process>& process)
{
	int index = -1;
	for (int32_t i = 0; i < m_Processes.size(); ++i) 
	{
		if (m_Processes[i] == process) 
		{
			index = i;
			break;
		}
	}

	if (index != -1)
	{
		m_Processes.erase(m_Processes.begin() + index);
	}
}

const std::vector<std::shared_ptr<Process>>& Scheduler::GetProcesses() const
{
	return m_Processes;
}

std::shared_ptr<Process> Scheduler::GetNextProcess()
{
	int minUtilization = INT_MAX;
	std::shared_ptr<Process> minProceess;

	for (const std::shared_ptr<Process>& process : m_Processes) 
	{
		if (!process->IsBlocked()) 
		{
			int utilization = process->GetUtilization();
			if (minUtilization > utilization)
			{
				minUtilization = utilization;
				minProceess = process;
			}
		}
	}

	return minProceess;
}

bool Scheduler::HasProcesses()
{
	return !m_Processes.empty();
}
