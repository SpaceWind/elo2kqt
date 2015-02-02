#ifndef TIMESYSTEM_H
#define TIMESYSTEM_H

#include <QTime>
#include <QHash>
#include "abstractystem.h"

class TimeSystem
{
public:
    static TimeSystem *getInstance();
    ~TimeSystem(){;}
    int getSystemTime() {return msecs;}
    int elapsed(int prev) {return msecs - prev;}
    virtual bool update();
protected:
    TimeSystem();
    int msecs;
    QTime lastTime;
    static TimeSystem* instance;
};

#endif // TIMESYSTEM_H
