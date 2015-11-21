#include "window.h"
#include "defines.h"
Window::Window()
{
    setWindowTitle(tr("2D Painting on Native and OpenGL Widgets"));

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
}
Window::~Window()
{

}

void Window::messageCycle()
{
    inputSystem.update();
    sp->update();
    rm->renderFunction();
}
