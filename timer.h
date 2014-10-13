#ifndef TIMER_H
#define TIMER_H

#include <QTime>

class Timer
{
private:
	static QTime _t;
	static double _currTime;
	static bool  _init;
	static double _prevTime;
	static double _dt;
public:
	static double getTimeSinceAppStart();
	static float deltaTime();
	static bool update();
};

#endif // TIMER_H
