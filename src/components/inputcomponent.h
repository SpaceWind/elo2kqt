#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include <QObject>
#include <QWidget>

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

class InputComponent : public QObject
{
    Q_OBJECT
public:

public slots:
    virtual void keyPressed(int key)=0;
    virtual void keyReleased(int key)=0;
    virtual void update()=0;
    void addCombo(QString s);
protected:
    QList<inputCombo> combos;
    keyHistory history;
};

#endif // INPUTCOMPONENT_H
