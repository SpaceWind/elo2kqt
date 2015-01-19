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
    case 'ф':
        return Qt::Key_A;
    case 'b':
    case 'и':
        return Qt::Key_B;
    case 'c':
    case 'с':
        return Qt::Key_C;
    case 'd':
    case 'в':
        return Qt::Key_D;
    case 'e':
    case 'у':
        return Qt::Key_E;
    case 'f':
    case 'а':
        return Qt::Key_F;
    case 'g':
    case 'п':
        return Qt::Key_G;
    case 'h':
    case 'р':
        return Qt::Key_H;
    case 'i':
    case 'ш':
        return Qt::Key_I;
    case 'j':
    case 'о':
        return Qt::Key_J;
    case 'k':
    case 'л':
        return Qt::Key_K;
    case 'l':
    case 'д':
        return Qt::Key_L;
    case 'm':
    case 'ь':
        return Qt::Key_M;
    case 'n':
    case 'т':
        return Qt::Key_N;
    case 'o':
    case 'щ':
        return Qt::Key_O;
    case 'p':
    case 'з':
        return Qt::Key_P;
    case 'q':
    case 'й':
        return Qt::Key_Q;
    case 'r':
    case 'к':
        return Qt::Key_R;
    case 's':
    case 'ы':
        return Qt::Key_S;
    case 't':
    case 'е':
        return Qt::Key_T;
    case 'u':
    case 'г':
        return Qt::Key_U;
    case 'v':
    case 'м':
        return Qt::Key_V;
    case 'w':
    case 'ц':
        return Qt::Key_W;
    case 'x':
    case 'ч':
        return Qt::Key_X;
    case 'y':
    case 'н':
        return Qt::Key_Y;
    case 'z':
    case 'я':
        return Qt::Key_Z;
    default:
        return 0;
    }
}
