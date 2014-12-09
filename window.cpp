#include "window.h"
Window::Window()
{
    setWindowTitle(tr("2D Painting on Native and OpenGL Widgets"));

    QRect screenRect = QApplication::desktop()->screenGeometry();
    rm = new RenderManager(this, screenRect.width(), screenRect.height());
    rm->init();
    rm->showFullScreen();
    rm->move(0,0);


    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), rm, SLOT(render()));
    timer->start(5);
}
Window::~Window()
{

}

void Window::messageCycle()
{
    ;
}

