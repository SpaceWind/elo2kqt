#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QtOpenGL>
#include <rendermanager.h>

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
};

#endif // WINDOW_H
