#include "common.h"

#include "cmainwindow.h"
#include "ui_cmainwindow.h"

#include "cseasondelegate.h"
#include "csearch.h"
#include "cmoviesearch.h"
#include "cmessageanimatedialog.h"
#include "cmessagedialog.h"
#include "cedit.h"
#include "cmovieedit.h"
#include "cimage.h"

#include "cthemoviedbv3.h"

#include "cmovieviewitemdelegate.h"

#include <QTreeWidgetItem>
#include <QDir>
#include <QFile>
#include <QSqlQuery>
#include <QSqlError>
#include <QDesktopServices>
#include <QClipboard>
#include <QUrl>
#include <QIcon>
#include <QThread>

#include <QSettings>

#include <QTime>
#include <QMessageBox>
#include <QtDebug>

#include <QElapsedTimer>

#include <QScrollBar>
#include <QDesktopWidget>


static bool serieSort(cSerie* s1, cSerie* s2)
{
	QString str1	= s1->seriesName();
	QString	str2	= s2->seriesName();
	return(str1 < str2);
}

static bool movieSort(cMovie* s1, cMovie* s2)
{
	QString	collection1	= s1->belongsToCollection();
	QString	collection2	= s2->belongsToCollection();

	QString title1		= s1->movieTitle();
	QString	title2		= s2->movieTitle();

	if(collection1.isEmpty() && collection2.isEmpty())
		return(title1 < title2);

	if(!collection1.isEmpty() && !collection2.isEmpty())
	{
		if(collection1 == collection2)
			return(title1 < title2);
		return(collection1 < collection2);
	}

	return(title1 < title2);
}

cMainWindow::cMainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::cMainWindow),
	m_szOldSelected(""),
	m_lpMessageDialog(0),
	m_lpUpdateThread(0),
	m_lpPicturesThread(0),
	m_bProcessing(false),
	m_lpShortcut(0)
{
	m_timer.start();

	cMessageAnimateDialog*	lpDialog	= new cMessageAnimateDialog(this);
	lpDialog->setTitle("Initializing");
	lpDialog->setMessage("Initializing");
	lpDialog->show();

	ui->setupUi(this);
	ui->m_lpMainTab->setCurrentIndex(0);

	m_lpSeriesListModel	= new QStandardItemModel(0, 3);
	initDB();

	ui->m_lpSeriesList1->setModel(m_lpSeriesListModel);
	ui->m_lpSeriesList1->setItemDelegate(new cSeasonDelegate(ui->m_lpSeriesList1));
	ui->m_lpSeriesList2->setModel(m_lpSeriesListModel);
	ui->m_lpSeriesList2->setItemDelegate(new cSeasonDelegate(ui->m_lpSeriesList2));

	ui->m_lpSeriesList1->header()->setSectionResizeMode(2, QHeaderView::Stretch);

	m_lpMoviesListModel			= new QStandardItemModel(0, 1);
	QStringList	headerLabels	= QStringList() << tr("Movie");
	m_lpMoviesListModel->setHorizontalHeaderLabels(headerLabels);
	ui->m_lpMoviesList->setModel(m_lpMoviesListModel);
	ui->m_lpMoviesList->setItemDelegate(new cMovieViewItemDelegate());

	loadDB();
	displaySeries();
	displayMovies();

	QSettings	settings;
	qint16		iX		= settings.value("main/x", QVariant::fromValue(-1)).toInt();
	qint16		iY		= settings.value("main/y", QVariant::fromValue(-1)).toInt();
	qint16		iWidth	= settings.value("main/width", QVariant::fromValue(-1)).toInt();
	qint16		iHeight	= settings.value("main/height", QVariant::fromValue(-1)).toInt();

	if(iWidth != -1 && iHeight != -1)
		resize(iWidth, iHeight);
	if(iX != -1 && iY != -1)
		move(iX, iY);

	qint16	iWindowWidth	= iWidth;
	qint16	iSubtract		= 50;

	if(settings.value("main/maximized").toBool())
		iWindowWidth	= QApplication::desktop()->geometry().width();

	qint16	iWidth1			= 0;
	qint16	iWidth2;

	for(int z = 0;z < 3;z++)
		iWidth1	+= ui->m_lpSeriesList1->columnWidth(z);

	iWidth1	+= 2;
	iWidth2	= iWindowWidth-iSubtract-iWidth1;

	ui->m_lpSplitter->setSizes(QList<int>() << iWidth1 << iWidth2);

	delete lpDialog;

	connect(ui->m_lpSeriesList1->selectionModel(), &QItemSelectionModel::selectionChanged, this, &cMainWindow::selectionChanged1);
	connect(ui->m_lpSeriesList2->selectionModel(), &QItemSelectionModel::selectionChanged, this, &cMainWindow::selectionChanged2);

	connect(ui->m_lpSeriesList1->verticalScrollBar(), &QScrollBar::valueChanged, this, &cMainWindow::scrollbarValueChanged1);
	connect(ui->m_lpSeriesList2->verticalScrollBar(), &QScrollBar::valueChanged, this, &cMainWindow::scrollbarValueChanged2);

	m_lpShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_A), this, SLOT(onActionAddGlobal()));
	m_lpShortcut->setAutoRepeat(false);
}

cMainWindow::~cMainWindow()
{
	if(m_lpShortcut)
		delete m_lpShortcut;

	delete ui;
}

void cMainWindow::closeEvent(QCloseEvent *event)
{
	QSettings	settings;
	settings.setValue("main/width", QVariant::fromValue(size().width()));
	settings.setValue("main/hight", QVariant::fromValue(size().height()));
	settings.setValue("main/x", QVariant::fromValue(x()));
	settings.setValue("main/y", QVariant::fromValue(y()));
	if(this->isMaximized())
		settings.setValue("main/maximized", QVariant::fromValue(true));
	else
		settings.setValue("main/maximized", QVariant::fromValue(false));

	event->accept();
}

void cMainWindow::initDB()
{
	QString		szDBPath	= rootPath()+ QDir::separator() + QString("qtmovies.db");

	m_db	= QSqlDatabase::addDatabase("QSQLITE");
	m_db.setHostName("localhost");
	m_db.setDatabaseName(szDBPath);
	if(!m_db.open())
		return;

	QSqlQuery	query;

	if(!m_db.tables().contains("serie"))
	{
		query.exec("CREATE TABLE serie ("
					"   seriesID            INTEGER,"
					"   seriesName          STRING,"
					"   originalName        STRING,"
					"   backdropPath        STRING,"
					"   createdBy           STRING,"
					"   homepage            STRING,"
					"   lastAired           DATE,"
					"   languages           STRING,"
					"   networks            STRING,"
					"   nrEpisodes          INTEGER,"
					"   nrSeasons           INTEGER,"
					"   originCountries     STRING,"
					"   originalLanguage    STRING,"
					"   popularity          DOUBLE,"
					"   posterPath          STRING,"
					"   productionCompanies STRING,"
					"   type                STRING,"
					"   voteAverage         DOUBLE,"
					"   voteCount           INT,"
					"   overview            TEXT,"
					"   firstAired          DATE,"
					"   cast                STRING,"
					"   crew                STRING,"
					"   genre               STRING,"
					"   status              STRING,"
					"   download            STRING,"
					"   cliffhanger         BOOL);");
	}

	if(!m_db.tables().contains("episode"))
	{
		query.exec("CREATE TABLE episode ("
					"	id             INTEGER,"
					"	name           STRING,"
					"	episodeNumber  INTEGER,"
					"	airDate        DATE,"
					"	guestStars     STRING,"
					"	overview       TEXT,"
					"	productioncode STRING,"
					"	seasonNumber   INTEGER,"
					"	seasonID       INTEGER,"
					"	seriesID       INTEGER,"
					"   stillPath      STRING,"
					"   voteAverage    DOUBLE,"
					"   voteCount      INTEGER,"
					"   crew           STRING,"
					"	state          INT);");

	}
	if(!m_db.tables().contains("movie"))
	{
		query.exec("CREATE TABLE movie ("
					"   movieID             INTEGER,"
					"   movieTitle          STRING,"
					"   originalTitle       STRING,"
					"   backdropPath        STRING,"
					"   posterPath          STRING,"
					"   overview            TEXT,"
					"   releaseDate         DATE,"
					"   genre               STRING,"
					"   imdbid              STRING,"
					"   originalLanguage    STRING,"
					"   popularity		    DOUBLE,"
					"   productionCompanies STRING,"
					"   productionCountries STRING,"
					"   voteAverage         DOUBLE,"
					"   voteCount           INTEGER,"
					"   adult               BOOL,"
					"   belongsToCollection STRING,"
					"   budget              DOUBLE,"
					"   homepage            STRING,"
					"   revenue             DOUBLE,"
					"   runtime             INTEGER,"
					"   spokenLanguages     STRING,"
					"   status              STRING,"
					"   tagline             STRING,"
					"   video               BOOL,"
					"   cast                TEXT,"
					"   crew                TEXT,"
					"   state               INTEGER);");
	}
}

void cMainWindow::loadDB()
{
//	convertSeries();
	loadSeriesDB();
	loadMoviesDB();
}

void cMainWindow::convertSeries()
{
	QSqlQuery		query;
	QString			szOldIMDBID	= "";
	cTheMovieDBV3	theMovieDB;
	cSerie*			lpSerie		= 0;

	if(query.exec("SELECT s.imdbid, s.download, s.cliffhanger, e.episodeNumber, e.seasonNumber, e.state FROM serie_old s LEFT JOIN episode_old e ON s.id = e.seriesID WHERE s.imdbid IS NOT NULL AND s.imdbid <> \"\" ORDER BY s.imdbid, e.seasonNumber, e.episodeNumber;"))
	{
		while(query.next())
		{
			QString	szIMDBID		= query.value("imdbid").toString();

			if(!szIMDBID.isEmpty())
			{
				if(szIMDBID != szOldIMDBID)
				{
					if(lpSerie)
					{
						lpSerie->save(m_db);
						delete lpSerie;
						lpSerie	= 0;
					}

					szOldIMDBID	= szIMDBID;
					lpSerie		= theMovieDB.loadSerie(szIMDBID);
					if(lpSerie)
					{
						lpSerie->setDownload(query.value("download").toString());
						lpSerie->setCliffhanger(query.value("cliffhanger").toBool());
					}
				}

				if(lpSerie)
				{
					cSeason*		lpSeason	= lpSerie->findSeason(query.value("seasonNumber").toInt());
					if(lpSeason)
					{
						cEpisode*	lpEpisode	= lpSeason->findEpisode(query.value("episodeNumber").toInt());
						if(lpEpisode)
							lpEpisode->setState((cEpisode::State)query.value("state").toInt());
					}
				}
			}
		}
	}
	if(lpSerie)
	{
		lpSerie->save(m_db);
		delete lpSerie;
		lpSerie	= 0;
	}
}

void cMainWindow::loadSeriesDB()
{
	m_serieList.clear();

	QSqlQuery	query;

	qint32		iOldSeriesID		= -1;
	qint32		iOldSeasonNumber	= -1;
	qint32		iSeriesID;
	qint32		iSeasonNumber;
	cSeason*	lpSeason;
	cEpisode*	lpEpisode;

	if(query.exec("SELECT serie.seriesID,serie.seriesName,serie.originalName,serie.backdropPath,serie.createdBy,serie.homepage,serie.lastAired,serie.languages,serie.networks,serie.nrEpisodes,serie.nrSeasons,serie.originCountries,serie.originalLanguage,serie.popularity,serie.posterPath,serie.productionCompanies,serie.type,serie.voteAverage,serie.voteCount,serie.overview,serie.firstAired,serie.cast,serie.crew,serie.genre,serie.status,serie.download,serie.cliffhanger,episode.id eid,episode.name ename,episode.episodeNumber eepisodeNumber,episode.airDate eairDate,episode.guestStars eguestStars,episode.overview eoverview,episode.productioncode eproductioncode,episode.seasonNumber eseasonNumber,episode.seasonID eseasonID,episode.seriesID eseriesID,episode.stillPath estillPath,episode.voteAverage evoteAverage,episode.voteCount evoteCount,episode.crew ecrew,episode.state estate FROM serie LEFT JOIN episode ON serie.seriesID = episode.seriesID ORDER BY serie.seriesName, serie.firstAired, episode.seasonNumber, episode.episodeNumber;"))
	{
		while(query.next())
		{
			iSeriesID		= query.value("seriesID").toInt();
			iSeasonNumber	= query.value("eseasonNumber").toInt();

			if(iSeriesID != iOldSeriesID)
			{
				m_serieList.add(iSeriesID);
				iOldSeriesID		= iSeriesID;
				iOldSeasonNumber	= -1;
			}

			cSerie*	lpSerie	= m_serieList.add(iSeriesID);
			lpSerie->setSeriesName(query.value("seriesName").toString());
			lpSerie->setOriginalName(query.value("originalName").toString());
			lpSerie->setBackdropPath(query.value("backdropPath").toString());
			lpSerie->setCreatedBy(query.value("createdBy").toString());
			lpSerie->setHomepage(query.value("homepage").toString());
			lpSerie->setLastAired(query.value("lastAired").toString());
			lpSerie->setLanguages(query.value("languages").toString());
			lpSerie->setNetworks(query.value("networks").toString());
			lpSerie->setEpisodes(query.value("nrEpisodes").toInt());
			lpSerie->setSeasons(query.value("nrSeasons").toInt());
			lpSerie->setOriginCountries(query.value("originCountries").toString());
			lpSerie->setOriginalLanguage(query.value("originalLanguage").toString());
			lpSerie->setPopularity(query.value("popularity").toDouble());
			lpSerie->setPosterPath(query.value("posterPath").toString());
			lpSerie->setProductionCompanies(query.value("productionCompanies").toString());
			lpSerie->setType(query.value("type").toString());
			lpSerie->setVoteAverage(query.value("voteAverage").toDouble());
			lpSerie->setVoteCount(query.value("voteCount").toInt());
			lpSerie->setOverview(query.value("overview").toString());
			lpSerie->setFirstAired(query.value("firstAired").toString());
			lpSerie->setCast(query.value("cast").toString().split("|"));
			lpSerie->setCrew(query.value("crew").toString().split("|"));
			lpSerie->setGenre(query.value("genre").toString());
			lpSerie->setStatus(query.value("status").toString());
			lpSerie->setDownload(query.value("download").toString());
			lpSerie->setCliffhanger(query.value("cliffhanger").toBool());

			if(iSeasonNumber != iOldSeasonNumber)
			{
				lpSeason			= lpSerie->addSeason(query.value("eseasonNumber").toInt());
				iOldSeasonNumber	= iSeasonNumber;
			}

			lpEpisode	= lpSeason->addEpisode(iSeasonNumber);

			lpEpisode->setID(query.value("eid").toInt());
			lpEpisode->setName(query.value("ename").toString());
			lpEpisode->setEpisodeNumber(query.value("eepisodeNumber").toInt());
			lpEpisode->setAirDate(query.value("eairDate").toString());
			lpEpisode->setGuestStars(query.value("eguestStars").toString());
			lpEpisode->setOverview(query.value("eoverview").toString());
			lpEpisode->setProductionCode(query.value("eproductioncode").toString());
			lpEpisode->setSeasonNumber(query.value("eseasonNumber").toInt());
			lpEpisode->setSeasonID(query.value("eseasonID").toInt());
			lpEpisode->setSeriesID(query.value("eseriesID").toInt());
			lpEpisode->setStillPath(query.value("estillPath").toString());
			lpEpisode->setVoteAverage(query.value("evoteAverage").toDouble());
			lpEpisode->setVoteCount(query.value("evoteCount").toInt());
			lpEpisode->setCrew(query.value("ecrew").toString());
			lpEpisode->setState((cEpisode::State)query.value("estate").toInt());
		}
	}
}

void cMainWindow::loadMoviesDB()
{
	m_movieList.clear();

	QSqlQuery	query;
	qint32		iMovieID;

	if(query.exec("SELECT movieID, movieTitle, originalTitle, backdropPath, posterPath, overview, releaseDate, genre, imdbid, originalLanguage, popularity, productionCompanies, productionCountries, voteAverage, voteCount, adult, belongsToCollection, budget, homepage, revenue, runtime, spokenLanguages, status, tagline, video, `cast`, crew, state, sortText FROM (SELECT *, IFNULL(belongsToCollection, movieTitle) AS sortText FROM movie) ORDER BY sortText, releaseDate;"))
	{
		while(query.next())
		{
			iMovieID	= query.value("movieID").toInt();
			cMovie*	lpMovie	= m_movieList.add(iMovieID);

			lpMovie->setMovieTitle(query.value("movieTitle").toString());
			lpMovie->setOriginalTitle(query.value("originalTitle").toString());
			lpMovie->setReleaseDate(query.value("releaseDate").toString());
			lpMovie->setAdult(query.value("adult").toBool());
			lpMovie->setBackdropPath(query.value("backdropPath").toString());
			lpMovie->setBelongsToCollection(query.value("belongsToCollection").toString());
			lpMovie->setBudget(query.value("budget").toDouble());
			lpMovie->setGenres(query.value("genre").toString().split(","));
			lpMovie->setHomepage(query.value("homepage").toString());
			lpMovie->setIMDBID(query.value("imdbid").toString());
			lpMovie->setOriginalLanguage(query.value("originalLanguage").toString());
			lpMovie->setOverview(query.value("overview").toString());
			lpMovie->setPopularity(query.value("popularity").toDouble());
			lpMovie->setPosterPath(query.value("posterPath").toString());
			lpMovie->setProductionCompanies(query.value("productionCompanies").toString());
			lpMovie->setProductionCountries(query.value("productionCountries").toString());
			lpMovie->setRevenue(query.value("revenue").toDouble());
			lpMovie->setRuntime(query.value("runtime").toInt());
			lpMovie->setSpokenLanguages(query.value("spokenLanguages").toString().split(","));
			lpMovie->setStatus(query.value("status").toString());
			lpMovie->setTagline(query.value("tagline").toString());
			lpMovie->setVideo(query.value("video").toBool());
			lpMovie->setVoteAverage(query.value("voteAverage").toDouble());
			lpMovie->setVoteCount(query.value("voteCount").toInt());
			lpMovie->setCast(query.value("cast").toString().split("|"));
			lpMovie->setCrew(query.value("crew").toString().split("|"));
			lpMovie->setState((cMovie::State)query.value("state").toInt());
		}
	}
	else
	{
		qDebug() << query.lastError().text();
	}
}

void cMainWindow::displaySeries()
{
	m_lpSeriesListModel->clear();

	qint16	iMin		= m_serieList.minSeason();
	qint16	iMax		= m_serieList.maxSeason();

	qint16	iSeries		= 0;
	qint16	iEpisodes	= 0;

	m_lpSeriesListModel->setColumnCount(iMax-iMin+2);

	QStringList	header;
	header << "Nr" << "Serie" << "Year";

	for(int z = 0;z <= iMax;z++)
		header.append(QString("Season %1").arg(z));

	m_lpSeriesListModel->setHorizontalHeaderLabels(header);
	m_lpSeriesListModel->setHeaderData(0, Qt::Horizontal, QVariant(iMin), Qt::UserRole);

	QFont	font	= ui->m_lpSeriesList1->font();
	QFont	fontI	= ui->m_lpSeriesList1->font();

	font.setBold(true);
	fontI.setItalic(true);

	QIcon		icon(":/128279.png");
	QModelIndex	selected;

	for(int serie = 0;serie < m_serieList.count();serie++)
	{
		iSeries++;

		QList<QStandardItem*>	lpItems;

		for(int z = 0;z < header.count();z++)
			lpItems.append(new QStandardItem);

		cSerie*	lpSerie	= m_serieList.at(serie);

		lpItems.at(0)->setText(QString("%1").arg(serie+1));
		lpItems.at(0)->setTextAlignment(Qt::AlignRight);
		lpItems.at(0)->setData(QVariant::fromValue(lpSerie), Qt::UserRole);

		lpItems.at(1)->setText(lpSerie->seriesName());
		lpItems.at(1)->setTextAlignment(Qt::AlignLeft);

		lpItems.at(2)->setText(lpSerie->firstAired().toString("yyyy"));
		lpItems.at(2)->setTextAlignment(Qt::AlignRight);

		bool		bHasInit	= false;
		bool		bHasProg	= false;
		bool		bHasDone	= false;

		QString		szOpen;

		QList<cSeason*>	seasonList	= lpSerie->seasonList();
		for(int season = 0;season < seasonList.count();season++)
		{
			QString		szInit		= "";
			QString		szProg		= "";
			QString		szDone		= "";

			cSeason*	lpSeason	= seasonList.at(season);
			lpItems.at(lpSeason->number()+3-iMin)->setData(QVariant::fromValue(lpSeason), Qt::UserRole);

			for(int y = 0;y < lpSeason->episodeList().count();y++)
			{
				iEpisodes++;

				if(lpSeason->episodeList().at(y)->state() == cEpisode::StateInit)
				{
					if(szInit.isEmpty())
						szInit.append(QString("%1").arg(lpSeason->episodeList().at(y)->episodeNumber()));
					else
						szInit.append(QString(", %1").arg(lpSeason->episodeList().at(y)->episodeNumber()));

					if(lpSeason->number())
						bHasInit	= true;
				}
				else if(lpSeason->episodeList().at(y)->state() == cEpisode::StateProgress)
				{
					if(szProg.isEmpty())
						szProg.append(QString("%1").arg(lpSeason->episodeList().at(y)->episodeNumber()));
					else
						szProg.append(QString(", %1").arg(lpSeason->episodeList().at(y)->episodeNumber()));

					if(lpSeason->number())
						bHasProg	= true;
				}
				else if(lpSeason->episodeList().at(y)->state() == cEpisode::StateDone)
				{
					if(szDone.isEmpty())
						szDone.append(QString("%1").arg(lpSeason->episodeList().at(y)->episodeNumber()));
					else
						szDone.append(QString(", %1").arg(lpSeason->episodeList().at(y)->episodeNumber()));

					if(lpSeason->number())
						bHasDone	= true;
				}
			}

			QString	szTooltip;

			if(szInit.isEmpty())
				szTooltip.append("open: none\n");
			else
				szTooltip.append("open: " + szInit + "\n");

			if(lpSeason->number())
			{
				if(szOpen.length())
					szOpen	+= "\n";

				if(szInit.isEmpty())
					szOpen	+= QString("Season %1: none").arg(lpSeason->number(), 2, 10, QChar('0'));
				else
					szOpen	+= QString("Season %1: %2").arg(lpSeason->number(), 2, 10, QChar('0')).arg(szInit);
			}

			if(szProg.isEmpty())
				szTooltip.append("in progress: none\n");
			else
				szTooltip.append("in progress: " + szProg + "\n");

			if(szDone.isEmpty())
				szTooltip.append("done: none");
			else
				szTooltip.append("done: " + szDone);

			if(szTooltip.isEmpty())
				lpItems.at(lpSeason->number()+3-iMin)->setToolTip(szTooltip);
			else
				lpItems.at(lpSeason->number()+3-iMin)->setToolTip(szTooltip);
		}

		if(lpSerie->status().compare("Ended", Qt::CaseInsensitive) &&
		   lpSerie->status().compare("canceled", Qt::CaseInsensitive))
		{
			lpItems.at(0)->setFont(font);
			lpItems.at(1)->setFont(font);
			lpItems.at(2)->setFont(font);
		}

		if(lpSerie->cliffhanger())
		{
			lpItems.at(0)->setFont(fontI);
			lpItems.at(1)->setFont(fontI);
			lpItems.at(2)->setFont(fontI);
			lpItems.at(0)->setForeground(QBrush(Qt::red));
			lpItems.at(1)->setForeground(QBrush(Qt::red));
			lpItems.at(2)->setForeground(QBrush(Qt::red));
		}

		if(bHasProg)
		{
			lpItems.at(0)->setForeground(QBrush(Qt::white));
			lpItems.at(1)->setForeground(QBrush(Qt::white));
			lpItems.at(2)->setForeground(QBrush(Qt::white));
			lpItems.at(0)->setBackground(QBrush(Qt::blue));
			lpItems.at(1)->setBackground(QBrush(Qt::blue));
			lpItems.at(2)->setBackground(QBrush(Qt::blue));
		}
		else if(bHasInit)
		{
			lpItems.at(0)->setBackground(QBrush(Qt::lightGray));
			lpItems.at(1)->setBackground(QBrush(Qt::lightGray));
			lpItems.at(2)->setBackground(QBrush(Qt::lightGray));
		}
		else
		{
			lpItems.at(0)->setBackground(QBrush(Qt::green));
			lpItems.at(1)->setBackground(QBrush(Qt::green));
			lpItems.at(2)->setBackground(QBrush(Qt::green));
		}

		if(lpSerie->download().length())
			lpItems.at(0)->setIcon(icon);
		m_lpSeriesListModel->appendRow(lpItems);

		if(!m_szOldSelected.isEmpty())
		{
			if(!m_szOldSelected.compare(lpSerie->seriesName()))
			{
				selected	= m_lpSeriesListModel->indexFromItem(lpItems.at(0));
				ui->m_lpSeriesList1->selectionModel()->select(selected, QItemSelectionModel::Select | QItemSelectionModel::Rows);
			}
		}

		lpItems.at(0)->setToolTip(szOpen);
		lpItems.at(1)->setToolTip(szOpen);
		lpItems.at(2)->setToolTip(szOpen);
	}

	for(int z = 3;z < m_lpSeriesListModel->columnCount();z++)
	{
		ui->m_lpSeriesList1->setColumnWidth(z, 0);
		ui->m_lpSeriesList2->resizeColumnToContents(z);
	}

	for(int z = 2;z >= 0;z--)
		ui->m_lpSeriesList1->resizeColumnToContents(z);

	if(selected.isValid())
	{
		ui->m_lpSeriesList1->scrollTo(selected, QAbstractItemView::PositionAtCenter);
		ui->m_lpSeriesList2->scrollTo(selected, QAbstractItemView::PositionAtCenter);
	}

	m_szOldSelected	= "";

	for(int z = 3;z < m_lpSeriesListModel->columnCount();z++)
		ui->m_lpSeriesList1->setColumnHidden(z, true);

	ui->m_lpSeriesList2->setColumnHidden(0, true);
	ui->m_lpSeriesList2->setColumnHidden(1, true);
	ui->m_lpSeriesList2->setColumnHidden(2, true);

	ui->m_lpSeriesCount->setText(QString("%1").arg(iSeries));
	ui->m_lpEpisodesCount->setText(QString("%1").arg(iEpisodes));
}

void cMainWindow::displayMovies()
{
	qint16	iMovies	= 0;

	m_lpMoviesListModel->clear();
	m_lpMoviesListModel->setColumnCount(1);

	QStringList	header;
	header << "Movie";

	m_lpMoviesListModel->setHorizontalHeaderLabels(header);

	QString			szOldCollection("");
	QStandardItem*	lpRoot	= 0;

	for(int x = 0;x < m_movieList.count();x++)
	{
		iMovies++;

		cMovie*	lpMovie	= m_movieList.at(x);

		if(lpMovie->belongsToCollection() != szOldCollection)
		{
			szOldCollection	= lpMovie->belongsToCollection();
			if(szOldCollection.isEmpty())
				lpRoot	= 0;
			else
			{
				lpRoot	= new QStandardItem(QString("<b>%1</b>").arg(szOldCollection));
				m_lpMoviesListModel->appendRow(lpRoot);
			}
		}

		QStandardItem*	lpItem	= new QStandardItem(QString("<b>%1</b> (%2)&nbsp;&nbsp;<br><i>%3</i>").arg(lpMovie->movieTitle()).arg(lpMovie->releaseDate().year()).arg(lpMovie->tagline()));
		lpItem->setData(QVariant::fromValue(lpMovie), Qt::UserRole);

		if(lpRoot)
			lpRoot->appendRow(lpItem);
		else
			m_lpMoviesListModel->appendRow(lpItem);
	}

	ui->m_lpMoviesCount->setText(QString("%1").arg(iMovies));
}

void cMainWindow::on_m_lpSeriesList1_customContextMenuRequested(const QPoint &pos)
{
	showSeriesContextMenu(ui->m_lpSeriesList1, pos);
}

void cMainWindow::on_m_lpSeriesList2_customContextMenuRequested(const QPoint &pos)
{
	showSeriesContextMenu(ui->m_lpSeriesList2, pos);
}

void cMainWindow::showSeriesContextMenu(QTreeView* lpTreeView, const QPoint &pos)
{
	QMenu*	lpMenu	= new QMenu(this);

	lpMenu->addAction("add", this, SLOT(onActionAdd()));

	lpMenu->addAction("update all", this, SLOT(onActionUpdateAll()));
	lpMenu->addAction("update unfinished", this, SLOT(onActionUpdateUnfinished()));
	lpMenu->addSeparator();

	if(lpTreeView->selectionModel()->selectedRows().count() == 1)
	{
		cSerie*	lpSerie	= m_lpSeriesListModel->itemFromIndex(lpTreeView->selectionModel()->selectedRows().at(0))->data(Qt::UserRole).value<cSerie*>();
		if(lpSerie)
		{
			lpMenu->addAction("update", this, SLOT(onActionUpdate()));
			lpMenu->addAction("delete", this, SLOT(onActionDelete()));
			lpMenu->addAction("edit", this, SLOT(onActionEdit()));
			lpMenu->addSeparator();

			if(!lpSerie->download().isEmpty())
			{
				lpMenu->addAction("open download link", this, SLOT(onActionGotoDownload()));
				lpMenu->addAction("copy download link", this, SLOT(onActionCopyDownload()));
			}
			lpMenu->addSeparator();
			lpMenu->addAction("load images", this, SLOT(onActionLoadPictures()));
		}
	}
	else if(lpTreeView->selectionModel()->selectedRows().count())
	{
		lpMenu->addAction("update selected", this, SLOT(onActionUpdate()));
		lpMenu->addAction("delete selected", this, SLOT(onActionDelete()));
		lpMenu->addSeparator();
		lpMenu->addAction("load images", this, SLOT(onActionLoadPictures()));
	}

	lpMenu->popup(lpTreeView->viewport()->mapToGlobal(pos));
}

void cMainWindow::on_m_lpMoviesList_customContextMenuRequested(const QPoint &pos)
{
	showMoviesContextMenu(ui->m_lpMoviesList, pos);
}

void cMainWindow::showMoviesContextMenu(QTreeView* lpTreeView, const QPoint &pos)
{
	QMenu*	lpMenu	= new QMenu(this);

	lpMenu->addAction("add", this, SLOT(onActionMovieAdd()));

	lpMenu->addAction("update all", this, SLOT(onActionMovieUpdateAll()));
	lpMenu->addSeparator();

	if(lpTreeView->selectionModel()->selectedRows().count() == 1)
	{
		cMovie*	lpMovie	= m_lpMoviesListModel->itemFromIndex(lpTreeView->selectionModel()->selectedRows().at(0))->data(Qt::UserRole).value<cMovie*>();
		if(lpMovie)
		{
			lpMenu->addAction("update", this, SLOT(onActionMovieUpdate()));
			lpMenu->addAction("delete", this, SLOT(onActionMovieDelete()));
			lpMenu->addAction("edit", this, SLOT(onActionMovieEdit()));
			lpMenu->addSeparator();

			if(!lpMovie->imdbID().isEmpty())
				lpMenu->addAction("open IMDB", this, SLOT(onActionMovieGotoIMDB()));

//			if(!lpMovie->download().isEmpty())
//			{
//				lpMenu->addAction("open download link", this, SLOT(onActionMovieGotoDownload()));
//				lpMenu->addAction("copy download link", this, SLOT(onActionMovieCopyDownload()));
//			}
			lpMenu->addSeparator();
			lpMenu->addAction("load images", this, SLOT(onActionMovieLoadPictures()));
		}
	}
	else if(lpTreeView->selectionModel()->selectedRows().count())
	{
		lpMenu->addAction("update selected", this, SLOT(onActionMovieUpdate()));
		lpMenu->addAction("delete selected", this, SLOT(onActionMovieDelete()));
		lpMenu->addSeparator();
		lpMenu->addAction("load images", this, SLOT(onActionLoadMoviePictures()));
	}

	lpMenu->popup(lpTreeView->viewport()->mapToGlobal(pos));
}

bool cMainWindow::runEdit(cSerie* lpSerie, QString& szDownload)
{
	cEdit*	lpEdit	= new cEdit;

	cMessageAnimateDialog*	lpDialog	= new cMessageAnimateDialog(this);
	lpDialog->setTitle("Edit");
	lpDialog->setMessage("Loading");
	lpDialog->show();

	lpEdit->setSerie(lpSerie);

	QSettings	settings;
	qint16		iX		= settings.value("edit/x", QVariant::fromValue(-1)).toInt();
	qint16		iY		= settings.value("edit/y", QVariant::fromValue(-1)).toInt();
	qint16		iWidth	= settings.value("edit/width", QVariant::fromValue(-1)).toInt();
	qint16		iHeight	= settings.value("edit/height", QVariant::fromValue(-1)).toInt();

	if(iX != -1 && iY != -1)
		lpEdit->move(iX, iY);
	if(iWidth != -1 && iHeight != -1)
		lpEdit->resize(iWidth, iHeight);

	delete lpDialog;

	qint16	ret	= lpEdit->exec();

	settings.setValue("edit/width", QVariant::fromValue(lpEdit->size().width()));
	settings.setValue("edit/height", QVariant::fromValue(lpEdit->size().height()));
	settings.setValue("edit/x", QVariant::fromValue(lpEdit->x()));
	settings.setValue("edit/y", QVariant::fromValue(lpEdit->y()));
	if(this->isMaximized())
		settings.setValue("edit/maximized", QVariant::fromValue(true));
	else
		settings.setValue("edit/maximized", QVariant::fromValue(false));

	if(ret == QDialog::Rejected)
	{
		delete lpEdit;

		int	x;
		QList<cSeason*>	seasonList	= lpSerie->seasonList();
		for(x = 0;x < seasonList.count();x++)
		{
			cSeason*	lpSeason	= seasonList.at(x);

			QList<cEpisode*>	episodeList	= lpSeason->episodeList();
			for(int y = 0;y < episodeList.count();y++)
			{
				cEpisode*	lpEpisode	= episodeList.at(y);
				if(lpEpisode)
				{
					lpEpisode->setButton1(0);
					lpEpisode->setButton2(0);
					lpEpisode->setButton3(0);
				}
			}
		}

		return(false);
	}

	szDownload	= lpEdit->download();

	lpSerie->setDownload(szDownload);
	lpSerie->updateState();

	delete lpEdit;

	return(true);
}

bool cMainWindow::runMovieEdit(cMovie *lpMovie)
{
	cMovieEdit*	lpMovieEdit	= new cMovieEdit(this);

	cMessageAnimateDialog*	lpDialog	= new cMessageAnimateDialog(this);
	lpDialog->setTitle("Edit");
	lpDialog->setMessage("Loading");
	lpDialog->show();

	lpMovieEdit->setMovie(lpMovie);

	QSettings	settings;
	qint16		iX		= settings.value("movieEdit/x", QVariant::fromValue(-1)).toInt();
	qint16		iY		= settings.value("movieEdit/y", QVariant::fromValue(-1)).toInt();
	qint16		iWidth	= settings.value("movieEdit/width", QVariant::fromValue(-1)).toInt();
	qint16		iHeight	= settings.value("movieEdit/height", QVariant::fromValue(-1)).toInt();

	if(iX != -1 && iY != -1)
		lpMovieEdit->move(iX, iY);
	if(iWidth != -1 && iHeight != -1)
		lpMovieEdit->resize(iWidth, iHeight);

	delete lpDialog;

	qint16	ret	= lpMovieEdit->exec();

	settings.setValue("movieEdit/width", QVariant::fromValue(lpMovieEdit->size().width()));
	settings.setValue("movieEdit/height", QVariant::fromValue(lpMovieEdit->size().height()));
	settings.setValue("movieEdit/x", QVariant::fromValue(lpMovieEdit->x()));
	settings.setValue("movieEdit/y", QVariant::fromValue(lpMovieEdit->y()));
	if(this->isMaximized())
		settings.setValue("movieEdit/maximized", QVariant::fromValue(true));
	else
		settings.setValue("movieEdit/maximized", QVariant::fromValue(false));

	if(ret == QDialog::Rejected)
	{
		delete lpMovieEdit;
		return(false);
	}

	delete lpMovieEdit;

	return(true);
}

void cMainWindow::onActionAddGlobal()
{
	if(ui->m_lpMainTab->currentIndex() == 0)
		onActionAdd();
	else
		onActionMovieAdd();
}

void cMainWindow::onActionAdd()
{
	cSearch*	lpSearch	= new cSearch(this);

	QSettings	settings;
	qint16		iX		= settings.value("search/x", QVariant::fromValue(-1)).toInt();
	qint16		iY		= settings.value("search/y", QVariant::fromValue(-1)).toInt();
	qint16		iWidth	= settings.value("search/width", QVariant::fromValue(-1)).toInt();
	qint16		iHeight	= settings.value("search/height", QVariant::fromValue(-1)).toInt();

	if(iX != -1 && iY != -1)
		lpSearch->move(iX, iY);
	if(iWidth != -1 && iHeight != -1)
		lpSearch->resize(iWidth, iHeight);

	if(lpSearch->exec() == QDialog::Rejected)
	{
		delete lpSearch;
		return;
	}

	settings.setValue("search/width", QVariant::fromValue(lpSearch->size().width()));
	settings.setValue("search/height", QVariant::fromValue(lpSearch->size().height()));
	settings.setValue("search/x", QVariant::fromValue(lpSearch->x()));
	settings.setValue("search/y", QVariant::fromValue(lpSearch->y()));

	qint32	id				= lpSearch->id();
	QString	szPlaceholder	= lpSearch->placeholderName();
	bool	bPlaceholder	= lpSearch->placeholder();
	qint16	iYear			= lpSearch->year();

	delete lpSearch;

	cSerie*	lpSerie			= 0;

	cMessageAnimateDialog*	lpDialog	= new cMessageAnimateDialog(this);
	lpDialog->setTitle("Refresh");
	lpDialog->setMessage("Loading");
	lpDialog->show();

	if(!bPlaceholder)
	{
		if(id == -1)
			return;

		cTheMovieDBV3		movieDB3;

		lpSerie	= movieDB3.loadSerie(id, "de-AT");
		if(!lpSerie)
			lpSerie	= movieDB3.loadSerie(id, "en");

		delete lpDialog;

		QString	szDownload;
		if(!runEdit(lpSerie, szDownload))
			return;

		lpDialog	= new cMessageAnimateDialog(this);
		lpDialog->setTitle("Update");
		lpDialog->setMessage("Updating");
		lpDialog->show();

		lpSerie->save(m_db);
	}
	else
	{
		lpSerie	= new cSerie;
		lpSerie->setSeriesName(szPlaceholder);

		qint32	iMax	= 0;
		QSqlQuery	query;
		if(query.exec("SELECT MAX(seriesID) FROM serie;"))
		{
			query.next();
			if(query.isValid())
				iMax	= query.value(0).toInt();
		}
		if(iMax < 1000000)
			iMax	= 1000000;
		else
			iMax++;
		lpSerie->setSeriesID(iMax);
		lpSerie->setFirstAired(QDate(iYear, 1, 1));
		lpSerie->save(m_db);
	}
	m_serieList.add(lpSerie);
	std::sort(m_serieList.begin(), m_serieList.end(), serieSort);

	m_szOldSelected	= lpSerie->seriesName();
	displaySeries();

	delete lpDialog;
}

void cMainWindow::onActionMovieAdd()
{
	cMovieSearch*	lpSearch	= new cMovieSearch(this);

	QSettings	settings;
	qint16		iX		= settings.value("movieSearch/x", QVariant::fromValue(-1)).toInt();
	qint16		iY		= settings.value("movieSearch/y", QVariant::fromValue(-1)).toInt();
	qint16		iWidth	= settings.value("movieSearch/width", QVariant::fromValue(-1)).toInt();
	qint16		iHeight	= settings.value("movieSearch/height", QVariant::fromValue(-1)).toInt();

	if(iX != -1 && iY != -1)
		lpSearch->move(iX, iY);
	if(iWidth != -1 && iHeight != -1)
		lpSearch->resize(iWidth, iHeight);

	if(lpSearch->exec() == QDialog::Rejected)
	{
		delete lpSearch;
		return;
	}

	settings.setValue("movieSearch/width", QVariant::fromValue(lpSearch->size().width()));
	settings.setValue("movieSearch/height", QVariant::fromValue(lpSearch->size().height()));
	settings.setValue("movieSearch/x", QVariant::fromValue(lpSearch->x()));
	settings.setValue("movieSearch/y", QVariant::fromValue(lpSearch->y()));

	qint32	id				= lpSearch->id();
	QString	szPlaceholder	= lpSearch->placeholderName();
	bool	bPlaceholder	= lpSearch->placeholder();
	qint16	iYear			= lpSearch->year();

	delete lpSearch;

	cMovie*	lpMovie			= 0;

	cMessageAnimateDialog*	lpDialog	= new cMessageAnimateDialog(this);
	lpDialog->setTitle("Refresh");
	lpDialog->setMessage("Loading");
	lpDialog->show();

	if(!bPlaceholder)
	{
		if(id == -1)
			return;

		cTheMovieDBV3		movieDB3;

		lpMovie	= movieDB3.loadMovie(id, "de-AT");
		if(!lpMovie)
			lpMovie	= movieDB3.loadMovie(id, "en");

		delete lpDialog;

		if(!runMovieEdit(lpMovie))
			return;

		lpDialog	= new cMessageAnimateDialog(this);
		lpDialog->setTitle("Update");
		lpDialog->setMessage("Updating");
		lpDialog->show();

		lpMovie->save(m_db);
	}
	else
	{
		lpMovie	= new cMovie;
		lpMovie->setMovieTitle(szPlaceholder);

		qint32	iMax	= 0;
		QSqlQuery	query;
		if(query.exec("SELECT MAX(movieID) FROM movie;"))
		{
			query.next();
			if(query.isValid())
				iMax	= query.value(0).toInt();
		}
		if(iMax < 1000000)
			iMax	= 1000000;
		else
			iMax++;
		lpMovie->setMovieID(iMax);
		lpMovie->setReleaseDate(QString("%1-01-01").arg(iYear));
		lpMovie->save(m_db);
	}

	loadMoviesDB();
	displayMovies();

	delete lpDialog;
}

void cMainWindow::onActionUpdateAll()
{
	cSerieList	serieList	= m_serieList;

	if(serieList.count())
		doUpdate(serieList);
}

void cMainWindow::onActionMovieUpdateAll()
{
}

void cMainWindow::onActionUpdateUnfinished()
{
	cSerieList	serieList;

	for(int x = 0;x < m_serieList.count();x++)
	{
		cSerie*	lpSerie	= m_serieList.at(x);
		if(lpSerie->status().compare("Ended", Qt::CaseInsensitive))
			serieList.add(lpSerie);
	}
	if(serieList.count())
		doUpdate(serieList);
}

void cMainWindow::onActionUpdate()
{
	cSerieList	serieList;

	for(int x = 0;x < ui->m_lpSeriesList1->selectionModel()->selectedRows().count();x++)
	{
		cSerie*	lpSerie	= ui->m_lpSeriesList1->selectionModel()->selectedRows().at(x).data(Qt::UserRole).value<cSerie*>();
		serieList.add(lpSerie);
	}
	if(serieList.count())
		doUpdate(serieList);
}

void cMainWindow::onActionMovieUpdate()
{
}

void cMainWindow::doUpdate(cSerieList& serieList)
{
	if(serieList.count())
	{
		if(ui->m_lpSeriesList1->selectionModel()->selectedRows().count() == 1)
			m_szOldSelected	= m_lpSeriesListModel->itemFromIndex(ui->m_lpSeriesList1->selectionModel()->selectedIndexes().at(1))->text();

		m_lpMessageDialog	= new cMessageDialog(this);
		m_lpMessageDialog->setWindowTitle("Update");
		m_lpMessageDialog->setMessage("Updating");
		m_lpMessageDialog->setProgress(0, serieList.count());
		m_lpMessageDialog->show();

		m_lpUpdateThread		= new cUpdateThread;
		m_lpUpdateThread->setData(m_lpMessageDialog, serieList, m_db);

		connect(m_lpUpdateThread, SIGNAL(finished()), this, SLOT(updateDone()));
		connect(m_lpUpdateThread, SIGNAL(updateMessage(QString,qint32)), this, SLOT(updateMessage(QString,qint32)));
		connect(m_lpUpdateThread, SIGNAL(updateAppendMessage(QString)), this, SLOT(updateAppendMessage(QString)));

		m_lpUpdateThread->start();
	}
}

void cMainWindow::updateMessage(const QString& szMessage, const qint32& iProgress)
{
	m_lpMessageDialog->setMessage(szMessage);
	m_lpMessageDialog->setProgress(iProgress);
}

void cMainWindow::updateAppendMessage(const QString& szMessage)
{
	m_lpMessageDialog->addMessage(szMessage);
}

void cMainWindow::updateDone()
{
	if(m_lpUpdateThread)
		delete m_lpUpdateThread;
	m_lpUpdateThread	= 0;

	loadDB();
	displaySeries();

	if(m_lpMessageDialog)
		delete m_lpMessageDialog;
	m_lpMessageDialog	= 0;
}

void cMainWindow::onActionDelete()
{
	if(QMessageBox::question(this, "Delete Serie", "Are you sure?") == QMessageBox::No)
		return;

	cSerie*	lpSerie	= m_lpSeriesListModel->itemFromIndex(ui->m_lpSeriesList1->selectionModel()->selectedRows().at(0))->data(Qt::UserRole).value<cSerie*>();
	if(!lpSerie)
		return;

	cMessageAnimateDialog*	lpDialog	= new cMessageAnimateDialog(this);
	lpDialog->setTitle("Delete");
	lpDialog->setMessage("Deleting");
	lpDialog->show();

	lpSerie->del(m_db);

	loadDB();
	displaySeries();

	delete lpDialog;
}

void cMainWindow::onActionMovieDelete()
{
	if(QMessageBox::question(this, "Delete Movie", "Are you sure?") == QMessageBox::No)
		return;

	cMovie*	lpMovie	= m_lpMoviesListModel->itemFromIndex(ui->m_lpMoviesList->selectionModel()->selectedRows().at(0))->data(Qt::UserRole).value<cMovie*>();
	if(!lpMovie)
		return;

	cMessageAnimateDialog*	lpDialog	= new cMessageAnimateDialog(this);
	lpDialog->setTitle("Delete");
	lpDialog->setMessage("Deleting");
	lpDialog->show();

	lpMovie->del(m_db);

	loadMoviesDB();
	displayMovies();

	delete lpDialog;
}

void cMainWindow::onActionEdit()
{
	QModelIndex	index	= ui->m_lpSeriesList1->selectionModel()->selectedRows().at(0);

//	cSerie*	lpSerie	= m_lpSeriesListModel->itemFromIndex(ui->m_lpSeriesList1->selectionModel()->selectedRows().at(0))->data(Qt::UserRole).value<cSerie*>();
	cSerie*	lpSerie	= m_lpSeriesListModel->itemFromIndex(index)->data(Qt::UserRole).value<cSerie*>();
	if(!lpSerie)
		return;

	QString	szDownload;
	if(!runEdit(lpSerie, szDownload))
		return;

	cMessageAnimateDialog*	lpDialog	= new cMessageAnimateDialog(this);
	lpDialog->setTitle("Update");
	lpDialog->setMessage("Updating");
	lpDialog->show();

	//lpSerie->setDownload(szDownload);
	//lpSerie->updateState();

	lpSerie->del(m_db);
	lpSerie->save(m_db);

	emit m_lpSeriesListModel->layoutChanged();

	delete lpDialog;
}

void cMainWindow::onActionMovieEdit()
{
	cMovie*	lpMovie	= m_lpMoviesListModel->itemFromIndex(ui->m_lpMoviesList->selectionModel()->selectedRows().at(0))->data(Qt::UserRole).value<cMovie*>();
	if(!lpMovie)
		return;

	QString	szDownload;
	if(!runMovieEdit(lpMovie))
		return;

	cMessageAnimateDialog*	lpDialog	= new cMessageAnimateDialog(this);
	lpDialog->setTitle("Update");
	lpDialog->setMessage("Updating");
	lpDialog->show();

	lpMovie->del(m_db);
	lpMovie->save(m_db);

	m_szOldSelected	= lpMovie->movieTitle();
	loadMoviesDB();
	displayMovies();

	delete lpDialog;
}

void cMainWindow::on_m_lpSeriesList1_doubleClicked(const QModelIndex &/*index*/)
{
	onActionEdit();
}

void cMainWindow::on_m_lpSeriesList2_doubleClicked(const QModelIndex &/*index*/)
{
	onActionEdit();
}

void cMainWindow::on_m_lpMoviesList_doubleClicked(const QModelIndex &index)
{
	onActionMovieEdit();
}
/*
void cMainWindow::onActionGotoIMDB()
{
	if(ui->m_lpSeriesList1->selectionModel()->selectedRows().count())
	{
		cSerie*	lpSerie	= m_lpSeriesListModel->itemFromIndex(ui->m_lpSeriesList1->selectionModel()->selectedRows().at(0))->data(Qt::UserRole).value<cSerie*>();
		if(lpSerie)
		{
			QString	link	= QString("http://www.imdb.com/title/%1").arg(lpSerie->imdbID());
			QDesktopServices::openUrl(QUrl(link));
		}
	}
}
*/
void cMainWindow::onActionMovieGotoIMDB()
{
	if(ui->m_lpMoviesList->selectionModel()->selectedRows().count())
	{
		cMovie*	lpMovie	= m_lpMoviesListModel->itemFromIndex(ui->m_lpMoviesList->selectionModel()->selectedRows().at(0))->data(Qt::UserRole).value<cMovie*>();
		if(lpMovie)
		{
			QString	link	= QString("http://www.imdb.com/title/%1").arg(lpMovie->imdbID());
			QDesktopServices::openUrl(QUrl(link));
		}
	}
}

void cMainWindow::onActionGotoDownload()
{
	if(ui->m_lpSeriesList1->selectionModel()->selectedRows().count())
	{
		cSerie*	lpSerie	= m_lpSeriesListModel->itemFromIndex(ui->m_lpSeriesList1->selectionModel()->selectedRows().at(0))->data(Qt::UserRole).value<cSerie*>();
		if(lpSerie)
		{
			QString	link	= lpSerie->download();
			QDesktopServices::openUrl(QUrl(link));
		}
	}
}

void cMainWindow::onActionCopyDownload()
{
	if(ui->m_lpSeriesList1->selectionModel()->selectedRows().count())
	{
		cSerie*	lpSerie	= m_lpSeriesListModel->itemFromIndex(ui->m_lpSeriesList1->selectionModel()->selectedRows().at(0))->data(Qt::UserRole).value<cSerie*>();
		if(lpSerie)
		{
			QString		link		= lpSerie->download();
			QClipboard*	lpClipboard	= QApplication::clipboard();
			lpClipboard->setText(link);
		}
	}
}

void cMainWindow::onActionLoadPictures()
{
	QList<cSerie*>	serieList;

	if(ui->m_lpSeriesList1->selectionModel()->selectedRows().count())
	{
		for(int z = 0;z < ui->m_lpSeriesList1->selectionModel()->selectedRows().count();z++)
			serieList.append(m_lpSeriesListModel->itemFromIndex(ui->m_lpSeriesList1->selectionModel()->selectedRows().at(z))->data(Qt::UserRole).value<cSerie*>());
	}

	if(!serieList.count())
		return;

	qint16	iTotal		= 0;

	for(int z = 0;z < serieList.count();z++)
	{
		cSerie*	lpSerie	= serieList.at(z);
		for(int y = 0;y < lpSerie->seasonList().count();y++)
			iTotal += lpSerie->seasonList().at(y)->episodeCount();
	}

	m_lpMessageDialog	= new cMessageDialog(this);
	m_lpMessageDialog->setWindowTitle("Images");
	m_lpMessageDialog->setMessage("loading Images");
	m_lpMessageDialog->setProgress(0, iTotal-1);
	m_lpMessageDialog->show();

	m_lpPicturesThread		= new cPicturesThread;
	m_lpPicturesThread->setData(m_lpMessageDialog, serieList);

	connect(m_lpPicturesThread, SIGNAL(finished()), this, SLOT(picturesDone()));
	connect(m_lpPicturesThread, SIGNAL(picturesMessage(QString,qint32)), this, SLOT(picturesMessage(QString,qint32)));
	connect(m_lpPicturesThread, SIGNAL(picturesAppendMessage(QString)), this, SLOT(picturesAppendMessage(QString)));

	m_lpPicturesThread->start();
}

void cMainWindow::onActionMovieLoadPictures()
{
}

void cMainWindow::picturesMessage(const QString& szMessage, const qint32& iProgress)
{
	m_lpMessageDialog->setMessage(szMessage);
	m_lpMessageDialog->setProgress(iProgress);
}

void cMainWindow::picturesAppendMessage(const QString& szMessage)
{
	m_lpMessageDialog->addMessage(szMessage);
}

void cMainWindow::picturesDone()
{
	if(m_lpPicturesThread)
		delete m_lpPicturesThread;
	m_lpPicturesThread	= 0;

	if(m_lpMessageDialog)
		delete m_lpMessageDialog;
	m_lpMessageDialog	= 0;
}

void cMainWindow::on_m_lpSeriesList1_pressed(const QModelIndex &/*index*/)
{
	switch(QGuiApplication::mouseButtons())
	{
	case Qt::MiddleButton:
		if(ui->m_lpSeriesList1->selectionModel()->selectedRows().count() == 1)
		{
			cSerie*	lpSerie	= m_lpSeriesListModel->itemFromIndex(ui->m_lpSeriesList1->selectionModel()->selectedRows().at(0))->data(Qt::UserRole).value<cSerie*>();
			if(lpSerie)
			{
				if(!lpSerie->download().isEmpty())
					onActionGotoDownload();
			}
		}
		break;
	default:
		break;
	}
}

void cMainWindow::on_m_lpSeriesList2_pressed(const QModelIndex &/*index*/)
{
	switch(QGuiApplication::mouseButtons())
	{
	case Qt::MiddleButton:
		if(ui->m_lpSeriesList2->selectionModel()->selectedRows().count() == 1)
		{
			cSerie*	lpSerie	= m_lpSeriesListModel->itemFromIndex(ui->m_lpSeriesList2->selectionModel()->selectedRows().at(0))->data(Qt::UserRole).value<cSerie*>();
			if(lpSerie)
			{
				if(!lpSerie->download().isEmpty())
					onActionGotoDownload();
			}
		}
		break;
	default:
		break;
	}
}

void cMainWindow::selectionChanged1(const QItemSelection& /*selected*/, const QItemSelection& /*deselected*/)
{
	if(m_bProcessing)
		return;

	m_bProcessing	= true;

	QItemSelectionModel*	lp1			= ui->m_lpSeriesList1->selectionModel();
	QItemSelectionModel*	lp2			= ui->m_lpSeriesList2->selectionModel();
	QModelIndexList			selected1	= lp1->selectedIndexes();

	lp2->clearSelection();

	for(int z = 0;z < selected1.count();z++)
	{

		QStandardItem*	lpItem	= m_lpSeriesListModel->itemFromIndex(selected1.at(z));
		QModelIndex		index	= lpItem->index();
		lp2->select(index, QItemSelectionModel::Select);
	}

	m_bProcessing	= false;
}

void cMainWindow::selectionChanged2(const QItemSelection& /*selected*/, const QItemSelection& /*deselected*/)
{
	if(m_bProcessing)
		return;

	m_bProcessing	= true;

	QItemSelectionModel*	lp1			= ui->m_lpSeriesList1->selectionModel();
	QItemSelectionModel*	lp2			= ui->m_lpSeriesList2->selectionModel();
	QModelIndexList			selected2	= lp2->selectedIndexes();

	lp1->clearSelection();

	for(int z = 0;z < selected2.count();z++)
	{
		QStandardItem*	lpItem	= m_lpSeriesListModel->itemFromIndex(selected2.at(z));
		QModelIndex		index	= lpItem->index();
		lp1->select(index, QItemSelectionModel::Select);
	}

	m_bProcessing	= false;
}

void cMainWindow::scrollbarValueChanged1(int value)
{
	if(m_bProcessing)
		return;

	m_bProcessing	= true;

	ui->m_lpSeriesList2->verticalScrollBar()->setValue(value);

	m_bProcessing	= false;
}

void cMainWindow::scrollbarValueChanged2(int value)
{
	if(m_bProcessing)
		return;

	m_bProcessing	= true;

	ui->m_lpSeriesList1->verticalScrollBar()->setValue(value);

	m_bProcessing	= false;
}
