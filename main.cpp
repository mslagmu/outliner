#include "outlinerviewer.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString locale = QLocale::system().name();
    QTranslator translator;
    QString t_name = QString("outliner_") + locale +(".qm");

    translator.load(t_name,":translations");

    a.installTranslator(&translator);
    OutLinerViewer w;
    w.show();

    return a.exec();
}
