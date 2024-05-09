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
        QStringList file_list_tmp = file_list;
        QStringList differ_list;

        QFileDialog dlg;
        file_list = dlg.getOpenFileNames(this, "Load Media", "", "Media Files (*.mp4 *.avi *mkv)");

        for (const QString& path : file_list) {
            if (!file_list_tmp.contains(path)) {
                differ_list.append(path);
                file_list_tmp.append(path);
            }
        }

        for (int i = 0; i < differ_list.size(); i++) {
            QString fileName_pre = differ_list[i].section("/", -1);
            file_name_list.append(fileName_pre.split(".")[0]);
        }

        std::sort(file_name_list.begin(), file_name_list.end());
        ui.list_filelist->clear();
        ui.list_filelist->addItems(file_name_list);

        ui.list_log->addItem(QString(QString::number(differ_list.size()) + "additional videos have been loaded"));

        std::sort(file_list_tmp.begin(), file_list_tmp.end());

        file_list = file_list_tmp;
        file_list_len = file_list.size();
        media_count = file_list.indexOf(current_media_path);
    }
    else {
        file_list.clear();
        ui.list_filelist->clear();

        QFileDialog dlg;

        file_list = dlg.getOpenFileNames(this, "Load Media", "", "Media Files (*.mp4 *.avi *.mkv)");

        file_name_list.clear();

        for (int i = 0; i < file_list.size(); i++) {
            QString fileName_pre = file_list[i].section("/", -1);
            file_name_list.append(fileName_pre.split(".")[0]);
        }

        ui.list_filelist->addItems(file_name_list);

        file_list_len = file_list.size();
        QString file_size = QString::number(file_list_len);

        if (file_list_len > 0) {
            play_media(file_list[0]);
        }

        ui.list_log->addItem(QString(file_size + " videos Load"));


        //play_media(file_list[0]);

        installEventFilter(this);
    }
}


void Annotation_Tool_Video::play_media(const QString& path) {
    //videoWidget->setFocus();
    videoWidget->setFocusPolicy(Qt::StrongFocus);
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

        pause_position = player->position();
        ui.list_log->addItem(QString(QString::number(pause_position) + " time pause"));

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