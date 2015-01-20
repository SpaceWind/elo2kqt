#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H
#include <QList>
#include "components.h"

class InputSystem : public QObject
{
    Q_OBJECT
public:
    InputSystem();
    ~InputSystem(){;}

    virtual void addComponent(InputComponent * c);
    virtual void removeComponent(InputComponent *c);
    virtual bool eventFilter(QObject *object, QEvent *event) override;
private:
    QList<InputComponent*> listeners;

};

struct keyEventDescriptor
{
    enum keyEventType {KEY_PRESSED = 0, KEY_RELEASED = 1};
    keyEventDescriptor();
    ~keyEventDescriptor(){;}
    int timeEvent;
    int key;
    keyEventType typeEvent;
};

class inputCombo
{
public:
    inputCombo(QString s){parse(s);}
    ~inputCombo(){;}
    static inputCombo fromString(QString s);
    void parse (QString s);
private:
    QList<QList<QList<keyEventDescriptor> > > parsed;
    int getVirtualKey(QChar key);
    QList<int> timeDif;
    QString name;
};

class keyHistory
{
    keyHistory(int size);
    ~keyHistory(){;}
    void add(const keyEventDescriptor& kd);
    int getLastKey();
    bool isLastKeyUp();
    bool isLastKeyDown(){return !isLastKeyUp();}
public:
    QList<keyEventDescriptor> history;
    int maxSize;
    int currentSize;
};

#endif // INPUTSYSTEM_H
