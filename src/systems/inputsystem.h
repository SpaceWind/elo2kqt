#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H
#include <QList>
#include "abstractystem.h"
#include "inputcomponent.h"
class InputSystem : public QObject, public AbstractSystem
{
    Q_OBJECT
public:
    InputSystem();
    ~InputSystem(){;}

    virtual void addKeyListener(InputComponent * c);
    virtual void removeKeyListener(InputComponent *c);

    virtual void addMouseListener(MouseInputComponent * c);
    virtual void removeMouseListener(MouseInputComponent *c);

    virtual bool eventFilter(QObject *object, QEvent *event) override;
    virtual bool update(uint){return false;}
private:
    MouseInputComponent::mouseButton buildMouseButton(Qt::MouseButtons buttons);
    QList<InputComponent*> keyListeners;
    QList<MouseInputComponent*> mouseListeners;

};


#endif // INPUTSYSTEM_H
