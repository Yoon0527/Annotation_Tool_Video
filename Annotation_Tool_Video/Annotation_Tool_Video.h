#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Annotation_Tool_Video.h"
#include <QMediaPlayer>

class Annotation_Tool_Video : public QMainWindow
{
    Q_OBJECT

public:
    Annotation_Tool_Video(QWidget *parent = nullptr);
    ~Annotation_Tool_Video();

private:
    Ui::Annotation_Tool_VideoClass ui;
    QMediaPlayer* mediaPlayer;
    bool isPlaying = false;

    QStringList file_list;

    void play_media(const QString& path);


private slots:
    void load_video();
};
