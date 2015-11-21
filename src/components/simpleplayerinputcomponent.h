#ifndef SIMPLEPLAYERINPUTCOMPONENT_H
#define SIMPLEPLAYERINPUTCOMPONENT_H

#include <inputcomponent.h>


class SimplePlayerInputComponent : public InputComponent
{
public:
    SimplePlayerInputComponent();
    ~SimplePlayerInputComponent();
    virtual void keyPressed(int key);
    virtual void keyReleased(int key);
    virtual bool update(uint){return true;}
    bool isUpPressed(){return upPressed;}
    bool isLeftPressed(){return leftPressed;}
    bool isRightPressed(){return rightPressed;}
    bool isDownPressed() {return downPressed;}
    bool isSpacePressed(){return spacePressed;}
    bool isShiftPressed(){return shiftPressed;}

private:
    bool upPressed, leftPressed, rightPressed, downPressed, spacePressed, shiftPressed;
};

#endif // SIMPLEPLAYERINPUTCOMPONENT_H
