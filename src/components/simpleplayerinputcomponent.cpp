#include "simpleplayerinputcomponent.h"

SimplePlayerInputComponent::SimplePlayerInputComponent()
{
    upPressed = false;
    downPressed = false;
    leftPressed = false;
    rightPressed = false;
    spacePressed = false;
    shiftPressed = false;
}

SimplePlayerInputComponent::~SimplePlayerInputComponent()
{

}

void SimplePlayerInputComponent::keyPressed(int key)
{
    switch (key)
    {
    case Qt::Key_Up:
        upPressed = true;
        break;
    case Qt::Key_Down:
        downPressed = true;
        break;
    case Qt::Key_Left:
        leftPressed = true;
        break;
    case Qt::Key_Right:
        rightPressed = true;
        break;
    case Qt::Key_Space:
        spacePressed = true;
        break;
    case Qt::Key_Shift:
        shiftPressed = true;
        break;
    default:
        break;
    }
}

void SimplePlayerInputComponent::keyReleased(int key)
{
    switch (key)
    {
    case Qt::Key_Up:
        upPressed = false;
        break;
    case Qt::Key_Down:
        downPressed = false;
        break;
    case Qt::Key_Left:
        leftPressed = false;
        break;
    case Qt::Key_Right:
        rightPressed = false;
        break;
    case Qt::Key_Space:
        spacePressed = false;
        break;
    case Qt::Key_Shift:
        shiftPressed = false;
        break;
    default:
        break;
    }
}

