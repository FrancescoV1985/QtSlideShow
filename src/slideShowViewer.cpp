
#include "slideShowViewer.h"



SlideShowViewer::SlideShowViewer(QWidget *parent)
{
    slideShowDelegate.reset(new SlideShowDelegate(QSharedPointer<SlideShowView>(new SlideShowView(parent)), parent));

    qDebug() << "main thread " << QThread::currentThreadId();

}



