#include "parallax.h"



parallaxConfig::parallaxConfig(QString filename, QString listName)
{
    parse(filename,listName);
}

parallaxConfig::parallaxConfig(QStringList text)
{
    parse(text);
}

void parallaxConfig::parse(QStringList text)
{
    paramParser pp(text);
    QList<QPointF> movePoints = getPointsFromParser(pp,"movePoints");
    QList<QPointF> scalePoints = getPointsFromParser(pp, "scalePoints");
    points["movePoints"] = sortPoints(movePoints);
    points["scalePoints"] = sortPoints(scalePoints);
}

void parallaxConfig::parse(QString filename, QString listName)
{
    Defines d(filename);
    QStringList text = d.GetList(listName);
    if (!text.empty())
        parse(text);
}

float parallaxConfig::interpolate(QString group, float Z)
{
    QVector<QPointF> gPoints = points[group];
    if (Z <= gPoints[0].x())
        return gPoints[0].y();
    if (Z >= gPoints.last().x())
        return gPoints.last().y();
    for (int i=0; i< gPoints.count()-1; ++i)
    {
        float currentPointValue = gPoints[i].x();
        float nextPointValue = gPoints[i+1].x();
        if (Z >= currentPointValue && Z < nextPointValue)
            return ((Z-currentPointValue)/(nextPointValue - currentPointValue)
                    *
                   (gPoints[i+1].y() - gPoints[i].y()))
                    +
                    gPoints[i].y();
    }
    return 0.f;
}

QList<QPointF> parallaxConfig::getPointsFromParser(paramParser &pp, QString pointGroup)
{
    QList<QPointF> list;
    int i=0;
    while (true)
    {
        QStringList result = pp.get(pointGroup+"["+QString::number(i)+"]");
        if (result.empty())
            break;
        else
        {
            QPointF p(result.at(0).toFloat(), result.at(1).toFloat()/1024.f);
            list.append(p);
        }
        i++;
    }
    return list;
}

QVector<QPointF> parallaxConfig::sortPoints(QList<QPointF> points)
{
    QVector<QPointF> result;
    while (!points.empty())
    {
        int min_index = 0;
        float min_value = points.at(0).x();
        int current_index = 0;
        foreach (const QPointF& point, points)
        {
            if (point.x() < min_value)
            {
                min_index = current_index;
                min_value = point.x();
            }
            current_index++;
        }
        result.append(points.at(min_index));
        points.removeAt(min_index);
    }
    return result;
}
