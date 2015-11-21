#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H

#include <QObject>

class AbstractSystem
{
public:
    virtual bool update(uint delta)=0;
};

#endif // GAMESYSTEM_H
