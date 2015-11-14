#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include <QObject>
#include <QWidget>
#include <QStringList>
#include "components.h"

class keyHistory;
struct keyEventDescriptor
{
    friend bool operator==(const keyEventDescriptor& x, const keyEventDescriptor& y);
    enum keyEventType {KEY_PRESSED = 0, KEY_RELEASED = 1};
    keyEventDescriptor();
    ~keyEventDescriptor(){;}
    static keyEventDescriptor create(int key_, keyEventType eventType_);


    int timeEvent;
    int key;
    keyEventType typeEvent;
};

class inputCombo
{
    friend class InputComponent;
public:
    inputCombo(QString s){parse(s);}
    ~inputCombo(){;}
    static inputCombo fromString(QString s);
    void parse (QString s);
    bool findCombo(keyHistory& history);
    QString getName() {return name;}
private:
    QList<QList<QList<keyEventDescriptor> > > parsed;
    int getVirtualKey(QChar key);
    bool testCombo(QList<keyEventDescriptor> tokens, keyHistory& history, int maxTime);
    QList<int> timeDif;
    QString name;
};

class keyHistory
{
public:
    keyHistory();
    keyHistory(int size);
    ~keyHistory(){;}
    void add(const keyEventDescriptor& kd);
    void clear();
    int getLastKey();
    bool isLastKeyUp();
    bool isLastKeyDown(){return !isLastKeyUp();}
    QList<keyEventDescriptor> history;
    int maxSize;
    int currentSize;
};
//------------------------------------------------------------------------------------------

class InputComponent : public QObject, public GameComponent
{
    Q_OBJECT
public:

public slots:
    virtual void keyPressed(int key)=0;
    virtual void keyReleased(int key)=0;
    virtual void processCombo(QString){;}

    void addCombo(QString s);
    QStringList findCombos();
    void processAllCombos();
protected:
    QList<inputCombo> combos;
    keyHistory history;
};

class MouseInputComponent : public QObject, public GameComponent
{
    Q_OBJECT
public:
    explicit MouseInputComponent(QObject *parent = 0);
    enum mouseButton {MOUSE_LEFT = 0, MOUSE_RIGHT = 1, MOUSE_BOTH = 2, MOUSE_NONE = 3};
signals:

public slots:
    virtual void mousePressed(mouseButton mb, int x, int y)=0;
    virtual void mouseReleased(mouseButton mb, int x, int y)=0;
    virtual void mouseMove(mouseButton mb, int x, int y)=0;
    virtual void mouseDoubleClick(mouseButton mb, int x, int y)=0;
};

#endif // INPUTCOMPONENT_H
