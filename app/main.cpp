#include <window.h>
#include <QApplication>
#include <defines.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Window w;
    w.showFullScreen();

    return a.exec();
}
