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
    // ������ ���� ������ �÷��̾ ��� ������ �̵���ŵ�ϴ�.
    QVideoWidget* videoWidget = new QVideoWidget();
    QMediaPlayer* player = new QMediaPlayer(this);

    // ���̾ƿ� �Ŵ����� ����Ͽ� ���� ������ ũ�⸦ �θ� ������ ����ϴ�.
    QVBoxLayout* layout = new QVBoxLayout(ui.groupBox_video);
    layout->addWidget(videoWidget);

    // ������ ����ϱ� ���� ���� �ҽ��� �����ϰ� ����մϴ�.
    player->setSource(QUrl::fromLocalFile(path));
    player->setVideoOutput(videoWidget);
    player->play();
}
