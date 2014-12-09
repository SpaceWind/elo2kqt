#include "rendercontext.h"

renderContext::renderContext(QObject *parent) :
    QObject(parent)
{
    contextImage = NULL;
}

renderContext::renderContext()
{
    contextImage = NULL;
}

renderContext::~renderContext()
{
    if (contextImage)
        delete contextImage;
    while (!spriteCopies.isEmpty())
    {
        delete spriteCopies.first();
        spriteCopies.removeFirst();
    }
}

void renderContext::addSprite(renderInfo *spr)
{
    sprites.append(spr);
    renderInfo * copy = new renderInfo();
    (*copy) = (*spr);
    spriteCopies.append(copy);
}

bool renderContext::isSpriteAdded(renderInfo *spr)
{
    return sprites.contains(spr);
}

void renderContext::removeSprite(renderInfo *spr)
{
    if (isSpriteAdded(spr))
    {
        int index = sprites.indexOf(spr);
        sprites.removeAt(index);
        renderInfo * toDelete = spriteCopies.at(index);
        spriteCopies.removeAt(index);
        delete toDelete;
    }
}

void renderContext::createContext(int internalRenderWidth, int internalRenderHeight, int externalRenderWidth, int externalRenderHeight)
{
    if (contextImage)
        delete contextImage;

    contextImage = new QImage(internalRenderWidth,internalRenderHeight,QImage::Format_ARGB32);
    contextImage->fill(QColor::fromRgba(qRgba(0,0,0,0)));
    contextWidthCoef = float(externalRenderWidth)/float(internalRenderWidth);
    contextHeightCoef = float(externalRenderHeight)/float(internalRenderHeight);
    scrollRect.setLeft(0);
    scrollRect.setTop(0);
    scrollRect.setWidth(externalRenderWidth);
    scrollRect.setHeight(externalRenderHeight);
}

void renderContext::setScroll(int left, int top, int maxLeft, int maxTop, int minLeft, int minTop)
{
    scrollRect.setLeft(left*contextWidthCoef);
    scrollRect.setTop(top*contextWidthCoef);
    minScrollLeft = minLeft;
    maxScrollLeft = maxLeft;
    minScrollTop = minTop;
    maxScrollTop = maxTop;
}

void renderContext::enableScolling(bool horizontal, bool vertical, bool minHorizontal, bool maxHorizontal, bool minVertical, bool maxVertical)
{
    horizontalScrollEnabled = horizontal;
    verticalScrollEnabled = vertical;
    horizontalMinBoundEnabled = minHorizontal;
    horizontalMaxBoundEnabled = maxHorizontal;
    verticalMaxBoundEnabled = maxVertical;
    verticalMinBoundEnabled = minVertical;
}

void renderContext::enableSmoothScrolling(bool horizontal, bool vertical)
{
    horizontalSmoothScrolling = horizontal;
    verticalSmoothScrolling = vertical;
}

void renderContext::setSmoothScroll(float horizontal, float vertical)
{
    horizontalSmoothScrollingValue = horizontal;
    verticalSmoothScrollingValue = vertical;
}

void renderContext::scrollTo(float left, float top)
{
    if (horizontalScrollEnabled)
    {
        if (horizontalMinBoundEnabled && left < minScrollLeft)
            scrollRect.setLeft(minScrollLeft);
        if (horizontalMaxBoundEnabled && left > maxScrollLeft)
            scrollRect.setLeft(maxScrollLeft);
        else
            scrollRect.setLeft(left);
    }
    if (verticalScrollEnabled)
    {
        if (verticalMinBoundEnabled && top < minScrollTop)
            scrollRect.setTop(minScrollTop);
        if (verticalMaxBoundEnabled && top > maxScrollTop)
            scrollRect.setTop(maxScrollTop);
        else
            scrollRect.setTop(top);
    }
}

void renderContext::scroll(float left, float top)
{
    if (horizontalSmoothScrolling)
        left = std::min(horizontalSmoothScrollingValue, left);
    if (verticalSmoothScrolling)
        top = std::min(verticalSmoothScrollingValue, top);
    scrollTo(scrollRect.left()+left*contextWidthCoef, scrollRect.top()+top*contextHeightCoef);
}

QVector<renderInfo *> renderContext::render()
{
    QVector<renderInfo*> result;
    if (contextImage == 0)
            return result;
    for (int i=0; i<sprites.count(); i++)
    {
        renderInfo * srcInfo = sprites.at(i);
        renderInfo * destInfo = spriteCopies.at(i);
        float parallaxScaleCoef = parallaxMode.interpolate("scalePoints",srcInfo->zIndex_);
        float parallaxMoveCoef = parallaxMode.interpolate("movePoints",srcInfo->zIndex_);
        destInfo->destWidth_  = srcInfo->destWidth_*contextWidthCoef*parallaxScaleCoef;
        destInfo->destHeight_ = srcInfo->destHeight_*contextHeightCoef*parallaxScaleCoef;
        destInfo->rotate_ = srcInfo->rotate_;
        destInfo->leftOffset_ = srcInfo->leftOffset_;
        destInfo->topOffset_ = srcInfo->topOffset_;
        destInfo->leftDest_ = srcInfo->leftDest_*contextHeightCoef*parallaxMoveCoef;
        destInfo->topDest_ = srcInfo->topDest_*contextHeightCoef*parallaxMoveCoef;
        if (destInfo->toRect().intersects(scrollRect) ||
            (destInfo->isScrollable == false && destInfo->toRect().intersects(QRectF(0,contextImage->width(),contextImage->height()))))
            result.append(destInfo);
    }

    std::sort(result.begin(), result.end(),
              [] (const renderInfo* lhs, const renderInfo* rhs) {
                  return lhs->zIndex_ < rhs->zIndex_;
              });
    foreach (renderInfo* item, result)
    {
        if (item->isScrollable)
        {
            item->leftDest_ -= scrollRect.left();
            item->topDest_ -= scrollRect.top();
        }
    }

    return result;
}
