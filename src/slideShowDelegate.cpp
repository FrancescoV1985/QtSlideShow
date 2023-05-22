
#include "slideShowDelegate.h"



SlideShowDelegate::SlideShowDelegate(QWidget *parent)
    :  updateTimeinMs(2000), worker(nullptr), slideShowView(new SlideShowView(parent))
{

    QPushButton& startButton = slideShowView->getStartButton();
    QPushButton& selectButton = slideShowView->getDirSelectButton();
    QComboBox& mirrorModeComboBox = slideShowView->getMirrorModeComboBox();
    QLabel& directoryLabel = slideShowView->getDirectoryLabel();

    auto lambdaWorkLoad = [&](const QString name, ImageMirroring mode) -> bool { return this->loadFile(name, mode); };


    connect(slideShowView.get(), &SlideShowView::startClicked, this, [&]()
    {
        emit notifyStart();
    });

    connect(slideShowView.get(), &SlideShowView::stopClicked, this, [&]()
    {
        emit notifyStop();
    });


    workerFuture = QtConcurrent::run([&]()
    {
        QEventLoop loop;

        worker.reset(new SlideShowWorker(lambdaWorkLoad, updateTimeinMs));
        auto slideShowWorker = qobject_cast<SlideShowWorker*>(worker.get());

        connect(slideShowWorker, &SlideShowWorker::notifyImageReady, this, &SlideShowDelegate::setImage);

        connect(slideShowWorker, &SlideShowWorker::notifyDirProcessed, this, [&]()
        {
            startButton.setText("Start");
            startButton.setProperty("state", "start");
        });

        connect(this, &SlideShowDelegate::notifyWorkDone, slideShowWorker, &Worker::quit);

        connect(this, &SlideShowDelegate::notifyStart, slideShowWorker, &Worker::start);
        connect(this, &SlideShowDelegate::notifyStop, slideShowWorker, &Worker::stop);

        connect(this, &SlideShowDelegate::notifyDirectoryChanged, slideShowWorker, &SlideShowWorker::setDirectory);
        connect(this, &SlideShowDelegate::notifyMirrorModeChanged, slideShowWorker, &SlideShowWorker::mirrorCurrentImage);

        loop.exec();
    });


    connect(&selectButton, &QAbstractButton::clicked, this, &SlideShowDelegate::setExistingDirectory);

    connect(&mirrorModeComboBox, &QComboBox::currentIndexChanged, this, &SlideShowDelegate::setMirroringMode);

    slideShowView->show();

}


SlideShowDelegate::~SlideShowDelegate()
{
    emit notifyWorkDone();
    workerFuture.waitForFinished();
}


void SlideShowDelegate::setMirroringMode(int index)
{
    qDebug() << Q_FUNC_INFO << "called, thread id " << QThread::currentThreadId();

    ImageMirroring val = static_cast<ImageMirroring>(index-1);
    emit notifyMirrorModeChanged(val);
}


void SlideShowDelegate::setExistingDirectory()
{
    qDebug() << Q_FUNC_INFO << "called, thread id " << QThread::currentThreadId();

    QFileDialog::Options options;
    options |= QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
    const QString& directory = QFileDialog::getExistingDirectory(slideShowView.get(),
                                                                 tr("Please select a folder"),
                                                                 slideShowView->getDirectoryLabel().text(),
                                                                 options);

    emit notifyDirectoryChanged(directory);

    slideShowView->getDirectoryLabel().setText(directory);
}


bool SlideShowDelegate::loadFile(const QString& fileName, ImageMirroring mode)
{
    qDebug() << Q_FUNC_INFO << "called, thread id " << QThread::currentThreadId();

    bool hori = (mode == ImageMirroring::both || mode == ImageMirroring::horizontal);
    bool verti = (mode == ImageMirroring::both || mode == ImageMirroring::vertical);

    QImage& image = slideShowView->getImage();


    QImageReader reader(fileName);
    reader.setAutoTransform(true);
    const QImage newImage = reader.read();

    if (newImage.isNull()) {
        QMessageBox::information(slideShowView.get(), QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1: %2")
                                 .arg(QDir::toNativeSeparators(fileName), reader.errorString()));
        return false;
    }

    image = newImage;


    image = image.mirrored(hori, verti);

    if (image.colorSpace().isValid())
        image.convertToColorSpace(QColorSpace::SRgb);

    return true;
}


void SlideShowDelegate::setImage()
{
    qDebug() << Q_FUNC_INFO << "called, thread id " << QThread::currentThreadId();

    slideShowView->getImageLabel().setPixmap(QPixmap::fromImage(slideShowView->getImage()));

    slideShowView->getScrollArea().setVisible(true);

    slideShowView->getImageLabel().adjustSize();
}




