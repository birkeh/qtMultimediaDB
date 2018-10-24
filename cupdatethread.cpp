#include "cupdatethread.h"
#include "cseason.h"
#include "cepisode.h"
#include "cmessagedialog.h"
#include "cthemoviedbv3.h"

#include <QMessageBox>

#include <QDebug>
#include <QTime>


cUpdateThread::cUpdateThread() :
	m_bStop(false)
{
}

void cUpdateThread::stop()
{
	QMutexLocker	locker(&m_mutex);
	m_bStop	= true;
	emit updateAppendMessage(" - cancel pending ...");
}

void cUpdateThread::run()
{
	QTime	timer;
	timer.restart();
	QString szFailed;

	for(int x = 0;x < m_serieList.count();x++)
	{
		cSerie*	lpSerie	= m_serieList.at(x);
		if(lpSerie)
		{
			emit updateMessage(lpSerie->seriesName(), x);
			cTheMovieDBV3	theMovieDB;
			cSerie*			lpSerieNew;

			if(lpSerie->seriesID() != -1 && lpSerie->seriesID() < 1000000)
			{
				lpSerieNew	= theMovieDB.loadSerie(lpSerie->seriesID(), "de-DE");
				if(!lpSerieNew)
					lpSerieNew = theMovieDB.loadSerie(lpSerie->seriesID(), "en");
				if(!lpSerieNew)
				{
					if(szFailed.length())
						szFailed += ", ";
					szFailed += lpSerie->seriesName();
					continue;
				}
				lpSerieNew->loadFanart();
				cFanartList	fanartList		= lpSerie->fanartList();
				cFanartList	fanartListNew	= lpSerieNew->fanartList();
				for(int x = 0;x < fanartListNew.count();x++)
				{
					cFanart*	lpFanartNew	= fanartListNew.at(x);

					for(int y = 0;y < fanartList.count();y++)
					{
						cFanart*	lpFanart	= fanartList.at(y);
						if(lpFanartNew->id() == lpFanart->id())
						{
							lpFanartNew->setActive(lpFanart->active());
							break;
						}
					}
				}
				lpSerieNew->setDownload(lpSerie->download());
				for(int x = 0;x < lpSerieNew->seasonList().count();x++)
				{
					cSeason*	lpSeasonNew	= lpSerieNew->seasonList().at(x);
					for(int y = 0;y < lpSeasonNew->episodeList().count();y++)
					{
						cEpisode*	lpEpisodeNew	= lpSeasonNew->episodeList().at(y);
						cEpisode*	lpEpisode		= lpSerie->findEpisode(lpEpisodeNew->id());
						if(lpEpisode)
							lpEpisodeNew->setState(lpEpisode->state());
					}
				}
                lpSerieNew->setCliffhanger(lpSerie->cliffhanger());
				if(!m_db.isOpen())
					m_db.open();
				lpSerie->del(m_db);
				lpSerieNew->save(m_db);
			}
		}

		QMutexLocker	locker(&m_mutex);
		if(m_bStop)
			break;
		msleep(10);
	}
	if(szFailed.length())
	{
		QMessageBox	msgBox;
		msgBox.setText(szFailed + QString(" has failed to update."));
		msgBox.exec();
	}
}

void cUpdateThread::setData(cMessageDialog* lpMessageDialog, const cSerieList &serieList, const QSqlDatabase& db)
{
	connect(lpMessageDialog->cancelButton(), SIGNAL(clicked()), this, SLOT(stop()));
	m_serieList	= serieList;
	m_db		= db;
}
