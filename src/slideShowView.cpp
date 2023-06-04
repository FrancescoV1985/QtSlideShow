
#include "slideShowView.h"



SlideShowView::SlideShowView(QWidget *parent)
    : QMainWindow(parent), imageLabel(new QLabel), startButton(new QPushButton),
      selectButton(new QPushButton(tr("QFileDialog::getExistingDirectory()"))), mirrorModeComboBox(new QComboBox),
      directoryLabel(new QLabel), scrollArea(new QScrollArea), gridLayout(new QGridLayout()), widget(new QWidget())


{
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);
    imageLabel->resize(1024, 768);//TBD: remove hard-coded values
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    scrollArea->setVisible(true);

    startButton->setText("Start"); //TBD: remove hard-coded strings, use state machine instead?
    startButton->setProperty("state", "start");

    connect(startButton, &QAbstractButton::clicked, this, [&] //notice: with C++23 we can omit ()
    {
        qDebug() << Q_FUNC_INFO << "called, thread id " << QThread::currentThreadId();

        if (startButton->property("state") == "start")
        {
            startButton->setProperty("state", "stop");
            startButton->setText("Stop");
            emit startClicked();
        }
        else
        {
            startButton->setText("Start");
            startButton->setProperty("state", "start");
            emit stopClicked();
        }
    });

    selectButton->setText("Define Image folder...");


    mirrorModeComboBox->addItems({"Mirror Mode", "None", "Vertical", "Horizontal", "Both"});

    if (auto * model = qobject_cast<QStandardItemModel*>(mirrorModeComboBox->model()); nullptr != model)
    {
       auto *item = model->item(0);
       item->setEnabled(false);
    }




    gridLayout->addWidget(startButton, 0, 0, 1, 1);

    gridLayout->addWidget(mirrorModeComboBox, 1, 0, 1, 1);

    gridLayout->addWidget(selectButton, 2, 0, 1, 1);
    gridLayout->addWidget(directoryLabel, 3, 0, 1, 1);

    gridLayout->addWidget(scrollArea, 4, 0, 1, 1);

    widget->setLayout(gridLayout);
    setCentralWidget(widget);

}

