#pragma once

struct GameTime
{
	double ElapsedTime;
	double TotalTime;

	GameTime()
		: ElapsedTime(0), TotalTime(0)
	{
	}

	GameTime(double elapsed, double total)
		: ElapsedTime(elapsed), TotalTime(total)
	{	
	}

	~GameTime()
	{
	}
};