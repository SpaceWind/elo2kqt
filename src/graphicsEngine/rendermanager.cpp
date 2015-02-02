#include "rendermanager.h"
#include <QBitmap>
#include <QTimer>
#include <QList>
#include <defines.h>

RenderManager::RenderManager(QWidget *parent, int width, int height)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    setFixedSize(width, height);
    setAutoFillBackground(false);
    QGLWidget::setFixedSize(width, height);
}

void RenderManager::init()
{

    background = QBrush(QColor(64, 98, 64));
    SpriteFabric * sf = SpriteFabric::getInstance();
    parallaxConfig p("data/config.txt","parallax_default");
    renderContext_.createContext(640,480,this->width(),this->height());
    renderContext_.setParallaxMode(p);
    renderContext_.setScroll(0,0);
    renderContext_.enableScolling();

    QString filename = "data/fx/sf.txt";
    sf->scanSprites(filename);
    sf->preload(filename);
    s = sf->newSprite("kappa+kappa_blue_boots");
    s->setAnimation("go_right");
    renderContext_.addSprite(s->getFrame());
}

void RenderManager::renderFunction(QPainter *painter, QPaintEvent *event)
{
    static QElapsedTimer t;
    static bool started = false;
    static qint64 nsecsPrev = 0;
    if (!started)
    {
        t.restart();
        started = true;
    }
    else
    {
        qDebug()<<(t.nsecsElapsed()-nsecsPrev)/1000;
        nsecsPrev = t.nsecsElapsed();
    }
    painter->fillRect(event->rect(), background);

    renderContext_.scroll(-0.4f,-0.8f);
    s->move(0.8f,0.0f);
    auto filteredSprites = renderContext_.render();
    foreach (renderInfo * item, filteredSprites)
    {
        QImage *img = SpriteFabric::getInstance()->getSpriteFrames(item->spriteType_);
        painter->drawImage(item->toRect(),*img, item->sourceRect());
    }
}



void RenderManager::renderFunction()
{
    if (s->update())
       repaint();
}
void RenderManager::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    renderFunction(&painter, event);
    painter.end();
}
