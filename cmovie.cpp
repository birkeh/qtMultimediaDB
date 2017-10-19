#include "cmovie.h"

#include <QStringList>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>

#include <QDebug>
#include <QMap>
#include <QMapIterator>


cMovie::cMovie()
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
	m_szGenres	= szGenres;
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
	m_szProductionCompanies	= szProductionCompanies;
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
	m_szProductionCountries	= szProductionCountries;
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
	m_szSpokenLanguages	= szSpokenLanguages;
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
	m_szCast	= szCast;
}

QStringList cMovie::cast()
{
	return(m_szCast);
}

void cMovie::setCrew(const QStringList &szCrew)
{
	m_szCrew	= szCrew;
}

QStringList cMovie::crew()
{
	return(m_szCrew);
}

bool cMovie::save(QSqlDatabase &db)
{
	QSqlQuery	query;
	QSqlQuery	queryMovie;

	queryMovie.prepare("INSERT INTO movie (movieID,movieTitle,originalTitle,backdropPath,posterPath,overview,releaseDate,genre,imdbid,originalLanguage,popularity,productionCompanies,productionCountries,voteAverage,voteCount,adult,belongsToCollection,budget,homepage,revenue,runtime,spokenLanguages,status,tagline,video,cast,crew)"
						  " VALUES (:movieID,:movieTitle,:originalTitle,:backdropPath,:posterPath,:overview,:releaseDate,:genre,:imdbid,:originalLanguage,:popularity,:productionCompanies,:productionCountries,:voteAverage,:voteCount,:adult,:belongsToCollection,:budget,:homepage,:revenue,:runtime,:spokenLanguages,:status,:tagline,:video,:cast,:crew);");

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

		if(queryMovie.exec())
		{
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
	query.prepare("DELETE FROM movie WHERE movieID=:movieID;");
	query.bindValue(":movieID", movieID());
	query.exec();

	db.commit();

	return(true);
}

cMovie* cMovieList::add(const qint32& iID)
{
	for(int z = 0;z < count();z++)
	{
		if(at(z)->movieID() == iID)
			return(at(z));
	}
	cMovie*	lpNew	= new cMovie;
	lpNew->setMovieID(iID);
	append(lpNew);
	return(lpNew);
}

cMovie* cMovieList::add(cMovie* lpMovie)
{
	for(int z = 0;z < count();z++)
	{
		if(at(z) == lpMovie)
			return(0);
	}
	append(lpMovie);
	return(lpMovie);
}
