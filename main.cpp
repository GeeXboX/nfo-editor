// main.cpp

#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include "nfomain.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QString locale = QLocale::system().name();
    QTranslator translator;
    translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&translator);


    NfoMain *mainWindow = new NfoMain();

    mainWindow->show();

    return app.exec();
}



