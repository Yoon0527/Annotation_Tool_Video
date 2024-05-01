#include "Annotation_Tool_Video.h"

#include <QFileDialog>
#include <QVideoWidget>

Annotation_Tool_Video::Annotation_Tool_Video(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    init_ui();
    connect(ui.btn_load, SIGNAL(clicked()), this, SLOT(load_video()));
}

Annotation_Tool_Video::~Annotation_Tool_Video()
{}

void Annotation_Tool_Video::load_video() {
    QFileDialog dlg;

    file_list = dlg.getOpenFileNames(this, "Load Media", "", "Media Files (*.mp4 *.avi *.mkv)");

    play_media(file_list[0]);

}

void Annotation_Tool_Video::init_ui() {
    QVideoWidget* videoWidget = new QVideoWidget(ui.centralWidget);
    videoWidget->setObjectName("videoWidget");
    QSizePolicy sizePolicy2(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(videoWidget->sizePolicy().hasHeightForWidth());
    videoWidget->setSizePolicy(sizePolicy2);
    ui.horizontalLayout->addWidget(videoWidget);
}

void Annotation_Tool_Video::play_media(const QString &path) {
    QMediaPlayer* player = new QMediaPlayer(this);

    //mediaPlayer->setSource(QUrl::fromLocalFile(path));
    //mediaPlayer->setVideoOutput(ui.lbl_video);
    //ui.lbl_video->show();
    //mediaPlayer->play();
    //isPlaying = true;
    QVideoWidget* videoWidget = new QVideoWidget(ui.centralWidget);
    videoWidget->setObjectName("videoWidget");
    QSizePolicy sizePolicy2(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(videoWidget->sizePolicy().hasHeightForWidth());
    videoWidget->setSizePolicy(sizePolicy2);
    ui.horizontalLayout->addWidget(videoWidget);

    player->setSource(QUrl::fromLocalFile(path));
    player->setVideoOutput(videoWidget);
    

    player->play();
    isPlaying = true;
}