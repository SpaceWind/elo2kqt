#include <QEvent>
#include <QKeyEvent>
#include <QStringList>
#include <QApplication>
#include <QMouseEvent>
#include "inputsystem.h"

InputSystem::InputSystem()
{
}

void InputSystem::addKeyListener(InputComponent *c)
{
    keyListeners.append(c);
}

void InputSystem::removeKeyListener(InputComponent *c)
{
    int index = keyListeners.indexOf(c);
    if (index != -1)
        keyListeners.removeAt(index);
}

void InputSystem::addMouseListener(MouseInputComponent *c)
{
    mouseListeners.append(c);
}

void InputSystem::removeMouseListener(MouseInputComponent *c)
{
    int index = mouseListeners.indexOf(c);
    if (index != -1)
        mouseListeners.removeAt(index);
}

bool InputSystem::eventFilter(QObject *object, QEvent *event)
{
    QKeyEvent *keyEvent;
    QMouseEvent * mouseEvent;
    switch (event->type())
    {
    case QEvent::KeyPress:
        keyEvent = static_cast<QKeyEvent *>(event);
        for (QList<InputComponent*>::iterator i=keyListeners.begin(); i!= keyListeners.end(); ++i)
            (*i)->keyPressed(keyEvent->key());
        return true;
        break;
    case QEvent::KeyRelease:
        keyEvent = static_cast<QKeyEvent *>(event);
        for (QList<InputComponent*>::iterator i=keyListeners.begin(); i!= keyListeners.end(); ++i)
            (*i)->keyReleased(keyEvent->key());
        return true;
        break;
    case QEvent::MouseButtonPress:
        mouseEvent = static_cast<QMouseEvent *>(event);

        for (QList<MouseInputComponent*>::iterator i = mouseListeners.begin(); i != mouseListeners.end(); ++i)
            (*i)->mousePressed(buildMouseButton(mouseEvent->buttons()),mouseEvent->pos().x(), mouseEvent->pos().y());
        return true;
        break;
    case QEvent::MouseButtonRelease:
        mouseEvent = static_cast<QMouseEvent *>(event);
        for (QList<MouseInputComponent*>::iterator i = mouseListeners.begin(); i != mouseListeners.end(); ++i)
            (*i)->mouseReleased(buildMouseButton(mouseEvent->buttons()),mouseEvent->pos().x(), mouseEvent->pos().y());
        return true;
        break;
    case QEvent::MouseButtonDblClick:
        mouseEvent = static_cast<QMouseEvent *>(event);
        for (QList<MouseInputComponent*>::iterator i = mouseListeners.begin(); i != mouseListeners.end(); ++i)
            (*i)->mouseDoubleClick(buildMouseButton(mouseEvent->buttons()),mouseEvent->pos().x(), mouseEvent->pos().y());
        return true;
        break;
    case QEvent::MouseMove:
        mouseEvent = static_cast<QMouseEvent *>(event);
        for (QList<MouseInputComponent*>::iterator i = mouseListeners.begin(); i != mouseListeners.end(); ++i)
            (*i)->mouseMove(buildMouseButton(mouseEvent->buttons()),mouseEvent->pos().x(), mouseEvent->pos().y());
        return true;
        break;
    default:
        object->parent();
        return false;
    }
}

MouseInputComponent::mouseButton InputSystem::buildMouseButton(Qt::MouseButtons buttons)
{
    MouseInputComponent::mouseButton mouseButtons;
    if ((buttons & Qt::LeftButton) && (buttons & Qt::RightButton))
        mouseButtons = MouseInputComponent::mouseButton::MOUSE_BOTH;
    else if (buttons & Qt::LeftButton)
        mouseButtons = MouseInputComponent::mouseButton::MOUSE_LEFT;
    else if (buttons & Qt::RightButton)
        mouseButtons = MouseInputComponent::mouseButton::MOUSE_RIGHT;
    else
        mouseButtons = MouseInputComponent::mouseButton::MOUSE_NONE;
    return mouseButtons;
}
