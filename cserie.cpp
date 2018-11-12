#include "cserie.h"
#include "cfanarttv.h"
#include "common.h"

#include <QStringList>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

#include <QDebug>


cSerie::cSerie() :
	m_szSeriesName(""),
	m_szOriginalName(""),
	m_iSeriesID(-1),
	m_szBackdropPath(""),
	m_szHomepage(""),
	m_lastAired(QDate(1900, 1, 1)),
	m_iEpisodes(-1),
	m_iSeasons(-1),
	m_szOriginalLanguage(""),
	m_dPopularity(-1.0),
	m_szType(""),
	m_dVoteAverage(-1.0),
	m_iVoteCount(-1),
	m_szOverview(""),
	m_firstAired(QDate(1900, 1, 1)),
	m_szIMDBID(""),
	m_szFreebaseMID(""),
	m_szFreebaseID(""),
	m_iTVDBID(-1),
	m_iTVRageID(-1),
	m_szStatus(""),
	m_szDownload(""),
	m_bCliffhanger(false)
{
}

void cSerie::setSeriesName(const QString& szSeriesName)
{
	m_szSeriesName	= szSeriesName;
}

QString cSerie::seriesName()
{
	return(m_szSeriesName);
}

void cSerie::setOriginalName(const QString& szOriginalName)
{
	m_szOriginalName	= szOriginalName;
}

QString cSerie::originalName()
{
	return(m_szOriginalName);
}

void cSerie::setSeriesID(const qint32& iSeriesID)
{
	m_iSeriesID		= iSeriesID;
}

qint32 cSerie::seriesID()
{
	return(m_iSeriesID);
}

void cSerie::setBackdropPath(const QString& szBackdropPath)
{
	m_szBackdropPath	= szBackdropPath;
}

QString cSerie::backdropPath()
{
	return(m_szBackdropPath);
}

void cSerie::setCreatedBy(const QStringList& szCreatedBy)
{
	m_szCreatedBy	= cleanList(szCreatedBy);
}

void cSerie::setCreatedBy(const QString& szCreatedBy)
{
	m_szCreatedBy	= szCreatedBy.split(",");
}

QStringList cSerie::createdBy()
{
	return(m_szCreatedBy);
}

void cSerie::setHomepage(const QString& szHomepage)
{
	m_szHomepage	= szHomepage;
}

QString cSerie::homepage()
{
	return(m_szHomepage);
}

void cSerie::setLastAired(const QString& szLastAired)
{
	m_lastAired	= QDate::fromString(szLastAired, "yyyy-MM-dd");
}

void cSerie::setLastAired(const QDate& lastAired)
{
	m_lastAired		= lastAired;
}

QDate cSerie::lastAired()
{
	return(m_lastAired);
}

void cSerie::setLanguages(const QString& szLanguages)
{
	m_szLanguages	= szLanguages.split(",");
}

void cSerie::setLanguages(const QStringList& szLanguages)
{
	m_szLanguages	= szLanguages;
}

QStringList cSerie::languages()
{
	return(m_szLanguages);
}

void cSerie::setNetworks(const QStringList& szNetworks)
{
	m_szNetworks	= cleanList(szNetworks);
}
void cSerie::setNetworks(const QString& szNetworks)
{
	m_szNetworks	= szNetworks.split(",");
}

QStringList cSerie::networks()
{
	return(m_szNetworks);
}

void cSerie::setEpisodes(const qint32& iEpisodes)
{
	m_iEpisodes	= iEpisodes;
}

qint32 cSerie::episodes()
{
	return(m_iEpisodes);
}

void cSerie::setSeasons(const qint32& iSeasons)
{
	m_iSeasons	= iSeasons;
}

qint32 cSerie::seasons()
{
	return(m_iSeasons);
}

void cSerie::setOriginCountries(const QStringList& szOriginCountries)
{
	m_szOriginCountries	= cleanList(szOriginCountries);
}

void cSerie::setOriginCountries(const QString& szOriginCountries)
{
	m_szOriginCountries	= szOriginCountries.split(",");
}

QStringList cSerie::originCountries()
{
	return(m_szOriginCountries);
}

void cSerie::setOriginalLanguage(const QString& szOriginalLanguage)
{
	m_szOriginalLanguage	= szOriginalLanguage;
}

QString	 cSerie::originalLanguage()
{
	return(m_szOriginalLanguage);
}

void cSerie::setPopularity(const qreal& dPopularity)
{
	m_dPopularity	= dPopularity;
}

qreal cSerie::popularity()
{
	return(m_dPopularity);
}

void cSerie::setPosterPath(const QString& szPosterPath)
{
	m_szPosterPath	= szPosterPath;
}

QString cSerie::posterPath()
{
	return(m_szPosterPath);
}

void cSerie::setProductionCompanies(const QStringList& szProductionCompanies)
{
	m_szProductionCompanies	= cleanList(szProductionCompanies);
}

void cSerie::setProductionCompanies(const QString& szProductionCompanies)
{
	m_szProductionCompanies	= szProductionCompanies.split(",");
}

QStringList cSerie::productionCompanies()
{
	return(m_szProductionCompanies);
}

void cSerie::setType(const QString& szType)
{
	m_szType	= szType;
}
QString cSerie::type()
{
	return(m_szType);
}

void cSerie::setVoteAverage(const qreal& dVoteAverage)
{
	m_dVoteAverage	= dVoteAverage;
}

qreal cSerie::voteAverage()
{
	return(m_dVoteAverage);
}

void cSerie::setVoteCount(const qint32& iVoteCount)
{
	m_iVoteCount	= iVoteCount;
}

qint32 cSerie::voteCount()
{
	return(m_iVoteCount);
}

void cSerie::setOverview(const QString& szOverview)
{
	m_szOverview	= szOverview;
}

QString cSerie::overview()
{
	return(m_szOverview);
}

void cSerie::setFirstAired(const QString& szFirstAired)
{
	m_firstAired	= QDate::fromString(szFirstAired, "yyyy-MM-dd");
}

void cSerie::setFirstAired(const QDate& firstAired)
{
	m_firstAired	= firstAired;
}

QDate cSerie::firstAired()
{
	return(m_firstAired);
}

void cSerie::setCast(const QStringList& szCast)
{
	m_szCast	= szCast;
}

QStringList cSerie::cast()
{
	return(m_szCast);
}

void cSerie::setCrew(const QStringList& szCrew)
{
	m_szCrew	= szCrew;
}

QStringList cSerie::crew()
{
	return(m_szCrew);
}

void cSerie::setGenre(const QString& szGenre)
{
	m_szGenre	= szGenre.split(",");
	m_szGenre.removeAll("");
}

void cSerie::setGenre(const QStringList& szGenre)
{
	m_szGenre	= szGenre;
	m_szGenre.removeAll("");
}

QStringList cSerie::genre()
{
	return(m_szGenre);
}

void cSerie::setIMDBID(const QString& szIMDBID)
{
	m_szIMDBID	= szIMDBID;
}

QString cSerie::IMDBID()
{
	return(m_szIMDBID);
}

void cSerie::setFreebaseMID(const QString& szFreebaseMID)
{
	m_szFreebaseMID	= szFreebaseMID;
}

QString cSerie::freebaseMID()
{
	return(m_szFreebaseMID);
}

void cSerie::setFreebaseID(const QString& szFreebaseID)
{
	m_szFreebaseID	= szFreebaseID;
}

QString cSerie::freebaseID()
{
	return(m_szFreebaseID);
}

void cSerie::setTVDBID(const qint32& iTVDBID)
{
	m_iTVDBID	= iTVDBID;
}

qint32 cSerie::tvdbID()
{
	return(m_iTVDBID);
}

void cSerie::setTVRageID(const qint32& iTVRageID)
{
	m_iTVRageID	= iTVRageID;
}

qint32 cSerie::tvrageID()
{
	return(m_iTVRageID);
}

void cSerie::setStatus(const QString& szStatus)
{
	m_szStatus	= szStatus;
}

QString cSerie::status()
{
	return(m_szStatus);
}

void cSerie::setDownload(const QString& szDownload)
{
	m_szDownload	= szDownload;
}

QString cSerie::download()
{
	return(m_szDownload);
}

void cSerie::setCliffhanger(const bool& bCliffhanger)
{
	m_bCliffhanger	= bCliffhanger;
}

bool cSerie::cliffhanger()
{
	return(m_bCliffhanger);
}

cSeason* cSerie::addSeason(const qint32& iSeason)
{
	cSeason*	lpNew	= new cSeason;
	lpNew->setSeasonNumber(iSeason);
	lpNew->setSerie(this);
	m_seasonList.append(lpNew);
	return(lpNew);
}

cSeason* cSerie::findSeason(const qint32& iSeason)
{
	for(int z = 0;z < m_seasonList.count();z++)
	{
		if(m_seasonList.at(z)->seasonNumber() == iSeason)
			return(m_seasonList.at(z));
	}
	return(0);
}

QList<cSeason*> cSerie::seasonList()
{
	return(m_seasonList);
}

qint32 cSerie::minSeason()
{
	qint32	iMin	= 9999;
	for(int z = 0;z < m_seasonList.count();z++)
	{
		if(m_seasonList.at(z)->seasonNumber() < iMin)
			iMin	= m_seasonList.at(z)->seasonNumber();
	}
	if(iMin == 9999)
		return(-1);
	return(iMin);
}

qint32 cSerie::maxSeason()
{
	qint32	iMax	= -1;
	for(int z = 0;z < m_seasonList.count();z++)
	{
		if(m_seasonList.at(z)->seasonNumber() > iMax)
			iMax	= m_seasonList.at(z)->seasonNumber();
	}
	return(iMax);
}

cEpisode* cSerie::findEpisode(const qint32& id)
{
	for(int x = 0;x < m_seasonList.count();x++)
	{
		cSeason*	lpSeason	= m_seasonList.at(x);
		for(int y = 0;y < lpSeason->episodeList().count();y++)
		{
			cEpisode*	lpEpisode	= lpSeason->episodeList().at(y);
			if(lpEpisode->id() == id)
				return(lpEpisode);
		}
	}
	return(0);
}

bool cSerie::isValid()
{
	if(m_iSeriesID != -1 &&
		m_szSeriesName.length())
		return(true);
	return(false);
}

qint32 cSerie::maxEpisode()
{
	qint32	iMax	= -1;
	for(int z = 0;z < m_seasonList.count();z++)
	{
		if(m_seasonList.at(z)->episodeCount() > iMax)
			iMax	= m_seasonList.at(z)->episodeCount();
	}
	return(iMax);
}

bool cSerie::hasInit()
{
	for(int x = 0;x < m_seasonList.count();x++)
	{
		cSeason*	lpSeason	= m_seasonList.at(x);
		if(!lpSeason->seasonNumber())
			continue;

		if(lpSeason->hasInit())
			return(true);
	}
	return(false);
}

bool cSerie::hasProgress()
{
	for(int x = 0;x < m_seasonList.count();x++)
	{
		cSeason*	lpSeason	= m_seasonList.at(x);
		if(!lpSeason->seasonNumber())
			continue;

		if(lpSeason->hasProgress())
			return(true);
	}
	return(false);
}

bool cSerie::hasDone()
{
	for(int x = 0;x < m_seasonList.count();x++)
	{
		cSeason*	lpSeason	= m_seasonList.at(x);
		if(!lpSeason->seasonNumber())
			continue;

		if(lpSeason->hasDone())
			return(true);
	}
	return(false);
}

bool cSerie::save(QSqlDatabase &db)
{
	QSqlQuery	query;
	QSqlQuery	querySerie;
	QSqlQuery	querySeason;
	QSqlQuery	queryEpisode;
	QSqlQuery	queryFanart;

	querySerie.prepare("INSERT INTO serie (seriesID,seriesName,originalName,backdropPath,createdBy,homepage,lastAired,languages,networks,nrEpisodes,nrSeasons,originCountries,originalLanguage,popularity,posterPath,productionCompanies,type,voteAverage,voteCount,overview,firstAired,cast,crew,genre,imdbid,freebasemid,freebaseid,tvdbid,tvrageid,status,download,cliffhanger)"
						" VALUES (:seriesID,:seriesName,:originalName,:backdropPath,:createdBy,:homepage,:lastAired,:languages,:networks,:nrEpisodes,:nrSeasons,:originCountries,:originalLanguage,:popularity,:posterPath,:productionCompanies,:type,:voteAverage,:voteCount,:overview,:firstAired,:cast,:crew,:genre,:imdbid,:freebasemid,:freebaseid,:tvdbid,:tvrageid,:status,:download,:cliffhanger);");
	querySeason.prepare("INSERT INTO season (_id,airDate,name,overview,id,posterPath,seasonNumber,seriesID) VALUES (:_id,:airDate,:name,:overview,:id,:posterPath,:seasonNumber,:seriesID);");
	queryEpisode.prepare("INSERT INTO episode (id,name,episodeNumber,airDate,guestStars,overview,productioncode,seasonNumber,seasonID,seriesID,stillPath,voteAverage,voteCount,crew,state)"
						 " VALUES (:id,:name,:episodeNumber,:airDate,:guestStars,:overview,:productioncode,:seasonNumber,:seasonID,:seriesID,:stillPath,:voteAverage,:voteCount,:crew,:state);");
	queryFanart.prepare("INSERT INTO fanart (id,type,url,language,likes,season,active,seriesID) VALUES (:id,:type,:url,:language,:likes,:season,:active,:seriesID);");

	db.transaction();
	query.exec(QString("SELECT seriesID FROM serie WHERE seriesID=%1;").arg(seriesID()));
	if(!query.next())
	{
		query.prepare(QString("SELECT id FROM episode WHERE id=:id"));

		querySerie.bindValue(":seriesID", seriesID());
		querySerie.bindValue(":seriesName", seriesName());
		querySerie.bindValue(":originalName", originalName());
		querySerie.bindValue(":backdropPath", backdropPath());
		querySerie.bindValue(":createdBy", createdBy().join(","));
		querySerie.bindValue(":homepage", homepage());
		querySerie.bindValue(":lastAired", lastAired());
		querySerie.bindValue(":languages", languages().join(","));
		querySerie.bindValue(":networks", networks().join(","));
		querySerie.bindValue(":nrEpisodes", episodes());
		querySerie.bindValue(":nrSeasons", seasons());
		querySerie.bindValue(":originCountries", originCountries().join(","));
		querySerie.bindValue(":originalLanguage", originalLanguage());
		querySerie.bindValue(":popularity", popularity());
		querySerie.bindValue(":posterPath", posterPath());
		querySerie.bindValue(":productionCompanies", productionCompanies().join(","));
		querySerie.bindValue(":type", type());
		querySerie.bindValue(":voteAverage", voteAverage());
		querySerie.bindValue(":voteCount", voteCount());
		querySerie.bindValue(":overview", overview());
		querySerie.bindValue(":firstAired", firstAired());
		querySerie.bindValue(":cast", cast().join("|"));
		querySerie.bindValue(":crew", crew().join("|"));
		querySerie.bindValue(":genre", genre().join(","));
		querySerie.bindValue(":imdbid", IMDBID());
		querySerie.bindValue(":freebasemid", freebaseMID());
		querySerie.bindValue(":freebaseid", freebaseID());
		querySerie.bindValue(":tvdbid", tvdbID());
		querySerie.bindValue("tvrageid", tvrageID());
		querySerie.bindValue(":status", status());
		querySerie.bindValue(":download", download());
		querySerie.bindValue(":cliffhanger", cliffhanger());
		if(querySerie.exec())
		{
			QList<cSeason*>	seasonList1	= seasonList();
			for(int season = 0;season < seasonList1.count();season++)
			{
				cSeason*	lpSeason	= seasonList1.at(season);

				querySeason.bindValue(":_id", lpSeason->_id());
				querySeason.bindValue(":airDate", lpSeason->airDate());
				querySeason.bindValue(":name", lpSeason->name());
				querySeason.bindValue(":overview", lpSeason->overview());
				querySeason.bindValue(":id", lpSeason->id());
				querySeason.bindValue(":posterPath", lpSeason->posterPath());
				querySeason.bindValue(":seasonNumber", lpSeason->seasonNumber());
				querySeason.bindValue(":seriesID", seriesID());
				if(!querySeason.exec())
					qDebug() << querySeason.lastError().text();

				QList<cEpisode*>	episodeList	= lpSeason->episodeList();
				for(int episode = 0;episode < episodeList.count();episode++)
				{
					cEpisode*	lpEpisode	= episodeList.at(episode);

					queryEpisode.bindValue(":id", lpEpisode->id());
					queryEpisode.bindValue(":name", lpEpisode->name());
					queryEpisode.bindValue(":episodeNumber", lpEpisode->episodeNumber());
					queryEpisode.bindValue(":airDate", lpEpisode->airDate());
					queryEpisode.bindValue(":guestStars", lpEpisode->guestStars().join("|"));
					queryEpisode.bindValue(":overview", lpEpisode->overview());
					queryEpisode.bindValue(":productioncode", lpEpisode->productionCode());
					queryEpisode.bindValue(":seasonNumber", lpEpisode->seasonNumber());
					queryEpisode.bindValue(":seasonID", lpEpisode->seasonID());
					queryEpisode.bindValue(":seriesID", lpEpisode->seriesID());
					queryEpisode.bindValue(":stillPath", lpEpisode->stillPath());
					queryEpisode.bindValue(":voteAverage", lpEpisode->voteAverage());
					queryEpisode.bindValue(":voteCount", lpEpisode->voteCount());
					queryEpisode.bindValue(":crew", lpEpisode->crew().join("|"));
					queryEpisode.bindValue(":state", lpEpisode->state());
					if(queryEpisode.exec())
					{
					}
				}
			}

			for(int x = 0;x < m_fanartList.count();x++)
			{
				cFanart*	lpFanart	= m_fanartList.at(x);
				queryFanart.bindValue(":id", lpFanart->id());
				queryFanart.bindValue(":type", lpFanart->type());
				queryFanart.bindValue(":url", lpFanart->url());
				queryFanart.bindValue(":language", lpFanart->language());
				queryFanart.bindValue(":likes", lpFanart->likes());
				queryFanart.bindValue(":season", lpFanart->season());
				queryFanart.bindValue(":active", lpFanart->active());
				queryFanart.bindValue(":seriesID", seriesID());
				if(queryFanart.exec())
				{
				}
				else
					qDebug() << queryFanart.lastError().text();
			}
		}
		else
			qDebug() << querySerie.lastError().text();
	}
	db.commit();

	return(true);
}

bool cSerie::del(QSqlDatabase& db)
{
	QSqlQuery			query;

	db.transaction();

	if(m_fanartList.count())
	{
		query.prepare("DELETE FROM fanart WHERE seriesID=:seriesID;");
		query.bindValue(":seriesID", seriesID());
		query.exec();
	}

	query.prepare("DELETE FROM episode WHERE seriesID=:seriesID;");
	query.bindValue(":seriesID", seriesID());
	query.exec();

	query.prepare("DELETE FROM season WHERE seriesID=:seriesID;");
	query.bindValue(":seriesID", seriesID());
	query.exec();

	query.prepare("DELETE FROM serie WHERE seriesID=:seriesID;");
	query.bindValue(":seriesID", seriesID());
	query.exec();

	db.commit();
	return(true);
}

void cSerie::allInit()
{
	for(int z = 0;z < m_seasonList.count();z++)
		m_seasonList.at(z)->allInit();
}

void cSerie::allProgress()
{
	for(int z = 0;z < m_seasonList.count();z++)
		m_seasonList.at(z)->allProgress();
}

void cSerie::allDone()
{
	for(int z = 0;z < m_seasonList.count();z++)
		m_seasonList.at(z)->allDone();
}

void cSerie::seasonInit(QPushButton* lpButton)
{
	for(int z = 0;z < m_seasonList.count();z++)
	{
		if(m_seasonList.at(z)->allInitButton() == lpButton)
		{
			m_seasonList.at(z)->allInit();
			return;
		}
	}
}

void cSerie::seasonProgress(QPushButton* lpButton)
{
	for(int z = 0;z < m_seasonList.count();z++)
	{
		if(m_seasonList.at(z)->allProgressButton() == lpButton)
		{
			m_seasonList.at(z)->allProgress();
			return;
		}
	}
}

void cSerie::seasonDone(QPushButton* lpButton)
{
	for(int z = 0;z < m_seasonList.count();z++)
	{
		if(m_seasonList.at(z)->allDoneButton() == lpButton)
		{
			m_seasonList.at(z)->allDone();
			return;
		}
	}
}

void cSerie::updateState()
{
	for(int z = 0;z < m_seasonList.count();z++)
		m_seasonList.at(z)->updateState();
}

void cSerie::deleteResources()
{
	for(int z = 0;z < m_seasonList.count();z++)
		m_seasonList.at(z)->deleteResources();
}

void cSerie::loadFanart()
{
	cFanartTV	fanartTV;
	m_fanartList	= fanartTV.loadFanartSerie(tvdbID());
}

cFanartList cSerie::fanartList()
{
	return(m_fanartList);
}

void cSerie::setFanartList(const cFanartList& fanartList)
{
	m_fanartList	= fanartList;
}

QString cSerie::fanartBanner()
{
	for(int x = 0;x < m_fanartList.count();x++)
	{
		cFanart*	lpFanartTV	= m_fanartList.at(x);
		if(lpFanartTV->type() == cFanart::TypeTVBanner)
			return(lpFanartTV->url());
	}
	return("");
}

cSerie* cSerieList::add(const qint32& iID)
{
	cSerie*	lpNew	= find(iID);
	if(!lpNew)
		lpNew	= new cSerie;
	lpNew->setSeriesID(iID);
	append(lpNew);
	return(lpNew);
}

cSerie* cSerieList::add(cSerie* lpSerie)
{
	for(int z = 0;z < count();z++)
	{
		if(at(z) == lpSerie)
			return(nullptr);
	}
	append(lpSerie);
	return(lpSerie);
}

cSerie* cSerieList::find(const qint32& iID)
{
	for(int x = 0;x < count();x++)
	{
		if(at(x)->seriesID() == iID)
			return(at(x));
	}
	return(nullptr);
}

qint32 cSerieList::minSeason()
{
	qint32	iMin	= 9999;
	for(int z = 0;z < count();z++)
	{
		if(at(z)->minSeason() < iMin)
			iMin	= at(z)->minSeason();
	}
	if(iMin == 9999 || iMin < 0)
		return(0);

	return(iMin);
}

qint32 cSerieList::maxSeason()
{
	qint32	iMax	= -1;
	for(int z = 0;z < count();z++)
	{
		if(at(z)->maxSeason() > iMax)
			iMax	= at(z)->maxSeason();
	}

	if(iMax < 0)
		return(0);

	return(iMax);
}

qint32 cSerieList::maxEpisode()
{
	qint32	iMax	= -1;
	for(int z = 0;z < count();z++)
	{
		if(at(z)->maxEpisode() > iMax)
			iMax	= at(z)->maxEpisode();
	}

	if(iMax < 0)
		return(0);

	return(iMax);
}
