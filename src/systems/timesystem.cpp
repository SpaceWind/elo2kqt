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

bool TimeSystem::update(uint)
{
    QTime currentTime = QTime::currentTime();
    msecs += lastTime.msecsTo(currentTime);
    lastTime = currentTime;
    return true;
}
TimeSystem* TimeSystem::instance = 0;

