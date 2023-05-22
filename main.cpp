#include <QApplication>

#include "slideShowViewer.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QGuiApplication::setApplicationDisplayName(SlideShowViewer::tr("Slide Show Viewer"));

    SlideShowViewer slideShowViewer;


    return app.exec();
}
