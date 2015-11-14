#ifndef SIMPLEPLAYER_H
#define SIMPLEPLAYER_H

#include <QObject>
#include <inputcomponent.h>
#include <rendermanager.h>

class SimplePlayer : public InputComponent
{
    Q_OBJECT
public:
    explicit SimplePlayer(RenderManager * m);
    ~SimplePlayer();

signals:

public slots:
    virtual void keyPressed(int key);
    virtual void keyReleased(int key);
    virtual bool update();
private:
    Sprite * s;
    RenderManager * rm;
    bool movingEnabled;
    bool upPressed, leftPressed, rightPressed, downPressed, spacePressed;
};

#endif // SIMPLEPLAYER_H
