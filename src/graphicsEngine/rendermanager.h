#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include <QGLWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QVector>
#include <QRect>
#include <QList>
#include <QDebug>
#include "sprite.h"
#include "rendercontext.h"


class RenderManager : public QGLWidget
{
    Q_OBJECT

public:
    RenderManager(QWidget *parent, int width, int height);

public slots:
    void renderFunction();
    void init();
    void addSprite(Sprite* s);
    void removeSprite(Sprite* s);
    void setContext(renderContext* c);


protected:
    void paintEvent(QPaintEvent *event);
    void renderFunction(QPainter *painter, QPaintEvent *event);
    bool updateSprites();

private:
    QBrush background;
    QImage img;
    renderContext * renderContext_;
    QList<Sprite*> sprites;

};
#endif // RENDERMANAGER_H
