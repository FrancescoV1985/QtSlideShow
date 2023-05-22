
#include <QtWidgets>
#include "commonDef.h"
#include "slideShowWorker.h"


Worker::Worker(unsigned int delayInMs) : delayInMs(delayInMs)
{
    connect(&timer, SIGNAL(timeout()), SLOT(timeout()));

    timer.start(delayInMs);
}


void Worker::quit()
{
    qDebug() << Q_FUNC_INFO << "called, thread id " << QThread::currentThreadId();

    timer.stop();
    QThread::currentThread()->exit();
}


SlideShowWorker::SlideShowWorker(std::function<bool(const QString, ImageMirroring)>work, unsigned int delayInMs) : Worker(delayInMs),
    workLoadMethod(work), state(false), mirrorMode(ImageMirroring::none), mirrorModeHasChanged(false)
{

}


void SlideShowWorker::timeout()
{

    qDebug() << Q_FUNC_INFO << "called, thread id " << QThread::currentThreadId();

    if (state)
    {

        if (!directory.isEmpty())
        {
            if (index < images.size())
            {
                const QString& filename = images[index];
                bool rv = workLoadMethod(directoryName + "/" + filename, mirrorMode);
                index++;
                if (rv)
                {
                    emit notifyImageReady(filename);
                }
            }
            else
            {
                emit notifyDirProcessed();
                state = false;
            }
        }
    }
    else if (mirrorModeHasChanged)
    {
        mirrorModeHasChanged = false;
        if (index > 0 && index <= images.size())
        {
            const QString& filename = images[index-1];

            bool rv = workLoadMethod(directoryName + "/" + filename, mirrorMode);

            if (rv)
            {
                emit notifyImageReady(filename);
            }
        }
    }
}


void SlideShowWorker::setDirectory(const QString& dirName)
{
    qDebug() << Q_FUNC_INFO << "called, thread id " << QThread::currentThreadId();

    directoryName = dirName;
    directory.setPath(directoryName);
    images = directory.entryList(QStringList() << "*.jpg" << "*.tiff" << "*.bmp", QDir::Files);
    index = 0;
}


void SlideShowWorker::mirrorCurrentImage(ImageMirroring mode)
{
    qDebug() << Q_FUNC_INFO << "called, thread id " << QThread::currentThreadId();

    mirrorModeHasChanged = true;
    mirrorMode = mode;
}


void SlideShowWorker::start()
{
    qDebug() << Q_FUNC_INFO << "called, thread id " << QThread::currentThreadId();

    index = 0;
    state = true;
}


void SlideShowWorker::stop()
{
    state = false;
}
