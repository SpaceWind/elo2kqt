#include "inputsystem.h"
#include <QEvent>
#include <QKeyEvent>
#include <QStringList>

InputSystem::InputSystem()
{
}

void InputSystem::addComponent(InputComponent *c)
{
    listeners.append(c);
}

void InputSystem::removeComponent(InputComponent *c)
{
    int index = listeners.indexOf(c);
    if (index != -1)
        listeners.removeAt(index);
}

bool InputSystem::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        for (QList<InputComponent*>::iterator i=listeners.begin(); i!= listeners.end(); ++i)
        {
            (*i)->keyPressed(keyEvent->key());
        }
        return true;
    }

    if (event->type() == QEvent::KeyRelease)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        for (QList<InputComponent*>::iterator i=listeners.begin(); i!= listeners.end(); ++i)
        {
            (*i)->keyReleased(keyEvent->key());
        }
        return true;
    }

    return false;
}
