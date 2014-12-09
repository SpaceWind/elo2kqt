#include "sprite.h"

Sprite::Sprite() : QObject(0)
{
}

Sprite::Sprite(QString descriptor, QString imageName)
{
    type = imageName;
    SpriteDescriptionParser sp(descriptor.split("\r\n"));

    currentAnimation = 0;
    currentFrame = 0;
    lastTimeUpdated = 0;
    scaleCoef = 1.0f;
    animations = sp.animations;
    frameWidth = sp.frameWidth;
    frameHeight = sp.frameHeight;
    texOffsetLeft = sp.texOffsetLeft;
    texOffsetTop = sp.texOffsetTop;
    z = 1024;
    isPaused = false;
    isTimerStarted = false;
    updated = false;
    genFirstFrame();
}

void Sprite::genFirstFrame()
{
    lastFrame.frameWidth_ = frameWidth;
    lastFrame.frameHeight_ = frameHeight;
    lastFrame.destWidth_ = frameWidth;
    lastFrame.destHeight_ = frameHeight;
    setPosition (0, 0, 1024);
    lastFrame.changeFrame(currentFrame, texOffsetLeft);
    lastFrame.spriteType_ = type;

}


renderInfo::renderInfo(QString spriteType, float left, float top, int frameWidth, int frameHeight, int zIndex,
                       int leftOffset, int topOffset, int destWidth, int destHeight, float rotate)
{
    spriteType_ = spriteType;
    leftDest_ = left;
    topDest_ = top;
    frameWidth_ = frameWidth;
    frameHeight_ = frameHeight;
    zIndex_ = zIndex;
    leftOffset_ = leftOffset;
    topOffset_ = topOffset;
    destWidth_ = (destWidth == -1)? frameWidth : destWidth;
    destHeight_ = (destHeight == -1)? frameHeight : destHeight;
    rotate_ = rotate;
    isScrollable = true;
}

renderInfo::renderInfo()
{
    spriteType_ = "";
    leftDest_ = leftOffset_ = 0;
    topDest_ = topOffset_ = 0;
    frameWidth_ = frameHeight_ = 0;
    zIndex_ = 0;
    destWidth_ = destHeight_ = 0;
    rotate_ = 0;
    isScrollable = true;
}

void renderInfo::translate(float x, float y, float z)
{
    leftDest_ += x;
    topDest_ += y;
    zIndex_ = z;
}

void renderInfo::changeFrame(int frameIndex, int startOffsetLeft)
{
    leftOffset_ = startOffsetLeft + frameIndex*frameWidth_;
}

void renderInfo::scale(float coefLeft, float coefTop)
{
    destWidth_ = float(destWidth_)*coefLeft;
    destHeight_= float(destHeight_)*coefTop;
}

QRectF renderInfo::toRect()
{
    return QRectF(leftDest_, topDest_,destWidth_,destHeight_);
}

QRectF renderInfo::sourceRect()
{
    return QRectF(leftOffset_,topOffset_,frameWidth_,frameHeight_);
}


void Sprite::setAnimation(QString name)
{
    int animationID = 0;
    foreach (const AnimationDescriptor& animation, animations)
    {
        if (animation.name == name)
        {
            currentAnimation = animationID;
            break;
        }
        animationID++;
    }
}

void Sprite::setAnimation(int id)
{
    if (id < animations.count())
        currentAnimation = id;
}

QString Sprite::getCurrentAnimationName()
{
    return animations.at(currentAnimation).name;
}

int Sprite::getCurrentAnimationID()
{
    return currentAnimation;
}

int Sprite::getAnimationID(QString name)
{
    int animationID = 0;
    foreach (const AnimationDescriptor& animation, animations)
    {
        if (animation.name == name)
            return animationID;
        animationID++;
    }
    return -1;
}

bool Sprite::isLastFrameInAnimation()
{
    return currentFrame == animations.at(currentAnimation).lastFrame;
}

void Sprite::addAnimation(QString name, int firstFrame, int lastFrame, int frameRate)
{
    AnimationDescriptor ad;
    ad.animationTime = frameRate;
    ad.firstFrame = firstFrame;
    ad.lastFrame = lastFrame;
    ad.name = name;
    animations.append(ad);
}

void Sprite::setScrollable(bool isScrollable)
{
    lastFrame.isScrollable = isScrollable
}

bool Sprite::update()
{
    if (isPaused)
        return false;
    if (!isTimerStarted)
    {
        timer.restart();
        isTimerStarted = true;
        return false;
    }
    if (timer.hasExpired(animations.at(currentAnimation).animationTime))
    {
        nextFrame();
        timer.restart();
        updated = true;
        return true;
    }
    updated = false;
    return false;
}

Sprite::~Sprite()
{

}

renderInfo Sprite::render()
{
    return lastFrame;
}

QRectF Sprite::getRect()
{
    return QRectF(left,top,float(frameWidth)*scaleCoef,float(frameHeight)*scaleCoef);
}

void Sprite::setPosition(float left_, float top_, float z_)
{
    left = left_;
    top = top_;
    z = z_;

    lastFrame.leftDest_ = left;
    lastFrame.topDest_ = top;
    lastFrame.zIndex_ = z;
}

void Sprite::move(float x, float y, float z_)
{
    left+=x;
    top+=y;
    z = z_;
    lastFrame.translate(x,y,z_);

}

void Sprite::scaleTranslate(float xMult, float yMult)
{
    lastFrame.scale(xMult,yMult);
}

bool Sprite::isSpriteCollision(Sprite *s)
{
    return getRect().intersects(s->getRect());
}

bool Sprite::isCursorCollision(int curX, int curY)
{
    return getRect().contains(curX,curY);
}

void Sprite::nextFrame()
{
    int animationFirstFrame = animations.at(currentAnimation).firstFrame;
    int animationLastFrame  = animations.at(currentAnimation).lastFrame;
    currentFrame++;
    if ((currentFrame < animationFirstFrame) || (currentFrame > animationLastFrame))
        currentFrame = animationFirstFrame;
    lastFrame.changeFrame(currentFrame, texOffsetLeft);
}
void Sprite::prevFrame()
{
    int animationFirstFrame = animations.at(currentAnimation).firstFrame;
    int animationLastFrame  = animations.at(currentAnimation).lastFrame;
    currentFrame--;
    if ((currentFrame < animationFirstFrame) || (currentFrame > animationLastFrame))
        currentFrame = animationFirstFrame;
    lastFrame.changeFrame(currentFrame, texOffsetLeft);
}


void SpriteFabric::scanSprites(QString filename)
{
    Defines d;
    d.Load(filename);
    QStringList spriteNames = d.GetList(".");
    if (spriteNames.isEmpty())
        return;
    foreach (const QString& str, spriteNames)
    {
        QStringList spriteDescList = d.GetList(str);
        if (spriteDescList.isEmpty())
            continue;
        for (QStringList::iterator i = spriteDescList.begin(); i!=spriteDescList.end(); ++i)
        {
            (*i) = (*i).simplified();
        }
        descriptors[str] = spriteDescList.join("\r\n");
    }
}

void SpriteFabric::preload(QString filename)
{
    Defines d(filename);
    QStringList spriteNames = d.GetList(".preload");
    foreach (const QString& str, spriteNames)
        newSprite(str);
}

QImage *SpriteFabric::getSpriteFrames(QString type)
{
    if (!frameCache.contains(type))
    {
        bool attach = type.indexOf(":") == 0;
        frameCache[type] = buildFramesByDesc(descriptors[type], attach);
    }
    return frameCache[type];
}


Sprite* SpriteFabric::newSprite(QString type)
{
    QStringList spriteTokens = type.split("+");

    if (!frameCache.contains(type))
    {
        QImage * context = 0;
        foreach (const QString& str, spriteTokens)
        {
            if (context == 0)
            {
                if (spriteTokens.count() != 1)
                    context = copyImage(getSpriteFrames(str));
                else
                    context = getSpriteFrames(str);
            }
            else
                drawImageOnImage(context, getSpriteFrames(str),QPoint(0,0));
        }
        frameCache[type] = context;
    }
    return new Sprite(descriptors[spriteTokens.first()],type);
}

QImage *SpriteFabric::buildFramesByDesc(QString desc, bool attach)
{

    SpriteDescriptionParser pt;
    QStringList descStrings = desc.split("\r\n");
    pt.parse(descStrings);

    QImage *context = createTransparentImage(":/data/fx/textures/"+pt.texture,pt.trColor);
    if (attach)
        foreach (const QString& att, pt.attachments)
        {
            QImage * attImage;
            if (frameCache.contains(att))
                attImage = frameCache[att];
            else
            {
                attImage = buildFramesByDesc(descriptors[att], (att.at(0) != ':'));
                frameCache[att] = attImage;
            }
            drawImageOnImage(context,attImage,
                             QPoint(pt.get("attachment."+att).at(0).toInt(),
                                    pt.get("attachment."+att).at(1).toInt()));
        }
    return context;
}
SpriteFabric* SpriteFabric::instance = 0;
