
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
    workLoadMethod(work), processingState(false), mirrorMode(ImageMirroring::none), mirrorModeHasChanged(false)
{

}


void SlideShowWorker::timeout()
{

    qDebug() << Q_FUNC_INFO << "called, thread id " << QThread::currentThreadId();


    static auto getNextImage = [&]()
    {
       return index >= images.size() ? std::nullopt : std::optional<const std::reference_wrapper<QString>>(images[index++]);

    };

    static auto getLastImage = [&]()
    {
       return index <= 0 || index > images.size() ? std::nullopt : std::optional<const std::reference_wrapper<QString>>(images[index-1]);

    };

    if (processingState)
    {

        if (!directory.isEmpty())
        {
            auto imageRef = getNextImage();

            if (imageRef != std::nullopt)
            {
                const QString& filename = imageRef->get();
                workLoadMethod(directoryName + "/" + filename, mirrorMode);
                if (workLoadMethod(directoryName + "/" + filename, mirrorMode))
                {
                    emit notifyImageReady(filename);
                }
            }
            else
            {
                emit notifyDirProcessed();
                processingState = false;
            }
        }
    }
    else if (mirrorModeHasChanged)
    {
        mirrorModeHasChanged = false;

        auto imageRef = getLastImage();

        if (imageRef != std::nullopt)
        {
            const QString& filename = imageRef->get();

            if (workLoadMethod(directoryName + "/" + filename, mirrorMode))
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
    processingState = true;
}


void SlideShowWorker::stop()
{
    processingState = false;
}
