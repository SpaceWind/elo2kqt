#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H
#include <QList>
#include "inputcomponent.h"
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


#endif // INPUTSYSTEM_H
