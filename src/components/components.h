#ifndef COMPONENTS_H
#define COMPONENTS_H
#include <QObject>
#include <Qlist>

class GameComponent
{
public:
    virtual bool update()=0;
};

#endif // COMPONENT_H
