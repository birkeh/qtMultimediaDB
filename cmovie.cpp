#include "cmovie.h"
#include "cfanarttv.h"
#include "common.h"

#include <QStringList>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>

#include <QDebug>
#include <QMap>
#include <QMapIterator>


cMovie::cMovie() :
	m_szOverview(QString("")),
	m_dPopularity(0.0),
	m_szPosterPath(QString("")),
	m_dRevenue(0.0),
	m_iRuntime(0),
	m_szStatus(QString("")),
	m_szTagline(QString("")),
	m_bVideo(false),
	m_dVoteAverage(0.0),
	m_iVoteCount(0),
	m_iState(StateInit),
	m_szLocalPath(""),
	m_szResolution("")
{
}

void cMovie::setMovieTitle(const QString& szTitle)
{
	m_szMovieTitle	= szTitle;
}

QString cMovie::movieTitle()
{
	return(m_szMovieTitle);
}

void cMovie::setMovieID(const qint32 iID)
{
	m_iID	= iID;
}

qint32 cMovie::movieID()
{
	return(m_iID);
}

void cMovie::setOriginalTitle(const QString& szOriginalTitle)
{
	m_szOriginalTitle	= szOriginalTitle;
}

QString cMovie::originalTitle()
{
	return(m_szOriginalTitle);
}

void cMovie::setReleaseDate(const QString& szDate)
{
	m_releaseDate	= QDate::fromString(szDate, "yyyy-MM-dd");
}

QDate cMovie::releaseDate()
{
	return(m_releaseDate);
}

void cMovie::setAdult(const bool bAdult)
{
	m_bAdult	= bAdult;
}

bool cMovie::adult()
{
	return(m_bAdult);
}

void cMovie::setBackdropPath(const QString& szBackdropPath)
{
	m_szBackdropPath	= szBackdropPath;
}

QString cMovie::backdropPath()
{
	return(m_szBackdropPath);
}

void cMovie::setBelongsToCollection(const QString& szBelongsToCollection)
{
	m_szBelongsToCollection	= szBelongsToCollection;
}

QString cMovie::belongsToCollection()
{
	return(m_szBelongsToCollection);
}

void cMovie::setBudget(const qreal dBudget)
{
	m_dBudget	= dBudget;
}

qreal cMovie::budget()
{
	return(m_dBudget);
}

void cMovie::setGenres(const QString& szGenres)
{
	m_szGenres	= szGenres.split(",");
}

void cMovie::setGenres(const QStringList& szGenres)
{
	m_szGenres	= cleanList(szGenres);
}

QStringList cMovie::genres()
{
	return(m_szGenres);
}

void cMovie::setHomepage(const QString& szHomepage)
{
	m_szHomepage	= szHomepage;
}

QString cMovie::homepage()
{
	return(m_szHomepage);
}

void cMovie::setIMDBID(const QString &szIMDBID)
{
	m_szIMDBID	= szIMDBID;
}

QString cMovie::imdbID()
{
	return(m_szIMDBID);
}

void cMovie::setOriginalLanguage(const QString& szOriginalLanguage)
{
	m_szOriginalLanguage	= szOriginalLanguage;
}

QString cMovie::originalLanguage()
{
	return(m_szOriginalLanguage);
}

void cMovie::setOverview(const QString& szOverview)
{
	m_szOverview	= szOverview;
}

QString cMovie::overview()
{
	return(m_szOverview);
}

void cMovie::setPopularity(const qreal dPopularity)
{
	m_dPopularity	= dPopularity;
}

qreal cMovie::popularity()
{
	return(m_dPopularity);
}

void cMovie::setPosterPath(const QString& szPosterPath)
{
	m_szPosterPath	= szPosterPath;
}

QString cMovie::posterPath()
{
	return(m_szPosterPath);
}

void cMovie::setProductionCompanies(const QString& szProductionCompanies)
{
	m_szProductionCompanies	= szProductionCompanies.split(",");
}

void cMovie::setProductionCompanies(const QStringList& szProductionCompanies)
{
	m_szProductionCompanies	= cleanList(szProductionCompanies);
}

QStringList cMovie::productionCompanies()
{
	return(m_szProductionCompanies);
}

void cMovie::setProductionCountries(const QString& szProductionCountries)
{
	m_szProductionCountries	= szProductionCountries.split(",");
}

void cMovie::setProductionCountries(const QStringList& szProductionCountries)
{
	m_szProductionCountries	= cleanList(szProductionCountries);
}

QStringList cMovie::productionCountries()
{
	return(m_szProductionCountries);
}

void cMovie::setRevenue(const qreal dRevenue)
{
	m_dRevenue	= dRevenue;
}

qreal cMovie::revenue()
{
	return(m_dRevenue);
}

void cMovie::setRuntime(const qint32 iRuntime)
{
	m_iRuntime	= iRuntime;
}

qint32 cMovie::runtime()
{
	return(m_iRuntime);
}

void cMovie::setSpokenLanguages(const QString& szSpokenLanguages)
{
	m_szSpokenLanguages	= szSpokenLanguages.split(",");
}

void cMovie::setSpokenLanguages(const QStringList& szSpokenLanguages)
{
	m_szSpokenLanguages	= cleanList(szSpokenLanguages);
}

QStringList cMovie::spokenLanguages()
{
	return(m_szSpokenLanguages);
}

void cMovie::setStatus(const QString& szStatus)
{
	m_szStatus	= szStatus;
}

QString cMovie::status()
{
	return(m_szStatus);
}

void cMovie::setTagline(const QString& szTagline)
{
	m_szTagline	= szTagline;
}

QString cMovie::tagline()
{
	return(m_szTagline);
}

void cMovie::setVideo(const bool bVideo)
{
	m_bVideo	= bVideo;
}

bool cMovie::video()
{
	return(m_bVideo);
}

void cMovie::setVoteAverage(const qreal dVoteAverage)
{
	m_dVoteAverage	= dVoteAverage;
}

qreal cMovie::voteAverage()
{
	return(m_dVoteAverage);
}

void cMovie::setVoteCount(const qint32 iVoteCount)
{
	m_iVoteCount	= iVoteCount;
}

qint32 cMovie::voteCount()
{
	return(m_iVoteCount);
}

void cMovie::setCast(const QStringList &szCast)
{
	m_szCast	= cleanList(szCast);
}

QStringList cMovie::cast()
{
	return(m_szCast);
}

void cMovie::setCrew(const QStringList &szCrew)
{
	m_szCrew	= cleanList(szCrew);
}

QStringList cMovie::crew()
{
	return(m_szCrew);
}

void cMovie::setState(const State state)
{
	m_iState	= state;
}

cMovie::State cMovie::state()
{
	return(m_iState);
}

void cMovie::setLocalPath(const QString& szLocalPath)
{
	m_szLocalPath	= szLocalPath;
}

QString cMovie::localPath()
{
	return(m_szLocalPath);
}

void cMovie::setResolution(const QString& szResolution)
{
	m_szResolution	= szResolution;
}

QString cMovie::resolution()
{
	return(m_szResolution);
}

void cMovie::loadFanart()
{
	cFanartTV	fanartTV;
	m_fanartList	= fanartTV.loadFanartMovie(imdbID());
}

cFanartList cMovie::fanartList()
{
	return(m_fanartList);
}

void cMovie::setFanartList(const cFanartList& fanartList)
{
	m_fanartList	= fanartList;
}

bool cMovie::save(QSqlDatabase &db)
{
	QSqlQuery	query;
	QSqlQuery	queryMovie;
	QSqlQuery	queryFanart;

	queryMovie.prepare("INSERT INTO movie (movieID,movieTitle,originalTitle,backdropPath,posterPath,overview,releaseDate,genre,imdbid,originalLanguage,popularity,productionCompanies,productionCountries,voteAverage,voteCount,adult,belongsToCollection,budget,homepage,revenue,runtime,spokenLanguages,status,tagline,video,cast,crew,state,localPath,resolution)"
						  " VALUES (:movieID,:movieTitle,:originalTitle,:backdropPath,:posterPath,:overview,:releaseDate,:genre,:imdbid,:originalLanguage,:popularity,:productionCompanies,:productionCountries,:voteAverage,:voteCount,:adult,:belongsToCollection,:budget,:homepage,:revenue,:runtime,:spokenLanguages,:status,:tagline,:video,:cast,:crew,:state,:localPath,:resolution);");
	queryFanart.prepare("INSERT INTO fanart (id,type,url,language,likes,discType,disc,active,movieID) VALUES (:id,:type,:url,:language,:likes,:discType,:disc,:active,:movieID);");

	db.transaction();
	query.exec(QString("SELECT movieID FROM movie WHERE movieID=%1;").arg(movieID()));
	if(!query.next())
	{
		queryMovie.bindValue(":movieID", movieID());
		queryMovie.bindValue(":movieTitle", movieTitle());
		queryMovie.bindValue(":originalTitle", originalTitle());
		queryMovie.bindValue(":backdropPath", backdropPath());
		queryMovie.bindValue(":posterPath", posterPath());
		queryMovie.bindValue(":overview", overview());
		queryMovie.bindValue(":releaseDate", releaseDate());
		queryMovie.bindValue(":genre", genres().join(","));
		queryMovie.bindValue(":imdbid", imdbID());
		queryMovie.bindValue(":originalLanguage", originalLanguage());
		queryMovie.bindValue(":popularity", popularity());
		queryMovie.bindValue(":productionCompanies", productionCompanies().join(","));
		queryMovie.bindValue(":productionCountries", productionCountries().join(","));
		queryMovie.bindValue(":voteAverage", voteAverage());
		queryMovie.bindValue(":voteCount", voteCount());
		queryMovie.bindValue(":adult", adult());
		queryMovie.bindValue(":belongsToCollection", belongsToCollection());
		queryMovie.bindValue(":budget", budget());
		queryMovie.bindValue(":homepage", homepage());
		queryMovie.bindValue(":revenue", revenue());
		queryMovie.bindValue(":runtime", runtime());
		queryMovie.bindValue(":spokenLanguages", spokenLanguages().join(","));
		queryMovie.bindValue(":status", status());
		queryMovie.bindValue(":tagline", tagline());
		queryMovie.bindValue(":video", video());
		queryMovie.bindValue(":cast", cast().join("|"));
		queryMovie.bindValue(":crew", crew().join("|"));
		queryMovie.bindValue(":state", state());
		queryMovie.bindValue(":localPath", localPath());
		queryMovie.bindValue(":resolution", resolution());

		if(queryMovie.exec())
		{
			for(int x = 0;x < m_fanartList.count();x++)
			{
				cFanart*	lpFanart	= m_fanartList.at(x);
				queryFanart.bindValue(":id", lpFanart->id());
				queryFanart.bindValue(":type", lpFanart->type());
				queryFanart.bindValue(":url", lpFanart->url());
				queryFanart.bindValue(":language", lpFanart->language());
				queryFanart.bindValue(":likes", lpFanart->likes());
				queryFanart.bindValue(":discType", lpFanart->discType());
				queryFanart.bindValue(":disc", lpFanart->disc());
				queryFanart.bindValue(":active", lpFanart->active());
				queryFanart.bindValue(":movieID", movieID());
				if(queryFanart.exec())
				{
				}
				else
					qDebug() << queryFanart.lastError().text();
			}
		}
		else
			qDebug() << queryMovie.lastError().text();
	}
	db.commit();

	return(true);
}

bool cMovie::del(QSqlDatabase& db)
{
	QSqlQuery			query;

	db.transaction();

	if(m_fanartList.count())
	{
		query.prepare("DELETE FROM fanart WHERE movieID=:movieID;");
		query.bindValue(":movieID", movieID());
		query.exec();
	}

	query.prepare("DELETE FROM movie WHERE movieID=:movieID;");
	query.bindValue(":movieID", movieID());
	query.exec();

	db.commit();

	return(true);
}

cMovie* cMovieList::add(const qint32& iID)
{
	cMovie*	lpNew	= find(iID);
	if(!lpNew)
		lpNew	= new cMovie;
	lpNew->setMovieID(iID);
	append(lpNew);
	return(lpNew);
}

cMovie* cMovieList::add(cMovie* lpMovie)
{
	for(int z = 0;z < count();z++)
	{
		if(at(z) == lpMovie)
			return(nullptr);
	}
	append(lpMovie);
	return(lpMovie);
}

cMovie* cMovieList::find(const qint32& iID)
{
	for(int z = 0;z < count();z++)
	{
		if(at(z)->movieID() == iID)
			return(at(z));
	}
	return(nullptr);
}
