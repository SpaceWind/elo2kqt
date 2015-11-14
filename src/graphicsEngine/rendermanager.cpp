#include "rendermanager.h"
#include <QBitmap>
#include <QTimer>
#include <QList>
#include <QTransform>
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
    background = QBrush(QColor(0, 0, 0));
    SpriteFabric * sf = SpriteFabric::getInstance();

    QString filename = "data/fx/sf.txt";
    sf->scanSprites(filename);
    sf->preload(filename);
}

void RenderManager::addSprite(Sprite *s)
{
    renderContext_->addSprite(s->getFrame());
    sprites.append(s);
}

void RenderManager::removeSprite(Sprite *s)
{
    renderContext_->removeSprite(s->getFrame());
    sprites.removeAt(sprites.indexOf(s));
}

void RenderManager::setContext(renderContext *c)
{
    renderContext_ = c;
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

    auto filteredSprites = renderContext_->render();
    foreach (renderInfo * item, filteredSprites)
    {
        QImage *img = SpriteFabric::getInstance()->getSpriteFrames(item->spriteType_);

        QRectF itemRect = item->toRect();

        if (item->rotate_ != 0.0f)
        {
            QTransform trans;

            trans.translate(itemRect.left() + itemRect.width()/2.0f, itemRect.top() + itemRect.height()/2.0f);
            trans.rotate(item->rotate_);
            painter->setTransform(trans);
            painter->drawImage(QRectF(-itemRect.width()/2.f,
                                      -itemRect.height()/2.f,
                                      itemRect.width(),
                                      itemRect.height()),
                               *img, item->sourceRect());
            painter->resetTransform();
        }
        else
            painter->drawImage(itemRect,*img,item->sourceRect());
    }
}

bool RenderManager::updateSprites()
{
    bool needRender = false;
    foreach(Sprite * s, sprites)
    {
        if (s->update())
            needRender = true;
    }
    return needRender;
}



void RenderManager::renderFunction()
{
    if (updateSprites())
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
