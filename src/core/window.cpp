#include "window.h"
#include "defines.h"
#include <fmod.h>
Window::Window()
{
    setWindowTitle(tr("2D Painting on Native and OpenGL Widgets"));

    FMOD_SYSTEM * soundSystem;
    FMOD_System_Create(&soundSystem);
    FMOD_System_Init(soundSystem,32,FMOD_INIT_NORMAL,0);
    FMOD_SOUND * sound;
    FMOD_CHANNEL * channel;
    FMOD_System_CreateSound(soundSystem,"data/sound/music/twilight.mp3",FMOD_LOOP_NORMAL,0,&sound);
    FMOD_System_PlaySound(soundSystem,sound,0,false,&channel);
    FMOD_Channel_SetVolume(channel,0.2f);

  //  FMOD::Sound * sound;
   // FMOD::Channel * channel;
    //soundSystem->createSound("data/sound/music/twilight.mp3", FMOD_LOOP_OFF, 0, &sound);
    //soundSystem->playSound(sound,0,false,&channel);
  //  soundSystem->playSound(1 /*channel #1*/, sound, true /*start paused*/, &channel);
    // actually play sound
  //  channel->setPaused(false);

    QRect screenRect = QApplication::desktop()->screenGeometry();

    rm = new RenderManager(this, screenRect.width(), screenRect.height());
    rm->init();

    const int SCREEN_WIDTH = screenRect.width();
    const int SCREEN_HEIGHT = screenRect.height();
    const int CONTEXT_WIDTH = 384/2;
    const int CONTEXT_HEIGHT = 210/2;

    parallaxConfig p("data/config.txt","parallax_default");
    auto renderContext_ = new renderContext(this);
    renderContext_->createContext(CONTEXT_WIDTH,CONTEXT_HEIGHT,SCREEN_WIDTH,SCREEN_HEIGHT);
    renderContext_->setParallaxMode(p);
    renderContext_->setScroll(0,0);
    renderContext_->enableScolling();
    rm->setContext(renderContext_);

    SpriteFabric * sf = SpriteFabric::getInstance();

    Sprite * horse = sf->newSprite("horse");
    horse->setAnimation("default");
    horse->move(0,0,-1);
    horse->scale(float(CONTEXT_WIDTH)/horse->getRect().width(),float(CONTEXT_HEIGHT)/horse->getRect().height());
    rm->addSprite(horse);

    rm->showFullScreen();
    rm->move(0,0);
    this->installEventFilter(&inputSystem);

    sp = new SimplePlayer(rm);
    inputSystem.addKeyListener(sp->keyComponent);
    inputSystem.addMouseListener(sp->mouseComponent);


    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(messageCycle()));
    timer->start(5);
    elapsedTimer = new QElapsedTimer();
    elapsedTimer->start();
}
Window::~Window()
{

}

void Window::messageCycle()
{
    qint64 delta = elapsedTimer->nsecsElapsed();
    elapsedTimer->restart();
    inputSystem.update(delta);
    sp->update(delta/1000);
  //  qDebug() << delta/1000;
    rm->renderFunction();
}
