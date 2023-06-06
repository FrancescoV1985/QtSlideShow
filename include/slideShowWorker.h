
#ifndef SLIDESHOWWORKER_H
#define SLIDESHOWWORKER_H

#include <QtWidgets>
#include "commonDef.h"


class Worker : public QObject
{
    Q_OBJECT
    QTimer timer;

public:

    Worker(unsigned int delayInMs);


protected slots:

    virtual void timeout() = 0;


public slots:

    virtual void start() = 0;

    virtual void stop() = 0;

    void quit();

private:

    unsigned int delayInMs;
};



class SlideShowWorker: public Worker
{
    Q_OBJECT


public:

    SlideShowWorker(std::function<bool(const QString, ImageMirroring)>work, unsigned int delayInMs);


signals:

    void notifyImageReady(QString name);

    void notifyDirProcessed();

private slots:

    void timeout() override;

public slots:

    void setDirectory(const QString& dirName);

    void mirrorCurrentImage(ImageMirroring mode);


    void start() override;


    void stop() override;


private:

    int index;
    QDir directory;
    QString directoryName;
    QStringList images;
    bool processingState;
    ImageMirroring mirrorMode;
    bool mirrorModeHasChanged;
    std::function<bool(const QString, ImageMirroring)> workLoadMethod;

};




#endif // SLIDESHOWWORKER_H
