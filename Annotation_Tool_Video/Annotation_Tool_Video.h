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

    QStringList file_list;

    void play_media(const QString& path);
    bool eventFilter(QObject* obj, QEvent* event) override;

private slots:
    void load_video();

protected:
    

//signals:
//    void spacePressed();

};
