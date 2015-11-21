#ifndef RENDERCONTEXT_H
#define RENDERCONTEXT_H

#include <QObject>
#include <QList>
#include <QVector>
#include <QRectF>
#include "sprite.h"
#include "parallax.h"

class renderContext : public QObject
{
    Q_OBJECT
public:
    renderContext (QObject * parent);
    renderContext ();
    ~renderContext();
    void addSprite(renderInfo *spr);
    bool isSpriteAdded(renderInfo* spr);
    void removeSprite(renderInfo *spr);

    void setParallaxMode(parallaxConfig p) {parallaxMode = p;}
    void createContext(int internalRenderWidth, int internalRenderHeight,
                       int externalRenderWidth, int externalRenderHeight);
    void setScroll(int left, int top, int maxLeft = 0, int maxTop = 0, int minLeft = 0, int minTop = 0);
    void enableScolling(bool horizontal = true, bool vertical = true,
                        bool minHorizontal = true, bool maxHorizontal = false,
                        bool minVertical=false, bool maxVertical=true);
    void enableSmoothScrolling(bool horizontal, bool vertical);
    void setSmoothScroll(float horizontal, float vertical);

    void scrollTo(float left, float top);
    void scroll(float left, float top);

    float scaleCoefLeft(){return contextWidthCoef;}
    float scaleCoefTop(){return contextHeightCoef;}

    QVector<renderInfo *> render();


signals:

public slots:

private:
    QList<renderInfo*> sprites;
    QList<renderInfo*> spriteCopies;
    parallaxConfig parallaxMode;

    float contextWidthCoef, contextHeightCoef;
    QImage * contextImage;

    QRectF scrollRect;
    float minScrollLeft, minScrollTop, maxScrollLeft, maxScrollTop;
    float horizontalSmoothScrollingValue, verticalSmoothScrollingValue;

    bool horizontalScrollEnabled, verticalScrollEnabled,
         horizontalMinBoundEnabled, horizontalMaxBoundEnabled,
         verticalMinBoundEnabled, verticalMaxBoundEnabled,
         horizontalSmoothScrolling, verticalSmoothScrolling;
};



#endif // RENDERCONTEXT_H
