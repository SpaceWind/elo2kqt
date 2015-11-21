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

bool SimplePlayer::update()
{
    if (keyComponent->isUpPressed())
        s->move(0.0f,-1.f);
    if (keyComponent->isDownPressed())
        s->move(0.0f,1.f);
    if (keyComponent->isLeftPressed())
    {
        s->move(-1.f,0.f);
        s->setAnimation("go_left");
    }
    if (keyComponent->isRightPressed())
    {
        s->move(1.f,0.f);
        s->setAnimation("go_right");
    }
    if (!keyComponent->isDownPressed() && !keyComponent->isLeftPressed() && !keyComponent->isRightPressed() && !keyComponent->isUpPressed())
        s->setAnimation("still");
    if (keyComponent->isSpacePressed())
    {
        s->rotate(15.f);
        s->scaleTranslate(0.99f,0.99f);
    }
    if (keyComponent->isShiftPressed())
    {
        s->rotate(-15.f);
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
            s->move(0.3f,0.f);
        else
            s->move(-0.3f,0.f);
        if (lastFrame.topDest_ + lastFrame.destHeight_ /2.f < yAim / rm->getContext()->scaleCoefTop())
            s->move(0.f,0.3f);
        else
            s->move(0.f,-0.3f);

        if (fabs(lastFrame.leftDest_ + lastFrame.destWidth_ /2.f - xAim / rm->getContext()->scaleCoefLeft()) < 1.0f &&
            fabs(lastFrame.topDest_ + lastFrame.destHeight_ /2.f - yAim / rm->getContext()->scaleCoefTop()) < 1.0f)
            getAim = false;
    }

    return true;
}

