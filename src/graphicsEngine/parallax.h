#ifndef LINEARINTERPOLATOR_H
#define LINEARINTERPOLATOR_H
#include <QVector>
#include <QHash>
#include <QStringList>
#include <QPointF>
#include <QList>
#include <defines.h>
#include "spritedescriptionparser.h"


class parallaxConfig
{
public:
    parallaxConfig(){;}
    parallaxConfig(QString filename, QString listName);
    parallaxConfig(QStringList text);
    ~parallaxConfig(){;}
    void parse(QStringList text);
    void parse(QString filename, QString listName);
    float interpolate(QString group, float Z);
private:

    QList<QPointF> getPointsFromParser(paramParser &pp, QString pointGroup);
    QVector<QPointF> sortPoints(QList<QPointF> points);

    QHash<QString, QVector<QPointF> > points;
};

#endif // LINEARINTERPOLATOR_H
