#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Annotation_Tool_Video.h"
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QKeyEvent>

using namespace std;

class Annotation_Tool_Video : public QMainWindow
{
    Q_OBJECT

public:
    Annotation_Tool_Video(QWidget *parent = nullptr);
    ~Annotation_Tool_Video();

    QVideoWidget* videoWidget = new QVideoWidget();
    QMediaPlayer* player = new QMediaPlayer(this);

    void init_ui();

private:
    Ui::Annotation_Tool_VideoClass ui;
    QMediaPlayer* mediaPlayer;
    bool isPlaying = false;
    qint64 mDuration;

    QStringList file_list;
    QStringList file_name_list;

    void play_media(const QString& path);
    void updateDuration(qint64 duration);

private slots:
    void load_video();
    void change_status();
    void click_skip();
    void click_skip_before();
    void durationChanged(qint64 duration);
    void positionChanged(qint64 duration);

protected:
    

//signals:
//    void spacePressed();

};
