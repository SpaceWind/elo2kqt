#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H

#include <QObject>

class AbstractSystem
{
public:
    virtual bool update()=0;
};

#endif // GAMESYSTEM_H
