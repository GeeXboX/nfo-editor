#ifndef NFOMAIN_H
#define NFOMAIN_H

#include <QMainWindow>
#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <QDirIterator>
#include <QRegExp>
#include <QDomDocument>
#include <QImage>
#include <QHttp>
#include <QUrl>
#include <ui_nfomainwindow.h>
#ifdef __cplusplus
extern "C" {
#include "nfo.h"
#include "valhalla.h"
}
#endif

class NfoMain : public QMainWindow, private Ui::NfoMainWindow
{
    Q_OBJECT

    public:
        NfoMain();

    private slots:
        void on_actionOpen_activated();
        void on_actionClose_activated();
        void on_listOfFiles_currentItemChanged(QListWidgetItem * current, QListWidgetItem * previous);
        void on_fanArtList_currentItemChanged(QListWidgetItem * current, QListWidgetItem * previous);
        void on_thumbList_currentItemChanged(QListWidgetItem * current, QListWidgetItem * previous);
        void on_launchScan_clicked();


    private:
        QStringList listFilter, filePathes, nfoFiles;
        QString folder;
        QStringList grabFiles(QString folderSelected);
        QImage m_fanArt, m_thumb;
        void grabNfoFiles(QString folderSelected);
        void fillFileInformationPanel(QString fileName);
        void fillMediaInformationPanel(QString fileName);
        void parseNfoFile(QString nfoFile);
        void getImage(const QUrl &p_url);
        void fillNfoMovie(nfo_movie_t *nfoMovie);
        void fillNfoTvShow(nfo_tvshow_episode_t *nfoTvShowEpisode);
        void fillProgressBar();
};

#endif // NFOMAIN_H
