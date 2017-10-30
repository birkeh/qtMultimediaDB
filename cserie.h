#ifndef CSERIE_H
#define CSERIE_H


#include "cseason.h"

#include <QMetaType>
#include <QDate>
#include <QSqlDatabase>


class cSerie
{
public:
	cSerie();

	void			setSeriesName(const QString& szSeriesName);
	QString			seriesName();

	void			setOriginalName(const QString& szOriginalName);
	QString			originalName();

	void			setSeriesID(const qint32& iSeriesID);
	qint32			seriesID();

	void			setBackdropPath(const QString& szBackdropPath);
	QString			backdropPath();

	void			setCreatedBy(const QStringList& szCreatedBy);
	void			setCreatedBy(const QString& szCreatedBy);
	QStringList		createdBy();

	void			setHomepage(const QString& szHomepage);
	QString			homepage();

	void			setLastAired(const QString& szLAstAired);
	void			setLastAired(const QDate& lastAired);
	QDate			lastAired();

	void			setNetworks(const QStringList& szNetworks);
	void			setNetworks(const QString& szNetworks);
	QStringList		networks();

	void			setEpisodes(const qint16& iEpisodes);
	qint16			episodes();

	void			setSeasons(const qint16& iSeasons);
	qint16			seasons();

	void			setOriginCountries(const QStringList& szOriginCountries);
	void			setOriginCountries(const QString& szOriginCountries);
	QStringList		originCountries();

	void			setOriginalLanguage(const QString& szOriginalLanguage);
	QString			originalLanguage();

	void			setPopularity(const qreal& dPopularity);
	qreal			popularity();

	void			setPosterPath(const QString& szPosterPath);
	QString			posterPath();

	void			setProductionCompanies(const QStringList& szProductionCompanies);
	void			setProductionCompanies(const QString& szProductionCompanies);
	QStringList		productionCompanies();

	void			setType(const QString& szType);
	QString			type();

	void			setVoteAverage(const qreal& dVoteAverage);
	qreal			voteAverage();

	void			setVoteCount(const qint16& iVoteCount);
	qint16			voteCount();

	void			setOverview(const QString& szOverview);
	QString			overview();

	void			setFirstAired(const QString& szFirstAired);
	void			setFirstAired(const QDate& firstAired);
	QDate			firstAired();

	void			setCast(const QStringList& szCast);
	QStringList		cast();

	void			setCrew(const QStringList& szCrew);
	QStringList		crew();

	void			setGenre(const QString& szGenre);
	void			setGenre(const QStringList& szGenre);
	QStringList		genre();

	void			setStatus(const QString& szStatus);
	QString			status();

	void			setDownload(const QString& szDownload);
	QString			download();

	void			setCliffhanger(const bool& bCliffhanger);
	bool			cliffhanger();

	cSeason*		addSeason(const qint16& iSeason);
	QList<cSeason*>	seasonList();

	cSeason*		findSeason(const qint16& iSeason);

	qint16			minSeason();
	qint16			maxSeason();

	qint16			maxEpisode();

	cEpisode*		findEpisode(const qint32& id);

	bool			isValid();

	bool			save(QSqlDatabase& db);
	bool			del(QSqlDatabase& db);

	void			allInit();
	void			allProgress();
	void			allDone();

	void			seasonInit(QPushButton* lpButton);
	void			seasonProgress(QPushButton* lpButton);
	void			seasonDone(QPushButton* lpButton);

	void			updateState();
	void			deleteResources();
private:
	QString			m_szSeriesName;
	QString			m_szOriginalName;
	qint32			m_iSeriesID;
	QString			m_szBackdropPath;
	QStringList		m_szCreatedBy;
	QString			m_szHomepage;
	QDate			m_lastAired;
	QStringList		m_szNetworks;
	qint16			m_iEpisodes;
	qint16			m_iSeasons;
	QStringList		m_szOriginCountries;
	QString			m_szOriginalLanguage;
	qreal			m_dPopularity;
	QString			m_szPosterPath;
	QStringList		m_szProductionCompanies;
	QString			m_szType;
	qreal			m_dVoteAverage;
	qint16			m_iVoteCount;
	QString			m_szOverview;
	QDate			m_firstAired;
	QStringList		m_szCast;
	QStringList		m_szCrew;
	QStringList		m_szGenre;
	QString			m_szStatus;
	QString			m_szDownload;
	bool			m_bCliffhanger;
	QList<cSeason*>	m_seasonList;
};

Q_DECLARE_METATYPE(cSerie*)

class cSerieList : public QList<cSerie*>
{
public:
	cSerie*			add(const qint32& iID);
	cSerie*			add(cSerie* lpSerie);

	qint16			minSeason();
	qint16			maxSeason();

	qint16			maxEpisode();
};

#endif // CSERIE_H
