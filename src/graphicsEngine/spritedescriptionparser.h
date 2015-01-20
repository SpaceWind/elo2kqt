#ifndef SPRITEDESCRIPTIONPARSER_H
#define SPRITEDESCRIPTIONPARSER_H

#include <paramparser.h>
#include "sprite.h"

struct AnimationDescriptor;
class SpriteDescriptionParser : public paramParser
{
public:
    SpriteDescriptionParser(){;}
    SpriteDescriptionParser(QStringList list);
    virtual ~SpriteDescriptionParser();

    QList<AnimationDescriptor> getAnimations() {return animations;}
    virtual void parse(QStringList list);


    QList<AnimationDescriptor> animations;
    QString texture;
    QStringList attachments;
    int texOffsetLeft, texOffsetTop, frameWidth, frameHeight, trColor;
};
#endif // SPRITEDESCRIPTIONPARSER_H
