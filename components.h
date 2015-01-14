#ifndef COMPONENTS_H
#define COMPONENTS_H
#include <QObject>
#include "message.h"

class MessageComponent
{
public:
    virtual bool processMessage(Message* m)=0;
    virtual float getObjectParam(QString query)=0;
    virtual QString execQuery(QString query)=0;

    virtual Message* selfAddMessage()=0;
    int ownerType;
};

class InputComponent : public QObject
{
    Q_OBJECT
public:

public slots:
    virtual void keyPressed(int key);
    virtual void keyReleased(int key);
};

#endif // COMPONENT_H
