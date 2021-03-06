#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QtOpenGL>
#include <QElapsedTimer>
#include <rendermanager.h>
#include "inputsystem.h"
#include "simpleplayer.h"

class RenderManager;
class Window : public QWidget
{
    Q_OBJECT

public:
    Window();
    ~Window();

public slots:
    void messageCycle();

protected:
//    void paintEvent(QPaintEvent *event);

private:
    RenderManager * rm;
    int elapsed;
    InputSystem inputSystem;
    SimplePlayer *sp;
    QElapsedTimer * elapsedTimer;

};

#endif // WINDOW_H
