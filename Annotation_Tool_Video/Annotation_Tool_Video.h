#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Annotation_Tool_Video.h"
#include <QMediaPlayer>
#include <QVideoWidget>
#include <opencv2/opencv.hpp>
#include <QKeyEvent>
#include <QTimer>
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
    cv::VideoCapture capture_;;
    bool isPlaying = false;
    QTimer timer_;
    qint64 mDuration;
    int pause_position;
    QSize videoSize;

    QStringList file_list;
    QStringList file_name_list;

    QString current_media_path;

    int file_list_len;
    int media_count = 0;
    int pause_frame;

    void play_media(const QString& path);
    void updateDuration(qint64 duration);

    double fps;
    int interval;
    void updateFrame();
private slots:
    void load_video();
    void change_status();
    void click_skip();
    void click_skip_before();
    void durationChanged(qint64 duration);
    void positionChanged(qint64 duration);

protected:
    //bool eventFilter(QObject* obj, QEvent* event);
    //QPoint mapToImageCoordinates(const QPoint& pos);

//signals:
//    void spacePressed();

};
