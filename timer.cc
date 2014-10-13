#include "timer.h"
#include <cfloat>

QTime Timer::_t;
bool  Timer::_init = false;
double Timer::_currTime = 0.f;
double Timer::_prevTime = 0.f;
double Timer::_dt = 0.f;

double Timer::getTimeSinceAppStart()
{
	if (!_init)
	{
		_init = true;
		_t.start();
	}
	else
	{
		_currTime += _t.elapsed()/1000.0;
		_t.restart();
	}
	return _currTime;
}

float Timer::deltaTime()
{
	return _dt;
}

bool Timer::update()
{
	double currTime = getTimeSinceAppStart();
	double dt = currTime - _prevTime;
	if (dt > FLT_MIN)
	{
		_dt = (float)dt;
		_prevTime = currTime;
		return true;
	}
	else
	{
		_dt = 0.0f;
		return false;
	}
}
