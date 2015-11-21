#ifndef SIMPLEPLAYER_H
#define SIMPLEPLAYER_H

#include <QObject>
#include <inputcomponent.h>
#include <rendermanager.h>
#include <simpleplayerinputcomponent.h>
#include <simpleplayermouseinputcomponent.h>

class SimplePlayer : public QObject
{
    Q_OBJECT
public:
    explicit SimplePlayer(RenderManager * m);
    ~SimplePlayer();

    SimplePlayerInputComponent * keyComponent;
    simplePlayerMouseInputComponent * mouseComponent;

signals:

public slots:
    virtual bool update(uint delta);
private:
    Sprite * s;
    RenderManager * rm;
    bool movingEnabled;
    bool getAim;
    float xAim, yAim;
};

#endif // SIMPLEPLAYER_H
