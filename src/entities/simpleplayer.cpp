#include "simpleplayer.h"

SimplePlayer::SimplePlayer(RenderManager * m)
{
    rm = m;
    s = SpriteFabric::getInstance()->newSprite("kappa");
    s->addAnimation("still",0,0,100000);
    s->setAnimation("still");
    rm->addSprite(s);
    movingEnabled = false;
    upPressed = false;
    downPressed = false;
    leftPressed = false;
    rightPressed = false;
    spacePressed = false;
}

SimplePlayer::~SimplePlayer()
{

}

void SimplePlayer::keyPressed(int key)
{
    switch (key)
    {
    case Qt::Key_Up:
        upPressed = true;
        if (!leftPressed && !rightPressed)
            s->setAnimation("go_right");
        break;
    case Qt::Key_Down:
        downPressed = true;
        if (!leftPressed && !rightPressed)
            s->setAnimation("go_right");
        break;
    case Qt::Key_Left:
        leftPressed = true;
        s->setAnimation("go_left");
        break;
    case Qt::Key_Right:
        rightPressed = true;
        s->setAnimation("go_right");
        break;
    case Qt::Key_Space:
        spacePressed = true;
        break;
    default:
        break;
    }
}

void SimplePlayer::keyReleased(int key)
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
        if (rightPressed)
            s->setAnimation("go_right");
        break;
    case Qt::Key_Right:
        rightPressed = false;
        if (leftPressed)
            s->setAnimation("go_left");
        break;
    case Qt::Key_Space:
        spacePressed = false;
        break;
    default:
        break;
    }
    if (!upPressed && !downPressed && !leftPressed && !rightPressed)
        s->setAnimation("still");
}

bool SimplePlayer::update()
{
    if (upPressed)
        s->move(0.0f,-1.f);
    if (downPressed)
        s->move(0.f,1.f);
    if (leftPressed)
        s->move(-1.0f,0.f);
    if (rightPressed)
        s->move(1.0f,0.f);
    if (spacePressed)
        s->rotate(1.5f);
    return true;
}

