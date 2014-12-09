#ifndef SPRITE_H
#define SPRITE_H

#include <QObject>
#include <QHash>
#include <QList>
#include <QStringList>
#include <QElapsedTimer>
#include <QRectF>
#include <QImage>
#include <defines.h>
#include "spritedescriptionparser.h"
#include "helpers.h"

#define MIN_Z       -1024




struct renderInfo
{
    renderInfo(QString spriteType,
               float left, float top, int frameWidth, int frameHeight,
               int zIndex=0, int leftOffset = 0, int topOffset = 0,
               int destWidth = -1, int destHeight = -1, float rotate = 0);
    renderInfo();
    ~renderInfo(){;}
    void translate(float x, float y, float z=0.f);
    void changeFrame(int frameIndex, int startOffsetLeft = 0);
    void scale(float coefLeft, float coefTop);
    bool operator<(const renderInfo& other) const {
            return zIndex_ < other.zIndex_;
        }
    QRectF toRect();
    QRectF sourceRect();


    QString spriteType_;     //sprite type for sprite Fabric
    float leftDest_;         //draw LEFT position
    float topDest_;          //draw TOP position
    int frameWidth_;         //sprite frame WIDTH
    int frameHeight_;        //sprite frame HEIGHT
    int zIndex_;             //zIndex deep; //more ZIndex - closer to Viewer
    int leftOffset_;         //pixels from FRAME left
    int topOffset_;          //pixels from FRAME top

    int destWidth_;          //mean scaling on draw item; if == -1 then set by widthFrame
    int destHeight_;         //--same
    float rotate_;           //rotate painter before drawing. It undo rotating after drawing item;
    bool isScrollable;
};
/*
bool operator<(const renderInfo* first, const renderInfo* second) const
{
    return first->zIndex_ < second->zIndex_;
}*/

class SpriteFabric;
class Renderable
{
public:
    virtual renderInfo render()=0;
    virtual bool update()=0;
};
struct AnimationDescriptor
{
        AnimationDescriptor()
        {
                name="";
                firstFrame=lastFrame=0;
                animationTime=50;
        }
        AnimationDescriptor(const AnimationDescriptor & c)
        {
                name=c.name;
                firstFrame=c.firstFrame;
                lastFrame = c.lastFrame;
                animationTime = c.animationTime;
        }
        AnimationDescriptor(QString _name, uint ff, uint lf, uint t)
        {
                name = _name;
                firstFrame = ff;
                lastFrame = lf;
                animationTime = t;
        }
        ~AnimationDescriptor(){;}
        QString name;
        int firstFrame;
        int lastFrame;
        int animationTime;
};

class Sprite : public QObject, public Renderable
{
    Q_OBJECT
    friend class SpriteFabric;
public: 
    virtual renderInfo render();
    virtual bool update();
    virtual ~Sprite();

    void setAnimation(QString name);
    void setAnimation(int id);
    QString getCurrentAnimationName();
    int getCurrentAnimationID();
    int getAnimationID(QString name);
    bool isLastFrameInAnimation();
    void addAnimation(QString name, int firstFrame, int lastFrame, int frameRate);

    void setScrollable(bool isScrollable);

    QRectF getRect();
    renderInfo* getFrame(){return &lastFrame;}

    void setPosition(float left, float top, float z=MIN_Z);

    void move(float x, float y, float z_=0.);
    void scaleTranslate(float xMult, float yMult);
    bool isSpriteCollision(Sprite * s);
    bool isCursorCollision(int curX, int curY);

    void pause() {isPaused = !(isTimerStarted = false);}
    void unpause() {isPaused = false;}


signals:

public slots:

protected:
    QString type;
    int currentAnimation;
    int animationCount;
    int currentFrame;
    uint lastTimeUpdated;
    int frameCount;
    int frameWidth, frameHeight;
    float scaleCoef;
    int z;
    float left, top;
    int texOffsetLeft, texOffsetTop;

    renderInfo lastFrame;
    QList<AnimationDescriptor> animations;
    QElapsedTimer timer;

private:
    Sprite();
    Sprite(QString descriptor, QString imageName);
    void genFirstFrame();

    void nextFrame();
    void prevFrame();
    bool isPaused;
    bool isTimerStarted;
    bool updated;

};


class SpriteFabric
{
public:
    void scanSprites(QString filename);
    void preload(QString filename);
    QImage* getSpriteFrames(QString type);
    Sprite* newSprite(QString type);
    static SpriteFabric* getInstance(){if (!instance) return instance=new SpriteFabric(); else return instance;}
    ~SpriteFabric(){;}
private:
    SpriteFabric(){;}
    QImage* buildFramesByDesc(QString desc, bool attach = true);
    QHash<QString, QString> descriptors;
    QHash<QString, QImage*> frameCache;
    static SpriteFabric* instance;
};

#endif // SPRITE_H
