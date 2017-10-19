#ifndef CMOVIE_H
#define CMOVIE_H


#include <QMetaType>
#include <QDate>
#include <QSqlDatabase>
#include <QStringList>
#include <QMap>


class cMovie
{
public:
	cMovie();

	void					setMovieTitle(const QString& szTitle);
	QString					movieTitle();

	void					setMovieID(const qint32 iID);
	qint32					movieID();

	void					setOriginalTitle(const QString& szOriginalTitle);
	QString					originalTitle();

	void					setReleaseDate(const QString& szDate);
	QDate					releaseDate();

	void					setAdult(const bool bAdult);
	bool					adult();

	void					setBackdropPath(const QString& szBackdropPath);
	QString					backdropPath();

	void					setBelongsToCollection(const QString& szBelongsToCollection);
	QString					belongsToCollection();

	void					setBudget(const qreal dBudget);
	qreal					budget();

	void					setGenres(const QString& szGenres);
	void					setGenres(const QStringList& szGenres);
	QStringList				genres();

	void					setHomepage(const QString& szHomepage);
	QString					homepage();

	void					setIMDBID(const QString& szIMDBID);
	QString					imdbID();

	void					setOriginalLanguage(const QString& szOriginalLanguage);
	QString					originalLanguage();

	void					setOverview(const QString& szOverview);
	QString					overview();

	void					setPopularity(const qreal dPopularity);
	qreal					popularity();

	void					setPosterPath(const QString& szPosterPath);
	QString					posterPath();

	void					setProductionCompanies(const QString& szProductionCompanies);
	void					setProductionCompanies(const QStringList& szProductionCompanies);
	QStringList				productionCompanies();

	void					setProductionCountries(const QString& szProductionCountries);
	void					setProductionCountries(const QStringList& szProductionCountries);
	QStringList				productionCountries();

	void					setRevenue(const qreal dRevenue);
	qreal					revenue();

	void					setRuntime(const qint32 iRuntime);
	qint32					runtime();

	void					setSpokenLanguages(const QString& szSpokenLanguages);
	void					setSpokenLanguages(const QStringList& szSpokenLanguages);
	QStringList				spokenLanguages();

	void					setStatus(const QString& szStatus);
	QString					status();

	void					setTagline(const QString& szTagline);
	QString					tagline();

	void					setVideo(const bool bVideo);
	bool					video();

	void					setVoteAverage(const qreal dVoteAverage);
	qreal					voteAverage();

	void					setVoteCount(const qint32 iVoteCount);
	qint32					voteCount();

	void					setCast(const QStringList& szCast);
	QStringList				cast();

	void					setCrew(const QStringList& szCrew);
	QStringList				crew();

	bool					save(QSqlDatabase& db);
	bool					del(QSqlDatabase& db);
private:
	QString					m_szMovieTitle;
	qint32					m_iID;
	QString					m_szOriginalTitle;
	QDate					m_releaseDate;

	bool					m_bAdult;
	QString					m_szBackdropPath;
	QString					m_szBelongsToCollection;
	qreal					m_dBudget;
	QStringList				m_szGenres;
	QString					m_szHomepage;
	QString					m_szIMDBID;
	QString					m_szOriginalLanguage;
	QString					m_szOverview;
	qreal					m_dPopularity;
	QString					m_szPosterPath;
	QStringList				m_szProductionCompanies;
	QStringList				m_szProductionCountries;
	qreal					m_dRevenue;
	qint32					m_iRuntime;
	QStringList				m_szSpokenLanguages;
	QString					m_szStatus;
	QString					m_szTagline;
	bool					m_bVideo;
	qreal					m_dVoteAverage;
	qint32					m_iVoteCount;
	QStringList				m_szCast;
	QStringList				m_szCrew;
};

Q_DECLARE_METATYPE(cMovie*)

class cMovieList : public QList<cMovie*>
{
public:
	cMovie*			add(const qint32& iID);
	cMovie*			add(cMovie* lpMovie);
};

#endif // CMOVIE_H
