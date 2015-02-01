#ifndef TIMESYSTEM_H
#define TIMESYSTEM_H

#include <QTime>
#include <QHash>

class TimeSystem
{
public:
    static TimeSystem *getInstance();
    ~TimeSystem(){;}
    int getSystemTime() {return msecs;}
    int elapsed(int prev) {return msecs - prev;}
    void update();
protected:
    TimeSystem();
    int msecs;
    QTime lastTime;
    static TimeSystem* instance;
};

#endif // TIMESYSTEM_H
