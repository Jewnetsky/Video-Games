#include "stdafx.h"
#include "Timer.h"


Timer::Timer() :
	m_reset(true),
	m_running(false),
	m_beginning(0),
	m_ending(0)
{
}

Timer::~Timer()
{
}

void Timer::Start()
{
	if (!m_running)
	{
		if (m_reset)
			m_beginning = (unsigned long)clock();
		else
			m_beginning -= m_ending - (unsigned long)clock(); // Sets beginning to new beginning 
		m_reset = false;
		m_running = true;
	}
}

void Timer::Stop()
{
	if (m_running)
	{
		m_ending = (unsigned long)clock();
		m_running = false;
	}
}

void Timer::Reset()
{
	bool wereRunning = m_running;
	if (wereRunning)
		Stop();

	m_reset = true;
	wereRunning = true;
	m_beginning = 0;
	m_ending = 0;

	// Start timer
	Start();
}

unsigned long Timer::GetTime() const
{
	if (m_running)
		return ((unsigned long)clock() - m_beginning) / CLOCKS_PER_SEC; // Change to ms by x1000
	else
		return ((m_ending - m_beginning) / CLOCKS_PER_SEC) * 1000.0l;
}
