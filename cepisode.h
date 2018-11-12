#ifndef CEPISODE_H
#define CEPISODE_H


#include <QMetaType>
#include <QList>
#include <QDate>

#include <QButtonGroup>
#include <QLabel>
#include <QRadioButton>


/*!
 \brief

 \class cEpisode cepisode.h "cepisode.h"
*/
class cEpisode
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

	cEpisode();
	/*!
	 \brief

	 \fn ~cEpisode
	*/
	~cEpisode();

	/*!
	 \brief

	 \fn setID
	 \param iID
	*/
	void		setID(const qint32& iID);
	/*!
	 \brief

	 \fn id
	 \return qint32
	*/
	qint32		id();

	/*!
	 \brief

	 \fn setName
	 \param szName
	*/
	void		setName(const QString& szName);
	/*!
	 \brief

	 \fn name
	 \return QString
	*/
	QString		name();

	/*!
	 \brief

	 \fn setEpisodeNumber
	 \param iEpisodeNumber
	*/
	void		setEpisodeNumber(const qint32& iEpisodeNumber);
	/*!
	 \brief

	 \fn episodeNumber
	 \return qint32
	*/
	qint32		episodeNumber();

	/*!
	 \brief

	 \fn setAirDate
	 \param szAirDate
	*/
	void		setAirDate(const QString& szAirDate);
	/*!
	 \brief

	 \fn setAirDate
	 \param airDate
	*/
	void		setAirDate(const QDate& airDate);
	/*!
	 \brief

	 \fn airDate
	 \return QDate
	*/
	QDate		airDate();

	/*!
	 \brief

	 \fn setGuestStars
	 \param szGuestStars
	*/
	void		setGuestStars(const QString& szGuestStars);
	/*!
	 \brief

	 \fn setGuestStars
	 \param szGuestStars
	*/
	void		setGuestStars(const QStringList& szGuestStars);
	/*!
	 \brief

	 \fn guestStars
	 \return QStringList
	*/
	QStringList	guestStars();

	/*!
	 \brief

	 \fn setOverview
	 \param szOverview
	*/
	void		setOverview(const QString& szOverview);
	/*!
	 \brief

	 \fn overview
	 \return QString
	*/
	QString		overview();

	/*!
	 \brief

	 \fn setProductionCode
	 \param szProductionCode
	*/
	void		setProductionCode(const QString& szProductionCode);
	/*!
	 \brief

	 \fn productionCode
	 \return QString
	*/
	QString		productionCode();

	/*!
	 \brief

	 \fn setSeasonNumber
	 \param iSeasonNumber
	*/
	void		setSeasonNumber(const qint32& iSeasonNumber);
	/*!
	 \brief

	 \fn seasonNumber
	 \return qint32
	*/
	qint32		seasonNumber();

	/*!
	 \brief

	 \fn setSeasonID
	 \param iSeasonID
	*/
	void		setSeasonID(const qint32& iSeasonID);
	/*!
	 \brief

	 \fn seasonID
	 \return qint32
	*/
	qint32		seasonID();

	/*!
	 \brief

	 \fn setSeriesID
	 \param iSeriesID
	*/
	void		setSeriesID(const qint32& iSeriesID);
	/*!
	 \brief

	 \fn seriesID
	 \return qint32
	*/
	qint32		seriesID();

	/*!
	 \brief

	 \fn setStillPath
	 \param szStillPath
	*/
	void		setStillPath(const QString& szStillPath);
	/*!
	 \brief

	 \fn stillPath
	 \return QString
	*/
	QString		stillPath();

	/*!
	 \brief

	 \fn setVoteAverage
	 \param dVoteAverage
	*/
	void		setVoteAverage(const qreal& dVoteAverage);
	/*!
	 \brief

	 \fn voteAverage
	 \return qreal
	*/
	qreal		voteAverage();

	/*!
	 \brief

	 \fn setVoteCount
	 \param iVoteCount
	*/
	void		setVoteCount(const qint32& iVoteCount);
	/*!
	 \brief

	 \fn voteCount
	 \return qint32
	*/
	qint32		voteCount();

	/*!
	 \brief

	 \fn setCrew
	 \param szCrew
	*/
	void		setCrew(const QString& szCrew);
	/*!
	 \brief

	 \fn setCrew
	 \param szCrew
	*/
	void		setCrew(const QStringList& szCrew);
	/*!
	 \brief

	 \fn crew
	 \return QStringList
	*/
	QStringList	crew();

	/*!
	 \brief

	 \fn setState
	 \param state
	*/
	void		setState(const State& state);
	/*!
	 \brief

	 \fn state
	 \return State
	*/
	State		state();

	/*!
	 \brief

	 \fn setFileName
	 \param szFileName
	*/
	void		setFileName(const QString& szFileName);
	/*!
	 \brief

	 \fn fileName
	 \return QString
	*/
	QString		fileName();

	/*!
	 \brief

	 \fn setThumbHeight
	 \param iThumbHeight
	*/
	void		setThumbHeight(const qint32& iThumbHeight);
	/*!
	 \brief

	 \fn thumbHeight
	 \return qint32
	*/
	qint32		thumbHeight();

	/*!
	 \brief

	 \fn setThumbWidth
	 \param iThumbWidth
	*/
	void		setThumbWidth(const qint32& iThumbWidth);
	/*!
	 \brief

	 \fn thumbWidth
	 \return qint32
	*/
	qint32		thumbWidth();

	/*!
	 \brief

	 \fn isValid
	 \return bool
	*/
	bool		isValid();

	/*!
	 \brief

	 \fn setGroup
	 \param lpGroup
	*/
	void		setGroup(QButtonGroup* lpGroup);
	/*!
	 \brief

	 \fn setLabel
	 \param lpLabel
	*/
	void		setLabel(QLabel* lpLabel);
	/*!
	 \brief

	 \fn setButton1
	 \param lpButton1
	*/
	void		setButton1(QRadioButton* lpButton1);
	/*!
	 \brief

	 \fn setButton2
	 \param lpButton2
	*/
	void		setButton2(QRadioButton* lpButton2);
	/*!
	 \brief

	 \fn setButton3
	 \param lpButton3
	*/
	void		setButton3(QRadioButton* lpButton3);

	/*!
	 \brief

	 \fn updateState
	*/
	void		updateState();
	/*!
	 \brief

	 \fn deleteResources
	*/
	void		deleteResources();
private:
	qint32			m_iID; /*!< TODO: describe */
	QString			m_szName; /*!< TODO: describe */
	qint32			m_iEpisodeNumber; /*!< TODO: describe */
	QDate			m_airDate; /*!< TODO: describe */
	QStringList		m_szGuestStars; /*!< TODO: describe */
	QString			m_szOverview; /*!< TODO: describe */
	QString			m_szProductionCode; /*!< TODO: describe */
	qint32			m_iSeasonNumber; /*!< TODO: describe */
	qint32			m_iSeasonID; /*!< TODO: describe */
	qint32			m_iSeriesID; /*!< TODO: describe */
	QString			m_szStillPath; /*!< TODO: describe */
	qreal			m_dVoteAverage; /*!< TODO: describe */
	qint32			m_iVoteCount; /*!< TODO: describe */
	QStringList		m_szCrew; /*!< TODO: describe */
	State			m_state; /*!< TODO: describe */
	QButtonGroup*	m_lpGroup; /*!< TODO: describe */
	QLabel*			m_lpLabel; /*!< TODO: describe */
	QRadioButton*	m_lpButton1; /*!< TODO: describe */
	QRadioButton*	m_lpButton2; /*!< TODO: describe */
	QRadioButton*	m_lpButton3; /*!< TODO: describe */
};

Q_DECLARE_METATYPE(cEpisode*)
Q_DECLARE_METATYPE(cEpisode::State)

#endif // CEPISODE_H
