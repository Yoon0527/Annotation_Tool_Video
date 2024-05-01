#include "Annotation_Tool_Video.h"

#include <QFileDialog>

Annotation_Tool_Video::Annotation_Tool_Video(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.btn_load, SIGNAL(clicked()), this, SLOT(load_video()));
}

Annotation_Tool_Video::~Annotation_Tool_Video()
{}

void Annotation_Tool_Video::load_video() {
    QFileDialog dlg;

    file_list = dlg.getOpenFileNames(this, "Load Media", "", "Media Files (*.mp4 *.avi *.mkv)");

    play_media(file_list[0]);

}

void Annotation_Tool_Video::play_media(const QString &path) {
    QMediaPlayer* player = new QMediaPlayer(this);

    //mediaPlayer->setSource(QUrl::fromLocalFile(path));
    //mediaPlayer->setVideoOutput(ui.lbl_video);
    //ui.lbl_video->show();
    //mediaPlayer->play();
    //isPlaying = true;

    ui.lbl_video->show();
    player->setSource(QUrl::fromLocalFile(path));
    player->setVideoOutput(ui.lbl_video);
    

    player->play();
    isPlaying = true;
}