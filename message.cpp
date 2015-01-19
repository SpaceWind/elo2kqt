#include "message.h"



MessagePool* MessagePool::instance = 0;


Message *MessagePool::createMessage(int messageGroup, float left, float top, float value, MessageComponent *sender, MessageComponent *super, Message *broadcast)
{
    if (inactiveMessages.empty())
        return 0;

    Message* pickedMessage = inactiveMessages.first();
    pickedMessage->messageGroup = messageGroup;
    pickedMessage->left = left;
    pickedMessage->top = top;
    pickedMessage->sender = sender;
    pickedMessage->super = super;
    pickedMessage->broadcast = broadcast;
    pickedMessage->value = value;

    inactiveMessages.removeFirst();
    activeMessages.append(pickedMessage);
}

void MessagePool::freeMessage(Message *m)
{
    if (activeMessages.contains(m))
    {
        activeMessages.removeAt(activeMessages.indexOf(m));
        inactiveMessages.append(m);
    }
}

MessagePool *MessagePool::getInstance()
{
    if (instance)
        return instance;
    return (instance = new MessagePool());
}

MessagePool::MessagePool()
{
    lastActive = -1;
}

void MessagePool::freeMessages()
{
    for (int i=0; i<inactiveMessages.count(); ++i)
        delete inactiveMessages.at(i);
    for (int i=0; i<activeMessages.count(); ++i)
        delete activeMessages.at(i);
}
