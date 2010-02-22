/********************************************************************************
** Form generated from reading ui file 'nfomainwindow.ui'
**
** Created: Mon Feb 15 22:34:15 2010
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_NFOMAINWINDOW_H
#define UI_NFOMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NfoMainWindow
{
public:
    QAction *actionOpen;
    QAction *actionClose;
    QAction *actionQuit;
    QAction *actionAbout;
    QAction *actionMovie;
    QAction *actionTV_Show;
    QWidget *centralwidget;
    QListWidget *listOfFiles;
    QTabWidget *tabInfos;
    QWidget *fileInformation;
    QTextEdit *fileInfo;
    QWidget *mediaInformatiion;
    QTextEdit *nfoInfo;
    QWidget *fanArt;
    QGroupBox *fanArtPosters;
    QListWidget *fanArtList;
    QLabel *fanartDisplayed;
    QGroupBox *thumb;
    QListWidget *thumbList;
    QLabel *thumbDisplayed;
    QPushButton *launchScan;
    QProgressBar *scanProgress;
    QLabel *labelListOfFiles;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuOptions;
    QMenu *menuView;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *NfoMainWindow)
    {
        if (NfoMainWindow->objectName().isEmpty())
            NfoMainWindow->setObjectName(QString::fromUtf8("NfoMainWindow"));
        NfoMainWindow->resize(800, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8("icons/icon_enna_128.png"), QSize(), QIcon::Normal, QIcon::Off);
        NfoMainWindow->setWindowIcon(icon);
        actionOpen = new QAction(NfoMainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionClose = new QAction(NfoMainWindow);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        actionQuit = new QAction(NfoMainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionAbout = new QAction(NfoMainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionMovie = new QAction(NfoMainWindow);
        actionMovie->setObjectName(QString::fromUtf8("actionMovie"));
        actionMovie->setCheckable(true);
        actionTV_Show = new QAction(NfoMainWindow);
        actionTV_Show->setObjectName(QString::fromUtf8("actionTV_Show"));
        actionTV_Show->setCheckable(true);
        centralwidget = new QWidget(NfoMainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        listOfFiles = new QListWidget(centralwidget);
        listOfFiles->setObjectName(QString::fromUtf8("listOfFiles"));
        listOfFiles->setGeometry(QRect(10, 50, 221, 511));
        tabInfos = new QTabWidget(centralwidget);
        tabInfos->setObjectName(QString::fromUtf8("tabInfos"));
        tabInfos->setGeometry(QRect(250, 90, 531, 471));
        fileInformation = new QWidget();
        fileInformation->setObjectName(QString::fromUtf8("fileInformation"));
        fileInfo = new QTextEdit(fileInformation);
        fileInfo->setObjectName(QString::fromUtf8("fileInfo"));
        fileInfo->setGeometry(QRect(20, 10, 471, 321));
        tabInfos->addTab(fileInformation, QString());
        mediaInformatiion = new QWidget();
        mediaInformatiion->setObjectName(QString::fromUtf8("mediaInformatiion"));
        nfoInfo = new QTextEdit(mediaInformatiion);
        nfoInfo->setObjectName(QString::fromUtf8("nfoInfo"));
        nfoInfo->setGeometry(QRect(20, 10, 471, 321));
        tabInfos->addTab(mediaInformatiion, QString());
        fanArt = new QWidget();
        fanArt->setObjectName(QString::fromUtf8("fanArt"));
        fanArtPosters = new QGroupBox(fanArt);
        fanArtPosters->setObjectName(QString::fromUtf8("fanArtPosters"));
        fanArtPosters->setGeometry(QRect(10, 10, 491, 201));
        fanArtList = new QListWidget(fanArtPosters);
        fanArtList->setObjectName(QString::fromUtf8("fanArtList"));
        fanArtList->setGeometry(QRect(260, 10, 221, 181));
        fanartDisplayed = new QLabel(fanArtPosters);
        fanartDisplayed->setObjectName(QString::fromUtf8("fanartDisplayed"));
        fanartDisplayed->setGeometry(QRect(20, 20, 211, 161));
        thumb = new QGroupBox(fanArt);
        thumb->setObjectName(QString::fromUtf8("thumb"));
        thumb->setGeometry(QRect(10, 220, 491, 201));
        thumbList = new QListWidget(thumb);
        thumbList->setObjectName(QString::fromUtf8("thumbList"));
        thumbList->setGeometry(QRect(260, 10, 221, 181));
        thumbDisplayed = new QLabel(thumb);
        thumbDisplayed->setObjectName(QString::fromUtf8("thumbDisplayed"));
        thumbDisplayed->setGeometry(QRect(20, 20, 211, 171));
        tabInfos->addTab(fanArt, QString());
        launchScan = new QPushButton(centralwidget);
        launchScan->setObjectName(QString::fromUtf8("launchScan"));
        launchScan->setGeometry(QRect(250, 30, 91, 23));
        scanProgress = new QProgressBar(centralwidget);
        scanProgress->setObjectName(QString::fromUtf8("scanProgress"));
        scanProgress->setGeometry(QRect(350, 30, 431, 23));
        scanProgress->setValue(0);
        labelListOfFiles = new QLabel(centralwidget);
        labelListOfFiles->setObjectName(QString::fromUtf8("labelListOfFiles"));
        labelListOfFiles->setGeometry(QRect(20, 20, 81, 21));
        NfoMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(NfoMainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 20));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuOptions = new QMenu(menubar);
        menuOptions->setObjectName(QString::fromUtf8("menuOptions"));
        menuView = new QMenu(menubar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuView->setEnabled(false);
        NfoMainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(NfoMainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        NfoMainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuView->menuAction());
        menubar->addAction(menuOptions->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionClose);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuOptions->addAction(actionAbout);
        menuView->addAction(actionMovie);
        menuView->addAction(actionTV_Show);

        retranslateUi(NfoMainWindow);
        QObject::connect(actionQuit, SIGNAL(activated()), NfoMainWindow, SLOT(close()));

        tabInfos->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(NfoMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *NfoMainWindow)
    {
        NfoMainWindow->setWindowTitle(QApplication::translate("NfoMainWindow", "NFO Editor", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("NfoMainWindow", "Open", 0, QApplication::UnicodeUTF8));
        actionClose->setText(QApplication::translate("NfoMainWindow", "Close", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("NfoMainWindow", "Quit", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("NfoMainWindow", "About", 0, QApplication::UnicodeUTF8));
        actionMovie->setText(QApplication::translate("NfoMainWindow", "Movie", 0, QApplication::UnicodeUTF8));
        actionTV_Show->setText(QApplication::translate("NfoMainWindow", "TV Show", 0, QApplication::UnicodeUTF8));
        tabInfos->setTabText(tabInfos->indexOf(fileInformation), QApplication::translate("NfoMainWindow", "File information", 0, QApplication::UnicodeUTF8));
        tabInfos->setTabText(tabInfos->indexOf(mediaInformatiion), QApplication::translate("NfoMainWindow", "Media information", 0, QApplication::UnicodeUTF8));
        fanArtPosters->setTitle(QApplication::translate("NfoMainWindow", "Fanart/Posters", 0, QApplication::UnicodeUTF8));
        fanartDisplayed->setText(QApplication::translate("NfoMainWindow", "Display Fanart", 0, QApplication::UnicodeUTF8));
        thumb->setTitle(QApplication::translate("NfoMainWindow", "Thumbnails", 0, QApplication::UnicodeUTF8));
        thumbDisplayed->setText(QApplication::translate("NfoMainWindow", "Display Thumbnail", 0, QApplication::UnicodeUTF8));
        tabInfos->setTabText(tabInfos->indexOf(fanArt), QApplication::translate("NfoMainWindow", "Fanart/Posters", 0, QApplication::UnicodeUTF8));
        launchScan->setText(QApplication::translate("NfoMainWindow", "Scan Files", 0, QApplication::UnicodeUTF8));
        labelListOfFiles->setText(QApplication::translate("NfoMainWindow", "List of files ", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("NfoMainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuOptions->setTitle(QApplication::translate("NfoMainWindow", "Options", 0, QApplication::UnicodeUTF8));
        menuView->setTitle(QApplication::translate("NfoMainWindow", "View", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NfoMainWindow: public Ui_NfoMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NFOMAINWINDOW_H
