#ifndef CSEASON_H
#define CSEASON_H


#include "cepisode.h"

#include <QMetaType>
#include <QList>

#include <QGroupBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpacerItem>


class cSerie;

class cSeason
{
public:
	cSeason();
	~cSeason();

	void				set_ID(const qint16& _iID);
	qint16				_id();

	void				setAirDate(const QString& szAirDate);
	void				setAirDate(const QDate&   airDate);
	QDate				airDate();

	void				setName(const QString& szName);
	QString				name();

	void				setOverview(const QString& szOverview);
	QString				overview();

	void				setID(const qint16& iID);
	qint16				id();

	void				setPosterPath(const QString& szPosterPath);
	QString				posterPath();

	void				setSeasonNumber(const qint16& iSeasonNumber);
	qint16				seasonNumber();

	void				setSerie(cSerie* lpSerie);
	cSerie*				serie();

	cEpisode*			addEpisode(qint16 iNumber);
	cEpisode*			addEpisode(cEpisode* lpEpisode);
	QList<cEpisode*>	episodeList();
	cEpisode*			findEpisode(qint16 iNumber);

	qint16				episodeCount();

	void				setGroupBox(QGroupBox* lpGroupBox);
	void				setGridLayout(QGridLayout* lpGridLayout);
	void				setGrid(QGridLayout* lpGrid);
	void				setLabel1(QLabel* lpLabel1);
	void				setAllInit(QPushButton* lpAllInit);
	void				setAllProgress(QPushButton* lpAllProgress);
	void				setAllDone(QPushButton* lpAllDone);
	void				setSpacer(QSpacerItem* lpSpacer);

	void				updateState();
	void				deleteResources();

	void				allInit();
	void				allProgress();
	void				allDone();

	QPushButton*		allInitButton();
	QPushButton*		allProgressButton();
	QPushButton*		allDoneButton();
private:
	qint16				m_i_ID;
	QDate				m_airDate;
	QString				m_szName;
	QString				m_szOverview;
	qint16				m_iID;
	QString				m_szPosterPath;
	qint16				m_iSeasonNumber;
	QList<cEpisode*>	m_episodeList;
	QGroupBox*			m_lpGroupBox;
	QGridLayout*		m_lpGridLayout;
	QGridLayout*		m_lpGrid;
	QLabel*				m_lpLabel1;
	QPushButton*		m_lpAllInit;
	QPushButton*		m_lpAllProgress;
	QPushButton*		m_lpAllDone;
	QSpacerItem*		m_lpSpacer;
	cSerie*				m_lpSerie;
};

Q_DECLARE_METATYPE(cSeason*)

#endif // CSEASON_H
