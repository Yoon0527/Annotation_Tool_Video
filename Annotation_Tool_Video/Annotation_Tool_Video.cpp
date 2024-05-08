#include "Annotation_Tool_Video.h"

#include <QFileDialog>
#include <QVideoWidget>
#include <QKeyEvent>
Annotation_Tool_Video::Annotation_Tool_Video(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    init_ui();

    connect(ui.btn_load, SIGNAL(clicked()), this, SLOT(load_video()));
    connect(ui.btn_play_status, SIGNAL(clicked()), this, SLOT(change_status()));
    connect(ui.btn_skip, SIGNAL(clicked()), this, SLOT(click_skip()));
    connect(ui.btn_skip_before, SIGNAL(clicked()), this, SLOT(click_skip_before()));


}

Annotation_Tool_Video::~Annotation_Tool_Video()
{}

void Annotation_Tool_Video::init_ui() {
    QVBoxLayout* layout = new QVBoxLayout(ui.groupBox_video);
    layout->addWidget(videoWidget);
    ui.btn_play_status->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui.btn_next->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
    ui.btn_prev->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
    ui.btn_skip->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    ui.btn_skip_before->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
}

void Annotation_Tool_Video::load_video() {
    if (file_list.size() != 0) {

    }
    else {
        file_list.clear();
        ui.list_filelist->clear();

        QFileDialog dlg;

        file_list = dlg.getOpenFileNames(this, "Load Media", "", "Media Files (*.mp4 *.avi *.mkv)");



        play_media(file_list[0]);

        installEventFilter(this);
    }
}


void Annotation_Tool_Video::play_media(const QString& path) {
    videoWidget->setFocus();
    player->setSource(QUrl::fromLocalFile(path));
    player->setVideoOutput(videoWidget);
    player->play();
    ui.btn_play_status->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    isPlaying = true;

    connect(player, &QMediaPlayer::durationChanged, this, &Annotation_Tool_Video::durationChanged);
    connect(player, &QMediaPlayer::positionChanged, this, &Annotation_Tool_Video::positionChanged);

    ui.slider_duration->setRange(0, player->duration() / 1000);
}

void Annotation_Tool_Video::change_status() {
    if (isPlaying) {
        player->pause();
        ui.btn_play_status->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        isPlaying = false;
    }
    else if(!isPlaying){
        player->play();
        ui.btn_play_status->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        isPlaying = true;
    }
}

void Annotation_Tool_Video::click_skip() {
    ui.slider_duration->setValue(ui.slider_duration->value() + 10);
    player->setPosition(ui.slider_duration->value() * 1000);
}

void Annotation_Tool_Video::click_skip_before() {
    ui.slider_duration->setValue(ui.slider_duration->value() - 10);
    player->setPosition(ui.slider_duration->value() * 1000);
}

void Annotation_Tool_Video::updateDuration(qint64 duration) {
    if (duration || mDuration)
    {
        QTime CurrentTime((duration / 3600) % 60, (duration / 60) % 60, duration % 60, (duration * 1000) % 1000);
        QTime TotalTime((mDuration / 3600) % 60, (mDuration / 60) % 60, mDuration % 60, (mDuration * 1000) % 1000);
        QString Format = "";
        if (mDuration > 3600) Format = "hh:mm:ss";
        else Format = "mm:ss";

        ui.lbl_presentTime->setText(CurrentTime.toString(Format));
        ui.lbl_totalTime->setText(TotalTime.toString(Format));
    }
}

void Annotation_Tool_Video::durationChanged(qint64 duration) {
    mDuration = duration / 1000;
    ui.slider_duration->setMaximum(mDuration);
}

void Annotation_Tool_Video::positionChanged(qint64 duration) {
    if (!ui.slider_duration->isSliderDown())
    {
        ui.slider_duration->setValue(duration / 1000);
    }
    updateDuration(duration / 1000);
}