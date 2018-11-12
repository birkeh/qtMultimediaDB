#ifndef CMOVIE_H
#define CMOVIE_H


#include "cfanart.h"

#include <QMetaType>
#include <QDate>
#include <QSqlDatabase>
#include <QStringList>
#include <QMap>


/*!
 \brief

 \class cMovie cmovie.h "cmovie.h"
*/
class cMovie
{
public:
	/*!
	 \brief

	 \enum State
	*/
	enum State
	{
		StateUnknown	= 0,
		StateInit		= 1,
		StateProgress	= 2,
		StateDone		= 3,
	};

	cMovie();

	/*!
	 \brief

	 \fn setMovieTitle
	 \param szTitle
	*/
	void					setMovieTitle(const QString& szTitle);
	/*!
	 \brief

	 \fn movieTitle
	 \return QString
	*/
	QString					movieTitle();

	/*!
	 \brief

	 \fn setMovieID
	 \param iID
	*/
	void					setMovieID(const qint32 iID);
	/*!
	 \brief

	 \fn movieID
	 \return qint32
	*/
	qint32					movieID();

	/*!
	 \brief

	 \fn setOriginalTitle
	 \param szOriginalTitle
	*/
	void					setOriginalTitle(const QString& szOriginalTitle);
	/*!
	 \brief

	 \fn originalTitle
	 \return QString
	*/
	QString					originalTitle();

	/*!
	 \brief

	 \fn setReleaseDate
	 \param szDate
	*/
	void					setReleaseDate(const QString& szDate);
	/*!
	 \brief

	 \fn releaseDate
	 \return QDate
	*/
	QDate					releaseDate();

	/*!
	 \brief

	 \fn setAdult
	 \param bAdult
	*/
	void					setAdult(const bool bAdult);
	/*!
	 \brief

	 \fn adult
	 \return bool
	*/
	bool					adult();

	/*!
	 \brief

	 \fn setBackdropPath
	 \param szBackdropPath
	*/
	void					setBackdropPath(const QString& szBackdropPath);
	/*!
	 \brief

	 \fn backdropPath
	 \return QString
	*/
	QString					backdropPath();

	/*!
	 \brief

	 \fn setBelongsToCollection
	 \param szBelongsToCollection
	*/
	void					setBelongsToCollection(const QString& szBelongsToCollection);
	/*!
	 \brief

	 \fn belongsToCollection
	 \return QString
	*/
	QString					belongsToCollection();

	/*!
	 \brief

	 \fn setBudget
	 \param dBudget
	*/
	void					setBudget(const qreal dBudget);
	/*!
	 \brief

	 \fn budget
	 \return qreal
	*/
	qreal					budget();

	/*!
	 \brief

	 \fn setGenres
	 \param szGenres
	*/
	void					setGenres(const QString& szGenres);
	/*!
	 \brief

	 \fn setGenres
	 \param szGenres
	*/
	void					setGenres(const QStringList& szGenres);
	/*!
	 \brief

	 \fn genres
	 \return QStringList
	*/
	QStringList				genres();

	/*!
	 \brief

	 \fn setHomepage
	 \param szHomepage
	*/
	void					setHomepage(const QString& szHomepage);
	/*!
	 \brief

	 \fn homepage
	 \return QString
	*/
	QString					homepage();

	/*!
	 \brief

	 \fn setIMDBID
	 \param szIMDBID
	*/
	void					setIMDBID(const QString& szIMDBID);
	/*!
	 \brief

	 \fn imdbID
	 \return QString
	*/
	QString					imdbID();

	/*!
	 \brief

	 \fn setOriginalLanguage
	 \param szOriginalLanguage
	*/
	void					setOriginalLanguage(const QString& szOriginalLanguage);
	/*!
	 \brief

	 \fn originalLanguage
	 \return QString
	*/
	QString					originalLanguage();

	/*!
	 \brief

	 \fn setOverview
	 \param szOverview
	*/
	void					setOverview(const QString& szOverview);
	/*!
	 \brief

	 \fn overview
	 \return QString
	*/
	QString					overview();

	/*!
	 \brief

	 \fn setPopularity
	 \param dPopularity
	*/
	void					setPopularity(const qreal dPopularity);
	/*!
	 \brief

	 \fn popularity
	 \return qreal
	*/
	qreal					popularity();

	/*!
	 \brief

	 \fn setPosterPath
	 \param szPosterPath
	*/
	void					setPosterPath(const QString& szPosterPath);
	/*!
	 \brief

	 \fn posterPath
	 \return QString
	*/
	QString					posterPath();

	/*!
	 \brief

	 \fn setProductionCompanies
	 \param szProductionCompanies
	*/
	void					setProductionCompanies(const QString& szProductionCompanies);
	/*!
	 \brief

	 \fn setProductionCompanies
	 \param szProductionCompanies
	*/
	void					setProductionCompanies(const QStringList& szProductionCompanies);
	/*!
	 \brief

	 \fn productionCompanies
	 \return QStringList
	*/
	QStringList				productionCompanies();

	/*!
	 \brief

	 \fn setProductionCountries
	 \param szProductionCountries
	*/
	void					setProductionCountries(const QString& szProductionCountries);
	/*!
	 \brief

	 \fn setProductionCountries
	 \param szProductionCountries
	*/
	void					setProductionCountries(const QStringList& szProductionCountries);
	/*!
	 \brief

	 \fn productionCountries
	 \return QStringList
	*/
	QStringList				productionCountries();

	/*!
	 \brief

	 \fn setRevenue
	 \param dRevenue
	*/
	void					setRevenue(const qreal dRevenue);
	/*!
	 \brief

	 \fn revenue
	 \return qreal
	*/
	qreal					revenue();

	/*!
	 \brief

	 \fn setRuntime
	 \param iRuntime
	*/
	void					setRuntime(const qint32 iRuntime);
	/*!
	 \brief

	 \fn runtime
	 \return qint32
	*/
	qint32					runtime();

	/*!
	 \brief

	 \fn setSpokenLanguages
	 \param szSpokenLanguages
	*/
	void					setSpokenLanguages(const QString& szSpokenLanguages);
	/*!
	 \brief

	 \fn setSpokenLanguages
	 \param szSpokenLanguages
	*/
	void					setSpokenLanguages(const QStringList& szSpokenLanguages);
	/*!
	 \brief

	 \fn spokenLanguages
	 \return QStringList
	*/
	QStringList				spokenLanguages();

	/*!
	 \brief

	 \fn setStatus
	 \param szStatus
	*/
	void					setStatus(const QString& szStatus);
	/*!
	 \brief

	 \fn status
	 \return QString
	*/
	QString					status();

	/*!
	 \brief

	 \fn setTagline
	 \param szTagline
	*/
	void					setTagline(const QString& szTagline);
	/*!
	 \brief

	 \fn tagline
	 \return QString
	*/
	QString					tagline();

	/*!
	 \brief

	 \fn setVideo
	 \param bVideo
	*/
	void					setVideo(const bool bVideo);
	/*!
	 \brief

	 \fn video
	 \return bool
	*/
	bool					video();

	/*!
	 \brief

	 \fn setVoteAverage
	 \param dVoteAverage
	*/
	void					setVoteAverage(const qreal dVoteAverage);
	/*!
	 \brief

	 \fn voteAverage
	 \return qreal
	*/
	qreal					voteAverage();

	/*!
	 \brief

	 \fn setVoteCount
	 \param iVoteCount
	*/
	void					setVoteCount(const qint32 iVoteCount);
	/*!
	 \brief

	 \fn voteCount
	 \return qint32
	*/
	qint32					voteCount();

	/*!
	 \brief

	 \fn setCast
	 \param szCast
	*/
	void					setCast(const QStringList& szCast);
	/*!
	 \brief

	 \fn cast
	 \return QStringList
	*/
	QStringList				cast();

	/*!
	 \brief

	 \fn setCrew
	 \param szCrew
	*/
	void					setCrew(const QStringList& szCrew);
	/*!
	 \brief

	 \fn crew
	 \return QStringList
	*/
	QStringList				crew();

	/*!
	 \brief

	 \fn setState
	 \param state
	*/
	void					setState(const State state);
	/*!
	 \brief

	 \fn state
	 \return State
	*/
	State					state();

	/*!
	 \brief

	 \fn save
	 \param db
	 \return bool
	*/
	bool					save(QSqlDatabase& db);
	/*!
	 \brief

	 \fn del
	 \param db
	 \return bool
	*/
	bool					del(QSqlDatabase& db);

	/*!
	 \brief

	 \fn loadFanart
	*/
	void					loadFanart();
	/*!
	 \brief

	 \fn setFanartList
	 \param fanartList
	*/
	void					setFanartList(const cFanartList& fanartList);
	/*!
	 \brief

	 \fn fanartList
	 \return cFanartList
	*/
	cFanartList				fanartList();
private:
	QString					m_szMovieTitle; /*!< TODO: describe */
	qint32					m_iID; /*!< TODO: describe */
	QString					m_szOriginalTitle; /*!< TODO: describe */
	QDate					m_releaseDate; /*!< TODO: describe */

	bool					m_bAdult; /*!< TODO: describe */
	QString					m_szBackdropPath; /*!< TODO: describe */
	QString					m_szBelongsToCollection; /*!< TODO: describe */
	qreal					m_dBudget; /*!< TODO: describe */
	QStringList				m_szGenres; /*!< TODO: describe */
	QString					m_szHomepage; /*!< TODO: describe */
	QString					m_szIMDBID; /*!< TODO: describe */
	QString					m_szOriginalLanguage; /*!< TODO: describe */
	QString					m_szOverview; /*!< TODO: describe */
	qreal					m_dPopularity; /*!< TODO: describe */
	QString					m_szPosterPath; /*!< TODO: describe */
	QStringList				m_szProductionCompanies; /*!< TODO: describe */
	QStringList				m_szProductionCountries; /*!< TODO: describe */
	qreal					m_dRevenue; /*!< TODO: describe */
	qint32					m_iRuntime; /*!< TODO: describe */
	QStringList				m_szSpokenLanguages; /*!< TODO: describe */
	QString					m_szStatus; /*!< TODO: describe */
	QString					m_szTagline; /*!< TODO: describe */
	bool					m_bVideo; /*!< TODO: describe */
	qreal					m_dVoteAverage; /*!< TODO: describe */
	qint32					m_iVoteCount; /*!< TODO: describe */
	QStringList				m_szCast; /*!< TODO: describe */
	QStringList				m_szCrew; /*!< TODO: describe */
	State					m_iState; /*!< TODO: describe */
	cFanartList				m_fanartList; /*!< TODO: describe */
};

Q_DECLARE_METATYPE(cMovie*)
Q_DECLARE_METATYPE(cMovie::State)

/*!
 \brief

 \class cMovieList cmovie.h "cmovie.h"
*/
class cMovieList : public QList<cMovie*>
{
public:
	/*!
	 \brief

	 \fn add
	 \param iID
	 \return cMovie
	*/
	cMovie*			add(const qint32& iID);
	/*!
	 \brief

	 \fn add
	 \param lpMovie
	 \return cMovie
	*/
	cMovie*			add(cMovie* lpMovie);
	/*!
	 \brief

	 \fn find
	 \param iID
	 \return cMovie
	*/
	cMovie*			find(const qint32& iID);
};

#endif // CMOVIE_H
