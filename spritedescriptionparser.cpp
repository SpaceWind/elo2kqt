#include "spritedescriptionparser.h"

SpriteDescriptionParser::SpriteDescriptionParser(QStringList list) :
    paramParser (list)
{
    texture = "";
    texOffsetLeft = texOffsetTop = frameWidth = frameHeight = trColor = 0;
    parse(list);
}

SpriteDescriptionParser::~SpriteDescriptionParser()
{

}

void SpriteDescriptionParser::parse(QStringList list)
{
    paramParser::parse(list);
    texture = get(":texture").first();
    texOffsetLeft = get(":textureOffset").at(0).toInt();
    texOffsetTop  = get(":textureOffset").at(1).toInt();
    frameWidth    = get(":frameSize").at(0).toInt();
    frameHeight   = get(":frameSize").at(1).toInt();
    QStringList trColorList = get(":transparentColor");
    trColor = qRgb(trColorList.at(0).toInt(),
                   trColorList.at(1).toInt(),
                   trColorList.at(2).toInt());
    QStringList animations = get("animation");
    foreach (const QString &name, animations)
    {
        AnimationDescriptor ad;
        ad.name = name;
        QStringList adParams = get("animation."+name);
        ad.firstFrame = adParams.at(0).toInt();
        ad.lastFrame = adParams.at(1).toInt();
        ad.animationTime = adParams.at(2).toInt();
        this->animations.append(ad);
    }
    attachments = get("attachment");
}
