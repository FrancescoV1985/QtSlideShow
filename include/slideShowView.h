#ifndef SLIDESHOWVIEW_H
#define SLIDESHOWVIEW_H


#include <QtWidgets>
#include <QMainWindow>
#include <QImage>

#include <QColorSpace>
#include <QDir>
#include <QImageReader>
#include <QMessageBox>
#include <QMimeData>
#include <QScreen>
#include <QStandardPaths>


#include "commonDef.h"


class SlideShowView : public QMainWindow
{
    Q_OBJECT

public:

    SlideShowView(QWidget *parent = nullptr);


private:



signals:
    void startClicked();
    void stopClicked();

public:

    QImage& getImage() { return image; }
    QLabel& getImageLabel() { return *imageLabel; }
    QPushButton& getStartButton() { return *startButton; }
    QPushButton& getDirSelectButton() { return *selectButton; }
    QComboBox& getMirrorModeComboBox() {return *mirrorModeComboBox; }
    QLabel& getDirectoryLabel() { return *directoryLabel; }
    QScrollArea& getScrollArea() {return *scrollArea;}

private:

    QImage image;
    QLabel *imageLabel;
    QPushButton *startButton;
    QPushButton *selectButton;
    QComboBox *mirrorModeComboBox;
    QLabel *directoryLabel;
    QScrollArea *scrollArea;
    QWidget* widget;
    QGridLayout* gridLayout;
};

#endif // SLIDESHOWVIEW_H
