#include "cpicturesthread.h"
#include "cserie.h"
#include "cseason.h"
#include "cepisode.h"
#include "cmessagedialog.h"
#include "cmovieimage.h"

#include <QDebug>


cPicturesThread::cPicturesThread() :
	m_bStop(false)
{
}

void cPicturesThread::stop()
{
	QMutexLocker	locker(&m_mutex);
	m_bStop	= true;
	emit picturesAppendMessage(" - cancel pending ...");
}

void cPicturesThread::run()
{
	qint32	iCurrent	= 0;

	for(int z = 0;z < m_items.count();z++)
	{
		cSerie*	lpSerie	= m_items.at(z);
		if(lpSerie)
		{
			emit picturesMessage(lpSerie->seriesName(), iCurrent);

			cMovieImage	image;
			image.getImage(lpSerie->backdropPath());
			image.getImage(lpSerie->posterPath());

			for(int y = 0;y < lpSerie->seasonList().count();y++)
			{
				cSeason*	lpSeason;
				lpSeason	= lpSerie->seasonList().at(y);

				emit picturesMessage(QString("%1 - Season %2").arg(lpSerie->seriesName()).arg(lpSeason->seasonNumber()), iCurrent);

				for(int x = 0;x < lpSeason->episodeList().count();x++)
				{
					cEpisode*	lpEpisode	= lpSeason->episodeList().at(x);
					image.getImage(lpEpisode->stillPath());
					iCurrent++;

					QMutexLocker	locker(&m_mutex);
					if(m_bStop)
						break;
					msleep(10);
				}
			}
		}
	}
}

void cPicturesThread::setData(cMessageDialog* lpMessageDialog, const QList<cSerie *> &list)
{
	connect(lpMessageDialog->cancelButton(), SIGNAL(clicked()), this, SLOT(stop()));
	m_items		= list;
}
