/*
 * GeeXboX NFO editor: GUI for media scanner application.
 * Copyright (C) 2009 Fabien Brisset <fbrisset@geexbox.org>
 *
 * This file is part of nfo-editor.
 *
 * nfo-editor is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * nfo-editor is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with libvalhalla; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

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
#include "nfo.h"
#include "valhalla.h"

class NfoMain : public QMainWindow, private Ui::NfoMainWindow
{
    Q_OBJECT

    public:
        NfoMain();

    private slots:
        void on_actionOpen_activated();
        void on_actionClose_activated();
        void on_listOfFiles_currentItemChanged(QListWidgetItem * current);
        void on_fanArtList_currentItemChanged(QListWidgetItem * current);
        void on_thumbList_currentItemChanged(QListWidgetItem * current);
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
