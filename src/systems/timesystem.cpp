#include "timesystem.h"

TimeSystem::TimeSystem()
{
    lastTime = QTime::currentTime();
    msecs = 0;
}

TimeSystem *TimeSystem::getInstance()
{
    if (!instance)
        instance = new TimeSystem();
    return instance;
}

void TimeSystem::update()
{
    QTime currentTime = QTime::currentTime();
    msecs += lastTime.msecsTo(currentTime);
    lastTime = currentTime;
}
TimeSystem* TimeSystem::instance = 0;

