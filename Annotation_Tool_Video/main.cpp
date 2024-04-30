#include "Annotation_Tool_Video.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Annotation_Tool_Video w;
    w.show();
    return a.exec();
}
