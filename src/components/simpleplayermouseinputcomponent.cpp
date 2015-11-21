#include "simpleplayermouseinputcomponent.h"

simplePlayerMouseInputComponent::simplePlayerMouseInputComponent()
{
    clicked = false;
    rotationEnabled = false;
}

simplePlayerMouseInputComponent::~simplePlayerMouseInputComponent()
{

}

void simplePlayerMouseInputComponent::mousePressed(MouseInputComponent::mouseButton mb, int x, int y)
{
    if (mb == MouseInputComponent::MOUSE_RIGHT)
    {
        lastClickLeft = x;
        lastClickTop = y;
        clicked = true;
    }
    if (mb == MouseInputComponent::MOUSE_LEFT)
    {
        rotationEnabled = !rotationEnabled;
    }
}

float simplePlayerMouseInputComponent::getLeft()
{
    clicked = false;
    return lastClickLeft;
}

float simplePlayerMouseInputComponent::getTop()
{
    clicked = false;
    return lastClickTop;
}

