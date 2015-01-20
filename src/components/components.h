#ifndef COMPONENTS_H
#define COMPONENTS_H
#include <QObject>


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

class InputComponent : public QObject
{
    Q_OBJECT
public:

public slots:
    virtual void keyPressed(int key)=0;
    virtual void keyReleased(int key)=0;
};

#endif // COMPONENT_H
