
#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
	Timer();
	~Timer();

private:
	bool m_reset;
	bool m_running;

	unsigned long m_beginning;
	unsigned long m_ending;

public:
	void Start();
	void Stop();
	void Reset();

	unsigned long GetTime() const;

	bool IsRunning() const { return m_running; }
	bool IsOver(const unsigned long seconds) const { return seconds > GetTime(); } // Pass a number in and see if the real time is past or before that number
};
#endif