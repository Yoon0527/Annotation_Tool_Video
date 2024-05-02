#include "Annotation_Tool_Video.h"

#include <QFileDialog>
#include <QVideoWidget>

Annotation_Tool_Video::Annotation_Tool_Video(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    //init_ui();
    connect(ui.btn_load, SIGNAL(clicked()), this, SLOT(load_video()));
}

Annotation_Tool_Video::~Annotation_Tool_Video()
{}

void Annotation_Tool_Video::load_video() {
    QFileDialog dlg;

    file_list = dlg.getOpenFileNames(this, "Load Media", "", "Media Files (*.mp4 *.avi *.mkv)");

    play_media(file_list[0]);

}


void Annotation_Tool_Video::play_media(const QString& path) {
    // 기존의 비디오 위젯과 플레이어를 멤버 변수로 이동시킵니다.
    QVideoWidget* videoWidget = new QVideoWidget();
    QMediaPlayer* player = new QMediaPlayer(this);

    // 레이아웃 매니저를 사용하여 비디오 위젯의 크기를 부모 위젯에 맞춥니다.
    QVBoxLayout* layout = new QVBoxLayout(ui.groupBox_video);
    layout->addWidget(videoWidget);

    // 비디오를 재생하기 전에 비디오 소스를 설정하고 재생합니다.
    player->setSource(QUrl::fromLocalFile(path));
    player->setVideoOutput(videoWidget);
    player->play();
}
