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
	int32_t index = -1;
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
	float minRatio = 10000.0f;
	std::shared_ptr<Process> minProceess;

	for (const std::shared_ptr<Process>& process : m_Processes) 
	{
		if (!process->IsBlocked()) 
		{
			int32_t creationTime = process->GetCreationTime();
			float entitledTime = 1.0f * (m_CurrentTime - creationTime) / m_Processes.size();

			int32_t utilization = process->GetUtilization();
			int32_t weight = process->GetWeight();

			float ratio = 1.0f * utilization / (weight * entitledTime);

			if (minRatio > ratio)
			{
				minRatio = ratio;
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

void Scheduler::UpdateCurrentTime()
{
	++m_CurrentTime;
}
