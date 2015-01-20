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
    typeEvent = keyEventType::KEY_PRESSED;
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
    return history.last().typeEvent == keyEventDescriptor::keyEventType::KEY_RELEASED;
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
    tail = tail.toLower();
    QStringList combosStr = tail.split("or");
    foreach(const QString& str, combosStr)
    {
        QString simpleStr = str.simplified();
     //   QStringList subCombos =
        QStringList thenList = simpleStr.split("then");
        QList<QList<keyEventDescriptor> > serialCombo;
        foreach (const QString& thenStr, thenList)
        {
            QList<keyEventDescriptor> combo;
            QString simpleThenStr = thenStr.simplified();
            QStringList tokens = simpleThenStr.split(" ");
            int index = 0;
            foreach (const QString& token, tokens)
            {
                QString simpleToken = token.simplified();
                if (index == 0)
                    timeDif.append(simpleToken.toInt());
                else
                {
                    keyEventDescriptor kd;
                    bool isKeyDown = (simpleToken.at(0) == '!');
                    kd.key = getVirtualKey(simpleToken.at(1));
                    kd.typeEvent = isKeyDown ? keyEventDescriptor::KEY_PRESSED : keyEventDescriptor::KEY_RELEASED;
                    combo.append(kd);
                }
            }
            serialCombo.append(combo);
        }
        parsed.append(serialCombo);
    }
}

int inputCombo::getVirtualKey(QChar key)
{
    char c = key.toLatin1();
    switch (c)
    {
    case '<':
        return Qt::Key_Left;
    case '>':
        return Qt::Key_Right;
    case '$':
        return Qt::Key_Shift;
    case '*':
        return Qt::Key_Control;
    case '^':
        return Qt::Key_Up;
    case '_':
        return Qt::Key_Down;
    case ' ':
        return Qt::Key_Space;
    case '#':
        return Qt::Key_Return;
    case '@':
        return Qt::Key_Enter;
    case 'a':
        return Qt::Key_A;
    case 'b':
        return Qt::Key_B;
    case 'c':
        return Qt::Key_C;
    case 'd':
        return Qt::Key_D;
    case 'e':
        return Qt::Key_E;
    case 'f':
        return Qt::Key_F;
    case 'g':
        return Qt::Key_G;
    case 'h':
        return Qt::Key_H;
    case 'i':
        return Qt::Key_I;
    case 'j':
        return Qt::Key_J;
    case 'k':
        return Qt::Key_K;
    case 'l':
        return Qt::Key_L;
    case 'm':
        return Qt::Key_M;
    case 'n':
        return Qt::Key_N;
    case 'o':
        return Qt::Key_O;
    case 'p':
        return Qt::Key_P;
    case 'q':
        return Qt::Key_Q;
    case 'r':
        return Qt::Key_R;
    case 's':
        return Qt::Key_S;
    case 't':
        return Qt::Key_T;
    case 'u':
        return Qt::Key_U;
    case 'v':
        return Qt::Key_V;
    case 'w':
        return Qt::Key_W;
    case 'x':
        return Qt::Key_X;
    case 'y':
        return Qt::Key_Y;
    case 'z':
        return Qt::Key_Z;
    default:
        return 0;
    }
}
