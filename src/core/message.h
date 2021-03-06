#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QVector>
#include <QList>
/*
struct Message
{
    Message();
    Message(int messageGroup, float left, float top, MessageComponent* sender, MessageComponent* super, Message* broadcast);
    ~Message(){;}
    int messageGroup;
    float left, top;
    float value;
    MessageComponent * sender;
    MessageComponent * super;

    Message * broadcast;
private:
    int poolID;
};

class MessagePool
{
public:
    ~MessagePool();
    Message *createMessage(int messageGroup, float left, float top, float value, MessageComponent* sender, MessageComponent* super, Message* broadcast);
    void freeMessage(Message* m);
    MessagePool *getInstance();
protected:
    MessagePool();
    void freeMessages();
    const int MESSAGE_COUNT = 2048;

    static MessagePool * instance;

    QList<Message*> activeMessages;
    QList<Message*> inactiveMessages;

    int lastActive;
};
*/





#endif // MESSAGECOMPONENT_H
