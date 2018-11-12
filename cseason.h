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

/*!
 \brief

 \class cSeason cseason.h "cseason.h"
*/
class cSeason
{
public:
	cSeason();
	/*!
	 \brief

	 \fn ~cSeason
	*/
	~cSeason();

	/*!
	 \brief

	 \fn set_ID
	 \param _iID
	*/
	void				set_ID(const qint32& _iID);
	/*!
	 \brief

	 \fn _id
	 \return qint32
	*/
	qint32				_id();

	/*!
	 \brief

	 \fn setAirDate
	 \param szAirDate
	*/
	void				setAirDate(const QString& szAirDate);
	/*!
	 \brief

	 \fn setAirDate
	 \param airDate
	*/
	void				setAirDate(const QDate&   airDate);
	/*!
	 \brief

	 \fn airDate
	 \return QDate
	*/
	QDate				airDate();

	/*!
	 \brief

	 \fn setName
	 \param szName
	*/
	void				setName(const QString& szName);
	/*!
	 \brief

	 \fn name
	 \return QString
	*/
	QString				name();

	/*!
	 \brief

	 \fn setOverview
	 \param szOverview
	*/
	void				setOverview(const QString& szOverview);
	/*!
	 \brief

	 \fn overview
	 \return QString
	*/
	QString				overview();

	/*!
	 \brief

	 \fn setID
	 \param iID
	*/
	void				setID(const qint32& iID);
	/*!
	 \brief

	 \fn id
	 \return qint32
	*/
	qint32				id();

	/*!
	 \brief

	 \fn setPosterPath
	 \param szPosterPath
	*/
	void				setPosterPath(const QString& szPosterPath);
	/*!
	 \brief

	 \fn posterPath
	 \return QString
	*/
	QString				posterPath();

	/*!
	 \brief

	 \fn setSeasonNumber
	 \param iSeasonNumber
	*/
	void				setSeasonNumber(const qint32& iSeasonNumber);
	/*!
	 \brief

	 \fn seasonNumber
	 \return qint32
	*/
	qint32				seasonNumber();

	/*!
	 \brief

	 \fn setSerie
	 \param lpSerie
	*/
	void				setSerie(cSerie* lpSerie);
	/*!
	 \brief

	 \fn serie
	 \return cSerie
	*/
	cSerie*				serie();

	/*!
	 \brief

	 \fn addEpisode
	 \param iNumber
	 \return cEpisode
	*/
	cEpisode*			addEpisode(qint32 iNumber);
	/*!
	 \brief

	 \fn addEpisode
	 \param lpEpisode
	 \return cEpisode
	*/
	cEpisode*			addEpisode(cEpisode* lpEpisode);
	/*!
	 \brief

	 \fn episodeList
	 \return QList<cEpisode *>
	*/
	QList<cEpisode*>	episodeList();
	/*!
	 \brief

	 \fn findEpisode
	 \param iNumber
	 \return cEpisode
	*/
	cEpisode*			findEpisode(qint32 iNumber);

	/*!
	 \brief

	 \fn episodeCount
	 \return qint32
	*/
	qint32				episodeCount();

	/*!
	 \brief

	 \fn setGroupBox
	 \param lpGroupBox
	*/
	void				setGroupBox(QGroupBox* lpGroupBox);
	/*!
	 \brief

	 \fn setGridLayout
	 \param lpGridLayout
	*/
	void				setGridLayout(QGridLayout* lpGridLayout);
	/*!
	 \brief

	 \fn setGrid
	 \param lpGrid
	*/
	void				setGrid(QGridLayout* lpGrid);
	/*!
	 \brief

	 \fn setLabel1
	 \param lpLabel1
	*/
	void				setLabel1(QLabel* lpLabel1);
	/*!
	 \brief

	 \fn setAllInit
	 \param lpAllInit
	*/
	void				setAllInit(QPushButton* lpAllInit);
	/*!
	 \brief

	 \fn setAllProgress
	 \param lpAllProgress
	*/
	void				setAllProgress(QPushButton* lpAllProgress);
	/*!
	 \brief

	 \fn setAllDone
	 \param lpAllDone
	*/
	void				setAllDone(QPushButton* lpAllDone);
	/*!
	 \brief

	 \fn setSpacer
	 \param lpSpacer
	*/
	void				setSpacer(QSpacerItem* lpSpacer);

	/*!
	 \brief

	 \fn updateState
	*/
	void				updateState();
	/*!
	 \brief

	 \fn deleteResources
	*/
	void				deleteResources();

	/*!
	 \brief

	 \fn hasInit
	 \return bool
	*/
	bool				hasInit();
	/*!
	 \brief

	 \fn hasProgress
	 \return bool
	*/
	bool				hasProgress();
	/*!
	 \brief

	 \fn hasDone
	 \return bool
	*/
	bool				hasDone();

	/*!
	 \brief

	 \fn allInit
	*/
	void				allInit();
	/*!
	 \brief

	 \fn allProgress
	*/
	void				allProgress();
	/*!
	 \brief

	 \fn allDone
	*/
	void				allDone();

	/*!
	 \brief

	 \fn allInitButton
	 \return QPushButton
	*/
	QPushButton*		allInitButton();
	/*!
	 \brief

	 \fn allProgressButton
	 \return QPushButton
	*/
	QPushButton*		allProgressButton();
	/*!
	 \brief

	 \fn allDoneButton
	 \return QPushButton
	*/
	QPushButton*		allDoneButton();
private:
	qint32				m_i_ID; /*!< TODO: describe */
	QDate				m_airDate; /*!< TODO: describe */
	QString				m_szName; /*!< TODO: describe */
	QString				m_szOverview; /*!< TODO: describe */
	qint32				m_iID; /*!< TODO: describe */
	QString				m_szPosterPath; /*!< TODO: describe */
	qint32				m_iSeasonNumber; /*!< TODO: describe */
	QList<cEpisode*>	m_episodeList; /*!< TODO: describe */
	QGroupBox*			m_lpGroupBox; /*!< TODO: describe */
	QGridLayout*		m_lpGridLayout; /*!< TODO: describe */
	QGridLayout*		m_lpGrid; /*!< TODO: describe */
	QLabel*				m_lpLabel1; /*!< TODO: describe */
	QPushButton*		m_lpAllInit; /*!< TODO: describe */
	QPushButton*		m_lpAllProgress; /*!< TODO: describe */
	QPushButton*		m_lpAllDone; /*!< TODO: describe */
	QSpacerItem*		m_lpSpacer; /*!< TODO: describe */
	cSerie*				m_lpSerie; /*!< TODO: describe */
};

Q_DECLARE_METATYPE(cSeason*)

#endif // CSEASON_H
