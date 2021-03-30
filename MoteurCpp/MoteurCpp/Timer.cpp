#include "Timer.h" 
#include <iostream>

bool Clock::Initialize()
{
#if defined(_DEBUG)
	m_DebugName = "Timer";
#endif
	TimePointAtStartup = TimeSource::now();
	PreviousTimePoint = TimePointAtStartup;
	std::cout << "[Timer] initialized\n";
	return true;
}

void Clock::DeInitialize()
{
	std::cout << "[Timer] deinitialized\n";
}

// ce n'est pas une fonction virtuelle !
void Clock::Update()
{
	CurrentTimePoint = TimeSource::now();
	TimeSinceStartup = std::chrono::duration<double>(CurrentTimePoint - TimePointAtStartup).count();

	ElapsedTime = std::chrono::duration<double>(CurrentTimePoint - PreviousTimePoint).count();
	PreviousTimePoint = CurrentTimePoint;

	// petit exemple simplifie de Scheduler 
	for (size_t i = 0; i < m_Timers.size(); )
	{
		Timer& timer = m_Timers[i].first;
		timer.CurrentTime += ElapsedTime;
		if (timer.CurrentTime >= timer.Delay)
		{
			// invoque notre fonction
			m_Timers[i].second();

			// reset le timer
			timer.CurrentTime -= timer.Delay;

			if (timer.Repeat == false) 
			{
				m_Timers[i] = m_Timers.back();
				m_Timers.pop_back();
				i--;
			}
		}

		i++;
	}

	std::cout << "[Timer] update\n";
}