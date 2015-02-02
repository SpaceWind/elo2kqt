#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include <QGLWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QVector>
#include <QRect>
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

protected:
    void paintEvent(QPaintEvent *event);
    void renderFunction(QPainter *painter, QPaintEvent *event);


   // QVector<renderInfo> filterSprites(QRect outerRect, QRect innerRect, QVector<renderInfo> sprites);

private:
    QBrush background;
    QImage img;
    Sprite* s;
    renderContext renderContext_;

};
#endif // RENDERMANAGER_H
