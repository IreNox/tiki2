#pragma once

struct GameTime
{
	double ElapsedTime;
	double TotalTime;

	GameTime(double elapsed, double total)
		: ElapsedTime(elapsed), TotalTime(total)
	{	
	}

	~GameTime()
	{
	}
};