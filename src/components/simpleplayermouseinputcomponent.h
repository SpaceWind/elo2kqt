#ifndef SIMPLEPLAYERMOUSEINPUTCOMPONENT_H
#define SIMPLEPLAYERMOUSEINPUTCOMPONENT_H

#include <inputcomponent.h>


class simplePlayerMouseInputComponent : public MouseInputComponent
{
public:
    simplePlayerMouseInputComponent();
    ~simplePlayerMouseInputComponent();
    virtual void mousePressed(mouseButton mb, int x, int y);
    virtual void mouseReleased(mouseButton, int, int){;}
    virtual void mouseMove(mouseButton, int, int){;}
    virtual void mouseDoubleClick(mouseButton, int, int){;}
    virtual bool update(){return true;}
    float getLeft();
    float getTop();
    bool isClicked(){return clicked;}
private:
    float lastClickLeft;
    float lastClickTop;
    bool clicked;
};

#endif // SIMPLEPLAYERMOUSEINPUTCOMPONENT_H
