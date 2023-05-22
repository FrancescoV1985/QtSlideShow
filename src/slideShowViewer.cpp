
#include "slideShowViewer.h"



SlideShowViewer::SlideShowViewer(QWidget *parent)
{

    slideShowDelegate.reset(new SlideShowDelegate(parent));


    qDebug() << "main thread " << QThread::currentThreadId();

}



