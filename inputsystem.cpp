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


keyEventDescriptor::keyEventDescriptor()
{
    timeEvent = 0;
    key = 0;
    keyEventType = KEY_PRESSED;
}


keyHistory::keyHistory(int size)
{
    maxSize = size;
    currentSize = 0;
}

void keyHistory::add(const keyEventDescriptor &kd)
{
    if (currentSize == maxSize)
    {
        history.removeFirst();
        currentSize--;
    }
    history.append(kd);
    currentSize++;
}

int keyHistory::getLastKey()
{
    if (history.empty())
        return 0;
    return history.last().key;
}

bool keyHistory::isLastKeyUp()
{
    if (history.empty())
        return false;
    return history.last().keyEventType == keyEventDescriptor::KEY_RELEASED;
}


inputCombo inputCombo::fromString(QString s)
{
    return inputCombo(s);
}

void inputCombo::parse(QString s)
{
    //left_dash 1200 _ < !< < !< !_ then 500 r !r or 150 q !q
    QStringList allWords = s.split(" ");
    name = allWords.first();
    QString tail;
    for (int i=0; i<allWords.count(); ++i)
    {
        tail += allWords.at(i);
        if (i != allWords.count()-1)
            tail += " ";
    }
    QStringList combosStr = tail.split("or");
    foreach(const QString& str, combosStr)
    {
        QString simpleStr = str.simplified();
     //   QStringList subCombos =
    }
}
