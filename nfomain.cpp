#include "nfomain.h"

NfoMain::NfoMain()
{
    setupUi(this);
    this->setWindowIcon(QIcon("icons/icon_enna_128.png"));

    QObject::connect(actionAbout, SIGNAL(activated()), qApp, SLOT(aboutQt()));
}

void NfoMain::on_actionOpen_activated()
{
    folder = QFileDialog::getExistingDirectory(this);
    this->listOfFiles->addItems(NfoMain::grabFiles(folder));
}

void NfoMain::fillProgressBar()
{
    //TO BE COMPLETED
}

void
eventgl_cb (valhalla_event_gl_t e, void *data)
{
  (void) data;
  printf ("Global event: %u\n", e);
  //TO BE COMPLETED/CHANGED
}

void
eventmd_cb (valhalla_event_md_t e, const char *id,
            const valhalla_file_t *file,
            const valhalla_metadata_t *md, void *data)
{
      const char *group;

  //TO BE COMPLETED/CHANGED
  (void) data;
  printf ("Metadata event\n");
  printf ("  File     : %s (%u)\n",
          file->path, file->type);
  switch (e)
  {
  case VALHALLA_EVENTMD_PARSER:
    printf ("  Parser\n");
    break;
  case VALHALLA_EVENTMD_GRABBER:
    printf ("  Grabber  : %s\n", id);
    break;
  }
  group = valhalla_metadata_group_str (md->group);
  printf ("  Name     : %s\n  Value    : %s\n  Group    : %u \"%s\"\n",
          md->name, md->value, md->group, group);
    //NfoMain::fillProgressBar();
}

void NfoMain::on_launchScan_clicked()
{
    int rc;
    const char *database = "./valhalla.db";
    valhalla_t *handle;
    valhalla_init_param_t param;
    valhalla_verb_t verbosity = VALHALLA_MSG_VERBOSE;
    int metadata_cb = 0, time_limit = 10000;

    valhalla_verbosity (verbosity);

    memset (&param, 0, sizeof (param));
    param.parser_nb   = 2;
    param.grabber_nb  = 8;
    param.commit_int  = 128;
    param.decrapifier = 1;
    param.gl_cb       = eventgl_cb;
    param.md_cb       = metadata_cb ? eventmd_cb : NULL;

    handle = valhalla_init (database, &param);
    if (!handle)
        return ;

    // TO BE CHANGED TO TAKE THE LIST OF THE APPLICATION
    const char *const *it;
    const char *const suf[] = {
      "avi",  "mkv", "mov",  "mpg", "wmv",
      NULL
    };

    for (it = suf; *it; it++)
    {
      valhalla_config_set(handle, SCANNER_SUFFIX, *it);
      printf (" %s", *it);
    }

    valhalla_config_set(handle, SCANNER_PATH, this->folder.toAscii().data(), 1);

    rc = valhalla_run (handle, 1, 0, 15);
    if (rc)
    {
        valhalla_uninit (handle);
        return;
    }

    if (!time_limit)
        valhalla_wait (handle);
    else
        usleep (time_limit * 1000);

   valhalla_uninit (handle);

    this->fileInfo->setPlainText(folder);
}

void NfoMain::on_actionClose_activated()
{
   if (!this->filePathes.empty())
       this->filePathes.clear();
   if (!this->nfoFiles.empty())
       this->nfoFiles.clear();
   this->thumbList->clear();
   this->fanArtList->clear();
   this->fanartDisplayed->clear();
   this->thumbDisplayed->clear();
   this->listOfFiles->clear();
   this->fileInfo->clear();
   this->nfoInfo->clear();
}

void NfoMain::on_listOfFiles_currentItemChanged(QListWidgetItem * current, QListWidgetItem * previous)
{
    if (current)
    {
        this->thumbList->clear();
        this->fanArtList->clear();
        this->fanartDisplayed->clear();
        this->thumbDisplayed->clear();
        fillFileInformationPanel(current->text());
        fillMediaInformationPanel(current->text());
    }
}

void NfoMain::on_thumbList_currentItemChanged(QListWidgetItem * current, QListWidgetItem * previous)
{
    if (current)
    {
        if (QFile::exists(current->text()))
        {
            m_fanArt.load(current->text());
        }
        else
        {
            //web file
            QUrl imageUrl(current->text());
            getImage(imageUrl);
        }
        this->thumbDisplayed->setPixmap(QPixmap::fromImage(m_fanArt).scaled(this->thumbDisplayed->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

void NfoMain::on_fanArtList_currentItemChanged(QListWidgetItem * current, QListWidgetItem * previous)
{
    if (current)
    {
        if (QFile::exists(current->text()))
        {
            m_fanArt.load(current->text());
        }
        else
        {
            //web file
            QUrl imageUrl(current->text());
            getImage(imageUrl);
        }
        this->fanartDisplayed->setPixmap(QPixmap::fromImage(m_fanArt).scaled(this->fanartDisplayed->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

void NfoMain::getImage(const QUrl &p_url) {
    // on indique à l'objet http le nom du serveur et le port
    QHttp http(p_url.host(), p_url.port(80));

    // Qt utilise un concept basé sur les évenements.
    // Nous allons donc utiliser QEventLoop pour attendre le signal done(bool) de http
    QEventLoop loop;
    QObject::connect(&http, SIGNAL(done(bool)), &loop, SLOT(quit()));

    // la requète HTTP
    http.get(p_url.path());

    // on attend le résultat du serveur
    loop.exec();

    // quand le serveur à finit,
    // on lit le résultat à partir de l'objet http pour créer notre pixmap
    m_fanArt.loadFromData(http.readAll());

}


QStringList NfoMain::grabFiles(QString folderSelected){
    QStringList fileNames;

    this->listFilter << "*.avi";
    this->listFilter << "*.mkv";

    QDirIterator dirIterator(folderSelected, listFilter ,QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
    while(dirIterator.hasNext())
    {
        dirIterator.next();
        fileNames << dirIterator.fileName();
        this->filePathes << dirIterator.filePath();
    }

    this->listFilter.clear();
    NfoMain::grabNfoFiles(folderSelected);

    return fileNames;
}

void NfoMain::grabNfoFiles(QString folderSelected){

    this->listFilter << "*.nfo";

    QDirIterator dirIterator(folderSelected, listFilter ,QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
    while(dirIterator.hasNext())
    {
        this->nfoFiles <<  dirIterator.next();
    }

    this->listFilter.clear();
}

void NfoMain::fillFileInformationPanel(QString fileName)
{
    this->fileInfo->setPlainText("No file information before scan by libvalhalla");
}

void NfoMain::fillMediaInformationPanel(QString fileName)
{
    QString preReg(".*");
    QString postReg(".nfo");
    fileName.chop(fileName.size()-fileName.lastIndexOf("."));
    fileName.prepend(preReg);
    fileName.append(postReg);

    QRegExp rx(fileName, Qt::CaseInsensitive);

    if (this->nfoFiles.indexOf(rx) != -1)
    {
        this->nfoInfo->setPlainText("Nfo found");
        NfoMain::parseNfoFile(this->nfoFiles.value(this->nfoFiles.indexOf(rx)));
    }
    else
        this->nfoInfo->setPlainText("No NFO file present. Launch libvalhalla to have information !");
}

void NfoMain::parseNfoFile(QString nfoFile)
{

    nfo_t *nfo_file = nfo_init(nfoFile.toAscii().data());
    switch (nfo_get_type(nfo_file))
    {
        case NFO_MOVIE:
            NfoMain::fillNfoMovie(nfo_get_movie(nfo_file));
            break;
        case NFO_TVSHOW:
            NfoMain::fillNfoTvShow(nfo_get_tvshow_episode(nfo_file));
            break;
        default:
            this->nfoInfo->setPlainText("This nfo si not valid.");
    }

}

void NfoMain::fillNfoMovie(nfo_movie_t *nfoMovie)
{
    QString contentNfo("");
    int i = 0;

    contentNfo.append("<b>Title :</b> ").append(nfo_movie_get(nfoMovie, NFO_MOVIE_TITLE));
    contentNfo.append("<br><b>Original title :</b> ").append(nfo_movie_get(nfoMovie, NFO_MOVIE_ORIGINAL_TITLE));
    contentNfo.append("<br><b>Plot :</b> ").append(nfo_movie_get(nfoMovie, NFO_MOVIE_PLOT));
    contentNfo.append("<br><b>Year :</b> ").append(nfo_movie_get(nfoMovie, NFO_MOVIE_YEAR));
    contentNfo.append("<br><b>Top 250 :</b> ").append(nfo_movie_get(nfoMovie, NFO_MOVIE_TOP250));
    contentNfo.append("<br><b>Outline :</b> ").append(nfo_movie_get(nfoMovie, NFO_MOVIE_OUTLINE));
    contentNfo.append("<br><b>Tagline :</b> ").append(nfo_movie_get(nfoMovie, NFO_MOVIE_TAGLINE));
    contentNfo.append("<br><b>Runtime :</b> ").append(nfo_movie_get(nfoMovie, NFO_MOVIE_RUNTIME));
    contentNfo.append("<br><b>Votes :</b> ").append(nfo_movie_get(nfoMovie, NFO_MOVIE_VOTES));
    contentNfo.append("<br><b>Rating :</b> ").append(nfo_movie_get(nfoMovie, NFO_MOVIE_RATING));
    contentNfo.append("<br><b>Genre :</b> ").append(nfo_movie_get(nfoMovie, NFO_MOVIE_GENRE));
    contentNfo.append("<br><b>Credits :</b> ").append(nfo_movie_get(nfoMovie, NFO_MOVIE_CREDITS));
    contentNfo.append("<br><b>Director :</b> ").append(nfo_movie_get(nfoMovie, NFO_MOVIE_DIRECTOR));
    contentNfo.append("<br><b>Studio :</b> ").append(nfo_movie_get(nfoMovie, NFO_MOVIE_STUDIO));
    contentNfo.append("<br><b>Trailer :</b> ").append(nfo_movie_get(nfoMovie, NFO_MOVIE_TRAILER));

    for (i = 0; i < nfo_movie_get_actors_count(nfoMovie); i++)
    {
        if (i == 0)
             contentNfo.append("<br><b>Actor : </b> ");
        else
             contentNfo.append(",<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;");

        contentNfo.append(nfo_actor_get(nfo_movie_get_actor(nfoMovie, i), NFO_ACTOR_NAME));

        if (nfo_actor_get(nfo_movie_get_actor(nfoMovie, i), NFO_ACTOR_ROLE))
            contentNfo.append(" as <i> ").append(nfo_actor_get(nfo_movie_get_actor(nfoMovie, i), NFO_ACTOR_ROLE)).append("</i>");

    }

    if (nfo_movie_get(nfoMovie, NFO_MOVIE_FAN_ART))
    {
        this->fanArtList->addItem(nfo_movie_get(nfoMovie, NFO_MOVIE_FAN_ART));
        QImage fanArt(nfo_movie_get(nfoMovie, NFO_MOVIE_FAN_ART));
        this->fanartDisplayed->setPixmap(QPixmap::fromImage(fanArt).scaled(this->fanartDisplayed->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    if (nfo_movie_get(nfoMovie, NFO_MOVIE_THUMB))
    {
        this->thumbList->addItem(nfo_movie_get(nfoMovie, NFO_MOVIE_THUMB));
        QImage thumb(nfo_movie_get(nfoMovie, NFO_MOVIE_THUMB));
        this->thumbDisplayed->setPixmap(QPixmap::fromImage(thumb).scaled(this->thumbDisplayed->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    this->nfoInfo->setText(contentNfo);
}

void NfoMain::fillNfoTvShow(nfo_tvshow_episode_t *nfoTvShow)
{
    QString contentNfo("");
    int i = 0;

    nfo_tvshow_t *nfoShow = nfo_tvshow_episode_get_show(nfoTvShow);

    if (nfoShow)
    {
        contentNfo.append("<b>Show Title :</b> ").append(nfo_tvshow_get(nfoShow, NFO_TVSHOW_TITLE));
        contentNfo.append("<br><b>Show Rating :</b> ").append(nfo_tvshow_get(nfoShow, NFO_TVSHOW_RATING));
        contentNfo.append("<br><b>Show Premiered :</b> ").append(nfo_tvshow_get(nfoShow, NFO_TVSHOW_PREMIERED));
        contentNfo.append("<br><b>Show Plot :</b> ").append(nfo_tvshow_get(nfoShow, NFO_TVSHOW_PLOT));
        contentNfo.append("<br><b>Show Episode Guide URL :</b> ").append(nfo_tvshow_get(nfoShow, NFO_TVSHOW_EPISODE_GUIDE_URL));
        contentNfo.append("<br><b>Show Total seasons :</b> ").append(nfo_tvshow_get(nfoShow, NFO_TVSHOW_SEASON));
        contentNfo.append("<br><b>Show Total episodes :</b> ").append(nfo_tvshow_get(nfoShow, NFO_TVSHOW_EPISODE));
        contentNfo.append("<br><b>Show Genre :</b> ").append(nfo_tvshow_get(nfoShow, NFO_TVSHOW_GENRE));
        contentNfo.append("<br><b>Show Studio :</b> ").append(nfo_tvshow_get(nfoShow, NFO_TVSHOW_STUDIO));
    }

    contentNfo.append("<br><b>Ep Title :</b> ").append(nfo_tvshow_episode_get(nfoTvShow, NFO_TVSHOW_EPISODE_TITLE));
    contentNfo.append("<br><b>Ep Season :</b> ").append(nfo_tvshow_episode_get(nfoTvShow, NFO_TVSHOW_EPISODE_SEASON));
    contentNfo.append("<br><b>Episode :</b> ").append(nfo_tvshow_episode_get(nfoTvShow, NFO_TVSHOW_EPISODE_EPISODE));
    contentNfo.append("<br><b>Ep Plot :</b> ").append(nfo_tvshow_episode_get(nfoTvShow, NFO_TVSHOW_EPISODE_PLOT));
    contentNfo.append("<br><b>Ep Rating :</b> ").append(nfo_tvshow_episode_get(nfoTvShow, NFO_TVSHOW_EPISODE_RATING));
    contentNfo.append("<br><b>Ep Credits :</b> ").append(nfo_tvshow_episode_get(nfoTvShow, NFO_TVSHOW_EPISODE_CREDITS));
    contentNfo.append("<br><b>Ep Director :</b> ").append(nfo_tvshow_episode_get(nfoTvShow, NFO_TVSHOW_EPISODE_DIRECTOR));
    contentNfo.append("<br><b>Ep Aired :</b> ").append(nfo_tvshow_episode_get(nfoTvShow, NFO_TVSHOW_EPISODE_AIRED));
    contentNfo.append("<br><b>Ep Votes :</b> ").append(nfo_tvshow_episode_get(nfoTvShow, NFO_TVSHOW_EPISODE_VOTES));

    for (i = 0; i < nfo_tvshow_episode_get_actors_count(nfoTvShow); i++)
    {
        if (i == 0)
             contentNfo.append("<br><b>Actor : </b> ");
        else
             contentNfo.append(",<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;");

        contentNfo.append(nfo_actor_get(nfo_tvshow_episode_get_actor(nfoTvShow, i), NFO_ACTOR_NAME));

        if ((nfo_actor_get(nfo_tvshow_episode_get_actor(nfoTvShow, i), NFO_ACTOR_ROLE))
            && (strlen(nfo_actor_get(nfo_tvshow_episode_get_actor(nfoTvShow, i), NFO_ACTOR_ROLE)) > 0))
            contentNfo.append(" as <i> ").append(nfo_actor_get(nfo_tvshow_episode_get_actor(nfoTvShow, i), NFO_ACTOR_ROLE)).append("</i>");

    }

    if (nfo_tvshow_episode_get(nfoTvShow, NFO_TVSHOW_EPISODE_FANART_SEASON))
    {
        this->fanArtList->addItem(nfo_tvshow_episode_get(nfoTvShow, NFO_TVSHOW_EPISODE_FANART_SEASON));
        QImage fanArt(nfo_tvshow_episode_get(nfoTvShow, NFO_TVSHOW_EPISODE_FANART_SEASON));
        this->fanartDisplayed->setPixmap(QPixmap::fromImage(fanArt).scaled(this->fanartDisplayed->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    if (nfo_tvshow_episode_get(nfoTvShow, NFO_TVSHOW_EPISODE_FANART))
    {
        this->thumbList->addItem(nfo_tvshow_episode_get(nfoTvShow, NFO_TVSHOW_EPISODE_FANART));
        QImage thumb(nfo_tvshow_episode_get(nfoTvShow, NFO_TVSHOW_EPISODE_FANART));
        this->thumbDisplayed->setPixmap(QPixmap::fromImage(thumb).scaled(this->thumbDisplayed->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    this->nfoInfo->setText(contentNfo);
}
