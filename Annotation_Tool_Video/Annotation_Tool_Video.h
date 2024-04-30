#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Annotation_Tool_Video.h"

class Annotation_Tool_Video : public QMainWindow
{
    Q_OBJECT

public:
    Annotation_Tool_Video(QWidget *parent = nullptr);
    ~Annotation_Tool_Video();

private:
    Ui::Annotation_Tool_VideoClass ui;
};
