#ifndef SLIDESHOWDELEGATE_H
#define SLIDESHOWDELEGATE_H

#include <QFuture>
#include <QtConcurrent>

#include "slideShowView.h"

#include "slideShowWorker.h"



class SlideShowDelegate : public QObject
{
    Q_OBJECT

public:

    SlideShowDelegate(QWidget *parent = nullptr);

    ~SlideShowDelegate();

    // loads a file with name "fileName" from file system and applies the mirroring specified by "mode"
    bool loadFile(const QString &fileName, ImageMirroring mode);
    void setMirroringMode(int);


private:

signals:

    void notifyDirectoryChanged(const QString&);
    void notifyStart();
    void notifyStop();
    void notifyWorkDone();
    void notifyMirrorModeChanged(ImageMirroring);


private slots:

    void setExistingDirectory();
    void setImage();


private:


    unsigned int updateTimeinMs;
    QScopedPointer<Worker> worker;
    QScopedPointer<SlideShowView> slideShowView;
    QFuture<void> workerFuture;
};


#endif // SLIDESHOWDELEGATE_H
