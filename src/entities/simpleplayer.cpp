#include "simpleplayer.h"

SimplePlayer::SimplePlayer(RenderManager * m)
{
    rm = m;
    s = SpriteFabric::getInstance()->newSprite("kappa");
    s->addAnimation("still",0,0,100000);
    s->setAnimation("still");
    rm->addSprite(s);
    movingEnabled = false;

    getAim = false;

    keyComponent = new SimplePlayerInputComponent();
    mouseComponent = new simplePlayerMouseInputComponent();
}

SimplePlayer::~SimplePlayer()
{

}

bool SimplePlayer::update(uint delta)
{
    const static float speed = 150;
    float deltaF = float(delta)/1000000.f;
    if (keyComponent->isUpPressed())
        s->move(0.0f,-deltaF*speed);
    if (keyComponent->isDownPressed())
        s->move(0.0f,deltaF*speed);
    if (keyComponent->isLeftPressed())
    {
        s->move(-deltaF*speed,0.f);
        s->setAnimation("go_left");
    }
    if (keyComponent->isRightPressed())
    {
        s->move(deltaF*speed,0.f);
        s->setAnimation("go_right");
    }
    if (!keyComponent->isDownPressed() && !keyComponent->isLeftPressed() && !keyComponent->isRightPressed() && !keyComponent->isUpPressed())
        s->setAnimation("still");
    if (keyComponent->isSpacePressed())
    {
        s->rotate(deltaF*speed);
        s->scaleTranslate(0.99f,0.99f);
    }
    if (keyComponent->isShiftPressed())
    {
        s->rotate(-deltaF*speed);
        s->scaleTranslate(1.01f,1.01f);
    }

    if (mouseComponent->isClicked())
    {
        xAim = mouseComponent->getLeft();
        yAim = mouseComponent->getTop();
        getAim = true;
    }
    if (getAim)
    {
        auto lastFrame = s->render();
        if (lastFrame.leftDest_ + lastFrame.destWidth_ /2.f < xAim / rm->getContext()->scaleCoefLeft())
            s->move(deltaF*speed/3.0f,0.f);
        else
            s->move(-deltaF*speed/3.0f,0.f);
        if (lastFrame.topDest_ + lastFrame.destHeight_ /2.f < yAim / rm->getContext()->scaleCoefTop())
            s->move(0.f,deltaF*speed/3.0f);
        else
            s->move(0.f,-deltaF*speed/3.0f);

        if (fabs(lastFrame.leftDest_ + lastFrame.destWidth_ /2.f - xAim / rm->getContext()->scaleCoefLeft()) < 1.0f &&
            fabs(lastFrame.topDest_ + lastFrame.destHeight_ /2.f - yAim / rm->getContext()->scaleCoefTop()) < 1.0f)
            getAim = false;
    }
    if (mouseComponent->isRotationEnabled())
        s->rotate(1.4f*deltaF*speed);

    return true;
}

