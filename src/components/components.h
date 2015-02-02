#ifndef COMPONENTS_H
#define COMPONENTS_H
#include <QObject>
#include <Qlist>

class GameComponent
{
public:
    virtual bool update()=0;
};

/*
class Message;
class MessageComponent
{
public:
    virtual bool processMessage(Message* m)=0;
    virtual float getObjectParam(QString query)=0;
    virtual QString execQuery(QString query)=0;

    virtual Message* selfAddMessage()=0;
    int ownerType;
};
*/

#endif // COMPONENT_H
