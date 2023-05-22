#ifndef SLIDESHOWVIEWER_H
#define SLIDESHOWVIEWER_H


#include "slideShowView.h"
#include "slideShowDelegate.h"


class SlideShowViewer : public QObject
{
    Q_OBJECT

public:

    SlideShowViewer(QWidget *parent = nullptr);


private:
    QScopedPointer<SlideShowView> slideShowView;

    QScopedPointer<SlideShowDelegate> slideShowDelegate;

};


#endif // SLIDESHOWVIEWER_H
