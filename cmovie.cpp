#include "cmovie.h"


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

void cMovie::setButget(const qreal dBudget)
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
