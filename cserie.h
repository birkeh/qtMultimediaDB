#ifndef CSERIE_H
#define CSERIE_H


#include "cseason.h"
#include "cfanart.h"

#include <QMetaType>
#include <QDate>
#include <QSqlDatabase>


/*!
 \brief

 \class cSerie cserie.h "cserie.h"
*/
class cSerie
{
public:
	cSerie();

	/*!
	 \brief

	 \fn setSeriesName
	 \param szSeriesName
	*/
	void			setSeriesName(const QString& szSeriesName);
	/*!
	 \brief

	 \fn seriesName
	 \return QString
	*/
	QString			seriesName();

	/*!
	 \brief

	 \fn setOriginalName
	 \param szOriginalName
	*/
	void			setOriginalName(const QString& szOriginalName);
	/*!
	 \brief

	 \fn originalName
	 \return QString
	*/
	QString			originalName();

	/*!
	 \brief

	 \fn setSeriesID
	 \param iSeriesID
	*/
	void			setSeriesID(const qint32& iSeriesID);
	/*!
	 \brief

	 \fn seriesID
	 \return qint32
	*/
	qint32			seriesID();

	/*!
	 \brief

	 \fn setBackdropPath
	 \param szBackdropPath
	*/
	void			setBackdropPath(const QString& szBackdropPath);
	/*!
	 \brief

	 \fn backdropPath
	 \return QString
	*/
	QString			backdropPath();

	/*!
	 \brief

	 \fn setCreatedBy
	 \param szCreatedBy
	*/
	void			setCreatedBy(const QStringList& szCreatedBy);
	/*!
	 \brief

	 \fn setCreatedBy
	 \param szCreatedBy
	*/
	void			setCreatedBy(const QString& szCreatedBy);
	/*!
	 \brief

	 \fn createdBy
	 \return QStringList
	*/
	QStringList		createdBy();

	/*!
	 \brief

	 \fn setHomepage
	 \param szHomepage
	*/
	void			setHomepage(const QString& szHomepage);
	/*!
	 \brief

	 \fn homepage
	 \return QString
	*/
	QString			homepage();

	/*!
	 \brief

	 \fn setLastAired
	 \param szLAstAired
	*/
	void			setLastAired(const QString& szLAstAired);
	/*!
	 \brief

	 \fn setLastAired
	 \param lastAired
	*/
	void			setLastAired(const QDate& lastAired);
	/*!
	 \brief

	 \fn lastAired
	 \return QDate
	*/
	QDate			lastAired();

	/*!
	 \brief

	 \fn setLanguages
	 \param szLanguages
	*/
	void			setLanguages(const QString& szLanguages);
	/*!
	 \brief

	 \fn setLanguages
	 \param szLanguages
	*/
	void			setLanguages(const QStringList& szLanguages);
	/*!
	 \brief

	 \fn languages
	 \return QStringList
	*/
	QStringList		languages();

	/*!
	 \brief

	 \fn setNetworks
	 \param szNetworks
	*/
	void			setNetworks(const QStringList& szNetworks);
	/*!
	 \brief

	 \fn setNetworks
	 \param szNetworks
	*/
	void			setNetworks(const QString& szNetworks);
	/*!
	 \brief

	 \fn networks
	 \return QStringList
	*/
	QStringList		networks();

	/*!
	 \brief

	 \fn setEpisodes
	 \param iEpisodes
	*/
	void			setEpisodes(const qint32& iEpisodes);
	/*!
	 \brief

	 \fn episodes
	 \return qint32
	*/
	qint32			episodes();

	/*!
	 \brief

	 \fn setSeasons
	 \param iSeasons
	*/
	void			setSeasons(const qint32& iSeasons);
	/*!
	 \brief

	 \fn seasons
	 \return qint32
	*/
	qint32			seasons();

	/*!
	 \brief

	 \fn setOriginCountries
	 \param szOriginCountries
	*/
	void			setOriginCountries(const QStringList& szOriginCountries);
	/*!
	 \brief

	 \fn setOriginCountries
	 \param szOriginCountries
	*/
	void			setOriginCountries(const QString& szOriginCountries);
	/*!
	 \brief

	 \fn originCountries
	 \return QStringList
	*/
	QStringList		originCountries();

	/*!
	 \brief

	 \fn setOriginalLanguage
	 \param szOriginalLanguage
	*/
	void			setOriginalLanguage(const QString& szOriginalLanguage);
	/*!
	 \brief

	 \fn originalLanguage
	 \return QString
	*/
	QString			originalLanguage();

	/*!
	 \brief

	 \fn setPopularity
	 \param dPopularity
	*/
	void			setPopularity(const qreal& dPopularity);
	/*!
	 \brief

	 \fn popularity
	 \return qreal
	*/
	qreal			popularity();

	/*!
	 \brief

	 \fn setPosterPath
	 \param szPosterPath
	*/
	void			setPosterPath(const QString& szPosterPath);
	/*!
	 \brief

	 \fn posterPath
	 \return QString
	*/
	QString			posterPath();

	/*!
	 \brief

	 \fn setProductionCompanies
	 \param szProductionCompanies
	*/
	void			setProductionCompanies(const QStringList& szProductionCompanies);
	/*!
	 \brief

	 \fn setProductionCompanies
	 \param szProductionCompanies
	*/
	void			setProductionCompanies(const QString& szProductionCompanies);
	/*!
	 \brief

	 \fn productionCompanies
	 \return QStringList
	*/
	QStringList		productionCompanies();

	/*!
	 \brief

	 \fn setType
	 \param szType
	*/
	void			setType(const QString& szType);
	/*!
	 \brief

	 \fn type
	 \return QString
	*/
	QString			type();

	/*!
	 \brief

	 \fn setVoteAverage
	 \param dVoteAverage
	*/
	void			setVoteAverage(const qreal& dVoteAverage);
	/*!
	 \brief

	 \fn voteAverage
	 \return qreal
	*/
	qreal			voteAverage();

	/*!
	 \brief

	 \fn setVoteCount
	 \param iVoteCount
	*/
	void			setVoteCount(const qint32& iVoteCount);
	/*!
	 \brief

	 \fn voteCount
	 \return qint32
	*/
	qint32			voteCount();

	/*!
	 \brief

	 \fn setOverview
	 \param szOverview
	*/
	void			setOverview(const QString& szOverview);
	/*!
	 \brief

	 \fn overview
	 \return QString
	*/
	QString			overview();

	/*!
	 \brief

	 \fn setFirstAired
	 \param szFirstAired
	*/
	void			setFirstAired(const QString& szFirstAired);
	/*!
	 \brief

	 \fn setFirstAired
	 \param firstAired
	*/
	void			setFirstAired(const QDate& firstAired);
	/*!
	 \brief

	 \fn firstAired
	 \return QDate
	*/
	QDate			firstAired();

	/*!
	 \brief

	 \fn setCast
	 \param szCast
	*/
	void			setCast(const QStringList& szCast);
	/*!
	 \brief

	 \fn cast
	 \return QStringList
	*/
	QStringList		cast();

	/*!
	 \brief

	 \fn setCrew
	 \param szCrew
	*/
	void			setCrew(const QStringList& szCrew);
	/*!
	 \brief

	 \fn crew
	 \return QStringList
	*/
	QStringList		crew();

	/*!
	 \brief

	 \fn setGenre
	 \param szGenre
	*/
	void			setGenre(const QString& szGenre);
	/*!
	 \brief

	 \fn setGenre
	 \param szGenre
	*/
	void			setGenre(const QStringList& szGenre);
	/*!
	 \brief

	 \fn genre
	 \return QStringList
	*/
	QStringList		genre();

	/*!
	 \brief

	 \fn setIMDBID
	 \param szIMDBID
	*/
	void			setIMDBID(const QString& szIMDBID);
	/*!
	 \brief

	 \fn IMDBID
	 \return QString
	*/
	QString			IMDBID();

	/*!
	 \brief

	 \fn setFreebaseMID
	 \param szFreebaseMID
	*/
	void			setFreebaseMID(const QString& szFreebaseMID);
	/*!
	 \brief

	 \fn freebaseMID
	 \return QString
	*/
	QString			freebaseMID();

	/*!
	 \brief

	 \fn setFreebaseID
	 \param szFreebaseID
	*/
	void			setFreebaseID(const QString& szFreebaseID);
	/*!
	 \brief

	 \fn freebaseID
	 \return QString
	*/
	QString			freebaseID();

	/*!
	 \brief

	 \fn setTVDBID
	 \param iTVDBID
	*/
	void			setTVDBID(const qint32& iTVDBID);
	/*!
	 \brief

	 \fn tvdbID
	 \return qint32
	*/
	qint32			tvdbID();

	/*!
	 \brief

	 \fn setTVRageID
	 \param iTVRageID
	*/
	void			setTVRageID(const qint32& iTVRageID);
	/*!
	 \brief

	 \fn tvrageID
	 \return qint32
	*/
	qint32			tvrageID();

	/*!
	 \brief

	 \fn setStatus
	 \param szStatus
	*/
	void			setStatus(const QString& szStatus);
	/*!
	 \brief

	 \fn status
	 \return QString
	*/
	QString			status();

	/*!
	 \brief

	 \fn setDownload
	 \param szDownload
	*/
	void			setDownload(const QString& szDownload);
	/*!
	 \brief

	 \fn download
	 \return QString
	*/
	QString			download();

	/*!
	 \brief

	 \fn setLocalPath
	 \param szLocalPath
	*/
	void			setLocalPath(const QString& szLocalPath);
	/*!
	 \brief

	 \fn localPath
	 \return QString
	*/
	QString			localPath();

	/*!
	 \brief

	 \fn setCliffhanger
	 \param bCliffhanger
	*/

	/*!
	 \brief

	 \fn setResolution
	 \param szResolution
	*/
	void			setResolution(const QString& szResolution);
	/*!
	 \brief

	 \fn resolution
	 \return QString
	*/
	QString			resolution();

	/*!
	 \brief

	 \fn setCliffhanger
	 \param bCliffhanger
	*/

	void			setCliffhanger(const bool& bCliffhanger);
	/*!
	 \brief

	 \fn cliffhanger
	 \return bool
	*/
	bool			cliffhanger();

	/*!
	 \brief

	 \fn addSeason
	 \param iSeason
	 \return cSeason
	*/
	cSeason*		addSeason(const qint32& iSeason);
	/*!
	 \brief

	 \fn seasonList
	 \return QList<cSeason *>
	*/
	QList<cSeason*>	seasonList();

	/*!
	 \brief

	 \fn findSeason
	 \param iSeason
	 \return cSeason
	*/
	cSeason*		findSeason(const qint32& iSeason);

	/*!
	 \brief

	 \fn minSeason
	 \return qint32
	*/
	qint32			minSeason();
	/*!
	 \brief

	 \fn maxSeason
	 \return qint32
	*/
	qint32			maxSeason();

	/*!
	 \brief

	 \fn maxEpisode
	 \return qint32
	*/
	qint32			maxEpisode();

	/*!
	 \brief

	 \fn findEpisode
	 \param id
	 \return cEpisode
	*/
	cEpisode*		findEpisode(const qint32& id);

	/*!
	 \brief

	 \fn isValid
	 \return bool
	*/
	bool			isValid();

	/*!
	 \brief

	 \fn hasInit
	 \return bool
	*/
	bool			hasInit();
	/*!
	 \brief

	 \fn hasProgress
	 \return bool
	*/
	bool			hasProgress();
	/*!
	 \brief

	 \fn hasDone
	 \return bool
	*/
	bool			hasDone();

	/*!
	 \brief

	 \fn save
	 \param db
	 \return bool
	*/
	bool			save(QSqlDatabase& db);
	/*!
	 \brief

	 \fn del
	 \param db
	 \return bool
	*/
	bool			del(QSqlDatabase& db);

	/*!
	 \brief

	 \fn allInit
	*/
	void			allInit();
	/*!
	 \brief

	 \fn allProgress
	*/
	void			allProgress();
	/*!
	 \brief

	 \fn allDone
	*/
	void			allDone();

	/*!
	 \brief

	 \fn seasonInit
	 \param lpButton
	*/
	void			seasonInit(QPushButton* lpButton);
	/*!
	 \brief

	 \fn seasonProgress
	 \param lpButton
	*/
	void			seasonProgress(QPushButton* lpButton);
	/*!
	 \brief

	 \fn seasonDone
	 \param lpButton
	*/
	void			seasonDone(QPushButton* lpButton);

	/*!
	 \brief

	 \fn updateState
	*/
	void			updateState();
	/*!
	 \brief

	 \fn deleteResources
	*/
	void			deleteResources();

	/*!
	 \brief

	 \fn loadFanart
	*/
	void			loadFanart();
	/*!
	 \brief

	 \fn setFanartList
	 \param fanartList
	*/
	void			setFanartList(const cFanartList& fanartList);
	/*!
	 \brief

	 \fn fanartList
	 \return cFanartList
	*/
	cFanartList		fanartList();

	/*!
	 \brief

	 \fn fanartBanner
	 \return QString
	*/
	QString			fanartBanner();
private:
	QString			m_szSeriesName; /*!< TODO: describe */
	QString			m_szOriginalName; /*!< TODO: describe */
	qint32			m_iSeriesID; /*!< TODO: describe */
	QString			m_szBackdropPath; /*!< TODO: describe */
	QStringList		m_szCreatedBy; /*!< TODO: describe */
	QString			m_szHomepage; /*!< TODO: describe */
	QDate			m_lastAired; /*!< TODO: describe */
	QStringList		m_szLanguages; /*!< TODO: describe */
	QStringList		m_szNetworks; /*!< TODO: describe */
	qint32			m_iEpisodes; /*!< TODO: describe */
	qint32			m_iSeasons; /*!< TODO: describe */
	QStringList		m_szOriginCountries; /*!< TODO: describe */
	QString			m_szOriginalLanguage; /*!< TODO: describe */
	qreal			m_dPopularity; /*!< TODO: describe */
	QString			m_szPosterPath; /*!< TODO: describe */
	QStringList		m_szProductionCompanies; /*!< TODO: describe */
	QString			m_szType; /*!< TODO: describe */
	qreal			m_dVoteAverage; /*!< TODO: describe */
	qint32			m_iVoteCount; /*!< TODO: describe */
	QString			m_szOverview; /*!< TODO: describe */
	QDate			m_firstAired; /*!< TODO: describe */
	QStringList		m_szCast; /*!< TODO: describe */
	QStringList		m_szCrew; /*!< TODO: describe */
	QStringList		m_szGenre; /*!< TODO: describe */
	QString			m_szIMDBID; /*!< TODO: describe */
	QString			m_szFreebaseMID; /*!< TODO: describe */
	QString			m_szFreebaseID; /*!< TODO: describe */
	qint32			m_iTVDBID; /*!< TODO: describe */
	qint32			m_iTVRageID; /*!< TODO: describe */
	QString			m_szStatus; /*!< TODO: describe */
	QString			m_szDownload; /*!< TODO: describe */
	QString			m_szLocalPath; /*!< TODO: describe */
	QString			m_szResolution; /*!< TODO: describe */
	bool			m_bCliffhanger; /*!< TODO: describe */
	cFanartList		m_fanartList; /*!< TODO: describe */
	QList<cSeason*>	m_seasonList; /*!< TODO: describe */
};

Q_DECLARE_METATYPE(cSerie*)

/*!
 \brief

 \class cSerieList cserie.h "cserie.h"
*/
class cSerieList : public QList<cSerie*>
{
public:
	/*!
	 \brief

	 \fn add
	 \param iID
	 \return cSerie
	*/
	cSerie*			add(const qint32& iID);
	/*!
	 \brief

	 \fn add
	 \param lpSerie
	 \return cSerie
	*/
	cSerie*			add(cSerie* lpSerie);

	/*!
	 \brief

	 \fn find
	 \param iID
	 \return cSerie
	*/
	cSerie*			find(const qint32& iID);

	/*!
	 \brief

	 \fn minSeason
	 \return qint32
	*/
	qint32			minSeason();
	/*!
	 \brief

	 \fn maxSeason
	 \return qint32
	*/
	qint32			maxSeason();

	/*!
	 \brief

	 \fn maxEpisode
	 \return qint32
	*/
	qint32			maxEpisode();
};

#endif // CSERIE_H
